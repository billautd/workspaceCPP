//#include <iostream>
//#include "Window.h"
//
//Window* mainWindow = new Window();
//SDL_Event event{};
//
//GLuint VAOs[2]{};
//GLuint VBOs[2]{};
//GLuint shaderProgramOrange{ 0 };
//GLuint shaderProgramYellow{ 0 };
//
//GLfloat verticesFirstTriangle[] = {
//	//x        y      z
//	 0.5f,   0.5f,   0.0f,    //top right
//	-0.5f,   0.5f,   0.0f,    //top left
//	 0.5f,  -0.5f,   0.0f,    //bottom right
//};
//
//GLfloat verticesSecondTriangle[] = {
//	//x        y      z
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
//	const char* fragmentShaderSourceOrange = "#version 330 core\n"
//		"out vec4 fragColor;\n"
//		"void main()\n"
//		"{\n"
//		"  fragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
//		"}\0";
//
//	GLuint fragmentShaderOrange{ glCreateShader(GL_FRAGMENT_SHADER) };
//	glShaderSource(fragmentShaderOrange, 1, &fragmentShaderSourceOrange, NULL);
//	glCompileShader(fragmentShaderOrange);
//
//	glGetShaderiv(fragmentShaderOrange, GL_COMPILE_STATUS, &success);
//	if (!success) {
//		glGetShaderInfoLog(fragmentShaderOrange, 512, NULL, infoLog);
//		std::cerr << "Error while compiling fragment shader orange: " << infoLog << '\n';
//	}
//
//	const char* fragmentShaderSourceYellow = "#version 330 core\n"
//		"out vec4 fragColor;\n"
//		"void main()\n"
//		"{\n"
//		"  fragColor = vec4(1.0f, 1.0f, 0.0f, 1.0f);\n"
//		"}\0";
//
//	GLuint fragmentShaderYellow{ glCreateShader(GL_FRAGMENT_SHADER) };
//	glShaderSource(fragmentShaderYellow, 1, &fragmentShaderSourceYellow, NULL);
//	glCompileShader(fragmentShaderYellow);
//
//	glGetShaderiv(fragmentShaderYellow, GL_COMPILE_STATUS, &success);
//	if (!success) {
//		glGetShaderInfoLog(fragmentShaderYellow, 512, NULL, infoLog);
//		std::cerr << "Error while compiling fragment shader yellow: " << infoLog << '\n';
//	}
//
//
//	//Shader program
//	shaderProgramOrange = glCreateProgram();
//	glAttachShader(shaderProgramOrange, vertexShader);
//	glAttachShader(shaderProgramOrange, fragmentShaderOrange);
//	glLinkProgram(shaderProgramOrange);
//	glGetProgramiv(shaderProgramOrange, GL_LINK_STATUS, &success);
//	if (!success) {
//		glGetProgramInfoLog(shaderProgramOrange, 512, NULL, infoLog);
//		std::cerr << "Error while linking shader program orange : " << infoLog << '\n';
//	}
//
//	shaderProgramYellow = glCreateProgram();
//	glAttachShader(shaderProgramYellow, vertexShader);
//	glAttachShader(shaderProgramYellow, fragmentShaderYellow);
//	glLinkProgram(shaderProgramYellow);
//	glGetProgramiv(shaderProgramYellow, GL_LINK_STATUS, &success);
//	if (!success) {
//		glGetProgramInfoLog(shaderProgramYellow, 512, NULL, infoLog);
//		std::cerr << "Error while linking shader program yellow : " << infoLog << '\n';
//	}
//
//	glDeleteShader(vertexShader);
//	glDeleteShader(fragmentShaderOrange);
//	glDeleteShader(fragmentShaderYellow);
//
//	glGenVertexArrays(2, VAOs);
//	glGenBuffers(2, VBOs);
//
//	glBindVertexArray(VAOs[0]);
//	{
//		//VBO
//		glBindBuffer(GL_ARRAY_BUFFER, VBOs[0]);
//
//		glBufferData(GL_ARRAY_BUFFER, sizeof(verticesFirstTriangle), verticesFirstTriangle, GL_STATIC_DRAW);
//		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (void*)0);
//		glEnableVertexAttribArray(0);
//
//		glBindBuffer(GL_ARRAY_BUFFER, 0);
//	}
//	glBindVertexArray(0);
//
//	glBindVertexArray(VAOs[1]);
//	{
//		//VBO
//		glBindBuffer(GL_ARRAY_BUFFER, VBOs[1]);
//
//		glBufferData(GL_ARRAY_BUFFER, sizeof(verticesSecondTriangle), verticesSecondTriangle, GL_STATIC_DRAW);
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
//		glUseProgram(shaderProgramOrange);
//		glBindVertexArray(VAOs[0]);
//		{
//			glDrawArrays(GL_TRIANGLES, 0, 3);
//		}
//		glBindVertexArray(0);
//
//		glUseProgram(shaderProgramYellow);
//		glBindVertexArray(VAOs[1]);
//		{
//			glDrawArrays(GL_TRIANGLES, 0, 3);
//		}
//		glBindVertexArray(0);
//
//		SDL_GL_SwapWindow(mainWindow->GetSDL_Window());
//	}
//
//	glDeleteVertexArrays(2, VAOs);
//	glDeleteBuffers(2, VBOs);
//	glDeleteProgram(shaderProgramYellow);
//	glDeleteProgram(shaderProgramOrange);
//
//	return 0;
//}
//
//
//
