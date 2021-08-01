#include "Model.h"
#include <iostream>
#include "AssetManager.h"

void Model::LoadModel(const std::string path) {
	Assimp::Importer importer;
	const aiScene* scene{ importer.ReadFile(path, aiProcess_Triangulate | aiProcess_FlipUVs) };

	if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode) {
		std::cerr << "Error loading ASSIMP model at" << path << '\n';
		std::cerr << importer.GetErrorString() << '\n';
		return;
	}

	directory = path.substr(0, path.find_last_of('/'));
	ProcessNode(scene->mRootNode, scene);
}

void Model::ProcessNode(const aiNode* node, const aiScene* scene) {
	//Process all meshes in node
	for (GLuint i{ 0 }; i < node->mNumMeshes; i++) {
		const aiMesh* mesh{ scene->mMeshes[node->mMeshes[i]] };
		meshes.push_back(ProcessMesh(mesh, scene));
	}
	//Do the same for each of the node's children
	for (GLuint i{ 0 }; i < node->mNumChildren; i++)
		ProcessNode(node->mChildren[i], scene);

}

const Mesh* Model::ProcessMesh(const aiMesh* mesh, const aiScene* scene) {

	std::vector<Vertex> vertices;
	std::vector<GLuint> indices;
	std::vector<Texture> textures;

	//Process vertices
	for (GLuint i{ 0 }; i < mesh->mNumVertices; i++) {
		Vertex vertex{
			glm::vec3(mesh->mVertices[i].x,
				mesh->mVertices[i].y,
				mesh->mVertices[i].z),
			glm::vec3(mesh->mNormals[i].x,
				mesh->mNormals[i].y,
				mesh->mNormals[i].z),
			glm::vec2(0.0f)
		};

		//If texture exists
		if (mesh->mTextureCoords[0]) {
			vertex.texCoords = glm::vec2(mesh->mTextureCoords[0][i].x,
				mesh->mTextureCoords[0][i].y);
		}
		vertices.push_back(vertex);
	}

	//Process indices
	for (GLuint i{ 0 }; i < mesh->mNumFaces; i++) {
		const aiFace& face{ mesh->mFaces[i] };
		for (GLuint j{ 0 }; j < face.mNumIndices; j++)
			indices.push_back(face.mIndices[j]);
	}

	//Process material
	if (mesh->mMaterialIndex >= 0) {
		const aiMaterial* material{ scene->mMaterials[mesh->mMaterialIndex] };
		std::vector<Texture> diffuseMaps = LoadMaterialTextures(material, aiTextureType_DIFFUSE, "texture_diffuse");
		textures.insert(textures.end(), diffuseMaps.begin(), diffuseMaps.end());
		std::vector<Texture> specularMaps = LoadMaterialTextures(material, aiTextureType_SPECULAR, "texture_specular");
		textures.insert(textures.end(), specularMaps.begin(), specularMaps.end());
	}

	return new Mesh(vertices, indices, textures);
}

const std::vector<Texture> Model::LoadMaterialTextures(const aiMaterial* material, const aiTextureType type, const std::string typeName) {
	std::vector<Texture> textures;
	for (GLuint i{ 0 }; i < material->GetTextureCount(type); i++) {
		aiString str;
		material->GetTexture(type, i, &str);

		//Check if texture is not already loaded
		GLboolean skip{ false };
		for (const Texture& loadedTexture : loadedTextures) {
			if (std::strcmp(loadedTexture.path.data(), str.C_Str()) == 0) {
				textures.push_back(loadedTexture);
				skip = true;
				break;
			}
		}
		//If texture not already loaded, add it
		if (!skip) {
			Texture texture{
				AssetManager::GenerateTexture(str.C_Str(), directory),
				typeName,
				std::string(str.C_Str())
			};
			textures.push_back(texture);
			loadedTextures.push_back(texture);
		}
	}
	return textures;
}

void Model::Draw(const Shader& shader) const {
	for (const Mesh* mesh : meshes)
		mesh->Draw(shader);
}
