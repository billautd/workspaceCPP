#include "Game.h"
#include "SpriteRenderer.h"
#include "ResourceManager.h"
#include "BallObject.h"

Game::Game(GLuint width, GLuint height) {}

Game::~Game() {
	delete renderer;
	delete player;
	delete ball;
}

int Game::BackEndInit() {
	//SDL init
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
		std::cerr << "Error initializing SDL.\n";
		SDL_Quit();
		return 1;
	}

	//SDL_mixer init
	if (Mix_OpenAudio(22050, MIX_DEFAULT_FORMAT, 2, 4096) != 0) {
		std::cerr << "Error initializing SDL audio.\n";
		SDL_Quit();
		return 1;
	}

	//Set backup OpenGl version to 3.3
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);

	//Set OpenGL profile to Core
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

	//Window init
	this->window = SDL_CreateWindow(
		"Arkanoid",
		SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED,
		width,
		height,
		SDL_WINDOW_RESIZABLE | SDL_WINDOW_OPENGL
	);

	if (!this->window) {
		std::cerr << "Error initializing SDL window.\n";
		SDL_Quit();
		return 1;
	}

	//Create OpenGL Context
	void* mainContext{ SDL_GL_CreateContext(this->window) };
	if (mainContext == nullptr) {
		std::cerr << "Error initializing OpenGL context.\n";
		SDL_Quit();
		return 1;
	}
	SDL_GL_MakeCurrent(this->window, mainContext);

	//Disable cursor
	SDL_ShowCursor(SDL_DISABLE);

	//Init GLAD
	if (!gladLoadGLLoader(SDL_GL_GetProcAddress)) {
		std::cerr << "Error initializing GLAD.\n";
		SDL_Quit();
		return 1;
	}

	//Viewport
	glViewport(0, 0, width, height);

	//Enable blend
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	this->state = GameStateEnum::GAME_ACTIVE;

	return 0;
}

int Game::Init() {
	int success{ BackEndInit() };
	if (success != 0)
		return success;

	//Load shaders
	ResourceManager::LoadShader("./Shaders/SpriteRendering.vert", "./Shaders/SpriteRendering.frag", nullptr, "SpriteRendering");
	ResourceManager::LoadShader("./Shaders/ParticleRendering.vert", "./Shaders/ParticleRendering.frag", nullptr, "ParticleRendering");
	ResourceManager::LoadShader("./Shaders/PostProcessing.vert", "./Shaders/PostProcessing.frag", nullptr, "PostProcessing");
	//Config shaders
	glm::mat4 projection{ glm::ortho(0.0f, static_cast<GLfloat>(this->width), static_cast<GLfloat>(this->height), 0.0f, -10.0f, 1.0f) };
	ResourceManager::GetShader("SpriteRendering").Use().SetInteger("sprite", 0);
	ResourceManager::GetShader("SpriteRendering").Use().SetMatrix4("projection", projection);
	ResourceManager::GetShader("ParticleRendering").Use().SetInteger("sprite", 0);
	ResourceManager::GetShader("ParticleRendering").Use().SetMatrix4("projection", projection);

	//Load textures
	ResourceManager::LoadTexture("./Textures/solidTile.png", false, "solidTile");
	ResourceManager::LoadTexture("./Textures/nonSolidTile.png", false, "nonSolidTile");
	ResourceManager::LoadTexture("./Textures/background.jpg", false, "background");
	ResourceManager::LoadTexture("./Textures/paddle.png", true, "paddle");
	ResourceManager::LoadTexture("./Textures/awesomeface.png", true, "ball");
	ResourceManager::LoadTexture("./Textures/particle.png", true, "particle");
	ResourceManager::LoadTexture("./Textures/PowerUps/chaos.png", true, "powerup_chaos");
	ResourceManager::LoadTexture("./Textures/PowerUps/confuse.png", true, "powerup_confuse");
	ResourceManager::LoadTexture("./Textures/PowerUps/pad_size_increase.png", true, "powerup_pad_size_increase");
	ResourceManager::LoadTexture("./Textures/PowerUps/passthrough.png", true, "powerup_passthrough");
	ResourceManager::LoadTexture("./Textures/PowerUps/speed.png", true, "powerup_speed");
	ResourceManager::LoadTexture("./Textures/PowerUps/sticky.png", true, "powerup_sticky");

	//Load music
	ResourceManager::LoadMusic("C://Users//David//workspaceC++//Projects//Arkanoid//Arkanoid//Musics//breakout.mp3", "breakout");

	//Init renderer
	renderer = new SpriteRenderer(ResourceManager::GetShader("SpriteRendering"));
	particleGenerator = new ParticleGenerator(ResourceManager::GetShader("ParticleRendering"), ResourceManager::GetTexture("particle"), 500);
	postProcessor = new PostProcessor(ResourceManager::GetShader("PostProcessing"), this->width, this->height);
	musicManager = new MusicManager();

	//Load levels
	GameLevel level1; level1.Load("./Levels/one.lvl", this->width, this->height / 2);
	GameLevel level2; level2.Load("./Levels/two.lvl", this->width, this->height / 2);
	GameLevel level3; level3.Load("./Levels/three.lvl", this->width, this->height / 2);
	GameLevel level4; level4.Load("./Levels/four.lvl", this->width, this->height / 2);
	this->levels.emplace_back(level1);
	this->levels.emplace_back(level2);
	this->levels.emplace_back(level3);
	this->levels.emplace_back(level4);


	//Setup player
	glm::vec2 playerPosition(this->width / 2.0f - PLAYER_SIZE.x / 2.0f, this->height - PLAYER_SIZE.y);
	player = new GameObject(playerPosition, PLAYER_SIZE, ResourceManager::GetTexture("paddle"));

	//Setup ball
	glm::vec2 ballPosition(this->width / 2.0f - BALL_RADIUS, this->height - PLAYER_SIZE.y - 2 * BALL_RADIUS);
	ball = new BallObject(ballPosition, BALL_RADIUS, INITIAL_BALL_VELOCITY, ResourceManager::GetTexture("ball"));

	//Play music
	musicManager->PlayMusic("breakout", true);

	return 0;
}

void Game::ProcessInput(SDL_Event& e, GLfloat dt) {
	if (e.type == SDL_WINDOWEVENT) {
		switch (e.window.event) {
			case SDL_WINDOWEVENT_SIZE_CHANGED:
				glViewport(0, 0, e.window.data1, e.window.data2);
				break;
		}
	}

	if (e.type == SDL_QUIT) {
		this->state = GameStateEnum::GAME_INACTIVE;
		SDL_Quit();
		return;
	}

	keys = SDL_GetKeyboardState(&keysNbr);

	if (this->state == GameStateEnum::GAME_ACTIVE) {
		GLfloat velocity{ PLAYER_VELOCITY * dt };

		//Left
		if (keys[SDL_SCANCODE_LEFT]) {
			if (player->GetPosition().x > 0.0f) {
				player->SetPositionX(player->GetPosition().x - velocity);
				if (ball->IsStuck())
					ball->SetPositionX(ball->GetPosition().x - velocity);
			}
		}
		//Right
		if (keys[SDL_SCANCODE_RIGHT]) {
			if (player->GetPosition().x + PLAYER_SIZE.x < this->width) {
				player->SetPositionX(player->GetPosition().x + velocity);
				if (ball->IsStuck())
					ball->SetPositionX(ball->GetPosition().x + velocity);
			}
		}
		//Space to set ball free
		if (keys[SDL_SCANCODE_SPACE])
			ball->SetStuck(false);
	}

}

GLfloat shakeTime{ 0.0f };
void Game::Update(GLfloat dt) {
	//Update objects
	ball->Move(dt, this->width);
	//Update particles
	particleGenerator->Update(dt, *ball, glm::vec2(ball->GetRadius() / 2.0f), 2);
	//Update powerups
	this->UpdatePowerUps(dt);
	//Collisions
	this->DoCollisions();
	//Update post processing effects
	if (shakeTime > 0.0f) {
		shakeTime -= dt;
		if (shakeTime <= 0.0f)
			postProcessor->SetShake(false);
	}

	if (ball->GetPosition().y >= this->height) {
		this->ResetBallPlayer();
		this->ResetPowerUps();
	}

	if (this->levels.at(this->level).IsCompleted()) {
		this->level = (this->level++) % this->levels.size();
		this->ResetBallPlayer();
		this->ResetPowerUps();
	}
}

void Game::Render() {
	if (this->state == GameStateEnum::GAME_ACTIVE) {
		postProcessor->BeginRender();
		//Draw BG
		renderer->DrawSprite(ResourceManager::GetTexture("background"), glm::vec2(0.0f, 0.0f), glm::vec2(this->width, this->height));
		//Draw Level
		this->levels.at(this->level).Draw(*renderer);
		//Draw player
		player->Draw(*renderer);
		//Draw ball
		ball->Draw(*renderer);
		//Draw particles
		if (!ball->IsStuck())
			particleGenerator->Render();
		//Draw power ups
		for (size_t i = 0; i < powerUps.size(); i++) {
			PowerUp& powerUp{ this->powerUps.at(i) };
			if (!powerUp.IsDestroyed())
				powerUp.Draw(*renderer);
		}
		//Post processing
		postProcessor->EndRender();
		postProcessor->Render(SDL_GetTicks() / 1000.0f);
	}
}

void Game::DoCollisions() {
	for (size_t i{ 0 }; i < this->levels.at(this->level).GetBricks().size(); i++) {
		GameObject& obj{ this->levels.at(this->level).GetBricks().at(i) };
		if (!obj.IsDestroyed()) {
			BallTileCollision(obj);
		}
	}
	BallPlayerCollision();

	for (size_t i = 0; i < powerUps.size(); i++) {
		PowerUp& powerUp{ powerUps.at(i) };
		PowerUpPlayerCollision(powerUp);
	}
}

void Game::ResetBallPlayer() {
	player->SetPositionX(this->width / 2.0f - player->GetSize().x / 2.0f);
	glm::vec2 ballPosition(this->width / 2.0f - BALL_RADIUS, this->height - PLAYER_SIZE.y - 2 * BALL_RADIUS);
	ball->Reset(ballPosition, ball->GetVelocity());
}

bool Game::ShouldSpawn(GLuint chance) {
	GLuint random{ rand() % chance };
	return random == 0;
}

void Game::ActivatePowerUp(PowerUp& powerUp) {
	if (powerUp.GetType() == "speed")
		ball->SetVelocity(ball->GetVelocity() * SPEED_INCREMENT);

	else if (powerUp.GetType() == "sticky") {
		ball->SetSticky(true);
		player->SetColor(1.0f, 0.5f, 1.0f);
	}

	else if (powerUp.GetType() == "passthrough") {
		ball->SetPassthrough(true);
		ball->SetColor(1.0f, 0.5f, 0.5f);
	}

	else if (powerUp.GetType() == "pad_size_increase") {
		player->SetPositionX(player->GetPosition().x - SIZE_INCREMENT / 2);
		player->SetSizeX(player->GetSize().x + SIZE_INCREMENT);
	}

	else if (powerUp.GetType() == "chaos") {
		if (!postProcessor->GetConfuse())
			postProcessor->SetChaos(true);
	}
	else if (powerUp.GetType() == "confuse") {
		if (!postProcessor->GetChaos())
			postProcessor->SetConfuse(true);
	}
}

bool Game::IsOtherPowerUpActive(std::string type) {
	for (size_t i = 0; i < powerUps.size(); i++) {
		PowerUp& powerUp{ this->powerUps.at(i) };
		if (powerUp.IsActivated())
			if (powerUp.GetType() == type)
				return true;
	}
	return false;
}

void Game::ResetPowerUps() {
	ball->SetVelocity(INITIAL_BALL_VELOCITY);
	ball->SetColor(glm::vec3(1.0f));
	ball->SetPassthrough(false);
	ball->SetSticky(false);
	player->SetSize(PLAYER_SIZE);
	player->SetColor(glm::vec3(1.0f));
	postProcessor->SetChaos(false);
	postProcessor->SetConfuse(false);
	postProcessor->SetShake(false);
	this->powerUps.clear();
}

void Game::SpawnPowerUp(GameObject& block) {
	if (ShouldSpawn(75)) {
		this->powerUps.emplace_back(PowerUp("speed", glm::vec3(0.5f, 0.5f, 1.0f), 0.0f, block.GetPosition(), ResourceManager::GetTexture("powerup_speed")));
		return;
	}
	if (ShouldSpawn(75)) {
		this->powerUps.emplace_back(PowerUp("sticky", glm::vec3(1.0f, 0.5f, 1.0f), 20.0f, block.GetPosition(), ResourceManager::GetTexture("powerup_sticky")));
		return;
	}
	if (ShouldSpawn(75)) {
		this->powerUps.emplace_back(PowerUp("passthrough", glm::vec3(0.5f, 1.0f, 0.5f), 10.0f, block.GetPosition(), ResourceManager::GetTexture("powerup_passthrough")));
		return;
	}
	if (ShouldSpawn(75)) {
		this->powerUps.emplace_back(PowerUp("pad_size_increase", glm::vec3(1.0f, 0.6f, 0.4f), 0.0f, block.GetPosition(), ResourceManager::GetTexture("powerup_pad_size_increase")));
		return;
	}
	if (ShouldSpawn(75)) {
		this->powerUps.emplace_back(PowerUp("chaos", glm::vec3(1.0f, 0.3f, 0.3f), 15.0f, block.GetPosition(), ResourceManager::GetTexture("powerup_chaos")));
		return;
	}
	if (ShouldSpawn(75)) {
		this->powerUps.emplace_back(PowerUp("confuse", glm::vec3(0.9f, 0.25f, 0.25f), 15.0f, block.GetPosition(), ResourceManager::GetTexture("powerup_confuse")));
		return;
	}
}

void Game::UpdatePowerUps(GLfloat dt) {
	for (size_t i = 0; i < powerUps.size(); i++) {
		PowerUp& powerUp{ powerUps.at(i) };
		powerUp.SetPosition(powerUp.GetPosition() + POWERUP_VELOCITY);
		if (powerUp.IsActivated()) {
			powerUp.SetDuration(powerUp.GetDuration() - dt);
			if (powerUp.GetDuration() <= 0.0f) {
				powerUp.SetActivated(false);

				//Remove effect
				if (powerUp.GetType() == "sticky") {
					if (!IsOtherPowerUpActive("sticky")) {
						ball->SetSticky(false);
						player->SetColor(glm::vec3(1.0f));
					}
				}
				else if (powerUp.GetType() == "passthrough") {
					if (!IsOtherPowerUpActive("passthrough")) {
						ball->SetPassthrough(false);
						ball->SetColor(glm::vec3(1.0f));
					}
				}
				else if (powerUp.GetType() == "chaos") {
					if (!IsOtherPowerUpActive("chaos"))
						postProcessor->SetChaos(false);
				}
				else if (powerUp.GetType() == "confuse") {
					if (!IsOtherPowerUpActive("confuse"))
						postProcessor->SetConfuse(false);
				}
			}
		}
	}
	//Remove powerups that aren't activated and that are destroyed in the model
	this->powerUps.erase(std::remove_if(this->powerUps.begin(), this->powerUps.end(), [](PowerUp& pu) {return pu.IsDestroyed() && !pu.IsActivated(); }), this->powerUps.end());
}

void Game::BallTileCollision(GameObject& obj) {
	//Ball-tile collision
	Collision collision{ ball->CheckCollision(obj) };
	//If collision
	if (std::get<0>(collision)) {
		//If not solid, destroy
		if (!obj.IsSolid()) {
			obj.SetDestroyed(true);
			this->SpawnPowerUp(obj);
		}
		else {
			shakeTime = SHAKE_TIME;
			postProcessor->SetShake(true);
		}

		//If passthrough, we don't check collision with non solid tiles
		if (ball->IsPassthrough() && !obj.IsSolid())
			return;

		//Collision resolution
		DirectionEnum dir{ std::get<1>(collision) };
		glm::vec2 difference{ std::get<2>(collision) };

		//Horizontal
		if (dir == DirectionEnum::LEFT || dir == DirectionEnum::RIGHT) {
			//Reverse horizontal velocity
			ball->SetVelocityX(-ball->GetVelocity().x);

			//Reloate
			GLfloat penetration{ ball->GetRadius() - std::abs(difference.x) };
			if (dir == DirectionEnum::LEFT)
				ball->SetPositionX(ball->GetPosition().x + penetration);
			else
				ball->SetPositionX(ball->GetPosition().x - penetration);
		}
		//Vertical
		else {
			//Reverse vertical velocity
			ball->SetVelocityY(-ball->GetVelocity().y);

			//Reloate
			GLfloat penetration{ ball->GetRadius() - std::abs(difference.y) };
			if (dir == DirectionEnum::UP)
				ball->SetPositionY(ball->GetPosition().y + penetration);
			else
				ball->SetPositionY(ball->GetPosition().y - penetration);
		}
	}
}

void Game::BallPlayerCollision() {
	Collision collision{ ball->CheckCollision(*player) };
	//If collision
	if (!ball->IsStuck() && std::get<0>(collision)) {
		if (ball->IsSticky())
			ball->SetStuck(true);

		//Check if hit the board and change velocity based on where it hits the paddle
		GLfloat centerBoard{ player->GetPosition().x + player->GetSize().x / 2.0f };
		GLfloat distance{ ball->GetPosition().x + ball->GetRadius() - centerBoard };
		GLfloat percentage{ distance / player->GetSize().x / 2.0f };

		//Move accordingly
		GLfloat strength{ 18.0f };
		glm::vec2 oldVelocity{ ball->GetVelocity() };
		GLfloat xVel{ INITIAL_BALL_VELOCITY.x * percentage * strength };
		GLfloat yVel{ -1.0f * glm::abs(ball->GetVelocity().y) };
		ball->SetVelocity(glm::length(oldVelocity) * glm::normalize(glm::vec2(xVel, yVel)));
	}
}

void Game::PowerUpPlayerCollision(PowerUp& powerUp) {
	Collision collision{ powerUp.CheckCollision(*player) };
	if (!powerUp.IsDestroyed()) {
		if (powerUp.GetPosition().y >= this->height)
			powerUp.SetDestroyed(true);
		if (std::get<0>(collision)) {
			//Collision with player, activate powerup
			ActivatePowerUp(powerUp);
			powerUp.SetDestroyed(true);
			powerUp.SetActivated(true);
		}
	}
}

