#define STB_IMAGE_IMPLEMENTATION
#include <iostream>
#include "Window.h"
#include "Shader.h"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"
#include "Camera.h"
#include "Game.h"
#include "Model.h"

//Static inits
Window* Game::mainWindow = new Window();

SDL_Event event{};


int main(int argc, char* argv[]) {
	Game game = Game();
	game.Init();
	//Model ourModel("C:/Users/David/workspaceC++/Projects/OpenGLCourseApp/OpenGLCourseApp/Assets/Objects/Backpack/backpack.obj");

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
		game.MVP();

		//ourModel.Draw(*(game.GetShader()));

		//Render
		SDL_GL_SwapWindow(Game::mainWindow->GetSDL_Window());
	}

	return 0;
}

