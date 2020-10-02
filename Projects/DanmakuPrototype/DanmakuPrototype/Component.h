#pragma once
#include "glad/glad.h"

class Entity;
class Component {
public:
	virtual ~Component() {}
	virtual void Init() {}
	virtual void Update(GLfloat dt) {}
	virtual void Render() {}
	Entity* GetOwner() { return owner; }
private:
	Entity* owner{ nullptr };
};