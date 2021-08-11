#include "AssetManager.h"
#include "stb_image.h"
#include <iostream>

void AssetManager::ClearData() {
	textures.clear();
	models.clear();
}

const GLuint AssetManager::GenerateTexture(const char* path, const std::string directory, const GLint textureWrap, const GLint minMagFilter) {
	const std::string filename{ directory + '/' + std::string(path) };

	GLuint texture;
	glGenTextures(1, &texture);

	int width, height, nbrChannels;
	unsigned char* data{ stbi_load(filename.c_str(), &width, &height, &nbrChannels, 0) };
	if (data) {
		GLenum format{};
		if (nbrChannels == 1)
			format = GL_RED;
		else if (nbrChannels == 3)
			format = GL_RGB;
		else if (nbrChannels == 4)
			format = GL_RGBA;

		glBindTexture(GL_TEXTURE_2D, texture);
		{
			glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
			glGenerateMipmap(GL_TEXTURE_2D);

			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, textureWrap);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, textureWrap);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, minMagFilter);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, minMagFilter);
		}

	}
	else {
		std::cerr << "Error loading texture at " << filename << '\n';
	}

	stbi_image_free(data);
	return texture;
}

const GLuint AssetManager::GenerateCubeMap(const std::vector<std::string> faces, const std::string directory, const GLint textureWrap, const GLint minMagFilter) {
	GLuint textureId;
	glGenTextures(1, &textureId);
	glBindTexture(GL_TEXTURE_CUBE_MAP, textureId); 

	int width, height, nbrChannels;
	for(size_t i{0}; i < faces.size(); i++)
	{
		const std::string filename{ directory + '/' + faces.at(i) };
		unsigned char* data{ stbi_load(filename.c_str(), &width, &height, &nbrChannels, 0) };
		if (data) {
			GLenum format{};
			if (nbrChannels == 1)
				format = GL_RED;
			else if (nbrChannels == 3)
				format = GL_RGB;
			else if (nbrChannels == 4)
				format = GL_RGBA;

			glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
			stbi_image_free(data);
		}
	}

	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, minMagFilter);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, minMagFilter);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, textureWrap);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, textureWrap);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, textureWrap);

	return textureId;
}

const std::vector<const Model*> AssetManager::GetModels() {
	std::vector<const Model*> modelList;
	for (auto& pair : models)
		modelList.push_back(pair.second);

	return modelList;

}