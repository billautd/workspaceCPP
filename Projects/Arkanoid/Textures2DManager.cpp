#define STB_IMAGE_IMPLEMENTATION
#include "Textures2DManager.h"
#include "stb_image.h"
#include <iostream>

std::map<std::string, Texture2D> Textures2DManager::textures2D{};

const Texture2D& Textures2DManager::Generate(const std::string name, const std::string path)
{
	Texture2D* texture{ new Texture2D() };
	glGenTextures(1, &(texture->id));

	int nbrChannels;
	unsigned char* data{ stbi_load(path.c_str(), &texture->width, &texture->height, &nbrChannels, 0) };

	if (data) {
		if (nbrChannels == 1) {
			texture->imageFormat = GL_RED;
			texture->internalFormat = GL_RED;
		}
		else if (nbrChannels == 3) {
			texture->imageFormat = GL_RGB;
			texture->internalFormat = GL_RGB;
		}
		else if (nbrChannels == 4) {
			texture->imageFormat = GL_RGBA;
			texture->internalFormat = GL_RGBA;
		}

		glBindTexture(GL_TEXTURE_2D, texture->id);
		{
			glTexImage2D(GL_TEXTURE_2D, 0, texture->internalFormat, texture->width, texture->height, 0, texture->imageFormat, GL_UNSIGNED_BYTE, data);
			glGenerateMipmap(GL_TEXTURE_2D);

			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, texture->wrapS);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, texture->wrapT);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, texture->filterMin);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, texture->filterMag);
		}
		glBindTexture(GL_TEXTURE_2D, 0);
		textures2D[name] = *texture;
	}

	else {
		std::cerr << "Error loading texture at " << path << '\n';
	}
	return *texture;
}
