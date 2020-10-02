#pragma once
#include "ft2build.h"
#include FT_FREETYPE_H
#include "glad/glad.h"
#include "glm/glm.hpp"
#include <map>
#include "Shader.h"
#include "Component.h"

struct Character {
	GLuint textureId;
	glm::vec2 size;
	glm::vec2 bearing;
	GLuint advance;
};

class TextComponent : public Component {
public:
	TextComponent(glm::vec2 position, std::string text, std::string fontFamily, GLuint fontSize, glm::vec3 color, GLuint width, GLuint height);
	void Load();
	void Render() override;
	glm::vec2 GetStringSize(std::string text, GLfloat scale = 1.0f);
private:
	std::map<char, Character> characters;
	Shader textShader;
	GLuint VAO{ 0 };
	GLuint VBO{ 0 };

	glm::vec2 position{};
	std::string text{ "" };
	std::string fontFamily{ "" };
	GLuint fontSize{ 14 };
	glm::vec3 color{ glm::vec3(1.0f) };

};

