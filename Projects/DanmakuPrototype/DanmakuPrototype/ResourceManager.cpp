#define STB_IMAGE_IMPLEMENTATION 
#include "ft2build.h"
#include FT_FREETYPE_H
#include "ResourceManager.h"
#include <fstream>
#include <sstream>


std::map<std::string, Texture2D> ResourceManager::textures;
std::map<std::string, Shader> ResourceManager::shaders;
std::map<std::string, Mix_Music*> ResourceManager::musics;
std::map<std::string, Mix_Chunk*> ResourceManager::chunks;
std::map<std::string, Font> ResourceManager::fonts;

Shader ResourceManager::LoadShader(const char* vShaderFile, const char* fShaderFile, const char* gShaderFile, std::string name) {
	//First = iterator to value inserted
	//first->second = shader
	return (shaders.emplace(name, LoadShaderFromFile(vShaderFile, fShaderFile, gShaderFile))).first->second;
}

Shader& ResourceManager::GetShader(std::string name) {
	return shaders.at(name);
}

Texture2D ResourceManager::LoadTexture(const char* file, bool alpha, std::string name) {
	//First = iterator to value inserted
	//first->second = texture
	return (textures.emplace(name, LoadTextureFromFile(file, alpha))).first->second;
}

Texture2D& ResourceManager::GetTexture(std::string name) {
	return textures.at(name);
}

void ResourceManager::ClearData() {
	for (auto iter : shaders)
		iter.second.Delete();
	for (auto iter : textures)
		iter.second.Delete();
}

Mix_Music* ResourceManager::LoadMusic(const char* file, std::string name) {
	Mix_Music* music = Mix_LoadMUS(file);
	if (music != nullptr)
		return (musics.emplace(name, music)).first->second;
	else {
		std::cerr << Mix_GetError() << "Error while loading music : " << file << '\n';
		return nullptr;
	}
}

Mix_Music* ResourceManager::GetMusic(std::string name) {
	return musics.at(name);
}

Mix_Chunk* ResourceManager::LoadChunk(const char* file, std::string name) {
	Mix_Chunk* chunk = Mix_LoadWAV(file);
	if (chunk != nullptr)
		return (chunks.emplace(name, chunk)).first->second;
	else {
		std::cerr << Mix_GetError() << "Error while loading chunk : " << file << '\n';
		return nullptr;
	}
}

Mix_Chunk* ResourceManager::GetChunk(std::string name) {
	return chunks.at(name);
}

Font ResourceManager::LoadFont(const char* file, std::string name, GLuint fontSize) {
	//First = iterator to value inserted
	//first->second = texture
	return (fonts.emplace(name, LoadFontFromFile(file, fontSize))).first->second;
}

Font ResourceManager::GetFont(std::string name) {
	return fonts.at(name);
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

Font ResourceManager::LoadFontFromFile(const char* file, GLuint fontSize) {
	Font font;

	//Init freetype
	FT_Library ft;
	if (FT_Init_FreeType(&ft))
		std::cout << "ERROR::FREETYPE: Could not init FreeType Library\n";

	//Load font
	FT_Face face;
	if (FT_New_Face(ft, file, 0, &face))
		std::cout << "ERROR::FREETYPE: Failed to load font\n";

	//Set size for glyphs
	FT_Set_Pixel_Sizes(face, 0, fontSize);

	//Disable byte-alignment
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

	//Pre-load/compile characters
	for (GLubyte c = 0; c < 128; c++) {
		if (FT_Load_Char(face, c, FT_LOAD_RENDER)) {
			std::cerr << "ERROR::FREETYTPE: Failed to load Glyph\n";
			continue;
		}

		//Generature texture
		GLuint texture{ 0 };
		glGenTextures(1, &texture);
		glBindTexture(GL_TEXTURE_2D, texture);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RED, face->glyph->bitmap.width,
			face->glyph->bitmap.rows, 0, GL_RED, GL_UNSIGNED_BYTE, face->glyph->bitmap.buffer);

		//Texture params
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		//Store character
		Character character{ texture, glm::vec2(face->glyph->bitmap.width, face->glyph->bitmap.rows),
			glm::vec2(face->glyph->bitmap_left, face->glyph->bitmap_top), static_cast<GLuint>(face->glyph->advance.x) };

		font.emplace(c, character);
	}
	glBindTexture(GL_TEXTURE_2D, 0);

	//Destroy Freetype
	FT_Done_Face(face);
	FT_Done_FreeType(ft);

	return font;
}
