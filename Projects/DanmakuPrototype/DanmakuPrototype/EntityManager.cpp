#include <iostream>
#include "EntityManager.h"
#include "Enum.h"

std::vector<Entity*> EntityManager::entities;

void EntityManager::ClearData() {
	for (GLuint i = 0; i < entities.size(); i++) {
		Entity* entity{ entities.at(i) };
		entity->Destroy();
	}
}

void EntityManager::Update(GLfloat dt) {
	for (GLuint i = 0; i < entities.size(); i++) {
		Entity* entity{ entities.at(i) };
		entity->Update(dt);
	}
	DestroyInactiveEntities();
}

void EntityManager::ProcessInput(SDL_Event& e, GLfloat dt) {
	for (GLuint i = 0; i < entities.size(); i++) {
		Entity* entity{ entities.at(i) };
		if (entity->IsActive()) {
			entity->ProcessInput(e, dt);
		}
	}
}

void EntityManager::DestroyInactiveEntities() {
	for (GLuint i = 0; i < entities.size(); i++) {
		if (!entities[i]->IsActive()) {
			entities.erase(entities.begin() + i);
		}
	}
}

void EntityManager::Render() {
	for (auto layer : Enum<LayerEnum>()) {
		auto layerEntites{ GetEntitiesByLayer(static_cast<LayerEnum>(layer)) };
		for (GLuint i = 0; i < layerEntites.size(); i++) {
			Entity* entity{ layerEntites.at(i) };
			entity->Render();
		}
	}
}

bool EntityManager::HasNoEntities() {
	return entities.size() == 0;
}


std::vector<Entity*> EntityManager::GetEntities() {
	return entities;
}

Entity* EntityManager::GetEntityByName(std::string entityName) {
	for (GLuint i = 0; i < entities.size(); i++) {
		Entity* entity{ entities.at(i) };
		if (entity->GetName().compare(entityName) == 0) {
			return entity;
		}
	}
	return nullptr;
}

std::vector<Entity*> EntityManager::GetEntitiesByLayer(LayerEnum layer) {
	std::vector<Entity*> selectedEntities;
	for (GLuint i = 0; i < entities.size(); i++) {
		Entity* entity{ entities.at(i) };
		if (entity->GetLayer() == layer) {
			selectedEntities.emplace_back(entity);
		}
	}
	return selectedEntities;
}

CollisionTypeEnum EntityManager::CheckCollisions() {
	return CollisionTypeEnum::NO_COLLISION;
}

Entity& EntityManager::AddEntity(Entity* entity) {
	entities.emplace_back(entity);
	return *entity;
}
