#pragma once
#include "Shader.h"
#include "Texture2D.h"
#include "SDL_mixer.h"
#include <string>
#include "stb_image.h"
#include <map>

struct Character {
	GLuint textureId;
	glm::vec2 size;
	glm::vec2 bearing;
	GLuint advance;
};

typedef std::map<char, Character> Font;

class ResourceManager
{
public:
	//Loads and generates shader program from file
	static Shader LoadShader(const char* vShaderFile, const char* fShaderFile, const char* gShaderFile, std::string name);
	static Shader& GetShader(std::string name);
	//Loads and generates texture from file
	static Texture2D LoadTexture(const char* file, bool alpha, std::string name);
	static Texture2D& GetTexture(std::string name);
	//Loads music
	static Mix_Music* LoadMusic(const char* file, std::string name);
	static Mix_Music* GetMusic(std::string name);
	//Loads sounds
	static Mix_Chunk* LoadChunk(const char* file, std::string name);
	static Mix_Chunk* GetChunk(std::string name);
	//Loads fonts
	static Font LoadFont(const char* file, std::string name, GLuint fontSize);
	static Font GetFont(std::string name);
	//Properly re-allocate all loaded resources
	static void ClearData();
private:
	//Private Constructor for no instanciation
	ResourceManager() = default;
	//Loads and generates shader from file
	static Shader LoadShaderFromFile(const char* vShaderFile, const char* fShaderFile, const char* gShaderFile = nullptr);
	//Loads a single texture from file
	static Texture2D LoadTextureFromFile(const char* file, bool alpha);
	//Loads a signle font from file
	static Font LoadFontFromFile(const char* file, GLuint fontSize);


	//Resource storage
	static std::map<std::string, Shader> shaders;
	static std::map<std::string, Texture2D> textures;
	static std::map<std::string, Mix_Music*> musics;
	static std::map<std::string, Mix_Chunk*> chunks;
	static std::map <std::string, Font> fonts;
};
