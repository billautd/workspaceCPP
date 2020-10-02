#include "TextComponent.h"
#include "ResourceManager.h"
#include <iostream>
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

TextComponent::TextComponent(glm::vec2 position, std::string text, std::string fontFamily, GLuint fontSize, glm::vec3 color, GLuint width, GLuint height)
	: position(position), text(text), fontFamily(fontFamily), color(color), fontSize(fontSize) {
	this->textShader = ResourceManager::GetShader("TextRendering");
	textShader.Use();
	this->textShader.SetMatrix4("projection", glm::ortho(0.0f, static_cast<GLfloat>(width), static_cast<GLfloat>(height), 0.0f));
	this->textShader.SetInteger("text", 0);

	//Configure VAO/VBO
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glBindVertexArray(VAO); {
		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * 6 * 4, nullptr, GL_DYNAMIC_DRAW);

		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), 0);

		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}
	glBindVertexArray(0);
}

void TextComponent::Load() {
	//Clear previously loaded characters
	characters.clear();

	//Init freetype
	FT_Library ft;
	if (FT_Init_FreeType(&ft))
		std::cout << "ERROR::FREETYPE: Could not init FreeType Library\n";

	//Load font
	FT_Face face;
	if (FT_New_Face(ft, fontFamily.c_str(), 0, &face))
		std::cout << "ERROR::FREETYPE: Failed to load font\n";

	//Set size for glyphs
	FT_Set_Pixel_Sizes(face, 0, fontSize);

	//Disable byte-alignment
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

	//Pre-load/compile characters
	for (GLubyte c = 0; c < 128; c++) {
		if (FT_Load_Char(face, c, FT_LOAD_RENDER)) {
			std::cerr << "ERROR::FREETYTPE: Failed to load Glyph\n";
			continue;
		}

		//Generature texture
		GLuint texture{ 0 };
		glGenTextures(1, &texture);
		glBindTexture(GL_TEXTURE_2D, texture);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RED, face->glyph->bitmap.width,
			face->glyph->bitmap.rows, 0, GL_RED, GL_UNSIGNED_BYTE, face->glyph->bitmap.buffer);

		//Texture params
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		//Store character
		Character character{ texture, glm::vec2(face->glyph->bitmap.width, face->glyph->bitmap.rows),
			glm::vec2(face->glyph->bitmap_left, face->glyph->bitmap_top), static_cast<GLuint>(face->glyph->advance.x) };

		characters.emplace(c, character);
	}
	glBindTexture(GL_TEXTURE_2D, 0);

	//Destroy Freetype
	FT_Done_Face(face);
	FT_Done_FreeType(ft);


}

void TextComponent::Render() {
	this->textShader.Use();
	this->textShader.SetVector3f("textColor", color);
	glActiveTexture(GL_TEXTURE0);
	glBindVertexArray(VAO); {
		//Iterate through characters
		std::string::const_iterator c;
		for (c = text.begin(); c != text.end(); c++) {
			Character ch{ characters.at(*c) };

			GLfloat xpos{ position.x + ch.bearing.x };
			GLfloat ypos{ position.y + (characters.at('H').bearing.y - ch.bearing.y) };

			GLfloat w{ ch.size.x };
			GLfloat h{ ch.size.y };

			//Update VBO
			GLfloat vertices[6][4] = {
				{xpos, ypos + h, 0.0f, 1.0f},
				{xpos + w, ypos, 1.0f, 0.0f},
				{xpos, ypos, 0.0f, 0.0f},

				{xpos, ypos + h, 0.0f, 1.0f},
				{xpos + w, ypos + h, 1.0f, 1.0f},
				{xpos + w, ypos, 1.0f, 0.0f}
			};

			//Render texture 
			glBindTexture(GL_TEXTURE_2D, ch.textureId);

			//Update VBO memory
			glBindBuffer(GL_ARRAY_BUFFER, VBO);
			glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices);
			glBindBuffer(GL_ARRAY_BUFFER, 0);

			//Render quad
			glDrawArrays(GL_TRIANGLES, 0, 6);

			//Advance cursor for next glyph
			position.x += (ch.advance >> 6);
		}
	}
	glBindVertexArray(0);
	glBindTexture(GL_TEXTURE_2D, 0);
}

glm::vec2 TextComponent::GetStringSize(std::string text, GLfloat scale) {
	glm::vec2 size{};
	std::string::const_iterator c;
	for (c = text.begin(); c != text.end(); c++) {
		Character ch{ characters.at(*c) };
		size.x += (ch.advance >> 6) * scale;
		if (ch.size.y * scale > size.y)
			size.y = ch.size.y * scale;
	}
	return size;
}