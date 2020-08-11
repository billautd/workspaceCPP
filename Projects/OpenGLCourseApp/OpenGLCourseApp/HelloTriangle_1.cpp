//#include <iostream>
//#include "Window.h"
//
//Window* mainWindow = new Window();
//SDL_Event event{};
//
//GLuint VAO{ 0 };
//GLuint VBO{ 0 };
//GLuint shaderProgram{ 0 };
//
//GLfloat vertices[] = {
//	//x        y      z
//	//First triangle
//	 0.5f,   0.5f,   0.0f,    //top right
//	-0.5f,   0.5f,   0.0f,    //top left
//	 0.5f,  -0.5f,   0.0f,    //bottom right
//
//	 //Second triangle
//	-0.5f,   0.5f,   0.0f,    //top left
//	-0.5f,  -0.5f,   0.0f,    //bottom left
//	 0.5f,  -0.5f,   0.0f    //bottom right
//};
//
//void method() {
//	//Vertex shader
//	const char* vertexShaderSource = "#version 330 core\n"
//		"layout (location = 0) in vec3 aPos;\n"
//		"void main()\n"
//		"{\n"
//		"   gl_Position = vec4(aPos, 1.0f);\n"
//		"}\0";
//
//	GLuint vertexShader{ glCreateShader(GL_VERTEX_SHADER) };
//	glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
//	glCompileShader(vertexShader);
//
//	GLint success{ 0 };
//	GLchar infoLog[512];
//	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
//	if (!success) {
//		glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
//		std::cerr << "Error while compiling vertex shader : " << infoLog << '\n';
//	}
//
//
//
//
//	//Fragment shader
//	const char* fragmentShaderSource = "#version 330 core\n"
//		"out vec4 fragColor;\n"
//		"void main()\n"
//		"{\n"
//		"  fragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
//		"}\0";
//
//	GLuint fragmentShader{ glCreateShader(GL_FRAGMENT_SHADER) };
//	glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
//	glCompileShader(fragmentShader);
//
//	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
//	if (!success) {
//		glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
//		std::cerr << "Error while compiling fragment shader : " << infoLog << '\n';
//	}
//
//
//	//Shader program
//	shaderProgram = glCreateProgram();
//	glAttachShader(shaderProgram, vertexShader);
//	glAttachShader(shaderProgram, fragmentShader);
//	glLinkProgram(shaderProgram);
//	glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
//	if (!success) {
//		glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
//		std::cerr << "Error while linking shader program : " << infoLog << '\n';
//	}
//
//	glDeleteShader(vertexShader);
//	glDeleteShader(fragmentShader);
//
//	glGenVertexArrays(1, &VAO);
//	glGenBuffers(1, &VBO);
//
//	glBindVertexArray(VAO);
//	{
//		//VBO
//		glBindBuffer(GL_ARRAY_BUFFER, VBO);
//
//		glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
//		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (void*)0);
//		glEnableVertexAttribArray(0);
//
//		glBindBuffer(GL_ARRAY_BUFFER, 0);
//	}
//	glBindVertexArray(0);
//}
//
//
//int main(int argc, char* argv[]) {
//	mainWindow->Init();
//
//	method();
//
//	//Render loop
//	while (mainWindow->IsRunning()) {
//		//Input
//		SDL_PollEvent(&event);
//		mainWindow->ProcessInput(event);
//
//		//Render colour
//		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
//		glClear(GL_COLOR_BUFFER_BIT);
//
//		glUseProgram(shaderProgram);
//		glBindVertexArray(VAO);
//		{
//			glDrawArrays(GL_TRIANGLES, 0, 6);
//		}
//		glBindVertexArray(0);
//
//		SDL_GL_SwapWindow(mainWindow->GetSDL_Window());
//	}
//
//	glDeleteVertexArrays(1, &VAO);
//	glDeleteBuffers(1, &VBO);
//	glDeleteProgram(shaderProgram);
//
//	return 0;
//}
//
//
//
