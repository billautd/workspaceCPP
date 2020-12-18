#pragma once
#include "Component.h"
#include "CollisionTypeEnum.h"
#include "Enum.h"
#include "Enemy.h"

class EntityManager {
private:
	EntityManager();
	static std::vector<Entity*> entities;
public:
	static void ClearData();
	static void Update(GLfloat dt);
	static void ProcessInput(SDL_Event& e, GLfloat dt);
	static void Render();
	static bool HasNoEntities();
	static std::vector<Entity*> GetEntities();
	static std::vector<Entity*> GetEntitiesByLayer(LayerEnum layer);
	static Entity* GetEntityByName(std::string entityName);
	static Entity& AddEntity(Entity* entity);
	static void CheckCollisions();
	static void DestroyInactiveEntities();
};

