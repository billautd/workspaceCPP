#include "SpriteRenderer.h"
#include "glm/gtc/matrix_transform.hpp"
#include "Constants.h"
#include "ResourceManager.h"
SpriteRenderer::SpriteRenderer(Shader& shader) :shader(shader) {
	InitRenderData();
}

void SpriteRenderer::DrawSprite(Texture2D& texture, glm::vec2 position, glm::vec2 size, GLfloat rotateDegrees, glm::vec3 color, GLfloat alpha) {
	this->shader.Use();

	//Model
	glm::mat4 model{ glm::mat4(1.0f) };
	//Translate
	model = glm::translate(model, glm::vec3(position, 0.0f));
	//Rotate (Around 0,0 so we translate to rotate around center)
	model = glm::translate(model, glm::vec3(0.5f * size.x, 0.5f * size.y, 0.0f));
	model = glm::rotate(model, glm::radians(rotateDegrees), glm::vec3(0.0f, 0.0f, 1.0f));
	model = glm::translate(model, glm::vec3(-0.5f * size.x, -0.5f * size.y, 0.0f));
	//Scale
	model = glm::scale(model, glm::vec3(size, 1.0f));

	this->shader.SetMatrix4("model", model);
	this->shader.SetVector3f("spriteColor", color);
	if (texture.GetImageFormat() == GL_RGBA)
		this->shader.SetFloat("alpha", alpha);
	else
		this->shader.SetFloat("alpha", 1.0f);

	glActiveTexture(GL_TEXTURE0);
	texture.Bind();

	glBindVertexArray(this->VAO);
	{
		glDrawArrays(GL_TRIANGLES, 0, 6);
	}
	glBindVertexArray(0);
}

void SpriteRenderer::InitRenderData() {
	GLuint VBO{ 0 };

	glGenVertexArrays(1, &this->VAO);
	glGenBuffers(1, &VBO);

	glBindVertexArray(this->VAO); {
		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(QUAD_TEXTURE_VERTICES), QUAD_TEXTURE_VERTICES, GL_STATIC_DRAW);

		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), (void*)0);

		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}
	glBindVertexArray(0);
}
