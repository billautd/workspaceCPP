#pragma once
#include "glad/glad.h"
#include "glm.hpp"
#include "Texture2D.h"
#include "SpriteRenderer.h"

class GameObject
{
public:
	glm::vec2 position{};
	glm::vec2 size{};
	glm::vec2 velocity{ glm::vec2(0.0f) };
	glm::vec3 color{glm::vec3(1.0f)};
	GLfloat rotation{ 0.0f };
	bool isSolid{ false };
	bool destroyed{ false };

	Texture2D sprite{};

	GameObject() {};
	GameObject(const glm::vec2 position, const glm::vec2 size, const Texture2D& sprite, 
		const glm::vec2 velocity = glm::vec2(0.0f),	const glm::vec3 color = glm::vec3(1.0f)) :
		position(position), size(size), sprite(sprite), color(color), velocity(velocity) {};
	~GameObject() {};

	void Draw(SpriteRenderer& renderer);
};

