#pragma once
#include "glad/glad.h"
#include "glm/glm.hpp"
#include "Shader.h"
#include "ComponentsInclude.h"

class TextComponent : public Component {
public:
	TextComponent(Shader& shader, std::string text, std::string font, GLfloat scale = 1.0f, glm::vec3 color = glm::vec3(1.0f))
		: shader(shader), text(text), font(font), scale(scale), color(color) {}

	void Init() override;
	void Render() override;

	glm::vec2 GetStringSize(std::string text, GLfloat scale = 1.0f);
private:
	Shader& shader;
	GLuint VAO{ 0 };
	GLuint VBO{ 0 };

	TransformComponent* transform{ nullptr };
	std::string text{ "" };
	std::string font{ "" };
	GLfloat scale{ 1.0f };
	glm::vec3 color{ glm::vec3(1.0f) };

};

