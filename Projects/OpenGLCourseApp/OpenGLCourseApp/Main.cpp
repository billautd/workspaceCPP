#define STB_IMAGE_IMPLEMENTATION
#include <iostream>
#include "Window.h"
#include "Shader.h"
#include "Texture.h"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"
#include "Camera.h"
#include "Game.h"

//Static inits
Window* Game::mainWindow = new Window();
Camera* Game::camera = new Camera();

SDL_Event event{};


int main(int argc, char* argv[]) {
	Game game = Game();
	game.Init();

	//Render loop
	while (game.IsRunning()) {
		//Input
		SDL_PollEvent(&event);
		game.ProcessKeyboardInput(event);
		game.ProcessMouseInput(event);
		while (SDL_PollEvent(&event))
			game.ProcessMouseScrollInput(event);


		//Update
		Game::mainWindow->GLClear();
		game.BindTextures();

		game.MVP();

		//Render
		SDL_GL_SwapWindow(Game::mainWindow->GetSDL_Window());

	}

	game.FreeShaders();

	return 0;
}

