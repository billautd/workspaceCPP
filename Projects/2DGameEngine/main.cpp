#define SDL_MAIN_HANDLED
#include <iostream>
#include "Constants.h"
#include "Game.h"

int main(int argc, char** argv) {
	Game game{ Game() };

	//Game loop
	game.Init();
	while (game.IsRunning()) {
		game.ProcessInput();
		game.Update();
		game.Render();
	}
	game.Destroy();

	return 0;
}