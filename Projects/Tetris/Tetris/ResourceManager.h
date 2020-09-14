#pragma once
#include "Texture2D.h"
#include "Shader.h"
#include <map>
#include <string>
#include "stb_image.h"


class ResourceManager {
public:
	//Loads and generates shader program from file
	static Shader LoadShader(std::string name, const char* vShaderFile, const char* fShaderFile, const char* gShaderFile = nullptr);
	static Shader& GetShader(std::string name) {
		return shaders.at(name);
	};

	//Loads and generates texture from image file
	static Texture2D LoadTexture(std::string name, const char* textureFile, bool alpha);
	static Texture2D& GetTexture(std::string name) {
		return textures.at(name);
	};

	//Check if item is in map before using it
	static bool ItemExists(std::string type, std::string name);

	//Clear everything
	static void Clear();

private:
	//Private constructor for no instanciation
	ResourceManager() = default;

	//Loads and generates shader from file
	static Shader LoadShaderFromFile(const char* vShaderFile, const char* fShaderFile, const char* gShaderFile = nullptr);
	static Texture2D LoadTextureFromFile(const char* textureFile, bool alpha);

	static std::map<std::string, Shader> shaders;
	static std::map<std::string, Texture2D> textures;

};

