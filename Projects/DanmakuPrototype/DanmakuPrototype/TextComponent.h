#pragma once
#include "glad/glad.h"
#include "glm/glm.hpp"
#include "Shader.h"
#include "Component.h"
#include "TransformComponent.h"

class TextComponent : public Component {
public:
	TextComponent(std::string text, std::string font, GLuint fontSize, glm::vec3 color);

	void Render() override;

	glm::vec2 GetStringSize(std::string text, GLfloat scale = 1.0f);
private:
	Shader textShader;
	GLuint VAO{ 0 };
	GLuint VBO{ 0 };

	TransformComponent* transform;
	std::string text{ "" };
	std::string font{ "" };
	GLuint fontSize{ 14 };
	glm::vec3 color{ glm::vec3(1.0f) };

};

