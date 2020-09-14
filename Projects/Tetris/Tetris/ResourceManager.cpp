#define STB_IMAGE_IMPLEMENTATION   

#include "ResourceManager.h"
#include <iostream>
#include <fstream>
#include <sstream>

std::map<std::string, Shader> ResourceManager::shaders{};
std::map<std::string, Texture2D> ResourceManager::textures{};

Shader ResourceManager::LoadShader(std::string name, const char* vShaderFile, const char* fShaderFile, const char* gShaderFile) {
	return shaders.emplace(name, LoadShaderFromFile(vShaderFile, fShaderFile, gShaderFile)).first->second;
}

Texture2D ResourceManager::LoadTexture(std::string name, const char* textureFile, bool alpha) {
	return textures.emplace(name, LoadTextureFromFile(textureFile, alpha)).first->second;

}

bool ResourceManager::ItemExists(std::string type, std::string name) {
	if (type == "texture")
		return textures.find(name) != textures.end();
	else if (type == "shaders")
		return shaders.find(name) != shaders.end();
	else {
		std::cerr << "ERROR::ITEM_EXISTS Cannot process type : " << type << '\n';
		return false;
	}
}

void ResourceManager::Clear() {
	for (auto iter : shaders)
		iter.second.Delete();
	for (auto iter : textures)
		iter.second.Delete();
}

Shader ResourceManager::LoadShaderFromFile(const char* vShaderFile, const char* fShaderFile, const char* gShaderFile) {
	std::string vertexCode{};
	std::string fragmentCode{};
	std::string geometryCode{};
	try {
		//Open files
		std::ifstream vertexShaderFile{ vShaderFile };
		std::ifstream fragmentShaderFile{ fShaderFile };
		std::stringstream vShaderStream{};
		std::stringstream fShaderStream{};

		//Read file into stream
		vShaderStream << vertexShaderFile.rdbuf();
		fShaderStream << fragmentShaderFile.rdbuf();

		//Close
		vertexShaderFile.close();
		fragmentShaderFile.close();

		//Convert stream to string
		vertexCode = vShaderStream.str();
		fragmentCode = fShaderStream.str();

		//Same if geometry
		if (gShaderFile != nullptr) {
			std::ifstream geometryShaderFile{ gShaderFile };
			std::stringstream gShaderStream{};
			gShaderStream << geometryShaderFile.rdbuf();
			geometryShaderFile.close();
			geometryCode = gShaderStream.str();
		}
	}
	catch (std::exception e) {
		std::cout << "ERROR::SHADER: Failed to read shader files" << std::endl;
	}

	const char* vShaderCode{ vertexCode.c_str() };
	const char* fShaderCode{ fragmentCode.c_str() };
	const char* gShaderCode{ nullptr };
	if (gShaderFile != nullptr)
		gShaderCode = geometryCode.c_str();

	Shader shader;
	shader.Compile(vShaderCode, fShaderCode, gShaderCode);

	return shader;
}

Texture2D ResourceManager::LoadTextureFromFile(const char* textureFile, bool alpha) {
	//Create texture
	Texture2D texture;

	//Load image
	int width{ 0 };
	int height{ 0 };
	int nbrChannels{ 0 };
	unsigned char* data{ stbi_load(textureFile, &width, &height, &nbrChannels, 0) };
	if (data) {
		//Set alpha
		if (alpha) {
			texture.SetImageFormat(GL_RGBA);
			texture.SetInternalFormat(GL_RGBA);
		}
		//Generate
		texture.Generate(width, height, data);
	}
	else
		std::cerr << "ERROR::TEXTURE Failed to load texture at path " << textureFile << '\n';


	//Free
	stbi_image_free(data);
	return texture;
}
