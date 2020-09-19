#include "Game.h"
#include "ResourceManager.h"
#include "glm/gtc/matrix_transform.hpp"
#include <iostream>
#include "UtilsPiece.h"
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
	ResourceManager::GetShader("SpriteRendering").Use().SetFloat("alpha", 1.0f);

	//Load textures
	ResourceManager::LoadTexture("grid", "./Textures/grid.png", true);
	ResourceManager::LoadTexture("background", "./Textures/background.jpg", false);
	ResourceManager::LoadTexture("block", "./Textures/block.png", false);

	//Init grid
	grid = new Grid();
	currentPiece = UtilsPiece::SpawnRandomPiece();
	grid->SetPiece(*currentPiece);

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

GLfloat moveLTime{ 0.0f };
GLfloat moveRTime{ 0.0f };
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

	keys = SDL_GetKeyboardState(&keysNbr);

	if (this->state == GameStateEnum::GAME_ACTIVE) {
		//Left
		if (keys[SDL_SCANCODE_LEFT]) {
			if (!keysProcessed[SDL_SCANCODE_LEFT]) {
				keysProcessed[SDL_SCANCODE_LEFT] = true;
				if (this->grid->CanPieceMove(*currentPiece, DirectionEnum::LEFT))
					grid->MovePiece(currentPiece, DirectionEnum::LEFT);
			}
			else {
				if (this->grid->CanPieceMove(*currentPiece, DirectionEnum::LEFT) && moveLTime >= INITIAL_MOVE_LR_SPEED) {
					grid->MovePiece(currentPiece, DirectionEnum::LEFT);
					moveLTime = 0.0f;
				}
			}
			moveLTime += dt;
			moveRTime = 0.0f;
		}
		else
			keysProcessed[SDL_SCANCODE_LEFT] = false;


		//Right
		if (keys[SDL_SCANCODE_RIGHT]) {
			if (!keysProcessed[SDL_SCANCODE_RIGHT]) {
				keysProcessed[SDL_SCANCODE_RIGHT] = true;
				if (this->grid->CanPieceMove(*currentPiece, DirectionEnum::RIGHT))
					grid->MovePiece(currentPiece, DirectionEnum::RIGHT);
			}
			else {
				if (this->grid->CanPieceMove(*currentPiece, DirectionEnum::RIGHT) && moveRTime >= INITIAL_MOVE_LR_SPEED) {
					grid->MovePiece(currentPiece, DirectionEnum::RIGHT);
					moveRTime = 0.0f;
				}
			}
			moveRTime += dt;
			moveLTime = 0.0f;
		}
		else
			keysProcessed[SDL_SCANCODE_RIGHT] = false;

		//Rotate left
		if (keys[SDL_SCANCODE_Z]) {
			if (!keysProcessed[SDL_SCANCODE_Z]) {
				keysProcessed[SDL_SCANCODE_Z] = true;
				if (grid->CanPieceRotate(*currentPiece, DirectionEnum::LEFT))
					grid->RotatePiece(currentPiece, DirectionEnum::LEFT);
			}
		}
		else
			keysProcessed[SDL_SCANCODE_Z] = false;
		//Rotate right
		if (keys[SDL_SCANCODE_X]) {
			if (!keysProcessed[SDL_SCANCODE_X]) {
				keysProcessed[SDL_SCANCODE_X] = true;
				if (grid->CanPieceRotate(*currentPiece, DirectionEnum::RIGHT))
					grid->RotatePiece(currentPiece, DirectionEnum::RIGHT);
			}
		}
		else
			keysProcessed[SDL_SCANCODE_X] = false;


		//Drop down
		if (keys[SDL_SCANCODE_DOWN]) {
			if (!keysProcessed[SDL_SCANCODE_DOWN]) {
				keysProcessed[SDL_SCANCODE_DOWN] = true;
				this->fallSpeed = 0.05f;
			}
		}
		else {
			keysProcessed[SDL_SCANCODE_DOWN] = false;
			this->fallSpeed = INITIAL_FALLING_SPEED;
		}


	}
}

//Stores fall time
GLfloat fallTime{ 0.0f };
void Game::Update(GLfloat dt) {
	if (this->state == GameStateEnum::GAME_ACTIVE) {
		//Move current piece down
		if (fallTime < fallSpeed)
			fallTime += dt;
		else {
			if (this->grid->CanPieceMove(*currentPiece, DirectionEnum::DOWN))
				grid->MovePiece(currentPiece, DirectionEnum::DOWN);
			else {
				//Update on full lines (from top to bottom of piece)
				for (GLshort y = UtilsPiece::PieceTop(*currentPiece); y >= UtilsPiece::PieceBottom(*currentPiece); y--) {
					if (grid->IsLineFull(y)) {
						grid->ClearLine(y);
						grid->MovePiecesAboveDown(y);
					}
				}

				currentPiece = UtilsPiece::SpawnRandomPiece();
			}
			fallTime = 0.0f;
		}


	}
}

void Game::Render() {
	if (this->state == GameStateEnum::GAME_ACTIVE) {
		//Draw grid & BG
		spriteRenderer->DrawSprite(ResourceManager::GetTexture("background"), glm::vec2(0.0f), glm::vec2(WINDOW_WIDTH, WINDOW_HEIGHT));
		spriteRenderer->DrawSprite(ResourceManager::GetTexture("grid"), glm::vec2(GRID_X, GRID_Y), glm::vec2(GRID_WIDTH, GRID_HEIGHT), 0.0f, glm::vec3(1.0f), 0.8f);

		//Render pieces
		grid->Render(spriteRenderer);
		//Draw rotation center (DEBUG)
		//spriteRenderer->DrawSprite(ResourceManager::GetTexture("block"),
		//	glm::vec2(
		//		GRID_X + currentPiece->rotationCenter.x * TILE_SIZE,
		//		GRID_Y + (Y_TILES - currentPiece->rotationCenter.y - 1) * TILE_SIZE),
		//	glm::vec2(5.0f));
	}
}

void Game::Quit() {
	this->state = GameStateEnum::GAME_INACTIVE;
	SDL_Quit();
}