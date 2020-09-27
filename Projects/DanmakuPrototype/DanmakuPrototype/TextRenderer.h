#pragma once
#include "ft2build.h"
#include FT_FREETYPE_H
#include "glad/glad.h"
#include "glm/glm.hpp"
#include <map>
#include "Shader.h"

struct Character {
	GLuint textureId;
	glm::vec2 size;
	glm::vec2 bearing;
	GLuint advance;
};

class TextRenderer {
public:
	TextRenderer(GLuint width, GLuint height);
	void Load(std::string font, GLuint pixelSize);
	void RenderText(std::string text, GLfloat x, GLfloat y, GLfloat scale = 1.0f, glm::vec3 color = glm::vec3(1.0f));
	glm::vec2 GetStringSize(std::string text, GLfloat scale = 1.0f);
private:
	std::map<char, Character> characters;
	Shader textShader;
	GLuint VAO{ 0 };
	GLuint VBO{ 0 };

};

