#pragma once
#include <map>
#include <string>
#include "Model.h"
#include "glad/glad.h"

class AssetManager
{
private:
	std::map<const std::string, GLuint> textures{};
	std::map<const std::string, GLuint> cubeMaps{};
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

	static const GLuint GenerateCubeMap(const std::vector<std::string> faces, const std::string directory, const GLint textureWrap = GL_REPEAT, const GLint minMagFilter = GL_LINEAR);
	const void AddCubeMap(const std::string id, const GLuint cubeMap) { cubeMaps.emplace(id, cubeMap); }
	const GLuint GetCubeMap(const std::string id) { return cubeMaps.at(id); }

	//Models
	static const Model* GenerateModel(const char* path, const std::string directory) { return new Model(directory + '/' + std::string(path)); }
	const void AddModel(const std::string id, const Model* model) { models.emplace(id, model); }
	const Model* GetModel(const std::string id) { return models.at(id); }
	const std::vector<const Model*> GetModels();

};

