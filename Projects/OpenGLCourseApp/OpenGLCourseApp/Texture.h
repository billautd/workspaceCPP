#pragma once

#include <glad\glad.h>
#include <iostream>
#include "stb_image.h"

class Texture {
public:
	Texture() = default;
	~Texture();

	GLint GetWidth() { return width; }
	GLint GetHeight() { return height; }
	GLint GetNbrChannels() { return nbrChannels; }
	GLubyte* GetData() { return data; }

	int Init(const char* path, GLuint* id, GLuint rgbMode);
	void FreeImage() { stbi_image_free(data); }

	static void SetTextureWrap(GLuint mode);
	static void SetTextureFilter(GLuint mode);

private:
	GLint width{ 0 };
	GLint height{ 0 };
	GLint nbrChannels{ 0 };
	GLubyte* data{ nullptr };
};

