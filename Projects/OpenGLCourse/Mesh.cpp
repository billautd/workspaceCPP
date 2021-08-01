#include "Mesh.h"

void Mesh::Draw(const Shader& shader) const {
	GLuint diffuseNbr{ 1 };
	GLuint specularNbr{ 1 };
	for (size_t i{ 0 }; i < textures.size(); i++) {
		//Bind to proper texture
		glActiveTexture(GL_TEXTURE0 + static_cast<GLenum>(i));

		//Retrieve texture number
		std::string number;
		std::string type{ textures.at(i).type };
		if (type == "texture_diffuse")
			number = std::to_string(diffuseNbr++);
		else if (type == "texture_specular")
			number = std::to_string(specularNbr++);

		shader.SetInt("material." + type + number, static_cast<int>(i));
		glBindTexture(GL_TEXTURE_2D, textures.at(i).id);
	}
	glActiveTexture(GL_TEXTURE0);

	//Draw mesh
	glBindVertexArray(vao);
	{
		glDrawElements(GL_TRIANGLES, static_cast<GLsizei>(indices.size()), GL_UNSIGNED_INT, 0);
	}
	glBindVertexArray(0);
}

void Mesh::SetupMesh() {
	glGenVertexArrays(1, &vao);
	glGenBuffers(1, &vbo);
	glGenBuffers(1, &ebo);

	glBindVertexArray(vao);
	{
		glBindBuffer(GL_ARRAY_BUFFER, vbo);
		glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), &vertices.at(0), GL_STATIC_DRAW);

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(GLuint), &indices.at(0), GL_STATIC_DRAW);
	}

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);

	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, texCoords));

	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, normal));
}