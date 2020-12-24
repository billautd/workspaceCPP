#include "Game.h"
#include "Constants.h"
#include "SDL.h"
#include "glad/glad.h"
#include "EventManager.h"

Game game{};
GLuint ticksLastFrame{ 0 };

int main(int argc, char** argv) {
	int success{ game.Init() };
	if (success != 0)
		return success;

	while (game.GetState() != GameStateEnum::GAME_INACTIVE) {
		SDL_PollEvent(&EventManager::event);

		//Delta time
		GLuint timeToWait{ static_cast<GLuint>(FRAME_TIME_TARGET) - (SDL_GetTicks() - ticksLastFrame) };
		if (timeToWait > 0 && timeToWait < FRAME_TIME_TARGET) {
			SDL_Delay(timeToWait);
		}
		GLfloat deltaTime{ (SDL_GetTicks() - ticksLastFrame) / 1000.0f };
		deltaTime = (deltaTime > 0.05f) ? 0.05f : deltaTime;
		ticksLastFrame = SDL_GetTicks();

		game.ProcessInput(EventManager::event, deltaTime);
		game.Update(deltaTime);
		game.Render();

		SDL_GL_SwapWindow(game.GetMainWindow());
	}
	return 0;
}