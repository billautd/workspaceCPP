#include "MusicManager.h"
#include "ResourceManager.h"

void MusicManager::PlayMusic(std::string name, bool loop) {
	Mix_PlayMusic(ResourceManager::GetMusic(name), loop ? -1 : 0);
}
