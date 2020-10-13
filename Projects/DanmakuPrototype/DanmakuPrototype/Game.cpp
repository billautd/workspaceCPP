#include "Game.h"
#include <iostream>
#include <glad\glad.h>
#include "GameData.h"
#include "ResourceManager.h"
#include "SDL_mixer.h"
#include <sstream>
#include <iomanip>
#include "ComponentsInclude.h"
#include "Player.h"

int Game::BackEndInit() {
	//SDL init
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
		std::cerr << "Error initializing SDL.\n";
		Quit();
		return 1;
	}

	//SDL_mixer init
	if (Mix_OpenAudio(22050, MIX_DEFAULT_FORMAT, 2, 1024) != 0) {
		std::cerr << "Error initializing SDL audio.\n";
		Quit();
		return 1;
	}

	//Set backup OpenGl version to 3.3
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);

	//Set OpenGL profile to Core
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

	//Window init
	this->mainWindow = SDL_CreateWindow(
		"Sample 2D OpenGL/SDL project",
		SDL_WINDOWPOS_UNDEFINED,
		SDL_WINDOWPOS_UNDEFINED,
		width,
		height,
		SDL_WINDOW_RESIZABLE | SDL_WINDOW_OPENGL
	);

	if (!this->mainWindow) {
		std::cerr << "Error initializing SDL window.\n";
		Quit();
		return 1;
	}

	//Create OpenGL Context
	void* mainContext{ SDL_GL_CreateContext(this->mainWindow) };
	if (mainContext == nullptr) {
		std::cerr << "Error initializing OpenGL context.\n";
		SDL_Quit();
		return 1;
	}
	SDL_GL_MakeCurrent(this->mainWindow, mainContext);

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

	this->LoadShaders();
	this->LoadAssets();
	this->LoadEntities();

	return 0;
}

void Game::LoadShaders() {
	ResourceManager::LoadShader("./Shaders/SpriteRendering.vert", "./Shaders/SpriteRendering.frag", nullptr, "SpriteRendering");
	ResourceManager::LoadShader("./Shaders/TextRendering.vert", "./Shaders/TextRendering.frag", nullptr, "TextRendering");
	//Set up shaders
	glm::mat4 projection{ glm::ortho(0.0f, static_cast<GLfloat>(this->width), static_cast<GLfloat>(this->height), 0.0f, -10.0f, 1.0f) };
	ResourceManager::GetShader("SpriteRendering").Use().SetInteger("sprite", 0);
	ResourceManager::GetShader("SpriteRendering").Use().SetMatrix4("projection", projection);
	ResourceManager::GetShader("TextRendering").Use().SetInteger("text", 0);
	ResourceManager::GetShader("TextRendering").Use().SetMatrix4("projection", projection);
}

void Game::LoadAssets() {
	//Texture
	ResourceManager::LoadTexture("./Textures/blank.png", false, "blank");
	ResourceManager::LoadTexture("./Textures/player.png", true, "player");
	ResourceManager::LoadTexture("./Textures/playerProjectile.png", false, "playerProjectile");

	//Fonts
	ResourceManager::LoadFont("./Fonts/Logopixies-owwBB.ttf", "logopixies", 20);
}

void Game::LoadEntities() {
	//BG
	auto& bg{ EntityManager::AddEntity(new Entity("GameBG", LayerEnum::BG_LAYER)) };
	bg.AddComponent<TransformComponent>(glm::vec2(10.0f), glm::vec2(0.0f), GAME_SIZE);
	bg.AddComponent<SpriteComponent>(ResourceManager::GetShader("SpriteRendering"), ResourceManager::GetTexture("blank"), false, glm::vec3(0.0f));
	//UI
	auto& highScore{ EntityManager::AddEntity(new Entity("HighScoreLabel", LayerEnum::UI_LAYER)) };
	highScore.AddComponent<TransformComponent>(glm::vec2(GAME_POSITION.x + GAME_SIZE.x + 20.0f, 30.0f), glm::vec2(0.0f), glm::vec2(30.0f));
	highScore.AddComponent<TextComponent>(ResourceManager::GetShader("TextRendering"), "HIGH SCORE", "logopixies");
	//Player
	auto& player{ EntityManager::AddEntity(new Player("Player", LayerEnum::PLAYER_LAYER)) };


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

	EntityManager::ProcessInput(e, dt);
}

void Game::Update(GLfloat dt) {
	EntityManager::Update(dt);
}

void Game::Render() {
	//Clear
	glClearColor(0.3f, 0.3f, 0.3f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	EntityManager::Render();
}

void Game::Quit() {
	EntityManager::ClearData();
	ResourceManager::ClearData();
	SDL_Quit();
}