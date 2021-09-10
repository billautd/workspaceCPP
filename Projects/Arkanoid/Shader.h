#pragma once
#include "glad/glad.h"
#include "glm.hpp"
#include <string>
#include "gtc/type_ptr.hpp"

class Shader
{
public:
	GLuint id{};

	Shader() {};
	~Shader() {};

	//Sets current shader as active
	const Shader& Use() const;
	//Compiles shader from given source code
	void Compile(const char* vertexSource, const char* fragmentSouce, const char* geometrySource = nullptr);
	//Utility functions
	void    SetFloat(const char* name, const GLfloat value) { glUniform1f(glGetUniformLocation(id, name), value); }
	void    SetInteger(const char* name, const GLint value) { glUniform1i(glGetUniformLocation(id, name), value); }
	void    SetVector2f(const char* name, const GLfloat x, const GLfloat y) { glUniform2f(glGetUniformLocation(id, name), x, y); }
	void    SetVector2f(const char* name, const glm::vec2 & value) { glUniform2f(glGetUniformLocation(id, name), value.x, value.y);}
	void    SetVector3f(const char* name, const GLfloat x, const GLfloat y, const GLfloat z) {glUniform3f(glGetUniformLocation(id, name), x, y, z);}
	void    SetVector3f(const char* name, const glm::vec3& value) {glUniform3f(glGetUniformLocation(id, name), value.x, value.y, value.z);}
	void    SetVector4f(const char* name, const GLfloat x, const GLfloat y, const GLfloat z, const GLfloat w) {glUniform4f(glGetUniformLocation(id, name), x, y, z, w);}
	void    SetVector4f(const char* name, const glm::vec4& value) {glUniform4f(glGetUniformLocation(id, name), value.x, value.y, value.z, value.w);}
	void    SetMatrix4(const char* name, const glm::mat4& value) {glUniformMatrix4fv(glGetUniformLocation(id, name), 1, false, glm::value_ptr(value));}

private:
	//Checks if compilation or linking failed and if so, print error logs
	void CheckCompileErrors(const GLuint object, const std::string type) const;
};

