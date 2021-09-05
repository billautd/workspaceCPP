#include "Textures2DManager.h"

std::map<std::string, Texture2D> Textures2DManager::textures2D{};

const Texture2D& Textures2DManager::Generate(const std::string name, const GLuint width, const GLuint height, const unsigned char* data)
{
	Texture2D* texture{ new Texture2D() };
	glGenTextures(1, &(texture->id));
	texture->width = width;
	texture->height = height;

	glBindTexture(GL_TEXTURE_2D, texture->id);
	{
		glTexImage2D(GL_TEXTURE_2D, 0, texture->internalFormat, width, height, 0, texture->imageFormat, GL_UNSIGNED_BYTE, data);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, texture->wrapS);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, texture->wrapT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, texture->filterMin);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, texture->filterMag);
	}
	glBindTexture(GL_TEXTURE_2D, 0);
	textures2D.at(name) = *texture;

	return *texture;
}
