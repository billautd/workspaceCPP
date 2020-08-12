#pragma once
#include "Entity.h"
#include "Constants.h"
#include <vector>
#include <string>

class Entity;

class EntityManager {
private:
	std::vector<Entity*> entities{};
public:
	EntityManager() = default;
	~EntityManager() = default;

	void ClearData();
	void DestroyInactiveEntities();
	void Update(float deltaTime);
	void Render();
	bool HasNoEntities() const { return entities.size() == 0; };
	Entity& AddEntity(std::string entityName, LayerType layer);
	std::vector<Entity*> GetEntitiesByLayer(LayerType layer) const;
	std::vector<Entity*> GetEntities() const {return entities;};
	size_t GetEntityCount() const {return entities.size();};
	void ListAllEntities() const;
	CollisionType CheckCollisions() const;
};
