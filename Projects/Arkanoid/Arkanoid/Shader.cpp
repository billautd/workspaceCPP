#include "Shader.h"

Shader& Shader::Use() {
	glUseProgram(id);
	return *this;
}

void Shader::Compile(const char* vertexSource, const char* fragmentSource, const char* geometrySource) {
	GLuint sVertex{ 0 };
	GLuint sFragment{ 0 };
	GLuint sGeometry{ 0 };

	//Vertex
	sVertex = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(sVertex, 1, &vertexSource, nullptr);
	glCompileShader(sVertex);
	CheckCompileErrors(sVertex, "VERTEX");

	//Fragment
	sFragment = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(sFragment, 1, &fragmentSource, nullptr);
	glCompileShader(sFragment);
	CheckCompileErrors(sFragment, "FRAGMENT");

	//Geometry
	if (geometrySource != nullptr) {
		sGeometry = glCreateShader(GL_GEOMETRY_SHADER);
		glShaderSource(sGeometry, 1, &geometrySource, nullptr);
		glCompileShader(sGeometry);
		CheckCompileErrors(sGeometry, "GEOMETRY");
	}

	//Shader program
	this->id = glCreateProgram();
	glAttachShader(this->id, sVertex);
	glAttachShader(this->id, sFragment);
	if (geometrySource != nullptr)
		glAttachShader(this->id, sGeometry);
	glLinkProgram(this->id);
	CheckCompileErrors(this->id, "PROGRAM");

	//Delete linked shaders
	glDeleteShader(sVertex);
	glDeleteShader(sFragment);
	if (geometrySource != nullptr)
		glDeleteShader(sGeometry);
}

void Shader::Delete() {
	glDeleteProgram(this->id);
	this->id = 0;
}

void Shader::SetFloat(const char* name, GLfloat value, bool useShader) {
	if (useShader)
		this->Use();
	glUniform1f(glGetUniformLocation(this->id, name), value);
}

void Shader::SetInteger(const char* name, GLint value, bool useShader) {
	if (useShader)
		this->Use();
	glUniform1i(glGetUniformLocation(this->id, name), value);
}

void Shader::SetVector2f(const char* name, GLfloat x, GLfloat y, bool useShader) {
	if (useShader)
		this->Use();
	glUniform2f(glGetUniformLocation(this->id, name), x, y);
}
void Shader::SetVector2f(const char* name, glm::vec2 value, bool useShader) {
	this->SetVector2f(name, value.x, value.y, useShader);
}

void Shader::SetVector3f(const char* name, GLfloat x, GLfloat y, GLfloat z, bool useShader) {
	if (useShader)
		this->Use();
	glUniform3f(glGetUniformLocation(this->id, name), x, y, z);
}

void Shader::SetVector3f(const char* name, glm::vec3 value, bool useShader) {
	this->SetVector3f(name, value.x, value.y, value.z, useShader);
}

void Shader::SetVector4f(const char* name, GLfloat x, GLfloat y, GLfloat z, GLfloat w, bool useShader) {
	if (useShader)
		this->Use();
	glUniform4f(glGetUniformLocation(this->id, name), x, y, z, w);
}

void Shader::SetVector4f(const char* name, glm::vec4 value, bool useShader) {
	this->SetVector4f(name, value.x, value.y, value.z, value.w, useShader);
}



void Shader::SetMatrix4(const char* name, glm::mat4 value, bool useShader) {
	if (useShader)
		this->Use();
	glUniformMatrix4fv(glGetUniformLocation(this->id, name), 1, false, glm::value_ptr(value));
}

void Shader::CheckCompileErrors(GLuint object, std::string type) {
	int success{ 0 };
	char infoLog[1024]{};

	if (type != "PROGRAM") {
		glGetShaderiv(object, GL_COMPILE_STATUS, &success);
		if (!success) {
			glGetShaderInfoLog(object, 1024, nullptr, infoLog);
			std::cout << "| ERROR::SHADER: Compile-time error: Type: " << type << "\n"
				<< infoLog << "\n -- --------------------------------------------------- -- \n\n";
		}
	}
	else {
		glGetProgramiv(object, GL_LINK_STATUS, &success);
		if (!success) {
			glGetProgramInfoLog(object, 1024, nullptr, infoLog);
			std::cout << "| ERROR::PROGRAM: Link-time error: Type: " << type << "\n"
				<< infoLog << "\n -- --------------------------------------------------- -- \n\n";
		}
	}
}
