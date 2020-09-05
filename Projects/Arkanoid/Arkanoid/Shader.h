#pragma once
#include "glad/glad.h"
#include "glm/glm.hpp"
#include "glm/gtc/type_ptr.hpp"
#include <string>
#include <iostream>


class Shader {
public:
	// C/D
	Shader() = default;
	~Shader() = default;

	//Sets current shader as active
	Shader& Use();
	//Compiles shader from source code
	void Compile(const char* vertexSource, const char* fragmentSource, const char* geometrySource = nullptr);
	//Deletes program
	void Delete();

	//Utility
	GLuint GetId() { return this->id; }
	void SetFloat(const char* name, GLfloat value, bool useShader = false);
	void SetInteger(const char* name, GLint value, bool useShader = false);
	void SetVector2f(const char* name, glm::vec2 value, bool useShader = false);
	void SetVector2f(const char* name, GLfloat x, GLfloat y, bool useShader = false);
	void SetVector3f(const char* name, glm::vec3 value, bool useShader = false);
	void SetVector3f(const char* name, GLfloat x, GLfloat y, GLfloat z, bool useShader = false);
	void SetVector4f(const char* name, glm::vec4 value, bool useShader = false);
	void SetVector4f(const char* name, GLfloat x, GLfloat y, GLfloat z, GLfloat w, bool useShader = false);
	void SetMatrix4(const char* name, glm::mat4 value, bool useShader = false);
private:
	GLuint id{ 0 };
	void CheckCompileErrors(GLuint object, std::string type);
};

