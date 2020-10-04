#include "EventManager.h"

SDL_Event EventManager::event{};
int EventManager::keysNbr{ 1024 };
bool* EventManager::keysProcessed{ new bool[keysNbr] {false} };
const Uint8* EventManager::keys{ new Uint8[keysNbr] };