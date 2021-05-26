#pragma once
#include <memory>

class Entity;

class Component
{
private:
	Entity* owner{ nullptr };
public:
	virtual ~Component() {};
	virtual void Init() {};
	virtual void Update(const float deltaTime) {};
	virtual void Render() const {};
	void SetOwner(Entity* entity) { owner = entity; }
	Entity& GetOwner() const { return *owner; }
};

