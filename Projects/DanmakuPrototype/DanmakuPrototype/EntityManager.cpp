#include "EntityManager.h"

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
	CheckCollisions();
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
	for (auto it = entities.begin(); it != entities.end(); ) {
		if (!(*it)->IsActive())
			it = entities.erase(it);
		else
			it++;
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

void EntityManager::CheckCollisions() {
	for (int i = 0; i < entities.size() - 1; i++) {
		Entity* entity = entities[i];
		//If no collider, no collision
		if (!entity->HasCollision())
			continue;
		for (int j = i + 1; j < entities.size(); j++) {
			Entity* other = entities[j];
			if (!other->HasCollision())
				continue;
			//Check collision between all pairs of entities, but only once
			CollisionTypeEnum collision{ CheckCollision(*entity, *other) };
			if (collision == CollisionTypeEnum::NO_COLLISION)
				continue;
			Player* player{ nullptr };
			Enemy* enemy{ nullptr };
			switch (collision) {
				case CollisionTypeEnum::PLAYER_PROJECTILE_COLLISION:
				case CollisionTypeEnum::PLAYER_ENEMY_COLLISION:
					if (entity->GetEntityType() == EntityTypeEnum::PLAYER)
						player = dynamic_cast<Player*>(entity);
					else
						player = dynamic_cast<Player*>(other);
					player->GetHitbox()->Destroy();
					player->Destroy();
					other->Destroy();
					break;
				case CollisionTypeEnum::ENEMY_PROJECTILE_COLLISION:
					if (entity->GetEntityType() == EntityTypeEnum::ENEMY)
						enemy = dynamic_cast<Enemy*>(entity);
					else
						enemy = dynamic_cast<Enemy*>(other);
					enemy->DecrementHealth();
					if (enemy->IsDead())
						entity->Destroy();
					other->Destroy();
					break;
				default:
					std::cerr << "Error while reading Collision type\n";
			}
		}
	}
}


CollisionTypeEnum EntityManager::CheckCollision(Entity& thisEntity, Entity& otherEntity) {
	//Same type should no collide
	if (thisEntity.GetEntityType() == otherEntity.GetEntityType())
		return CollisionTypeEnum::NO_COLLISION;
	//Two projectiles should not collide
	if ((thisEntity.GetEntityType() == EntityTypeEnum::PLAYER_PROJECTILE || thisEntity.GetEntityType() == EntityTypeEnum::ENEMY_PROJECTILE) &&
		(otherEntity.GetEntityType() == EntityTypeEnum::PLAYER_PROJECTILE || otherEntity.GetEntityType() == EntityTypeEnum::ENEMY_PROJECTILE))
		return CollisionTypeEnum::NO_COLLISION;

	//Enemy projectiles and enemies should not collide
	if (CheckCollisionType(thisEntity, otherEntity, EntityTypeEnum::ENEMY, EntityTypeEnum::ENEMY_PROJECTILE))
		return CollisionTypeEnum::NO_COLLISION;

	if (CollisionUtils::CheckRectangleCollision(*thisEntity.GetComponent<ColliderComponent>(), *otherEntity.GetComponent<ColliderComponent>())) {
		if (CheckCollisionType(thisEntity, otherEntity, EntityTypeEnum::ENEMY, EntityTypeEnum::PLAYER_PROJECTILE))
			return CollisionTypeEnum::ENEMY_PROJECTILE_COLLISION;
		if (CheckCollisionType(thisEntity, otherEntity, EntityTypeEnum::ENEMY_PROJECTILE, EntityTypeEnum::PLAYER))
			return CollisionTypeEnum::PLAYER_PROJECTILE_COLLISION;
		if (CheckCollisionType(thisEntity, otherEntity, EntityTypeEnum::PLAYER, EntityTypeEnum::ENEMY))
			return CollisionTypeEnum::PLAYER_ENEMY_COLLISION;
		return CollisionTypeEnum::NO_COLLISION;
	}
}

bool EntityManager::CheckCollisionType(Entity& thisEntity, Entity& otherEntity, EntityTypeEnum thisType, EntityTypeEnum otherType) {
	return (thisEntity.GetEntityType() == thisType && otherEntity.GetEntityType() == otherType) ||
		(thisEntity.GetEntityType() == otherType && otherEntity.GetEntityType() == thisType);
}



Entity* EntityManager::AddEntity(Entity* entity) {
	entities.emplace_back(entity);
	return entity;
}
