#pragma once

#include "LayerEnum.h"
#include "SDL.h"
#include "glad/glad.h"
#include <vector>
#include <string>
#include <map>
#include <typeinfo>
#include "Component.h"
#include "ComponentsInclude.h"
#include "EventManager.h"
#include <iostream>
#include "CollisionTypeEnum.h"
#include "ColliderComponent.h"
#include "EntityTypeEnum.h"

class Component;
class Entity {
public:
	Entity() = default;
	Entity(std::string name, LayerEnum layer) : name(name), layer(layer) {};

	//Run for each component
	virtual void Update(GLfloat dt);
	virtual void Render();
	virtual void Destroy();
	virtual CollisionTypeEnum CheckCollision(Entity& entity);

	//Each entity has its own
	virtual void ProcessInput(SDL_Event& e, GLfloat dt) {
		EventManager::keys = SDL_GetKeyboardState(&EventManager::keysNbr);
	};

	void SetActive(bool active) { this->isActive = active; }
	bool IsActive() { return isActive; }
	LayerEnum GetLayer() { return layer; }
	std::string GetName() { return name; }
	EntityTypeEnum GetEntityType() { return entityType; }
	void SetEntityType(EntityTypeEnum type) { entityType = type; }

	//Component management
	template <typename T, typename... TArgs>
	T& AddComponent(TArgs&&... args) {
		T* newComponent(new T(std::forward<TArgs>(args)...));
		newComponent->SetOwner(this);
		components.emplace_back(newComponent);
		componentTypeMap[&typeid(*newComponent)] = newComponent;
		newComponent->Init();
		return *newComponent;
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
};

