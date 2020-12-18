#include "MusicPlayer.h"

void MusicPlayer::PlayMusic(std::string name, bool loop) {
	Mix_PlayMusic(ResourceManager::GetMusic(name), loop ? -1 : 0);
}

void MusicPlayer::PlaySound(std::string name) {
	Mix_PlayChannel(0, ResourceManager::GetChunk(name), 0);
}