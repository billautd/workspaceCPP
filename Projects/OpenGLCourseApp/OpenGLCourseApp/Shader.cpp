#include "Shader.h"

int Shader::Init(const char* vertexPath, const char* fragmentPath) {
	//1. Read from files
	std::ifstream vertexFile{};
	std::ifstream fragmentFile{};
	std::string vertexCode{};
	std::string fragmentCode{};

	//Open files
	vertexFile.open(vertexPath);
	if (!vertexFile) {
		std::cerr << "Error while opening vertex shader file : " << vertexPath << '\n';
		return 1;
	}
	fragmentFile.open(fragmentPath);
	if (!vertexFile) {
		std::cerr << "Error while opening fragment shader file : " << fragmentPath << '\n';
		return 1;
	}

	std::stringstream vertexStream{};
	std::stringstream fragmentStream{};
	//Read from file
	vertexStream << vertexFile.rdbuf();
	fragmentStream << fragmentFile.rdbuf();

	//Close files
	vertexFile.close();
	fragmentFile.close();

	//From stream to string
	vertexCode = vertexStream.str();
	fragmentCode = fragmentStream.str();




	//2. Compile shaders

	//Vertex shader
	const char* vertexSource{ vertexCode.c_str() };
	GLuint vertexShader{ glCreateShader(GL_VERTEX_SHADER) };
	glShaderSource(vertexShader, 1, &vertexSource, NULL);
	glCompileShader(vertexShader);

	GLint success{ 0 };
	GLchar infoLog[512]{};
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
	if (!success) {
		glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
		std::cerr << "Error while compiling vertex shader : " << infoLog << '\n';
		return 2;
	}

	//Fragment shader
	const char* fragmentSource{ fragmentCode.c_str() };
	GLuint fragmentShader{ glCreateShader(GL_FRAGMENT_SHADER) };
	glShaderSource(fragmentShader, 1, &fragmentSource, NULL);
	glCompileShader(fragmentShader);

	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
	if (!success) {
		glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
		std::cerr << "Error while compiling fragment shader : " << infoLog << '\n';
		return 2;
	}

	programID = glCreateProgram();
	glAttachShader(programID, vertexShader);
	glAttachShader(programID, fragmentShader);
	glLinkProgram(programID);
	glGetProgramiv(programID, GL_LINK_STATUS, &success);
	if (!success) {
		glGetProgramInfoLog(programID, 512, NULL, infoLog);
		std::cerr << "Error while linking shader program : " << infoLog << '\n';
		return 3;
	}

	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);

	return 0;
}