#include <iostream>
#include "EntityManager.h"
#include "Collision.h"
#include "ColliderComponent.h"


void EntityManager::ClearData() {
	for (auto& entity : entities) {
		entity->Destroy();
	}
}

void EntityManager::Update(float deltaTime) {
	for (auto& entity: entities) {
		entity->Update(deltaTime);
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
	for (int layer = 0; layer < NUM_LAYER; layer++) {
		for (auto& entity : GetEntitiesByLayer(static_cast<LayerType>(layer))) {
			entity->Render();
		}
	}
}

Entity& EntityManager::AddEntity(std::string entityName, LayerType layer) {
	Entity* entity = new Entity(*this, layer, entityName);
	entities.push_back(entity);
	return *entity;
}

std::vector<Entity*> EntityManager::GetEntitiesByLayer(LayerType layer) const {
	std::vector<Entity*> layerEntities{};
	for (auto& entity : entities) {
		if (entity->GetLayerType() == layer)
			layerEntities.emplace_back(entity);
	}
	return layerEntities;
}

void EntityManager::ListAllEntities() const {
	std::cout << "Entities : \n";
	for (auto& entity : entities) {
		std::cout << '\t';
		entity->ListAllComponents();
		std::cout << '\n';
	}
}

CollisionType EntityManager::CheckCollisions() const {
	for (size_t i = 0; i < entities.size(); i++) {
		const Entity* thisEntity = entities.at(i);
		if (thisEntity->HasComponent<ColliderComponent>()) {
			ColliderComponent* thisCollider = thisEntity->GetComponent<ColliderComponent>();
			for (size_t j = i + 1; j < entities.size(); j++) {
				const Entity* otherEntity = entities.at(j);
				if (thisEntity->GetName().compare(otherEntity->GetName()) != 0 &&
					otherEntity->HasComponent<ColliderComponent>()) {

					ColliderComponent* otherCollider = otherEntity->GetComponent<ColliderComponent>();
					if (Collision::CheckRectangleCollision(thisCollider->GetCollider(), otherCollider->GetCollider())) {

						if (thisCollider->GetColliderTag().compare("PLAYER") == 0 && otherCollider->GetColliderTag().compare("ENEMY") == 0)
							return CollisionType::PLAYER_ENEMY_COLLISION;

						if (thisCollider->GetColliderTag().compare("PLAYER") == 0 && otherCollider->GetColliderTag().compare("PROJECTILE") == 0)
							return CollisionType::PLAYER_PROJECTILE_COLLISION;

						if (thisCollider->GetColliderTag().compare("ENEMY") == 0 && otherCollider->GetColliderTag().compare("FRIENDLY_PROJECTILE") == 0)
							return CollisionType::ENEMY_PROJECTILE_COLLISION;

						if (thisCollider->GetColliderTag().compare("PLAYER") == 0 && otherCollider->GetColliderTag().compare("VEGETATION") == 0)
							return CollisionType::PLAYER_VEGETATION_COLLISION;

						if (thisCollider->GetColliderTag().compare("PLAYER") == 0 && otherCollider->GetColliderTag().compare("LEVEL_COMPLETE") == 0)
							return CollisionType::PLAYER_LEVEL_COMPLETE_COLLISION;
					}
				}
			}
		}
	}
	return CollisionType::NO_COLLISION;
}
