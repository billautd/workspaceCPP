#include "Game.h"

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
	ResourceManager::LoadTexture("./Textures/enemy.png", false, "enemy");
	ResourceManager::LoadTexture("./Textures/enemyProjectile.png", false, "enemyProjectile");
	ResourceManager::LoadTexture("./Textures/hitbox.png", true, "hitbox");
	ResourceManager::LoadTexture("./Textures/lifeBar.png", false, "lifeBar");

	//Fonts
	ResourceManager::LoadFont("./Fonts/Logopixies-owwBB.ttf", "logopixies", 20);
}

void Game::LoadEntities() {
	//BG
	Entity* bg{ EntityManager::AddEntity(new Entity("GameBG", LayerEnum::BG_LAYER)) };
	bg->AddComponent<TransformComponent>(glm::vec2(10.0f), glm::vec2(0.0f), GAME_SIZE);
	bg->AddComponent<SpriteComponent>("SpriteRendering", "blank", false, glm::vec3(0.0f));

	//UI
	Label* highScoreLabel{ dynamic_cast<Label*>(EntityManager::AddEntity(
		new Label(UI_POSITION + glm::vec2(20.0f, 10.0f), "HIGH SCORE", "HighScoreLabel", LayerEnum::UI_LAYER))) };
	Label* scoreLabel{ dynamic_cast<Label*>(EntityManager::AddEntity(
		new Label(UI_POSITION + glm::vec2(20.0f, 50.0f), "SCORE", "ScoreLabel", LayerEnum::UI_LAYER))) };

	Label* highScore{ dynamic_cast<Label*>(EntityManager::AddEntity(
		new Label(UI_POSITION_2 + glm::vec2(20.0f, 10.0f),  std::to_string(GameData::GetHighScore()), "HighScore", LayerEnum::UI_LAYER))) };
	Label* score{ dynamic_cast<Label*>(EntityManager::AddEntity(
		new Label(UI_POSITION_2 + glm::vec2(20.0f, 50.0f), std::to_string(GameData::GetScore()), "Score",  LayerEnum::UI_LAYER))) };

	Label* livesLabel{ dynamic_cast<Label*>(EntityManager::AddEntity(
		new Label(UI_POSITION + glm::vec2(20.0f, 120.0f), "LIVES", "LivesLabel", LayerEnum::UI_LAYER))) };

	Label* lives{ dynamic_cast<Label*>(EntityManager::AddEntity(
	new Label(UI_POSITION_2 + glm::vec2(20.0f, 120.0f),std::to_string(GameData::GetLives()), "Lives",  LayerEnum::UI_LAYER))) };

	//Player + hitbox
	Player* player{ dynamic_cast<Player*>(EntityManager::AddEntity(new Player("Player", LayerEnum::PLAYER_LAYER))) };

	//Enemy
	glm::vec2 position{ GAME_POSITION.x + GAME_SIZE.x / 2.0f - ENEMY_SIZE.x / 2.0f, GAME_POSITION.y + 20.0f };
	Boss* boss{ dynamic_cast<Boss*>(EntityManager::AddEntity(new Boss(position, 300, "Boss", LayerEnum::ENEMY_LAYER))) };
	boss->AddComponent<FirePatternComponent>(&Patterns::MoveToCenterThenSpiral);
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
		Quit();
		return;
	}

	EntityManager::ProcessInput(e, dt);
}

void Game::Update(GLfloat dt) {
	if (state == GameStateEnum::GAME_INACTIVE)
		return;
	EntityManager::Update(dt);
}

void Game::Render() {
	if (state == GameStateEnum::GAME_INACTIVE)
		return;
	//Clear
	glClearColor(0.3f, 0.3f, 0.3f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	EntityManager::Render();
}

void Game::Quit() {
	this->state = GameStateEnum::GAME_INACTIVE;
	EntityManager::ClearData();
	ResourceManager::ClearData();
	SDL_Quit();
}