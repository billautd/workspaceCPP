//#define STB_IMAGE_IMPLEMENTATION
//#include <iostream>
//#include "Window.h"
//#include "Shader.h"
//#include "Texture.h"
//
//Window* mainWindow{ new Window() };
//SDL_Event event{};
//
//GLuint VAO{ 0 };
//GLuint VBO{ 0 };
//GLuint EBO{ 0 };
//GLuint shaderProgram{ 0 };
//GLuint texture1{ 0 };
//GLuint texture2{ 0 };
//
//GLfloat vertices[]{
//	//     x      y     z       r     g     b      texX  texY
//		-0.5f,  0.5f,  0.0f,   1.0f, 1.0f, 0.0f,   0.45f, 0.55f,     //top left
//		 0.5f,  0.5f,  0.0f,   1.0f, 0.0f, 0.0f,   0.55f, 0.55f,    //top right
//		-0.5f, -0.5f,  0.0f,   0.0f, 0.0f, 1.0f,   0.45f, 0.45f,    //bottom left
//		 0.5f, -0.5f,  0.0f,   0.0f, 1.0f, 0.0f,   0.55f, 0.45f    //bottom right
//};
//
//GLuint indices[]{
//	0, 2, 3, //first triangle
//	0, 1, 3 //second triangle
//};
//
//void GenerateVertexData() {
//
//	glGenVertexArrays(1, &VAO);
//	glGenBuffers(1, &VBO);
//	glGenBuffers(1, &EBO);
//
//	glBindVertexArray(VAO);
//	{
//		//VBO
//		glBindBuffer(GL_ARRAY_BUFFER, VBO);
//		glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
//
//		//EBO
//		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
//		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
//
//		//Position
//		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (void*)0);
//		glEnableVertexAttribArray(0);
//
//		//Color
//		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (void*)(3 * sizeof(GLfloat)));
//		glEnableVertexAttribArray(1);
//
//		//Texture
//		glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (void*)(6 * sizeof(GLfloat)));
//		glEnableVertexAttribArray(2);
//
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
//	Shader shader{};
//	if (shader.Init("Shaders/vertex.shader", "Shaders/fragment.shader") != 0) {
//		std::cerr << "Error while initializing shaders\n";
//		return 1;
//	};
//	GenerateVertexData();
//
//	Texture wallTexture{};
//	if (wallTexture.Init("Assets/Textures/wall.jpg") != 0) {
//		std::cerr << "Error while initializing wall texture\n";
//		return 2;
//	}
//	glGenTextures(1, &texture1);
//	glBindTexture(GL_TEXTURE_2D, texture1);
//	{
//		Texture::SetTextureFilter(GL_NEAREST);
//		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, wallTexture.GetWidth(),
//			wallTexture.GetHeight(), 0, GL_RGB, GL_UNSIGNED_BYTE, wallTexture.GetData());
//		glGenerateMipmap(GL_TEXTURE_2D);
//	}
//
//	Texture faceTexture{};
//	stbi_set_flip_vertically_on_load(true);
//	if (faceTexture.Init("Assets/Textures/awesomeface.png") != 0) {
//		std::cerr << "Error while initializing face texture\n";
//		return 2;
//	}
//	glGenTextures(1, &texture2);
//	glBindTexture(GL_TEXTURE_2D, texture2);
//	{
//		Texture::SetTextureFilter(GL_NEAREST);
//		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, faceTexture.GetWidth(),
//			faceTexture.GetHeight(), 0, GL_RGBA, GL_UNSIGNED_BYTE, faceTexture.GetData());
//		glGenerateMipmap(GL_TEXTURE_2D);
//	}
//
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
//		glActiveTexture(GL_TEXTURE0);
//		glBindTexture(GL_TEXTURE_2D, texture1);
//		glActiveTexture(GL_TEXTURE1);
//		glBindTexture(GL_TEXTURE_2D, texture2);
//		shader.SetInt("textureUnit1", 0);
//		shader.SetInt("textureUnit2", 1);
//
//		glBindVertexArray(VAO);
//		{
//			glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
//		}
//		glBindVertexArray(0);
//
//		SDL_GL_SwapWindow(mainWindow->GetSDL_Window());
//	}
//
//	wallTexture.FreeImage();
//	glDeleteVertexArrays(1, &VAO);
//	glDeleteBuffers(1, &VBO);
//	glDeleteBuffers(1, &EBO);
//	glDeleteProgram(shaderProgram);
//
//	return 0;
//}
//
