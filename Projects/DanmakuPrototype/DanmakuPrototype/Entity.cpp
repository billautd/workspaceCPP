#include "Entity.h" 

void Entity::Update(GLfloat dt) {
	for (auto& component : components)
		component->Update(dt);
}

void Entity::Render() {
	for (auto& component : components)
		component->Render();
}

void Entity::Destroy() {
	this->isActive = false;
	for (auto& component : components)
		delete component;
}