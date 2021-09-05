#pragma once
#include "Texture2D.h"
#include "glm.hpp"
#include "Shader.h"

const GLfloat vertices[]{
	//pos            //tex
	0.0f, 1.0f,      0.0f, 1.0f,
	1.0f, 0.0f,      1.0f, 0.0f,
	0.0f, 0.0f,      0.0f, 0.0f,

	0.0f, 1.0f,      0.0f, 1.0f,
	1.0f, 1.0f,      1.0f, 1.0f,
	1.0f, 0.0f,      1.0f, 0.0f,
};

class SpriteRenderer
{
public:
	SpriteRenderer(const Shader& shader) : shader(shader) { InitRenderData(); }
	~SpriteRenderer() { glDeleteVertexArrays(1, &vao); }
	void DrawSprite(const Texture2D& texture, const glm::vec2 position, const glm::vec2 size, const GLfloat rotate, const glm::vec3 color = glm::vec3(1.0f));
private:
	Shader shader;
	GLuint vao;

	void InitRenderData();
};

