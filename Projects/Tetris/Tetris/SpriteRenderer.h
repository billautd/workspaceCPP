#pragma once
#include "Texture2D.h"
#include "Shader.h"

class SpriteRenderer {
public:
	SpriteRenderer() = default;
	SpriteRenderer(Shader& shader);
	~SpriteRenderer() = default;

	//Draw sprite
	void DrawSprite(Texture2D& texture, glm::vec2 position, glm::vec2 size, GLfloat rotateDegrees = 0.0f, glm::vec3 color = glm::vec3(1.0f), GLfloat alpha = 1.0f);

private:
	Shader shader{};
	GLuint VAO{ 0 };

	void InitRenderData();
};

