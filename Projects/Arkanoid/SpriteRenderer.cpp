#include "SpriteRenderer.h"
#include "glfw3.h"

void SpriteRenderer::DrawSprite(const Texture2D& texture, const glm::vec2 position, const glm::vec2 size, const GLfloat rotate, const glm::vec3 color)
{
	shader.Use();
	//Transformations
	glm::mat4 model{ glm::mat4(1.0f) };
	model = glm::translate(model, glm::vec3(position, 0.0f));
	//To rotate around center and not aroundtop left corner
	model = glm::translate(model, glm::vec3(0.5f * size.x, 0.5f * size.y, 0.0f));
	model = glm::rotate(model, static_cast<GLfloat>(glfwGetTime()) * glm::radians(rotate), glm::vec3(0.0f, 0.0f, 1.0f));
	model = glm::translate(model, glm::vec3(-0.5f * size.x, -0.5f * size.y, 0.0f));
	
	model = glm::scale(model, glm::vec3(size, 1.0f));

	shader.SetMat4("model", model);
	shader.SetVec3("spriteColor", color);

	glActiveTexture(GL_TEXTURE0);
	texture.Bind();

	glBindVertexArray(vao);
	{
		glDrawArrays(GL_TRIANGLES, 0, sizeof(vertices) / sizeof(GLfloat));
	}
	glBindVertexArray(0);
}

void SpriteRenderer::InitRenderData() {
	//Configure VAO/VBO
	GLuint vbo;

	glGenVertexArrays(1, &vao);
	glGenBuffers(1, &vbo);

	glBindVertexArray(vao);
	{
		glBindBuffer(GL_ARRAY_BUFFER, vbo);
		glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

		glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), (void*)0);
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), (void*)(2*sizeof(GLfloat)));
		glEnableVertexAttribArray(1);
	}
	glBindVertexArray(0);
}
