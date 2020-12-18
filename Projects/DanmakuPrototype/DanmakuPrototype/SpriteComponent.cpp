#include "SpriteComponent.h"

void SpriteComponent::Init() {
	transform = GetOwner()->GetComponent<TransformComponent>();
}

void SpriteComponent::Update(GLfloat dt) {
	transform->Update(dt);
}

void SpriteComponent::Render() {
	this->shader.Use();
	//Model
	glm::mat4 model{ glm::mat4(1.0f) };

	//Translate
	model = glm::translate(model, glm::vec3(transform->GetPosition(), 0.0f));

	//Rotate (Around 0,0 so we translate to rotate around center)
	if (transform->GetRotation() != 0.0f) {
		model = glm::translate(model, glm::vec3(0.5f * transform->GetWidth(), 0.5f * transform->GetHeight(), 0.0f));
		model = glm::rotate(model, glm::radians(transform->GetRotation()), glm::vec3(0.0f, 0.0f, 1.0f));
		model = glm::translate(model, glm::vec3(-0.5f * transform->GetWidth(), -0.5f * transform->GetHeight(), 0.0f));
	}

	//Scale
	model = glm::scale(model, glm::vec3(transform->GetSize(), 1.0f));

	this->shader.SetMatrix4("model", model);
	this->shader.SetVector3f("spriteColor", color);
	this->shader.SetFloat("alpha", alpha);

	glActiveTexture(GL_TEXTURE0);
	texture.Bind();

	glBindVertexArray(this->quadVAO);
	{
		glDrawArrays(GL_TRIANGLES, 0, 6);
	}
	glBindVertexArray(0);
}

void SpriteComponent::InitRenderData() {
	//Config VAO/VBO
	GLuint VBO{ 0 };

	glGenVertexArrays(1, &this->quadVAO);
	glGenBuffers(1, &VBO);

	glBindVertexArray(this->quadVAO);
	{
		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(QUAD_TEXTURE_VERTICES), QUAD_TEXTURE_VERTICES, GL_STATIC_DRAW);

		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), (void*)0);

		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}
	glBindVertexArray(0);
}