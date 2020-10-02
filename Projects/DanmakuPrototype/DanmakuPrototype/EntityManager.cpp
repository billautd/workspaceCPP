#include <iostream>
#include "EntityManager.h"
#include "Enum.h"

std::vector<Entity*> EntityManager::entities;

void EntityManager::ClearData() {
	for (auto& entity : entities) {
		entity->Destroy();
	}
}

void EntityManager::Update(GLfloat dt) {
	for (auto& entity : entities) {
		entity->Update(dt);
	}
	DestroyInactiveEntities();
}

void EntityManager::DestroyInactiveEntities() {
	for (int i = 0; i < entities.size(); i++) {
		if (!entities[i]->IsActive()) {
			entities.erase(entities.begin() + i);
		}
	}
}

void EntityManager::Render() {
	for (auto layer : Enum<LayerEnum>()) {
		for (auto& entity : GetEntitiesByLayer(static_cast<LayerEnum>(layer))) {
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
	for (auto* entity : entities) {
		if (entity->GetName().compare(entityName) == 0) {
			return entity;
		}
	}
	return NULL;
}

std::vector<Entity*> EntityManager::GetEntitiesByLayer(LayerEnum layer) {
	std::vector<Entity*> selectedEntities;
	for (auto& entity : entities) {
		if (entity->GetLayer() == layer) {
			selectedEntities.emplace_back(entity);
		}
	}
	return selectedEntities;
}

void EntityManager::ListAllEntities() {
	unsigned int i = 0;
	for (auto& entity : entities) {
		std::cout << "Entity[" << i << "]: " << entity->GetName() << std::endl;
		entity->ListAllComponents();
		i++;
	}
}

CollisionTypeEnum EntityManager::CheckCollisions() {
	return CollisionTypeEnum::NO_COLLISION;
}

Entity& EntityManager::AddEntity(std::string entityName, LayerEnum layer) {
	Entity* entity = new Entity(entityName, layer);
	entities.emplace_back(entity);
	return *entity;
}
