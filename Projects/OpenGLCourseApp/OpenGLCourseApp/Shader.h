#pragma once
#include "glad/glad.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include "glm/gtc/type_ptr.hpp"

class Shader {
public:
	Shader() = default;
	~Shader() = default;

	void Use() { glUseProgram(programID); }
	void SetBool(const std::string& name, GLboolean value) {
		glUniform1i(glGetUniformLocation(programID, name.c_str()), (int)value);
	};
	void SetInt(const std::string& name, GLint value) {
		glUniform1i(glGetUniformLocation(programID, name.c_str()), value);
	};
	void SetFloat(const std::string& name, GLfloat value) {
		glUniform1f(glGetUniformLocation(programID, name.c_str()), value);
	};
	void SetMat4f(const std::string& name, glm::mat4 value) {
		glUniformMatrix4fv(glGetUniformLocation(programID, name.c_str()), 1, GL_FALSE, glm::value_ptr(value));
	};
	void SetVec3(const std::string& name, GLfloat x, GLfloat y, GLfloat z) {
		glUniform3fv(glGetUniformLocation(programID, name.c_str()), 1, glm::value_ptr(glm::vec3(x, y, z)));
	}
	void SetVec3(const std::string& name, glm::vec3 value) {
		glUniform3fv(glGetUniformLocation(programID, name.c_str()), 1, glm::value_ptr(value));
	}
	GLuint GetProgramID() { return programID; }

	int Init(const char* vertexPath, const char* fragmentPath);

private:
	GLuint programID{ 0 };
};

