#pragma once
#include "Camera.h"
#include "Window.h"
#include "Shader.h"
#include "Texture.h"
#include "Utils.h"
#include <vector>

class Game {
public:
	Game() = default;
	~Game();

	static Camera* camera;
	static Window* mainWindow;

	bool IsRunning() { return isRunning; }

	void Init();
	void ProcessInput(SDL_Event& e);
	void ProcessCameraMovement(GLfloat deltaTime);

	//Shaders
	int InitShaders();
	void GenerateVertexData();
	void FreeShaders();

	//Texture
	void GenerateTextureData();
	void BindTextures();

	void MVP();

	void UseShader() { shader.Use(); }

private:
	bool isRunning{ false };
	GLuint ticksLastFrame{ 0 };

	GLuint VAO{ 0 };
	GLuint VBO{ 0 };
	GLuint EBO{ 0 };
	Shader shader{};
	std::vector<GLuint> textureIds{ 0, 1 };
};

