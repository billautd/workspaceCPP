#pragma once
#include "glad/glad.h"
#include <string>
#include "glm/glm.hpp"

class Shader {
public:
	Shader() = default;
	~Shader() = default;

	//Use current shader
	Shader& Use();
	//Compile
	void Compile(const char* vSource, const char* fSource, const char* gSource = nullptr);
	//Deletes program
	void Delete();

	//Utility
	GLuint GetId() { return this->id; }
	void SetFloat(const char* name, GLfloat value);
	void SetInteger(const char* name, GLint value);
	void SetVector2f(const char* name, glm::vec2 value);
	void SetVector2f(const char* name, GLfloat x, GLfloat y);
	void SetVector3f(const char* name, glm::vec3 value);
	void SetVector3f(const char* name, GLfloat x, GLfloat y, GLfloat z);
	void SetVector4f(const char* name, glm::vec4 value);
	void SetVector4f(const char* name, GLfloat x, GLfloat y, GLfloat z, GLfloat w);
	void SetMatrix4(const char* name, glm::mat4 value);

private:
	GLuint id{ 0 };
	void CheckCompileErrors(GLuint object, std::string type);
};

