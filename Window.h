#pragma once
#include "glad/glad.h"
#include <SDL.h>
#include <SDL_ttf.h>
#include <iostream>
#include "Constants.h"

class Window {
public:
	Window();
	Window(GLuint cWidth, GLuint cHeight);
	~Window() = default;

	int Init();
	void GLClear();

	SDL_Window* GetSDL_Window() { return mainWindow; }

private:
	SDL_Window* mainWindow{ nullptr };
	GLuint width{ 0 };
	GLuint height{ 0 };

};

