#include "Game.h"
#include "ResourceManager.h"
#include "glm/gtc/matrix_transform.hpp"
#include <iostream>
#include "SDL.h"

Game::~Game() {
	this->Quit();
}

int Game::Init() {
	int backEndInitSuccess{ BackEndInit() };
	if (backEndInitSuccess != 0)
		return backEndInitSuccess;

	//Load Shaders
	ResourceManager::LoadShader("SpriteRendering", "./Shaders/SpriteRendering.vert", "./Shaders/SpriteRendering.frag");
	//Config shaders
	glm::mat4 projection{ glm::ortho(0.0f, static_cast<GLfloat>(this->width), static_cast<GLfloat>(this->height), 0.0f, -10.0f, 1.0f) };
	ResourceManager::GetShader("SpriteRendering").Use().SetMatrix4("projection", projection);

	//Load textures
	ResourceManager::LoadTexture("grid", "./Textures/grid.png", true);
	ResourceManager::LoadTexture("background", "./Textures/background.jpg", false);

	//Init renderers
	spriteRenderer = new SpriteRenderer(ResourceManager::GetShader("SpriteRendering"));

	this->state = GameStateEnum::GAME_ACTIVE;

	return 0;
}

int Game::BackEndInit() {
	//SDL init
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
		std::cerr << SDL_GetError() << "ERROR:SDL_INIT : Cannot init SDL\n";
		this->Quit();
		return 1;
	}

	//Set OpenGL to its 3.3 version
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);

	//Set OpenGL profile to Core
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

	//Create window
	this->mainWindow = SDL_CreateWindow(
		"Tetris",
		SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED,
		this->width,
		this->height,
		SDL_WINDOW_RESIZABLE | SDL_WINDOW_OPENGL);
	if (!this->mainWindow) {
		std::cerr << SDL_GetError() << "ERROR::MAIN_WINDOW : Cannot init SDL_Window\n";
		this->Quit();
		return 1;
	}

	//Create OpenGL context
	void* mainContext{ SDL_GL_CreateContext(this->mainWindow) };
	if (!mainContext) {
		std::cerr << SDL_GetError() << "ERROR::MAIN_CONTEXT : Cannot init OpenGL context\n";
		this->Quit();
		return 1;
	}
	SDL_GL_MakeCurrent(this->mainWindow, mainContext);

	//Init GLAD
	if (!gladLoadGLLoader(SDL_GL_GetProcAddress)) {
		std::cerr << "ERROR::GLAD_LOADER : Cannot init GLAD\n";
		this->Quit();
		return 1;
	}

	//Disable Cursor
	SDL_ShowCursor(SDL_DISABLE);

	//Init viewport
	glViewport(0, 0, width, height);

	//Enable blend
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

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
		this->Quit();
		return;
	}
}

void Game::Update(GLfloat dt) {}

void Game::Render() {
	if (this->state == GameStateEnum::GAME_ACTIVE) {
		//Draw grid & BG
		spriteRenderer->DrawSprite(ResourceManager::GetTexture("background"), glm::vec2(0.0f), glm::vec2(WINDOW_WIDTH, WINDOW_HEIGHT));
		spriteRenderer->DrawSprite(ResourceManager::GetTexture("grid"), glm::vec2(WINDOW_WIDTH / 2 - GRID_WIDTH / 2, WINDOW_HEIGHT / 2 - GRID_HEIGHT / 2), glm::vec2(GRID_WIDTH, GRID_HEIGHT), 0.0f, glm::vec3(1.0f), 0.8f);
	}
}

void Game::Quit() {
	this->state = GameStateEnum::GAME_INACTIVE;
	SDL_Quit();
	//delete this->spriteRenderer;
}