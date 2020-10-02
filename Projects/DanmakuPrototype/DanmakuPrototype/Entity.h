#pragma once
//
#include "LayerEnum.h"
#include "Component.h" 

#include "SDL.h"
#include "glad/glad.h"
#include <vector>
#include "LayerEnum.h"
#include <string>
#include <map>
#include <typeinfo>

class Component;
class Entity {
public:
	Entity() { isActive = true; };
	Entity(std::string name, LayerEnum layer) : name(name), layer(layer) { isActive = true; };

	void Update(GLfloat dt);
	void Render();
	void Destroy();
	bool IsActive() { return isActive; }
	void ListAllComponents() const;

	LayerEnum GetLayer() { return layer; }
	std::string GetName() { return name; }
	virtual void ProcessInput(SDL_Event& e, GLfloat dt) {};

	template <typename T, typename... TArgs>
	T& AddComponent(TArgs&&... args) {
		T* newComponent(new T(std::forward<TArgs>(args)...));
		newComponent->owner = this;
		components.emplace_back(newComponent);
		componentTypeMap[&typeid(*newComponent)] = newComponent;
		newComponent->Initialize();
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
	std::vector<Component*> components;
	std::map<const std::type_info*, Component*> componentTypeMap;
	std::string name{ "" };
	LayerEnum layer{ LayerEnum::BEGIN };

	//Input 
	int keysNbr{ 1024 };
	const Uint8* keys{ new Uint8[keysNbr] };
	bool* keysProcessed{ new bool[keysNbr] {false} };
};

