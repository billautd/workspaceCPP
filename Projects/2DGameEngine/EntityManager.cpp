#include "EntityManager.h"
#include "ColliderComponent.h"
#include <iostream>

void EntityManager::DestroyInactiveEntities() {
	for (size_t i{ 0 }; i < entities.size(); i++) {
		if (!entities.at(i)->IsActive())
			entities.erase(entities.begin() + i);
	}
}

void EntityManager::Update(const float deltaTime) {
	for (const std::unique_ptr<Entity>& entity : entities)
		entity->Update(deltaTime);
	DestroyInactiveEntities();
}

void EntityManager::Render() const {
	for (const LayerTypeEnum& layer : Enum<LayerTypeEnum>()) {
		const std::vector<Entity*> layerEntities{ GetEntitiesByLayer(static_cast<LayerTypeEnum>(layer)) };
		for (Entity* entity : layerEntities)
			entity->Render();
	}
}

void EntityManager::ClearData() const {
	for (const std::unique_ptr<Entity>& entity : entities)
		entity->Destroy();
}

const std::vector<Entity*> EntityManager::GetEntitiesByLayer(const LayerTypeEnum layer) const {
	std::vector <Entity*> selectedEntities{};
	for (size_t i = 0; i < entities.size(); i++) {
		Entity* entity{ entities.at(i).get() };
		if (entity->GetLayer() == layer) {
			selectedEntities.emplace_back(entity);
		}
	}
	return selectedEntities;
}

CollisionTypeEnum EntityManager::CheckCollisions() const {
	for (size_t i = 0; i < entities.size() - 1; i++) {
		const std::unique_ptr<Entity>& thisEntity = entities.at(i);
		if (thisEntity->HasComponent<ColliderComponent>()) {
			ColliderComponent* thisCollider = thisEntity->GetComponent<ColliderComponent>();
			for (size_t j = i + 1; j < entities.size(); j++) {
				const std::unique_ptr<Entity>& thatEntity = entities[j];
				if (thisEntity->GetName().compare(thatEntity->GetName()) != 0 && thatEntity->HasComponent<ColliderComponent>()) {
					ColliderComponent* thatCollider = thatEntity->GetComponent<ColliderComponent>();
					if (thisCollider->CheckRectangleCollision(thatCollider)) {
						if ((thisCollider->GetColliderTag().compare("PLAYER") == 0 && thatCollider->GetColliderTag().compare("ENEMY") == 0) ||
							(thatCollider->GetColliderTag().compare("PLAYER") == 0 && thisCollider->GetColliderTag().compare("ENEMY") == 0)) {
							return CollisionTypeEnum::PLAYER_ENEMY_COLLISION;
						}
						if ((thisCollider->GetColliderTag().compare("PLAYER") == 0 && thatCollider->GetColliderTag().compare("PROJECTILE") == 0) ||
							(thatCollider->GetColliderTag().compare("PLAYER") == 0 && thisCollider->GetColliderTag().compare("PROJECTILE") == 0)) {
							return CollisionTypeEnum::PLAYER_PROJECTILE_COLLISION;
						}
						if ((thisCollider->GetColliderTag().compare("ENEMY") == 0 && thatCollider->GetColliderTag().compare("FRIENDLY_PROJECTILE") == 0) ||
							(thatCollider->GetColliderTag().compare("ENEMY") == 0 && thisCollider->GetColliderTag().compare("FRIENDLY_PROJECTILE") == 0)) {
							return CollisionTypeEnum::ENEMY_PROJECTILE_COLLISION;
						}
						if ((thisCollider->GetColliderTag().compare("PLAYER") == 0 && thatCollider->GetColliderTag().compare("LEVEL_COMPLETE") == 0) ||
							(thatCollider->GetColliderTag().compare("PLAYER") == 0 && thisCollider->GetColliderTag().compare("LEVEL_COMPLETE") == 0)) {
							return CollisionTypeEnum::PLAYER_LEVEL_COMPLETE_COLLISION;
						}
					}
				}
			}
		}
	}
	return CollisionTypeEnum::NO_COLLISION;
}
