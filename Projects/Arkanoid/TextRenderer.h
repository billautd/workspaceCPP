#pragma once
#include "Character.h"
#include "Shader.h"
#include <map>

class TextRenderer
{
public:
	//List of precompiled characters
	std::map<char, Character> characters{};
	//Precompiles list of characters from given font
	void Load(const std::string font, const GLuint fontSize);
	//Renders a string of text using precompiled characters
	void RenderText(const std::string text, GLfloat x, GLfloat y, const GLfloat scale = 1.0f, const glm::vec3 color = glm::vec3(1.0f));

	TextRenderer(Shader& shader, const GLuint width, const GLuint height);

private:
	Shader shader{};
	GLuint vao{};
	GLuint vbo{};

	void InitRenderData(Shader& shader, const GLfloat width, const GLfloat height);
};

