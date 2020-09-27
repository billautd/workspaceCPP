#include "Game.h"
#include <iostream>
#include <glad\glad.h>
#include "GameData.h"
#include "ResourceManager.h"
#include "SDL_mixer.h"
#include <sstream>
#include <iomanip>


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
		SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED,
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

	//Load an set shaders
	ResourceManager::LoadShader("./Shaders/SpriteRendering.vert", "./Shaders/SpriteRendering.frag", nullptr, "SpriteRendering");
	glm::mat4 projection{ glm::ortho(0.0f, static_cast<GLfloat>(this->width), static_cast<GLfloat>(this->height), 0.0f, -10.0f, 1.0f) };
	ResourceManager::GetShader("SpriteRendering").Use().SetInteger("sprite", 0);
	ResourceManager::GetShader("SpriteRendering").Use().SetMatrix4("projection", projection);

	ResourceManager::LoadShader("./Shaders/TextRendering.vert", "./Shaders/TextRendering.frag", nullptr, "TextRendering");

	//Load textures
	ResourceManager::LoadTexture("./Textures/blank.png", true, "blank");


	//Init renderers
	this->spriteRenderer = new SpriteRenderer(ResourceManager::GetShader("SpriteRendering"));
	this->textRenderer = new TextRenderer(this->width, this->height);
	this->textRenderer->Load("./Fonts/Logopixies-owwBB.ttf", 22);

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
}

void Game::Update(GLfloat dt) {}

void Game::Render() {
	if (this->state == GameStateEnum::GAME_ACTIVE) {
		//Game BG
		spriteRenderer->DrawSprite(ResourceManager::GetTexture("blank"), GAME_POSITION, GAME_SIZE, 1.0f, glm::vec3(0.0f));
		//Right UI
		//Hi Score
		textRenderer->RenderText("HI SCORE", GAME_POSITION.x + GAME_SIZE.x + 20.0f, 30.0f);
		std::stringstream hiScoreSS; hiScoreSS << std::setw(10) << std::setfill('0') << GameData::hi_score;
		textRenderer->RenderText(hiScoreSS.str(), this->width - 20.0f - textRenderer->GetStringSize(hiScoreSS.str()).x, 30.0f);

		//Score
		textRenderer->RenderText("SCORE", GAME_POSITION.x + GAME_SIZE.x + 20.0f, 80.0f);
		std::stringstream scoreSS; scoreSS << std::setw(10) << std::setfill('0') << GameData::score;
		textRenderer->RenderText(scoreSS.str(), this->width - 20.0f - textRenderer->GetStringSize(scoreSS.str()).x, 80.0f);

		//Lives
		textRenderer->RenderText("LIVES", GAME_POSITION.x + GAME_SIZE.x + 20.0f, 200.0f);
		std::stringstream livesSS; livesSS << GameData::lives;
		textRenderer->RenderText(livesSS.str(), this->width - 50.0f - textRenderer->GetStringSize(livesSS.str()).x, 200.0f);

		//Bombs 
		textRenderer->RenderText("BOMBS", GAME_POSITION.x + GAME_SIZE.x + 20.0f, 250.0f);
		std::stringstream bombsSS; bombsSS << GameData::bombs;
		textRenderer->RenderText(bombsSS.str(), this->width - 50.0f - textRenderer->GetStringSize(bombsSS.str()).x, 250.0f);

		//Power
		textRenderer->RenderText("POWER", GAME_POSITION.x + GAME_SIZE.x + 20.0f, 350.0f);
		std::stringstream powerSS; powerSS << GameData::power;
		textRenderer->RenderText(powerSS.str(), this->width - 50.0f - textRenderer->GetStringSize(powerSS.str()).x, 350.0f);

		//Graze
		textRenderer->RenderText("GRAZE", GAME_POSITION.x + GAME_SIZE.x + 20.0f, 400.0f);
		std::stringstream grazeSS; grazeSS << GameData::graze;
		textRenderer->RenderText(grazeSS.str(), this->width - 50.0f - textRenderer->GetStringSize(grazeSS.str()).x, 400.0f);

	}
}

void Game::Quit() {
	SDL_Quit();
}