#pragma once
#include "Shader.h"
#include "Texture2D.h"
class SpriteRenderer
{
public:
	SpriteRenderer() = default;
	SpriteRenderer(Shader& shader);
	~SpriteRenderer() = default;

	//Rotate in degrees
	void DrawSprite(Texture2D& texture, glm::vec2 position, glm::vec2 size, GLfloat alpha = 1.0f, glm::vec3 color = glm::vec3(1.0f), GLfloat rotate = 0.0f);
private:
	Shader shader{};
	GLuint quadVAO{ 0 };

	void InitRenderData();
};

