#pragma once
#include "Mesh.h"
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

class Model
{
private:
	std::vector<const Mesh*> meshes;
	std::vector<Texture> loadedTextures;
	std::string directory;

	void LoadModel(const std::string path);
	void ProcessNode(const aiNode* node, const aiScene* scene);
	const Mesh* ProcessMesh(const aiMesh* mesh, const aiScene* scene);
	const std::vector<Texture> LoadMaterialTextures(const aiMaterial* material, const aiTextureType type, const std::string typeName);

public:
	Model(const char* path) { LoadModel(std::string(path)); }

	void Draw(const Shader& shader) const;
};

