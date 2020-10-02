#include "Entity.h" 
#include <iostream>

void Entity::Update(GLfloat dt) {
	for (auto& component : components) {
		component->Update(dt);
	}
}

void Entity::Render() {
	for (auto& component : components) {
		component->Render();
	}
}

void Entity::Destroy() {
	this->isActive = false;
}

void Entity::ListAllComponents() const {
	for (auto mapElement : componentTypeMap) {
		std::cout << "    Component<" << mapElement.first->name() << ">" << std::endl;
	}
}
