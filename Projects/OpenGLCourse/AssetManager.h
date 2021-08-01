#pragma once
#include <map>
#include <string>
#include "Model.h"
#include "glad/glad.h"

class AssetManager
{
private:
	std::map<const std::string, GLuint> textures{};
	std::map<const std::string, const Model*> models{};
public:
	~AssetManager() {
		ClearData();
	}

	void ClearData();

	//Textures
	static const GLuint GenerateTexture(const char* path, const std::string directory, const GLint textureWrap = GL_REPEAT, const GLint minMagFilter = GL_LINEAR);
	const void AddTexture(const std::string id, const GLuint texture) { textures.emplace(id, texture); }
	const GLuint GetTexture(const std::string id) { return textures.at(id); }

	//Models
	static const Model* GenerateModel(const std::string path) { return new Model(path.c_str()); }
	const void AddModel(const std::string id, const Model* model) { models.emplace(id, model); }
	const Model* GetModel(const std::string id) { return models.at(id); }
	const std::vector<const Model*> GetModels();

};

