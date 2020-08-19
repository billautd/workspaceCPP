#pragma once
#include "glm/glm.hpp"
#include "glad/glad.h"
#include <string>
#include <vector>
#include "Shader.h"

struct Vertex {
	glm::vec3 position;
	glm::vec3 normal;
	glm::vec2 texturePos;
};

struct Texture {
	GLuint id;
	std::string type;
	std::string path;  // we store the path of the texture to compare with other textures
};

class Mesh {
public:
	Mesh(std::vector<Vertex> cVertices, std::vector<GLuint> cIndices, std::vector<Texture> cTextures);
	void Draw(Shader& shader);
private:
	std::vector<Vertex> vertices;
	std::vector<GLuint> indices;
	std::vector<Texture> textures;

	GLuint VAO{ 0 };
	GLuint VBO{ 0 };
	GLuint EBO{ 0 };

	void SetupMesh();
};

