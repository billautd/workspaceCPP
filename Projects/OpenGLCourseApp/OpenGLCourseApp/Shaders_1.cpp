//#include <iostream>
//#include "Window.h"
//#include "Shader.h"
//
//Window* mainWindow = new Window();
//SDL_Event event{};
//
//GLuint VAO{ 0 };
//GLuint VBO{ 0 };
//GLuint shaderProgram{ 0 };
//
//GLfloat vertices[] = {
//	//     x      y     z       r     g     b
//		 0.0f,  0.5f,  0.0f,   1.0f, 0.0f, 0.0f,   //top
//		 0.5f, -0.5f,  0.0f,   0.0f, 1.0f, 0.0f,   //bottom right
//		-0.5f, -0.5f,  0.0f,   0.0f, 0.0f, 1.0f    //bottom left
//};
//
//void GenerateVertexData() {
//	glGenVertexArrays(1, &VAO);
//	glGenBuffers(1, &VBO);
//
//	glBindVertexArray(VAO);
//	{
//		//VBO
//		glBindBuffer(GL_ARRAY_BUFFER, VBO);
//
//		glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
//
//		//Position
//		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (void*)0);
//		glEnableVertexAttribArray(0);
//
//		//Color
//		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (void*)(3 * sizeof(GLfloat)));
//		glEnableVertexAttribArray(1);
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
//	Shader shader;
//  if(shader.Init("Shaders/Shaders_1_Vertex.shader", "Shaders/fragment.shader") != 0){
//		std::cerr << "Error while initializing shaders\n";
//		return 0;
//	};
//	GenerateVertexData();
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
//
//		shader.Use();
//
//		glBindVertexArray(VAO);
//		{
//			glDrawArrays(GL_TRIANGLES, 0, 3);
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
