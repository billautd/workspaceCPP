#include "Shader.h"
#include <iostream>
const std::string VERTEX_TYPE{ "VERTEX" };
const std::string FRAGMENT_TYPE{ "FRAGMENT" };
const std::string GEOMETRY_TYPE{ "GEOMETRY" };
const std::string PROGRAM_TYPE{ "PROGRAM" };

const Shader& Shader::Use() const
{
	glUseProgram(id);
	return *this;
}
void Shader::Compile(const char* vertexSource, const char* fragmentSouce, const char* geometrySource) {
	GLuint sVertex{};
	GLuint sFragment{};
	GLuint sGeometry{};

	//Vertex shader
	sVertex = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(sVertex, 1, &vertexSource, nullptr);
	glCompileShader(sVertex);
	CheckCompileErrors(sVertex, VERTEX_TYPE);

	//Fragment shader
	sFragment = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(sFragment, 1, &fragmentSouce, nullptr);
	glCompileShader(sFragment);
	CheckCompileErrors(sFragment, FRAGMENT_TYPE);

	//Geometry shader
	if (geometrySource != nullptr) {
		sGeometry = glCreateShader(GL_GEOMETRY_SHADER);
		glShaderSource(sGeometry, 1, &geometrySource, nullptr);
		glCompileShader(sGeometry);
		CheckCompileErrors(sGeometry, GEOMETRY_TYPE);
	}

	//Shader program
	id = glCreateProgram();
	glAttachShader(id, sVertex);
	glAttachShader(id, sFragment);
	if (geometrySource != nullptr) 
		glAttachShader(id, sGeometry);
	glLinkProgram(id);
	CheckCompileErrors(id, PROGRAM_TYPE);

	//Delete shaders as they're linked into our program now and are no longer necessary
	glDeleteShader(sVertex);
	glDeleteShader(sFragment);
	if(geometrySource != nullptr)
		glDeleteShader(sGeometry);
}

void Shader::CheckCompileErrors(const GLuint object, const std::string type) const
{
	int success{ 0 };
	char infoLog[1024];
	if (type != PROGRAM_TYPE) {
		glGetShaderiv(object, GL_COMPILE_STATUS, &success);
		if (!success) {
			glGetShaderInfoLog(object, 1024, nullptr, infoLog);
			std::cout << "| ERROR::SHADER: Compile-time error: Type: " << type << "\n"
				<< infoLog << "\n -- --------------------------------------------------- -- "
				<< std::endl;
		}
	}
	else {
		glGetProgramiv(object, GL_LINK_STATUS, &success);
		if (!success) {
			glGetProgramInfoLog(object, 1024, nullptr, infoLog);
			glGetProgramInfoLog(object, 1024, NULL, infoLog);
			std::cout << "| ERROR::Shader: Link-time error: Type: " << type << "\n"
				<< infoLog << "\n -- --------------------------------------------------- -- "
				<< std::endl;
		}
	}
}
