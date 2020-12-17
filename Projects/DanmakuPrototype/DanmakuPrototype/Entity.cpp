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

CollisionTypeEnum Entity::CheckCollision(Entity& other) {
	//Check for Collider Component existence is done in EntityManager to avoid useless calculation
	ColliderComponent thisCollider = *GetComponent<ColliderComponent>();
	ColliderComponent otherCollider = *other.GetComponent<ColliderComponent>();

	if (thisCollider.GetX() < otherCollider.GetX() + otherCollider.GetWidth() &&
		thisCollider.GetX() + thisCollider.GetWidth() > otherCollider.GetX() &&
		thisCollider.GetY() < otherCollider.GetY() + otherCollider.GetHeight() &&
		thisCollider.GetHeight() + thisCollider.GetY() > otherCollider.GetY()) {
		if ((this->GetEntityType() == EntityTypeEnum::PROJECTILE && other.GetEntityType() == EntityTypeEnum::ENEMY) ||
			(this->GetEntityType() == EntityTypeEnum::ENEMY && other.GetEntityType() == EntityTypeEnum::PROJECTILE))
			return CollisionTypeEnum::ENEMY_PROJECTILE_COLLISION;
		if ((this->GetEntityType() == EntityTypeEnum::PROJECTILE && other.GetEntityType() == EntityTypeEnum::PLAYER) ||
			(this->GetEntityType() == EntityTypeEnum::PLAYER && other.GetEntityType() == EntityTypeEnum::PROJECTILE))
			return CollisionTypeEnum::PLAYER_PROJECTILE_COLLISION;
	}

	return CollisionTypeEnum::NO_COLLISION;
}