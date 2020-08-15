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
	void ProcessKeyboardInput(SDL_Event& e);
	void ProcessMouseInput(SDL_Event& e);
	void ProcessMouseScrollInput(SDL_Event& e);

	//Shaders
	int InitShaders();
	void GenerateVertexData();
	void FreeShaders();

	//Texture
	void GenerateTextureData();
	void BindTextures();

	void MVP();

	Shader GetContainerShader() { return containerShader; }
	Shader GetLightSourceShader() { return lightSourceShader; }

private:
	bool isRunning{ false };
	GLuint ticksLastFrame{ 0 };

	GLuint containerVAO{ 0 };
	GLuint lightSourceVAO{ 0 };
	GLuint VBO{ 0 };
	GLuint EBO{ 0 };
	Shader containerShader{};
	Shader lightSourceShader{};
	std::vector<GLuint> textureIds{ 0,0,0 };
};

