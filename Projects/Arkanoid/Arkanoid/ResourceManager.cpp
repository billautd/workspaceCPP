#define STB_IMAGE_IMPLEMENTATION    
#include "ResourceManager.h"

std::map<std::string, Texture2D> ResourceManager::textures;
std::map<std::string, Shader> ResourceManager::shaders;

Shader ResourceManager::LoadShader(const char* vShaderFile, const char* fShaderFile, const char* gShaderFile, std::string name) {
	//First = iterator to value inserted
	//first->second = shader
	return (shaders.emplace(name, LoadShaderFromFile(vShaderFile, fShaderFile, gShaderFile))).first->second;
}

Texture2D ResourceManager::LoadTexture(const char* file, bool alpha, std::string name) {
	//First = iterator to value inserted
	//first->second = texture
	return (textures.emplace(name, LoadTextureFromFile(file, alpha))).first->second;
}

void ResourceManager::Clear() {
	for (auto iter : shaders)
		iter.second.Delete();
	for (auto iter : textures)
		iter.second.Delete();
}

Shader ResourceManager::LoadShaderFromFile(const char* vShaderFile, const char* fShaderFile, const char* gShaderFile) {
	//Retrieve source code from file
	std::string vertexCode{};
	std::string fragmentCode{};
	std::string geometryCode{};
	try {
		//Open files
		std::ifstream vertexShaderFile{ vShaderFile };
		std::ifstream fragmentShaderFile{ fShaderFile };
		std::stringstream vShaderStream{};
		std::stringstream fShaderStream{};
		//Read file buffer into stream
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
	//Create shader from source
	Shader shader;
	shader.Compile(vShaderCode, fShaderCode, gShaderCode);

	return shader;
}

Texture2D ResourceManager::LoadTextureFromFile(const char* file, bool alpha) {
	//Create texture
	Texture2D texture;

	//Load image
	int width, height, nbrChannels;
	unsigned char* data{ stbi_load(file, &width, &height, &nbrChannels, 0) };
	if (data) {
		//Set alpha
		if (alpha) {
			texture.SetInternalFormat(GL_RGBA);
			texture.SetImageFormat(GL_RGBA);
		}
		//Generate
		texture.Generate(width, height, data);
	}
	else
		std::cout << "Texture failed to load at path: " << file << std::endl;

	//Free
	stbi_image_free(data);
	return texture;
}