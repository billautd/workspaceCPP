#include "Game.h"
#include "SpriteRenderer.h"
#include "ResourceManager.h"
SpriteRenderer* renderer{ nullptr };
GameObject* player{ nullptr };
Game::Game(GLuint width, GLuint height) {}

Game::~Game() {
	delete renderer;
}

int Game::BackEndInit() {
	//SDL init
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
		std::cerr << "Error initializing SDL.\n";
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
	if (int success = BackEndInit() != 0)
		return success;

	//Load shaders
	ResourceManager::LoadShader("./Shaders/SpriteRendering.vert", "./Shaders/SpriteRendering.frag", nullptr, "SpriteRendering");
	//Config shaders
	glm::mat4 projection = glm::ortho(0.0f, static_cast<GLfloat>(this->width), static_cast<GLfloat>(this->height), 0.0f, -10.0f, 1.0f);
	ResourceManager::GetShader("SpriteRendering").Use().SetInteger("image", 0);
	ResourceManager::GetShader("SpriteRendering").Use().SetMatrix4("projection", projection);

	//Set render-specific controls
	renderer = new SpriteRenderer(ResourceManager::GetShader("SpriteRendering"));

	//Load textures
	ResourceManager::LoadTexture("./Textures/solidTile.png", false, "solidTile");
	ResourceManager::LoadTexture("./Textures/nonSolidTile.png", false, "nonSolidTile");
	ResourceManager::LoadTexture("./Textures/background.jpg", false, "background");
	ResourceManager::LoadTexture("./Textures/paddle.png", true, "paddle");

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
	glm::vec2 position(this->width / 2.0f - PLAYER_SIZE.x / 2.0f, this->height - PLAYER_SIZE.y);
	player = new GameObject(position, PLAYER_SIZE, ResourceManager::GetTexture("paddle"));

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
		GLfloat velocity = PLAYER_VELOCITY * dt;

		//Left
		if (keys[SDL_SCANCODE_LEFT]) {
			if (player->GetPosition().x > 0.0f)
				player->SetPosition(glm::vec2(player->GetPosition().x - velocity, player->GetPosition().y));
		}
		//Right
		if (keys[SDL_SCANCODE_RIGHT]) {
			if (player->GetPosition().x + PLAYER_SIZE.x < this->width)
				player->SetPosition(glm::vec2(player->GetPosition().x + velocity, player->GetPosition().y));
		}
	}

}

void Game::Update(GLfloat dt) {}

void Game::Render() {
	if (this->state == GameStateEnum::GAME_ACTIVE) {
		//Draw BG
		renderer->DrawSprite(ResourceManager::GetTexture("background"), glm::vec2(0.0f, 0.0f), glm::vec2(this->width, this->height));
		//Draw Level
		this->levels.at(this->level).Draw(*renderer);
		//Draw player
		player->Draw(*renderer);
	}
}


