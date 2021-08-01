#pragma once
#include "glm.hpp"
#include <vector>
#include "glad/glad.h"
#include <string>
#include "Shader.h"

struct Vertex {
	glm::vec3 position;
	glm::vec3 normal;
	glm::vec2 texCoords;
};

struct Texture {
	GLuint id;
	std::string type;
	std::string path;
};

class Mesh {
private:
	std::vector<Vertex> vertices;
	std::vector<GLuint> indices;
	std::vector<Texture> textures;

	GLuint vao, vbo, ebo;
	void SetupMesh();

public:
	Mesh(std::vector<Vertex> vertices, std::vector<GLuint> indices, std::vector<Texture> textures) : vertices(vertices), indices(indices), textures(textures) {
		SetupMesh();
	}
	void Draw(const Shader& shader) const;
};