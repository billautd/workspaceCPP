#include "Game.h"
#include "ResourceManager.h"
#include "Utils.h"
#include <iostream>

Game::Game()
{
}

Game::~Game()
{
	delete spriteRenderer;
	glfwTerminate();
}

const int Game::InitGL() {
	//Init GLFW
	int success{ 0 };
	if (!(success = glfwInit())) {
		std::cerr << "ERROR::GLFW : Failed to initialize GLFW" << std::endl;
		return success;
	}
	//Using OpenGL 4.3.0
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

	glfwWindowHint(GLFW_RESIZABLE, false);

	window = glfwCreateWindow(width, height, "Arkanoid", nullptr, nullptr);
	glfwMakeContextCurrent(window);

	//Init GLAD
	if (!(success = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)))
	{
		std::cout << "ERROR::GLAD : Failed to initialize GLAD" << std::endl;
		return success;
	}

	//Init OpenGL
	glViewport(0, 0, width, height);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	return success;
}

void Game::Init() {
	//Shaders
	Shader& spriteShader{ ResourceManager::LoadShader("sprite", "./Shaders/Vertex/vertexSprite.shader", "./Shaders/Fragment/fragmentSprite.shader") };
	Shader& particleShader{ ResourceManager::LoadShader("particle", "./Shaders/Vertex/vertexParticle.shader", "./Shaders/Fragment/fragmentParticle.shader") };
	Shader& postProcessingShader{ ResourceManager::LoadShader("postProcessing",
		"./Shaders/Vertex/vertexPostProcessing.shader", "./Shaders/Fragment/fragmentPostProcessing.shader") };
	glm::mat4 projection{ glm::ortho(0.0f, static_cast<GLfloat>(width), static_cast<GLfloat>(height), 0.0f, -1.0f, 1.0f) };
	spriteShader.Use();
	spriteShader.SetInteger("sprite", 0);
	spriteShader.SetMatrix4("projection", projection);

	particleShader.Use();
	particleShader.SetInteger("sprite", 0);
	particleShader.SetMatrix4("projection", projection);

	postProcessingShader.Use();
	postProcessingShader.SetInteger("scene", 0);
	//Set offsets
	glUniform2fv(glGetUniformLocation(postProcessingShader.id, "offsets"), 9, (GLfloat*)OFFSETS);
	//Set edge kernel
	glUniform1iv(glGetUniformLocation(postProcessingShader.id, "edgeKernel"), 9, (GLint*)EDGE_KERNEL);
	//Set blur kernel
	glUniform1fv(glGetUniformLocation(postProcessingShader.id, "blurKernel"), 9, (GLfloat*)BLUR_KERNEL);

	//Textures
	spriteRenderer = new SpriteRenderer(spriteShader);
	ResourceManager::LoadTexture2D("ball", "./Assets/face.png", true);
	ResourceManager::LoadTexture2D("block", "./Assets/block.png", false);
	ResourceManager::LoadTexture2D("background", "./Assets/background.jpg", false);
	ResourceManager::LoadTexture2D("blockSolid", "./Assets/blockSolid.png", false);
	ResourceManager::LoadTexture2D("paddle", "./Assets/paddle.png", true);
	//Powerups
	ResourceManager::LoadTexture2D("chaos", "./Assets/powerupChaos.png", true);
	ResourceManager::LoadTexture2D("confuse", "./Assets/powerupConfuse.png", true);
	ResourceManager::LoadTexture2D("increase", "./Assets/powerupIncrease.png", true);
	ResourceManager::LoadTexture2D("passthrough", "./Assets/powerupPassthrough.png", true);
	ResourceManager::LoadTexture2D("speed", "./Assets/powerupSpeed.png", true);
	ResourceManager::LoadTexture2D("sticky", "./Assets/powerupSticky.png", true);

	const Texture2D& particleTexture{ ResourceManager::LoadTexture2D("particle", "./Assets/particle.png", true) };

	particleRenderer = new ParticleRenderer(particleShader, particleTexture);

	postProcessor = new PostProcessor(postProcessingShader, width, height);

	//Levels
	GameLevel one; one.Load("./Levels/one.lvl", width, height / 2);
	GameLevel two; two.Load("./Levels/two.lvl", width, height / 2);
	GameLevel three; three.Load("./Levels/three.lvl", width, height / 2);
	GameLevel four; four.Load("./Levels/four.lvl", width, height / 2);
	levels.emplace_back(one);
	levels.emplace_back(two);
	levels.emplace_back(three);
	levels.emplace_back(four);

	//Player
	player = new Player();

	//Ball
	ball = new Ball();
}

void Game::ProcessInput(const GLfloat dt) {
	if (state == GAME_ACTIVE) {
		GLfloat velocity{ PLAYER_VELOCITY * dt };
		//Move player
		if (keys[GLFW_KEY_LEFT]) {
			if (player->position.x >= 0.0f) {
				player->position.x -= velocity;
				if (ball->isStuck)
					ball->position.x -= velocity;
			}
		}
		if (keys[GLFW_KEY_RIGHT]) {
			if (player->position.x + player->size.x <= width) {
				player->position.x += velocity;
				if (ball->isStuck)
					ball->position.x += velocity;
			}
		}

		if (keys[GLFW_KEY_SPACE]) {
			ball->isStuck = false;
		}

	}
}

GLfloat shakeTime{ 0.0f };
void Game::Update(const GLfloat dt) {
	//Ball
	ball->Move(dt, width);

	//Collisions
	DoCollisions();

	//Powerups
	UpdatePowerUps(dt);

	//Particles
	particleRenderer->Update(dt, *ball, 2, glm::vec2(ball->radius / 2.0f));

	//Effects
	if (shakeTime > 0.0f) {
		shakeTime -= dt;
		if (shakeTime <= 0.0f)
			postProcessor->shake = false;
	}

	//On ball touch bottom
	if (ball->position.y >= height) {
		ResetLevel();
		ResetPlayer();
	}
}

void Game::Render() {
	if (state == GAME_ACTIVE) {
		postProcessor->BeginRender();
		{
			//Draw background
			spriteRenderer->DrawSprite(ResourceManager::GetTexture2D("background"), glm::vec2(0.0f), glm::vec2(width, height));
			//Draw level
			levels[currentLevel].Draw(*spriteRenderer);
			//Draw player
			player->Draw(*spriteRenderer);
			//Draw particles
			particleRenderer->Draw();
			//Draw Ball
			ball->Draw(*spriteRenderer);
		}
		postProcessor->EndRender();
		postProcessor->Render(static_cast<GLfloat>(glfwGetTime()));

		//Draw powerup
		for (auto& powerUp : powerUps) {
			if (!powerUp.isDestroyed)
				powerUp.Draw(*spriteRenderer);
		}
	}
}

void Game::DoCollisions(){
	//Ball/Brick collisions
	for (auto& brick : levels[currentLevel].bricks) {
		if (!brick.isDestroyed) {
			Collision collision{ CheckCollision(*ball, brick) };
			if (std::get<0>(collision)) {
				//Shake screen
				if (!brick.isSolid) {
					brick.isDestroyed = true;
					SpawnPowerUps(brick);
					//If ball passthrough, no collision resolution
					if(ball->isPassthrough)
						return;
				}
				else if (brick.isSolid) {
					shakeTime = 0.05f;
					postProcessor->shake = true;
				}

				//Collision resolution
				Direction dir{ std::get<1>(collision) };
				glm::vec2 diffVector{ std::get<2>(collision) };

				if (dir == LEFT || dir == RIGHT) {
					ball->velocity.x *= -1.0f;
					//Rellocate
					GLfloat penetration = ball->radius - std::abs(diffVector.x);
					if (dir == LEFT)
						ball->position.x += penetration; // Move ball to right
					else
						ball->position.x -= penetration; //Move ball to left
				}
				else {
					ball->velocity.y *= -1.0f;
					//Rellocate
					GLfloat penetration = ball->radius - std::abs(diffVector.y);
					if (dir == UP)
						ball->position.y -= penetration; // Move ball up
					else
						ball->position.y += penetration; //Move ball down
				}
			}
		}
	}
	//Collision ball player
	Collision result{ CheckCollision(*ball, *player) };
	if (!ball->isStuck && std::get<0>(result)) {
		//Check where it hit the board
		GLfloat centerBoard{ player->position.x + player->size.x / 2.0f };
		GLfloat distance{ ball->position.x + ball->radius - centerBoard };
		GLfloat percentage{ distance / (player->size.x / 2.0f) };
		//Then move accordingly
		GLfloat strength{ 5.0f };
		glm::vec2 oldVelocity{ ball->velocity };
		ball->velocity.x = INITIAL_BALL_VELOCITY.x * percentage * strength;
		ball->velocity.y = -1.0f * abs(ball->velocity.y);
		ball->velocity = glm::normalize(ball->velocity) * glm::length(oldVelocity);
		//If sticky, stick to player
		ball->isStuck = ball->isSticky;
	}
	//Powerups
	for (auto& powerUp : powerUps) {
		if (!powerUp.isDestroyed) {
			if (powerUp.position.y >= height)
				powerUp.isDestroyed = true;
			//Collided with player, activate powerup
			if (CheckCollision(*player, powerUp)) {
				powerUp.isActivated = true;
				powerUp.isDestroyed = true;
				ActivatePowerUp(powerUp);
			}
		}
	}

}

bool Game::CheckCollision(const GameObject& obj1, const GameObject& obj2)
{
	// collision x-axis?
	bool collisionX = obj1.position.x + obj1.size.x >= obj2.position.x && obj2.position.x + obj2.size.x >= obj1.position.x;
	// collision y-axis?
	bool collisionY = obj1.position.y + obj1.size.y >= obj2.position.y && obj2.position.y + obj2.size.y >= obj1.position.y;
	// collision only if on both axes
	return collisionX && collisionY;
}

Collision Game::CheckCollision(const Ball& ball, const GameObject& obj2)
{
	//Get center point circle first
	glm::vec2 center{ ball.position + ball.radius};
	//Calculate AABB info (center, half-extents)
	glm::vec2 aabbHalfExtents{ obj2.size / 2.0f };
	glm::vec2 aabbCenter{ obj2.position + aabbHalfExtents };

	//Get difference vector between both centers
	glm::vec2 difference{ center - aabbCenter };
	glm::vec2 clamped = glm::clamp(difference, -aabbHalfExtents, aabbHalfExtents);
	//Add clamped value to AABB center and we get the value of box closest to circle
	glm::vec2 closest{ aabbCenter + clamped };
	//Retrieve vector between center circle and closest point AABB and check if length <= radius
	difference = closest - center;

	if (glm::length(difference) <= ball.radius)
		return std::make_tuple(true, Utils::VectorDirection(difference), difference);
	else
		return std::make_tuple(false, UP, glm::vec2(0.0f));
}

void Game::ResetPlayer()
{
	player->Reset();
	ball->Reset();

	//Deactivate all effects
	postProcessor->chaos = false;
	postProcessor->confuse = false;
}

void Game::ResetLevel()
{
	if (currentLevel == 0)
		levels[0].Load("levels/one.lvl", width, height / 2);
	else if (currentLevel == 1)
		levels[0].Load("levels/two.lvl", width, height / 2);
	else if (currentLevel == 2)
		levels[0].Load("levels/three.lvl", width, height / 2);
	else if (currentLevel == 3)
		levels[0].Load("levels/four.lvl", width, height / 2);

	powerUps.clear();
}

bool Game::ShouldSpawn(const GLuint chance) {
	GLuint random{ rand() % chance };
	return random == 0;
}

void Game::SpawnPowerUps(const GameObject& block)
{
	//1 in 75
	if (ShouldSpawn(75))
		powerUps.emplace_back(PowerUp("speed", glm::vec3(0.5f, 0.5f, 1.0f), 0.0f, block.position, ResourceManager::GetTexture2D("speed")));
	if (ShouldSpawn(75))
		powerUps.emplace_back(PowerUp("sticky", glm::vec3(1.0f, 0.5f, 1.0f), 20.0f, block.position, ResourceManager::GetTexture2D("sticky")));
	if (ShouldSpawn(75))
		powerUps.emplace_back(PowerUp("passthrough", glm::vec3(0.5f, 1.0f, 0.5f), 10.0f, block.position, ResourceManager::GetTexture2D("passthrough")));
	if (ShouldSpawn(75))
		powerUps.emplace_back(PowerUp("increase", glm::vec3(1.0f, 0.6f, 0.4f), 0.0f, block.position, ResourceManager::GetTexture2D("increase")));
	if (ShouldSpawn(15))
		powerUps.emplace_back(PowerUp("confuse", glm::vec3(1.0f, 0.3f, 0.3f), 15.0f, block.position, ResourceManager::GetTexture2D("confuse")));
	if (ShouldSpawn(15))
		powerUps.emplace_back(PowerUp("chaos", glm::vec3(0.9f, 0.25f, 0.25f), 15.0f, block.position, ResourceManager::GetTexture2D("chaos")));

}

void Game::ActivatePowerUp(const PowerUp& powerUp)
{
	const std::string type{ powerUp.type };
	if (type == "speed")
		ball->velocity *= 1.2f;
	else if (type == "sticky") {
		ball->isSticky = true;
		player->color = glm::vec3(1.0f, 0.5f, 1.0f);
	}
	else if (type == "passthrough") {
		ball->isPassthrough = true;
		ball->color = glm::vec3(1.0f, 0.5f, 0.5f);
	}
	else if (type == "increase") {
		if (player->size.x + 50.0f >= MAX_PLAYER_SIZE)
			player->size.x = MAX_PLAYER_SIZE;
		else
			player->size.x += 50.0f;
	}
	else if (type == "chaos") {
		//only activate if not confuse
		if (!postProcessor->confuse)
			postProcessor->chaos = true; 
	}
	else if (type == "confuse") {
		//Only activate if not chaos
		if (!postProcessor->chaos) {
			postProcessor->confuse = true;
		}
	}
}

bool Game::IsOtherPowerUpActive(const std::string type) {
	for (const auto& powerUp : powerUps) {
		if (powerUp.isActivated && powerUp.type == type)
			return true;
	}
	return false;
}

void Game::UpdatePowerUps(const GLfloat dt)
{
	for (auto& powerUp : powerUps) {
		powerUp.position += powerUp.velocity * dt;
		if (powerUp.isActivated) {
			powerUp.duration -= dt;
			if (powerUp.duration <= 0.0f) {
				powerUp.isActivated = false;
				//Deactivate effects
				const std::string type{ powerUp.type };
				if (type == "sticky") {
					ball->isSticky = false;
					player->color = glm::vec3(1.0f);
				}
				else if (type == "passthrough") {
					ball->isPassthrough = false;
					ball->color = glm::vec3(1.0f);
				}
				else if (type == "confuse") {
					if (!IsOtherPowerUpActive("confuse"))
						postProcessor->confuse = false;
				}
				else if (type == "chaos") {
					if (!IsOtherPowerUpActive("chaos"))
						postProcessor->chaos = false;
				}
			}
		}
	}
	powerUps.erase(std::remove_if(powerUps.begin(), powerUps.end(), 
		[](const PowerUp& powerUp) {return powerUp.isDestroyed && !powerUp.isActivated; }),
		powerUps.end());
}
