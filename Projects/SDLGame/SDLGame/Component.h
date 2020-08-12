#pragma once
#include "Entity.h"

class Entity;

class Component {
private:
	Entity* owner{nullptr};
public:
	virtual ~Component() = default;
	virtual void Initialize() = 0;
	virtual void Update(float deltaTime) = 0;
	virtual void Render() = 0;
	Entity* GetOwner() const { return owner; };
	void SetOwner(Entity* owner)  { this->owner = owner; };
};
