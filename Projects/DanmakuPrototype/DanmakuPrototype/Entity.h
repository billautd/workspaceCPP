#pragma once

#include "SDL.h"
#include "glad/glad.h"

#include <vector>
#include <string>
#include <iostream>
#include <map>
#include <typeinfo>

#include "EventManager.h"

#include "CollisionTypeEnum.h"
#include "EntityTypeEnum.h"
#include "LayerEnum.h"
#include "Component.h"

class Component;
class Entity {
public:
	Entity() = default;
	Entity(std::string name, LayerEnum layer) : name(name), layer(layer) {};

	//Run for each component
	virtual void Update(GLfloat dt);
	virtual void Render();
	virtual void Destroy();

	//Each entity has its own
	virtual void ProcessInput(SDL_Event& e, GLfloat dt) {
		EventManager::keys = SDL_GetKeyboardState(&EventManager::keysNbr);
	};

	bool IsActive() { return isActive; }
	LayerEnum GetLayer() { return layer; }
	std::string GetName() { return name; }
	EntityTypeEnum GetEntityType() { return entityType; }
	void SetEntityType(EntityTypeEnum type) { entityType = type; }
	void SetHasCollision(bool hasCollision) { this->hasCollision = hasCollision; }
	bool HasCollision() { return hasCollision; }

	//Component management
	template <typename T, typename... TArgs>
	T* AddComponent(TArgs&&... args) {
		T* newComponent(new T(std::forward<TArgs>(args)...));
		newComponent->SetOwner(this);
		components.emplace_back(newComponent);
		componentTypeMap[&typeid(*newComponent)] = newComponent;
		newComponent->Init();
		return newComponent;
	}

	template <typename T>
	bool HasComponent() const {
		return componentTypeMap.count(&typeid(T));
	}

	template <typename T>
	T* GetComponent() {
		return static_cast<T*>(componentTypeMap[&typeid(T)]);
	}



private:

	bool isActive{ true };
	std::string name{ "" };
	LayerEnum layer{ LayerEnum::BEGIN };
	EntityTypeEnum entityType{ EntityTypeEnum::ENTITY };

	//Components
	std::vector<Component*> components{};
	std::map<const std::type_info*, Component*> componentTypeMap{};

	bool hasCollision{ false };
};

