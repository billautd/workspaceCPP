#pragma once
#include "TransformComponent.h"
#include "Entity.h"

class ColliderComponent : public Component {
public:
	ColliderComponent(GLfloat x, GLfloat y, GLfloat width, GLfloat height) : x(x), y(y), width(width), height(height) {};

	void Init() override;
	void Update(GLfloat dt) override;

	GLfloat GetX() { return x; }
	GLfloat GetY() { return y; }
	GLfloat GetWidth() { return width; }
	GLfloat GetHeight() { return height; }
private:
	TransformComponent* transform{ nullptr };
	GLfloat x{ 0 };
	GLfloat y{ 0 };
	GLfloat width{ 0 };
	GLfloat height{ 0 };
};