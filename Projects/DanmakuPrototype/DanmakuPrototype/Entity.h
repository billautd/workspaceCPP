#pragma once

#include "LayerEnum.h"
#include "SDL.h"
#include "glad/glad.h"
#include <vector>
#include <string>
#include <map>
#include <typeinfo>
#include "Component.h"
#include "TransformComponent.h"
#include "EventManager.h"

class Component;
class Entity {
public:
	Entity() { isActive = true; };
	Entity(std::string name, LayerEnum layer) : name(name), layer(layer) { isActive = true; };

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

	bool isActive{ false };
	std::string name{ "" };
	LayerEnum layer{ LayerEnum::BEGIN };

	//Components
	std::vector<Component*> components{};
	std::map<const std::type_info*, Component*> componentTypeMap{};
};

