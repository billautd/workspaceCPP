#include "Game.h"
#include "Constants.h"
#include "TransformComponent.h"
#include "SpriteComponent.h"
#include "KeyboardComponent.h"
#include "ColliderComponent.h"
#include "CollisionTypeEnum.h"
#include "TextLabelComponent.h"
#include "ProjectileEmitterComponent.h"

//Static variables
rendererPtr Game::renderer{ nullptr, SDL_DestroyRenderer };
EntityManager Game::entityManager{};
AssetManager Game::assetManager{};
SDL_Event Game::event{};
SDL_Rect Game::camera{ 0, 0, WINDOW_WIDTH, WINDOW_HEIGHT };
Map* Game::map{ new Map("jungleTilemap", 25, 20, 32, 2.5f) };

void Game::Init() {
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
		std::cerr << "Error initializing SDL\n";
		return;
	}
	if (TTF_Init() != 0) {
		std::cerr << "Error initializing SDL_ttf\n";
		return;
	}

	window.reset(SDL_CreateWindow(
		"2DGameEngine",
		SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED,
		WINDOW_WIDTH,
		WINDOW_HEIGHT,
		SDL_WINDOW_RESIZABLE));

	if (!window) {
		std::cerr << "Error initializing SDL Window\n";
		return;
	}

	renderer.reset(SDL_CreateRenderer(window.get(), -1, 0));
	if (!renderer) {
		std::cerr << "Error initializing SDL Renderer\n";
		return;
	}

	//Run game
	isRunning = true;

	//Load first level
	LoadLevel(0);
}


Entity* player{ nullptr };

void Game::HandleCameraMovement() const {
	TransformComponent* playerTransform{ player->GetComponent<TransformComponent>() };

	camera.x = static_cast<int>(playerTransform->GetX() - WINDOW_WIDTH / 2);
	camera.y = static_cast<int>(playerTransform->GetY() - WINDOW_HEIGHT / 2);

	camera.x = camera.x < 0 ? 0 : camera.x;
	camera.y = camera.y < 0 ? 0 : camera.y;
	camera.x = camera.x > map->GetMapSizePixelsX() - camera.w ? map->GetMapSizePixelsX() - camera.w : camera.x;
	camera.y = camera.y > map->GetMapSizePixelsY() - camera.h ? map->GetMapSizePixelsY() - camera.h : camera.y;
}

void Game::CheckCollisions() {
	CollisionTypeEnum collisionType = entityManager.CheckCollisions();
	if (collisionType == CollisionTypeEnum::PLAYER_ENEMY_COLLISION ||
		collisionType == CollisionTypeEnum::PLAYER_PROJECTILE_COLLISION)
		ProcessGameOver();

	if (collisionType == CollisionTypeEnum::PLAYER_LEVEL_COMPLETE_COLLISION)
		ProcessNextLevel(1);

}


void Game::LoadLevel(const unsigned short levelNumber) const {
	assetManager.AddTexture("tank", std::string("./Assets/Images/tank-big-right.png").c_str());
	assetManager.AddTexture("heliport", std::string("./Assets/Images/Heliport.png").c_str());
	assetManager.AddTexture("choppersheet", std::string("./Assets/Images/chopper-spritesheet.png").c_str());
	assetManager.AddTexture("radarsheet", std::string("./Assets/Images/radar-spritesheet.png").c_str());
	assetManager.AddTexture("jungleTilemap", std::string("./Assets/TileMaps/jungle.png").c_str());
	assetManager.AddTexture("projectileImage", std::string("./Assets/Images/bullet-enemy.png").c_str());
	assetManager.AddFont("charriotFont", std::string("./Assets/Fonts/charriot.ttf").c_str(), 20);

	map->LoadMap("./Assets/TileMaps/jungle.map");

	player = entityManager.AddEntity(std::make_unique<Entity>("chopper", LayerTypeEnum::PLAYER_LAYER))
		->AddComponent<TransformComponent>(240, 106, 0, 0, 32, 32, true)
		->AddComponent<SpriteComponent>("choppersheet", 1.0f, false, true, 2, 60, true)
		->AddComponent<KeyboardComponent>()
		->AddComponent<ColliderComponent>("PLAYER", 240, 106, 32, 32);

	entityManager.AddEntity(std::make_unique<Entity>("tank", LayerTypeEnum::ENEMY_LAYER))
		->AddComponent<TransformComponent>(220, 620, 0, 0, 32, 32)
		->AddComponent<SpriteComponent>("tank")
		->AddComponent<ColliderComponent>("ENEMY", 0, 0, 32, 32);

	entityManager.AddEntity(std::make_unique<Entity>("projectile", LayerTypeEnum::PROJECTILE_LAYER))
		->AddComponent<TransformComponent>(220 + 16, 620 + 16, 0, 0, 4, 4)
		->AddComponent<SpriteComponent>("projectileImage")
		->AddComponent<ColliderComponent>("PROJECTILE", 0, 0, 4, 4)
		->AddComponent<ProjectileEmitterComponent>(50, 270, 200, true);

	entityManager.AddEntity(std::make_unique<Entity>("heliport", LayerTypeEnum::OBSTACLE_LAYER))
		->AddComponent<TransformComponent>(470, 420, 0, 0, 32, 32, 1)
		->AddComponent<SpriteComponent>("heliport")
		->AddComponent<ColliderComponent>("LEVEL_COMPLETE", 470, 420, 32, 32);

	entityManager.AddEntity(std::make_unique<Entity>("radar", LayerTypeEnum::UI_LAYER))
		->AddComponent<TransformComponent>(1600, 15, 0, 0, 64, 64)
		->AddComponent<SpriteComponent>("radarsheet", 2.0f, true, true, 8, 100, false);

	entityManager.AddEntity(std::make_unique<Entity>("labelLevelName", LayerTypeEnum::UI_LAYER))
		->AddComponent<TextLabelComponent>(10, 10, "First level", "charriotFont", WHITE_COLOR);

}

void Game::ProcessInput() {
	SDL_PollEvent(&event);
	switch (event.type) {
		case SDL_QUIT: {
			isRunning = false;
			break;
		}
		case SDL_KEYDOWN: {
			if (event.key.keysym.sym == SDLK_ESCAPE) {
				isRunning = false;
				break;
			}
		}
	}

}

void Game::Update() {
	//Sleep the execution until we reach the target frame time in milliseconds
	const unsigned int timeToWait{ static_cast<unsigned int>(ticksLastFrame + FRAME_TARGET - SDL_GetTicks()) };

	//Pnly call delay if we are too fast to process this frame
	if (timeToWait > 0 && timeToWait <= FRAME_TARGET)
		SDL_Delay(timeToWait);

	//Delta time is the differentce in ticks from last frame converted to seconds
	float deltaTime{ (SDL_GetTicks() - ticksLastFrame) / 1000.0f };
	deltaTime = (deltaTime > 0.05f) ? 0.05f : deltaTime;

	//Sets the new ticks for the current frame to be used in the next pass
	ticksLastFrame = SDL_GetTicks();

	//Update entities
	entityManager.Update(deltaTime);

	HandleCameraMovement();
	CheckCollisions();
}

void Game::Render() const {
	SDL_SetRenderDrawColor(renderer.get(), 21, 21, 21, 255);
	SDL_RenderClear(renderer.get());

	if (!entityManager.HasNoEntities())
		entityManager.Render();

	SDL_RenderPresent(renderer.get());
}

void Game::Destroy() const {
	SDL_DestroyRenderer(renderer.get());
	SDL_DestroyWindow(window.get());
	SDL_Quit();
}

void Game::ProcessNextLevel(const unsigned int levelNumber) {
	std::cout << "Next Level" << std::endl;
	isRunning = false;
}

void Game::ProcessGameOver() {
	std::cout << "Game Over" << std::endl;
	isRunning = false;
}