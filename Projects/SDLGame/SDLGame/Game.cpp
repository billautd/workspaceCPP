#include <iostream>
#include "Game.h"
#include "Constants.h"
#include "glm.hpp"
#include "EntityManager.h"
#include "TransformComponent.h"
#include "TextLabelComponent.h"
#include "AssetManager.h"
#include "SpriteComponent.h"
#include "KeyboardControlComponent.h"
#include "ProjectileEmitterComponent.h"
#include "ColliderComponent.h"
#include "Map.h"

//Static inits
EntityManager entityManager = EntityManager();

SDL_Renderer* Game::renderer{ nullptr };
AssetManager* Game::assetManager = new AssetManager(&entityManager);
SDL_Event Game::event = SDL_Event();
SDL_Rect Game::camera = { 0, 0, WINDOW_WIDTH, WINDOW_HEIGHT };
Map* Game::map{ nullptr };
Entity* Game::player{ nullptr };



Game::Game() {
	isRunning = false;
}

void Game::Initialize(int width, int height) {
	//SDL init
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
		std::cerr << "Error initializing SDL.\n";
		return;
	}

	if (TTF_Init() != 0) {
		std::cerr << "Error initializing TTF.\n";
		return;
	}

	//Window init
	window = SDL_CreateWindow(
		NULL,
		SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED,
		width,
		height,
		SDL_WINDOW_BORDERLESS
	);
	if (!window) {
		std::cerr << "Error initializing SDL window.\n";
		return;
	}

	//Renderer init
	renderer = SDL_CreateRenderer(this->window, -1, 0);
	if (!renderer) {
		std::cerr << "Error initializing SDL renderer.\n";
		return;
	}

	LoadLevel(1);

	isRunning = true;
}

void Game::LoadLevel(unsigned int levelNumber) {
	sol::state lua;
	lua.open_libraries(sol::lib::base, sol::lib::os, sol::lib::math);

	std::string levelName{ "Level" + std::to_string(levelNumber) };
	lua.script_file("./Assets/Scripts/" + levelName + ".lua");


	sol::table levelData = lua[levelName];

	/**************************************************************/
	/********************* LOADING ASSETS *************************/
	/**************************************************************/
	sol::table levelAssets = levelData["assets"];
	unsigned int assetIndex{ 0 };
	while (true) {
		sol::optional<sol::table> existsAssetIndexNode = levelAssets[assetIndex];
		if (existsAssetIndexNode == sol::nullopt)
			break;
		else {
			sol::table asset = levelAssets[assetIndex];
			std::string assetType = asset["type"];
			std::string assetId = asset["id"];
			std::string assetFile = asset["file"];
			if (assetType.compare("texture") == 0)
				assetManager->AddTexture(assetId, assetFile.c_str());
			if (assetType.compare("font") == 0) {
				int fontSize = asset["fontSize"];
				assetManager->AddFont(assetId, assetFile.c_str(), fontSize);
			}
			if (assetType.compare("sound") == 0) {

			}
		}
		assetIndex++;
	}

	/**************************************************************/
	/********************* LOADING MAP ****************************/
	/**************************************************************/
	sol::table levelMap = levelData["map"];
	std::string textureAssetId = levelMap["textureAssetId"];
	std::string mapFile = levelMap["file"];
	float scale = levelMap["scale"];
	unsigned int tileSize = levelMap["tileSize"];
	int mapSizeX = levelMap["mapSizeX"];
	int mapSizeY = levelMap["mapSizeY"];


	map = new Map(textureAssetId, scale, tileSize);
	map->LoadMap(mapFile, mapSizeX, mapSizeY);

	/**************************************************************/
	/****************** LOADING ENTITIES **************************/
	/**************************************************************/
	sol::table levelEntities = levelData["entities"];
	unsigned int entityIndex{ 0 };
	while (true) {
		sol::optional<sol::table> existsEntityNode = levelEntities[entityIndex];
		if (existsEntityNode == sol::nullopt)
			break;
		else {
			sol::table entity = levelEntities[entityIndex];
			std::string entityName = entity["name"];
			int entityLayer = entity["layer"];
			Entity* newEntity = &(entityManager.AddEntity(entityName, static_cast<LayerType>(entityLayer)));
			if (entityName.compare("player") == 0)
				player = newEntity;
			/**********************/
			/* LOADING COMPONENTS */
			/**********************/
			sol::optional<sol::table> existComponentNode = entity["components"];
			if (existComponentNode != sol::nullopt) {
				sol::table components = entity["components"];
				//LOADING TRANSFORM COMPONENT
				sol::optional<sol::table> existTransformNode = components["transform"];
				if (existTransformNode != sol::nullopt) {
					sol::table transform = components["transform"];
					int posX = transform["position"]["x"];
					int posY = transform["position"]["y"];
					int velX = transform["velocity"]["x"];
					int velY = transform["velocity"]["y"];
					unsigned int w = transform["width"];
					unsigned int h = transform["height"];
					float s = transform["scale"];
					newEntity->AddComponent<TransformComponent>(
						posX,
						posY,
						velX,
						velY,
						w,
						h,
						s);
				}

				//LOADING SPRITE COMPONENT
				sol::optional<sol::table> existSpriteNode = components["sprite"];
				if (existSpriteNode != sol::nullopt) {
					sol::table sprite = components["sprite"];
					std::string textureAssetId = sprite["textureAssetId"];
					unsigned int numFrames = sprite["frameCount"];
					unsigned int animationSpeed = sprite["animationSpeed"];
					bool animated = sprite["animated"];
					bool hasDirection = sprite["hasDirections"];
					bool fixed = sprite["fixed"];
					newEntity->AddComponent<SpriteComponent>(
						textureAssetId,
						numFrames,
						animationSpeed,
						hasDirection,
						fixed,
						animated);
				}

				//LOADING COLLIDER COMPONENT
				sol::optional<sol::table> existColliderNode = components["collider"];
				if (existColliderNode != sol::nullopt) {
					sol::table collider = components["collider"];
					std::string tag = collider["tag"];
					TransformComponent* newEntityTransform = newEntity->GetComponent<TransformComponent>();
					newEntity->AddComponent<ColliderComponent>(
						tag,
						static_cast<int>(newEntityTransform->GetPosition().x),
						static_cast<int>(newEntityTransform->GetPosition().y),
						newEntityTransform->GetWidth(),
						newEntityTransform->GetHeight());
				}

				//LOADING INPUT COMPONENT
				sol::optional<sol::table> existInputNode = components["input"];
				if (existInputNode != sol::nullopt) {
					sol::table input = components["input"];
					sol::optional<sol::table> existKeyboardNode = input["keyboard"];
					if (existKeyboardNode != sol::nullopt) {
						sol::table keyboard = input["keyboard"];
						std::string up = keyboard["up"];
						std::string left = keyboard["left"];
						std::string down = keyboard["down"];
						std::string right = keyboard["right"];
						std::string shoot = keyboard["shoot"];
						newEntity->AddComponent<KeyboardControlComponent>(
							up,
							down,
							left,
							right,
							shoot);
					}
				}

				//LOADING PROJECTILE EMITTER COMPONENT
				sol::optional<sol::table> existProjectileEmitterNode = components["projectileEmitter"];
				if (existProjectileEmitterNode != sol::nullopt) {
					sol::table projectileEmitter = components["projectileEmitter"];
					Entity& projectile = entityManager.AddEntity(entityName + "Projectile", LayerType::PROJECTILE_LAYER);
					TransformComponent* newEntityTransform = newEntity->GetComponent<TransformComponent>();
					unsigned int width = projectileEmitter["width"];
					unsigned int height = projectileEmitter["height"];
					unsigned int speed = projectileEmitter["speed"];
					int angleDeg = projectileEmitter["angle"];
					int projectileX = static_cast<int>(newEntityTransform->GetPosition().x) + 16;
					int projectileY = static_cast<int>(newEntityTransform->GetPosition().y) + 16;
					projectile.AddComponent<TransformComponent>(projectileX, projectileY, static_cast<int>(speed * cos(angleDeg)), static_cast<int>(speed * sin(angleDeg)), width, height, 1.0f);

					std::string textureAssetId = projectileEmitter["textureAssetId"];
					projectile.AddComponent<SpriteComponent>(textureAssetId);

					projectile.AddComponent<ColliderComponent>("PROJECTILE", projectileX, projectileY, width, height);

					int range = projectileEmitter["range"];
					bool shouldLoop = projectileEmitter["shouldLoop"];
					projectile.AddComponent<ProjectileEmitterComponent>(
						speed,
						angleDeg,
						range,
						shouldLoop);
				}
			}

		}
		entityIndex++;
	}

}

void Game::ProcessInput() {
	SDL_PollEvent(&event);
	switch (event.type) {
		case SDL_QUIT: {
			isRunning = false;
			break;
		}
		case SDL_KEYDOWN: {
			if (event.key.keysym.sym == SDLK_ESCAPE)
				isRunning = false;
			break;
		}
		default:
			break;
	}
}

void Game::Update() {
	Uint32 timeToWait{ FRAME_TARGET_TIME - (SDL_GetTicks() - ticksLastFrame) };
	if (timeToWait > 0 && timeToWait < FRAME_TARGET_TIME)
		SDL_Delay(timeToWait);

	//Delta time is the difference in seconds from the last frame
	float deltaTime{ (SDL_GetTicks() - ticksLastFrame) / 1000.0f };

	//Clamp delta time to a max value
	deltaTime = (deltaTime > 0.05f) ? 0.05f : deltaTime;

	//Set the new ticks at the current frame for the next pass
	ticksLastFrame = SDL_GetTicks();

	entityManager.Update(deltaTime);

	HandleCameraMovement();

	CheckCollisions();
}

void Game::Render() {
	SDL_SetRenderDrawColor(renderer, 21, 21, 21, 255);
	SDL_RenderClear(renderer);

	if (entityManager.HasNoEntities())
		return;

	entityManager.Render();

	SDL_RenderPresent(renderer);
}

void Game::Destroy() {
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
}



void Game::HandleCameraMovement() {
	if (!player)
		return;
	TransformComponent* playerTransform = player->GetComponent<TransformComponent>();


	camera.x = static_cast<int>(playerTransform->GetPosition().x) - (WINDOW_WIDTH / 2);
	camera.y = static_cast<int>(playerTransform->GetPosition().y) - (WINDOW_HEIGHT / 2);

	//Left and top limit
	camera.x = camera.x < 0 ? 0 : camera.x;
	camera.y = camera.y < 0 ? 0 : camera.y;

	//Right and bottom limit
	camera.x = camera.x > static_cast<int>(map->GetMapSizeX()) - camera.w ? map->GetMapSizeX() - camera.w : camera.x;
	camera.y = camera.y > static_cast<int>(map->GetMapSizeY()) - camera.h ? map->GetMapSizeY() - camera.h : camera.y;
}



void Game::CheckCollisions() {
	CollisionType collisionType = entityManager.CheckCollisions();

	switch (collisionType) {
		case CollisionType::PLAYER_ENEMY_COLLISION:
		case CollisionType::PLAYER_PROJECTILE_COLLISION:
			ProcessGameOver();
			break;
		case CollisionType::PLAYER_LEVEL_COMPLETE_COLLISION:
			ProcessNextLevel(1);
			break;
		case CollisionType::ENEMY_PROJECTILE_COLLISION:
			break;
		case CollisionType::PLAYER_VEGETATION_COLLISION:
			break;
	}
}

void Game::ProcessGameOver() {
	std::cout << "Game over\n";
	isRunning = false;
}

void Game::ProcessNextLevel(unsigned int levelNumber) {
	std::cout << "Next level : Level " << levelNumber << '\n';
	isRunning = false;
}


