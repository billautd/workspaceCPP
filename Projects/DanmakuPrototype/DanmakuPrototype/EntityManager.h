#pragma once
#include "Entity.h"
#include "Component.h"
#include "CollisionTypeEnum.h"

class EntityManager {
private:
	static std::vector<Entity*> entities;
public:
	static void ClearData();
	static void Update(GLfloat dt);
	static void Render();
	static bool HasNoEntities();
	static void ListAllEntities();
	static std::vector<Entity*> GetEntities();
	static std::vector<Entity*> GetEntitiesByLayer(LayerEnum layer);
	static Entity* GetEntityByName(std::string entityName);
	static Entity& AddEntity(std::string entityName, LayerEnum layer);
	static CollisionTypeEnum CheckCollisions();
	static void DestroyInactiveEntities();
};

