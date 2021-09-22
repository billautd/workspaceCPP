#include "TextRenderer.h"
#include <ft2build.h>
#include <iostream>
#include FT_FREETYPE_H

void TextRenderer::Load(const std::string font, const GLuint fontSize)
{
	characters.clear();

	//Init freetype library
	FT_Library ft;
	if (FT_Init_FreeType(&ft))
		std::cerr << "ERROR::FREETYPE : Could not init FreeType library" << std::endl;
	//Load font as face
	FT_Face face;
	if (FT_New_Face(ft, font.c_str(), 0, &face))
		std::cerr << "ERROR:FREETYPE : Failed to load font" << std::endl;

	//Set size to load glyphs at
	FT_Set_Pixel_Sizes(face, 0, fontSize);
	//Disable byte-alignment restriction
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
	//For the first 128 ascii characters, preload/compile their characters and store them
	for (GLubyte c{ 0 }; c < 128; c++) {
		//Load character glyph
		if (FT_Load_Char(face, c, FT_LOAD_RENDER)) {
			std::cerr << "ERROR::FREETYPE : Failed to load glyph" << std::endl;
			continue;
		}

		//Generate texture
		GLuint texture{};
		glGenTextures(1, &texture);
		glBindTexture(GL_TEXTURE_2D, texture);
		glTexImage2D(GL_TEXTURE_2D,
			0,
			GL_RED,
			face->glyph->bitmap.width,
			face->glyph->bitmap.rows,
			0,
			GL_RED,
			GL_UNSIGNED_BYTE,
			face->glyph->bitmap.buffer);
		//Set texture options
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		//Store character for later use
		Character character{ texture,
			glm::ivec2(face->glyph->bitmap.width, face->glyph->bitmap.rows),
			glm::ivec2(face->glyph->bitmap_left, face->glyph->bitmap_top),
			face->glyph->advance.x };
		characters.insert(std::pair<char, Character>(c, character));
	}
	glBindTexture(GL_TEXTURE_2D, 0);
	//Destroy freetype
	FT_Done_Face(face);
	FT_Done_FreeType(ft);
}


void TextRenderer::RenderText(const std::string text, GLfloat x, GLfloat y, const GLfloat scale, const glm::vec3 color)
{
	//Activate corresponding render state
	shader.Use();
	shader.SetVector3f("textColor", color);
	glActiveTexture(GL_TEXTURE0);
	glBindVertexArray(vao);
	{
		//Iterate through all characters
		std::string::const_iterator c;
		for (c = text.begin(); c != text.end(); c++) {
			Character ch{ characters[*c] };

			GLfloat xpos{ x + ch.bearing.x * scale };
			GLfloat ypos{ y + (this->characters['H'].bearing.y - ch.bearing.y) * scale };

			GLfloat w{ ch.size.x * scale };
			GLfloat h{ ch.size.y * scale };

			//Update VBo for each character
			GLfloat vertices[6][4]{
				{xpos    , ypos + h, 0.0f, 1.0f},
				{xpos + w, ypos    , 1.0f, 0.0f},
				{xpos    , ypos    , 0.0f, 0.0f},

				{xpos    , ypos + h, 0.0f, 1.0f},
				{xpos + w, ypos + h, 1.0f, 1.0f},
				{xpos + w, ypos    , 1.0f, 0.0f}
			};
			//Render glyph texture over quad
			glBindTexture(GL_TEXTURE_2D, ch.textureId);
			//Update content of VBO memory
			glBindBuffer(GL_ARRAY_BUFFER, vbo);
			glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices);
			glBindBuffer(GL_ARRAY_BUFFER, 0);
			//Render quad
			glDrawArrays(GL_TRIANGLES, 0, 6);
			//Now advance cursors for next glyph
			//Bitshift by 6 to get value in pixels 
			x += (ch.advance >> 6) * scale;
		}
	}
	glBindVertexArray(0);
	glBindTexture(GL_TEXTURE_2D, 0);
}

TextRenderer::TextRenderer(Shader& shader, const GLuint width, const GLuint height) : shader(shader)
{
	InitRenderData(shader, static_cast<GLfloat>(width), static_cast<GLfloat>(height));
}

void TextRenderer::InitRenderData(Shader& shader, const GLfloat width, const GLfloat height)
{
	//Config shader
	shader.Use();
	shader.SetMatrix4("projection", glm::ortho(0.0f, width, height, 0.0f));
	shader.SetInteger("text", 0);

	//Configure vao/vbo for texture quads
	glGenVertexArrays(1, &vao);
	glGenBuffers(1, &vbo);
	glBindVertexArray(vao);
	{
		glBindBuffer(GL_ARRAY_BUFFER, vbo);
		glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * 6 * 4, nullptr, GL_DYNAMIC_DRAW);

		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), (void*)0);

		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}
	glBindVertexArray(0);
}
