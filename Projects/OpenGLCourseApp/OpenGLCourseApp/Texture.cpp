#include "Texture.h"

Texture::~Texture() {}

int Texture::Init(const char* path) {
	data = stbi_load(path, &width, &height, &nbrChannels, 0);
	if (!data) {
		std::cerr << "Error while initialize texture data : " << path << '\n';
		return 1;
	}
	return 0;
}

void Texture::SetTextureWrap(GLuint mode) {
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, mode);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, mode);
}

void Texture::SetTextureFilter(GLuint mode) {
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, mode);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, mode);
}
