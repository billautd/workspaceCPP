#include "TextComponent.h"
#include "ResourceManager.h"
#include <iostream>
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp" 

TextComponent::TextComponent(std::string text, std::string font, GLuint fontSize, glm::vec3 color)
	: text(text), font(font), color(color), fontSize(fontSize) {
	this->textShader = ResourceManager::GetShader("TextRendering");
	textShader.Use();
	this->textShader.SetMatrix4("projection", glm::ortho(0.0f, static_cast<GLfloat>(transform->GetWidth()), static_cast<GLfloat>(transform->GetHeight()), 0.0f));
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



void TextComponent::Render() {
	this->textShader.Use();
	this->textShader.SetVector3f("textColor", color);
	Font currentFont{ ResourceManager::GetFont(font) };
	glm::vec2 position{ transform->GetPosition() };
	glActiveTexture(GL_TEXTURE0);
	glBindVertexArray(VAO); {
		//Iterate through characters
		std::string::const_iterator c;
		for (c = text.begin(); c != text.end(); c++) {

			Character ch{ currentFont.at(*c) };

			GLfloat xpos{ position.x + ch.bearing.x };
			GLfloat ypos{ position.y + (currentFont.at('H').bearing.y - ch.bearing.y) };

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
	Font currentFont{ ResourceManager::GetFont(font) };
	for (c = text.begin(); c != text.end(); c++) {
		Character ch{ currentFont.at(*c) };
		size.x += (ch.advance >> 6) * scale;
		if (ch.size.y * scale > size.y)
			size.y = ch.size.y * scale;
	}
	return size;
}