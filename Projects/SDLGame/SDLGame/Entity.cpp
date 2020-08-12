#include "Entity.h"
#include <iostream>

Entity::Entity(EntityManager& manager, LayerType layer, std::string name) : manager(manager), layer(layer), name(name){
	isActive = true;
}

void Entity::Update(float deltaTime) {
	for (auto& comp : components) {
		comp->Update(deltaTime);
	}
}

void Entity::Render() {
	for (auto& comp : components) {
		comp->Render();
	}
}

void Entity::Destroy() {
	isActive = false;
}

void Entity::ListAllComponents() const {
	std::cout << this->name << " : \n";
	for (auto& comp : componentTypeMap) {
		std::cout << "\t\t" << comp.first->name() << '\n';
	}
}
