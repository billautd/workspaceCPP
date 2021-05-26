#pragma once
#include <vector>
#include <memory>
#include <string>

#include "Entity.h"
#include "CollisionTypeEnum.h"

class EntityManager
{
private:
	std::vector<std::unique_ptr<Entity>> entities{};
	void DestroyInactiveEntities();
public:
	void Update(const float deltaTime);
	void Render() const;
	void ClearData() const;
	std::unique_ptr<Entity>& AddEntity(std::unique_ptr<Entity> entity) { return entities.emplace_back(std::move(entity)); }
	bool HasNoEntities() const { return entities.empty(); }
	size_t GetEntityCount() const { return entities.size(); }
	const std::vector<Entity*> GetEntitiesByLayer(const LayerTypeEnum layer) const;
	CollisionTypeEnum CheckCollisions() const;

};

