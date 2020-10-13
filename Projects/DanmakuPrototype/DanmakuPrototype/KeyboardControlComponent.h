#pragma once
#include "ComponentsInclude.h"
#include "SDL.h"
class KeyboardControlComponent : public Component
{
public:
	KeyboardControlComponent() = default;
	KeyboardControlComponent(SDL_Scancode upKey, SDL_Scancode downKey, SDL_Scancode leftKey, SDL_Scancode rightKey, SDL_Scancode shootKey, SDL_Scancode focusKey, SDL_Scancode bombKey) :
		upKey(upKey), downKey(downKey), leftKey(leftKey), rightKey(rightKey), shootKey(shootKey), focusKey(focusKey), bombKey(bombKey) {};

	SDL_Scancode GetUpKey() { return upKey; }
	SDL_Scancode GetDownKey() { return downKey; }
	SDL_Scancode GetLeftKey() { return leftKey; }
	SDL_Scancode GetRightKey() { return rightKey; }
	SDL_Scancode GetShootKey() { return shootKey; }
	SDL_Scancode GetBombKey() { return bombKey; }
	SDL_Scancode GetFocusKey() { return focusKey; }
private:
	SDL_Scancode upKey{ SDL_SCANCODE_UP };
	SDL_Scancode downKey{ SDL_SCANCODE_DOWN };
	SDL_Scancode leftKey{ SDL_SCANCODE_LEFT };
	SDL_Scancode rightKey{ SDL_SCANCODE_RIGHT };
	SDL_Scancode shootKey{ SDL_SCANCODE_KP_0 };
	SDL_Scancode focusKey{ SDL_SCANCODE_LSHIFT };
	SDL_Scancode bombKey{ SDL_SCANCODE_X };
};

