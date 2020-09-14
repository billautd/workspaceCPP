#include "Game.h"
#include "ResourceManager.h"

Game game{};
SDL_Event event{};
GLuint ticksLastFrame{ 0 };

int main(int argc, char** argv) {
	int success{ game.Init() };
	if (success != 0)
		return success;

	while (game.GetState() != GameStateEnum::GAME_INACTIVE) {
		SDL_PollEvent(&event);

		//Delta time
		GLuint timeToWait{ static_cast<GLuint>(FRAME_TIME) - (SDL_GetTicks() - ticksLastFrame) };
		if (timeToWait > 0 && timeToWait < FRAME_TIME)
			SDL_Delay(timeToWait);

		GLfloat deltaTime{ (SDL_GetTicks() - ticksLastFrame) / 1000.0f };
		deltaTime = (deltaTime > 0.05f) ? 0.05f : deltaTime;

		ticksLastFrame = SDL_GetTicks();

		//Process input
		game.ProcessInput(event, deltaTime);
		//Update
		game.Update(deltaTime);
		//Render
		glClearColor(0.3f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		game.Render();

		SDL_GL_SwapWindow(game.GetMainWindow());
	}
	ResourceManager::Clear();
	game.Quit();
	return 0;
}