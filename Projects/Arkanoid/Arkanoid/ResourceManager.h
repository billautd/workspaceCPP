#pragma once
#include "Shader.h"
#include "stb_image.h"
#include "Texture2D.h"
#include <string>
#include <fstream>
#include <sstream>
#include <map>

class ResourceManager {
public:
	//Loads and generates shader program from file
	static Shader LoadShader(const char* vShaderFile, const char* fShaderFile, const char* gShaderFile, std::string name);
	static Shader& GetShader(std::string name) { return shaders.at(name); }
	//Loads and generates texture from file
	static Texture2D LoadTexture(const char* file, bool alpha, std::string name);
	static Texture2D& GetTexture(std::string name) { return textures.at(name); }
	//Properly re-allocate all loaded resources
	static void Clear();

private:
	//Private Constructor for no instanciation
	ResourceManager() = default;
	//Loads and generates shader from file
	static Shader LoadShaderFromFile(const char* vShaderFile, const char* fShaderFile, const char* gShaderFile = nullptr);
	//Loads a single texture from file
	static Texture2D LoadTextureFromFile(const char* file, bool alpha);


	//Resource storage
	static std::map<std::string, Shader> shaders;
	static std::map<std::string, Texture2D> textures;
};

