#include "Game.h"
#include "ResourceManager.h"
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
	Shader& spriteShader{ ResourceManager::LoadShader("texture", "./Shaders/Vertex/vertexSprite.shader", "./Shaders/Fragment/fragmentSprite.shader") };
	glm::mat4 projection{ glm::ortho(0.0f, static_cast<GLfloat>(width), static_cast<GLfloat>(height), 0.0f, -1.0f, 1.0f) };
	spriteShader.Use();
	spriteShader.SetInteger("image", 0);
	spriteShader.SetMatrix4("projection", projection);

	//Textures
	spriteRenderer = new SpriteRenderer(spriteShader);
	ResourceManager::LoadTexture2D("ball", "./Assets/face.png", true);
	ResourceManager::LoadTexture2D("block", "./Assets/block.png", false);
	ResourceManager::LoadTexture2D("background", "./Assets/background.jpg", false);
	ResourceManager::LoadTexture2D("blockSolid", "./Assets/blockSolid.png", false);
	ResourceManager::LoadTexture2D("paddle", "./Assets/paddle.png", true);

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

void Game::Update(const GLfloat dt) {
	ball->Move(dt, width);
}

void Game::Render() {
	if (state == GAME_ACTIVE) {
		//Draw background
		spriteRenderer->DrawSprite(ResourceManager::GetTexture2D("background"), glm::vec2(0.0f), glm::vec2(width, height));

		//Draw level
		levels[currentLevel].Draw(*spriteRenderer);

		//Draw player
		player->Draw(*spriteRenderer);

		//Draw Ball
		ball->Draw(*spriteRenderer);
	}
}