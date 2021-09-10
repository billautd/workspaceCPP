#pragma once
#include "Shader.h"
#include "Texture2D.h"

class SpriteRenderer
{
public:
	SpriteRenderer(const Shader& shader);
	~SpriteRenderer();

	void DrawSprite(const Texture2D& texture, const glm::vec2 position, const glm::vec2 size, 
		const GLfloat rotate = 0.0f, const glm::vec3 color = glm::vec3(1.0f));

private:
	Shader shader;
	GLuint vao;

	void InitRenderData();
};

