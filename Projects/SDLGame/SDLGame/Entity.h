#pragma once
#include "Component.h"
#include "EntityManager.h"
#include <vector>
#include <string>
#include <map>
#include <iostream>
#include "Constants.h"


class EntityManager;
class Component;

class Entity {
private:
	EntityManager& manager;
	bool isActive{ false };
	std::vector<Component*> components{};
	std::string name{""};
	std::map<const std::type_info*, Component*> componentTypeMap;
	LayerType layer{};
public:
	Entity() = default;
	~Entity() = default;
	Entity(EntityManager& manager, LayerType layer, std::string name = "Unnamed Entity");
	void Update(float deltaTime);
	void Render();
	void Destroy();
	bool IsActive() const { return isActive; };
	std::string GetName() const { return name; };
	LayerType GetLayerType() const { return layer; }
	void ListAllComponents() const;

	template <typename T, typename... TArgs>
	T& AddComponent(TArgs&&... args) {
		T* component(new T(std::forward<TArgs>(args)...));
		component->SetOwner(this);
		components.emplace_back(component);
		componentTypeMap.emplace(&typeid(*component), component);
		component->Initialize();
		return *component;
	}

	template <typename T>
	T* GetComponent() const {
		if(HasComponent<T>())
			return static_cast<T*>(componentTypeMap.at(&typeid(T)));
		return nullptr;
	}


	template <typename T>
	bool HasComponent() const {
		return componentTypeMap.find(&typeid(T)) != componentTypeMap.end();
	}
};