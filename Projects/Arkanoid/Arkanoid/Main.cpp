#include "Game.h"
#include "Constants.h"
#include "ResourceManager.h"

Game game{ };
SDL_Event event{};
GLuint ticksLastFrame{ 0 };

int main(int argc, char** argv) {
	int success{ game.Init() };
	if (success != 0)
		return success;

	while (game.GetState() != GameStateEnum::GAME_INACTIVE) {
		//Input
		SDL_PollEvent(&event);

		//Delta time
		GLuint timeToWait{ static_cast<GLuint>(FRAME_TARGET) - (SDL_GetTicks() - ticksLastFrame) };
		if (timeToWait > 0 && timeToWait < FRAME_TARGET)
			SDL_Delay(timeToWait);

		GLfloat deltaTime{ (SDL_GetTicks() - ticksLastFrame) / 1000.0f };

		deltaTime = (deltaTime > 0.05f) ? 0.05f : deltaTime;

		ticksLastFrame = SDL_GetTicks();

		//Process input
		game.ProcessInput(event, deltaTime);
		//Update
		game.Update(deltaTime);
		//Render
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		game.Render();

		//Render
		SDL_GL_SwapWindow(game.GetWindow());
	}
	ResourceManager::Clear();
	SDL_Quit();
	return 0;
}