#pragma once
#include <map>
#include <string>
#include "Shader.h"
#include "Texture2D.h"

class ResourceManager
{
public:
	//Resource storage
	static std::map<std::string, Shader> shaders;
	static std::map<std::string, Texture2D> textures2D;

	//Loads and generates a shader program from file loading vertex, fragment and geometry shader source code
	static Shader& LoadShader(const std::string name, const char* vShaderFile, const char* fShaderFile, const char* gShaderFile = nullptr);
	//Loads and generates a 2D texture from file
	static Texture2D& LoadTexture2D(const std::string name, const char* file, const bool alpha);

	static Shader& GetShader(const std::string name) { return shaders.at(name); }
	static Texture2D& GetTexture2D(const std::string name) { return textures2D.at(name); }
	static void Clear();

private:
	ResourceManager() {};
	~ResourceManager() { Clear(); }

	//Loads and generates a shader from file
	static Shader& LoadShaderFromFile(const char* vShaderFile, const char* fShaderFile, const char* gShaderFile = nullptr);
	//Loads a single texture from file
	static Texture2D& LoadTextureFromFile(const char* file, const bool alpha);
};

