#include "Shader.h"
#include "glm/gtc/type_ptr.hpp"
#include <iostream>

Shader& Shader::Use() {
	glUseProgram(this->id);
	return *this;
}

void Shader::Compile(const char* vSource, const char* fSource, const char* gSource) {
	GLuint sVertex{ 0 };
	GLuint sFragment{ 0 };
	GLuint sGeometry{ 0 };

	//Vertex
	sVertex = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(sVertex, 1, &vSource, nullptr);
	glCompileShader(sVertex);
	CheckCompileErrors(sVertex, "VERTEX");

	//Fragment
	sFragment = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(sFragment, 1, &fSource, nullptr);
	glCompileShader(sFragment);
	CheckCompileErrors(sFragment, "FRAGMENT");

	//Geometry
	if (gSource != nullptr) {
		sGeometry = glCreateShader(GL_GEOMETRY_SHADER);
		glShaderSource(sGeometry, 1, &gSource, nullptr);
		glCompileShader(sGeometry);
		CheckCompileErrors(sGeometry, "GEOMETRY");
	}

	//Program
	this->id = glCreateProgram();
	glAttachShader(this->id, sVertex);
	glAttachShader(this->id, sFragment);
	if (gSource != nullptr)
		glAttachShader(this->id, sGeometry);
	glLinkProgram(this->id);
	CheckCompileErrors(this->id, "PROGRAM");

	//Delete linked shaders
	glDeleteShader(sVertex);
	glDeleteShader(sFragment);
	if (gSource != nullptr)
		glDeleteShader(sGeometry);
}

void Shader::Delete() {
	glDeleteProgram(this->id);
	this->id = 0;
}

void Shader::SetFloat(const char* name, GLfloat value) {
	glUniform1f(glGetUniformLocation(this->id, name), value);
}

void Shader::SetInteger(const char* name, GLint value) {
	glUniform1i(glGetUniformLocation(this->id, name), value);
}

void Shader::SetVector2f(const char* name, glm::vec2 value) {
	glUniform2f(glGetUniformLocation(this->id, name), value.x, value.y);
}

void Shader::SetVector2f(const char* name, GLfloat x, GLfloat y) {
	glUniform2f(glGetUniformLocation(this->id, name), x, y);
}

void Shader::SetVector3f(const char* name, glm::vec3 value) {
	glUniform3f(glGetUniformLocation(this->id, name), value.x, value.y, value.z);
}

void Shader::SetVector3f(const char* name, GLfloat x, GLfloat y, GLfloat z) {
	glUniform3f(glGetUniformLocation(this->id, name), x, y, z);
}

void Shader::SetVector4f(const char* name, glm::vec4 value) {
	glUniform4f(glGetUniformLocation(this->id, name), value.x, value.y, value.z, value.w);
}

void Shader::SetVector4f(const char* name, GLfloat x, GLfloat y, GLfloat z, GLfloat w) {
	glUniform4f(glGetUniformLocation(this->id, name), x, y, z, w);
}

void Shader::SetMatrix4(const char* name, glm::mat4 value) {
	glUniformMatrix4fv(glGetUniformLocation(this->id, name), 1, GL_FALSE, glm::value_ptr(value));
}

void Shader::CheckCompileErrors(GLuint object, std::string type) {
	int success{ 0 };
	char infoLog[1024]{};

	if (type != "PROGRAM") {
		glGetShaderiv(object, GL_COMPILE_STATUS, &success);
		if (!success) {
			glGetShaderInfoLog(object, 1024, nullptr, infoLog);
			std::cerr << "ERROR::SHADER: Compile-time error: Type: " << type << '\n' << infoLog << "\n--------------------------------------------------\n";
		}
	}
	else {
		glGetProgramiv(object, GL_LINK_STATUS, &success);
		if (!success) {
			glGetProgramInfoLog(object, 1024, nullptr, infoLog);
			std::cerr << "ERROR::PROGRAM: Link-time error: Type: " << type << '\n' << infoLog << "\n--------------------------------------------------\n";
		}
	}
}
