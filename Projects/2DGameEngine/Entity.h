#pragma once
#include <vector>
#include <string>
#include <memory>
#include <map>

#include "Component.h"
#include "LayerTypeEnum.h"

class EntityManager;

class Entity
{
private:
	bool isActive{ true };
	std::vector<std::unique_ptr<Component>> components;
	std::string name{ "" };
	std::map<const std::type_info*, Component&> componentTypeMap;
	const LayerTypeEnum layerType{};
public:
	Entity(const std::string name, const LayerTypeEnum layerType) : name(name), layerType(layerType) {}
	void Update(const float deltaTime) const;
	void Render() const;
	void Destroy();
	bool IsActive() const { return isActive; };
	const std::string GetName() const { return name; }
	const LayerTypeEnum GetLayer() const { return layerType; }

	template<typename T, typename... TArgs>
	Entity* AddComponent(TArgs&&... args) {
		std::unique_ptr<T>newComp{ std::make_unique<T>(std::forward<TArgs>(args)...) };
		newComp->SetOwner(this);
		newComp->Init();
		componentTypeMap.emplace(&typeid(*newComp), *newComp);
		components.emplace_back(std::move(newComp));
		return this;
	}

	template<typename T>
	T* GetComponent() const {
		return dynamic_cast<T*>(&componentTypeMap.at(&typeid(T)));
	}

	template <typename T>
	bool HasComponent() const {
		return componentTypeMap.count(&typeid(T));
	}
};

