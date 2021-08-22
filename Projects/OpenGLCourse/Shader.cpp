#include "Shader.h"
#include <fstream>
#include <sstream>
#include <iostream>

Shader::Shader(const char* vertexPath, const char* fragmentPath) {
	std::ifstream vShaderFile;
	std::ifstream fShaderFile;

	std::string vShaderString;
	std::string fShaderString;

	//Ensure ifstream objects can throw exceptions:
	vShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
	fShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);

	try {
		//Open files
		vShaderFile.open(vertexPath);
		fShaderFile.open(fragmentPath);
		std::stringstream vShaderStream;
		std::stringstream fShaderStream;

		//Read from files
		vShaderStream << vShaderFile.rdbuf();
		fShaderStream << fShaderFile.rdbuf();

		//Close file handlers
		vShaderFile.close();
		fShaderFile.close();

		vShaderString = vShaderStream.str();
		fShaderString = fShaderStream.str();
	}
	catch (std::ifstream::failure e) {
		std::cerr << "Error trying to create shader at " << vertexPath << " & " << fragmentPath << '\n';
	}

	CompileAndLinkShaders(vertexPath, vShaderString.c_str(), fragmentPath, fShaderString.c_str());
}

void Shader::SetDirLight(const DirLight& dirLight, const std::string name) const {
	SetVec3(name + ".ambient", dirLight.ambient);
	SetVec3(name + ".diffuse", dirLight.diffuse);
	SetVec3(name + ".specular", dirLight.specular);
	SetVec3(name + ".color", dirLight.color);
	SetVec3(name + ".direction", dirLight.direction);
}

void Shader::SetPointLight(const PointLight& pointLight, const std::string name) const {
	SetVec3(name + ".ambient", pointLight.ambient);
	SetVec3(name + ".diffuse", pointLight.diffuse);
	SetVec3(name + ".specular", pointLight.specular);
	SetVec3(name + ".color", pointLight.color);
	SetVec3(name + ".position", pointLight.position);
	SetFloat(name + ".Kconstant", pointLight.constant);
	SetFloat(name + ".Klinear", pointLight.linear);
	SetFloat(name + ".Kquadratic", pointLight.quadratic);
}

void Shader::CompileAndLinkShaders(const char* vertexPath, const char* vertexShaderCode, const char* fragmentPath, const char* fragmentShaderCode) {
	GLuint vertexShader, fragmentShader;

	//Create and compile vertex shader
	vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vertexShaderCode, NULL);
	glCompileShader(vertexShader);

	int success;
	char infoLog[512];
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
	if (!success) {
		glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
		std::cerr << "Error compiling vertex shader at " << vertexPath << " : " << infoLog << '\n';
	}

	//Create and compile vertex shader
	fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragmentShaderCode, NULL);
	glCompileShader(fragmentShader);

	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
	if (!success) {
		glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
		std::cerr << "Error compiling fragment shader at " << fragmentPath << " : " << infoLog << '\n';
	}

	id = glCreateProgram();
	glAttachShader(id, vertexShader);
	glAttachShader(id, fragmentShader);
	glLinkProgram(id);

	glGetProgramiv(id, GL_LINK_STATUS, &success);
	if (!success) {
		glGetProgramInfoLog(id, 512, NULL, infoLog);
		std::cerr << "Error linking shaders to program : " << infoLog << '\n';
	}

	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);
}
