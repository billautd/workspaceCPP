#include "Entity.h"

void Entity::Update(const float deltaTime) const {
	for (const std::unique_ptr<Component>& component : components)
		component->Update(deltaTime);

}

void Entity::Render() const {
	for (const std::unique_ptr<Component>& component : components)
		component->Render();
}

void Entity::Destroy() {
	isActive = false;
}
