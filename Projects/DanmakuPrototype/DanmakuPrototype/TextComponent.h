#pragma once
#include "glad/glad.h"
#include "glm/glm.hpp"
#include "Shader.h"
#include "TransformComponent.h"
#include "ResourceManager.h"
#include "Entity.h"

class TextComponent : public Component {
public:
	TextComponent(std::string shader, std::string text, std::string font, GLfloat scale = 1.0f, glm::vec3 color = glm::vec3(1.0f))
		: shader(ResourceManager::GetShader(shader)), text(text), font(font), scale(scale), color(color) {}

	void Init() override;
	void Render() override;

	void SetText(std::string text) { this->text = text; }
private:
	Shader* shader;
	GLuint VAO{ 0 };
	GLuint VBO{ 0 };

	TransformComponent* transform{ nullptr };
	std::string text{ "" };
	std::string font{ "" };
	GLfloat scale{ 1.0f };
	glm::vec3 color{ glm::vec3(1.0f) };

};

