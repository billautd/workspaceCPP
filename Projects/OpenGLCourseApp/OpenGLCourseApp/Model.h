#pragma once
#include "Shader.h"
#include <vector>
#include "Mesh.h"
#include "stb_image.h"

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>


class Model {
public:
	Model(std::string path, GLboolean gamma = false) {
		LoadModel(path);
	}
	void Draw(Shader& shader);

	static GLuint TextureFromFile(const char* path, const std::string& directory, bool gamma = false);
private:
	std::vector<Mesh> meshes{};
	std::string directory{};
	std::vector<Texture> texturesLoaded;

	void LoadModel(std::string path);
	void ProcessNode(aiNode* node, const aiScene* scene);
	Mesh ProcessMesh(aiMesh* mesh, const aiScene* scene);
	std::vector<Texture> LoadMaterialTextures(aiMaterial* mat, aiTextureType type, std::string typeName);
};

