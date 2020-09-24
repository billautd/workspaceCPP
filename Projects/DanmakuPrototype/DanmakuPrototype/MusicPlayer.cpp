#include "MusicPlayer.h"
#include "ResourceManager.h"

void MusicPlayer::PlayMusic(std::string name, bool loop) {
	if (ResourceManager::ItemExists("musics", name))
		Mix_PlayMusic(ResourceManager::GetMusic(name), loop ? -1 : 0);
}

void MusicPlayer::PlaySound(std::string name) {
	if (ResourceManager::ItemExists("chunks", name))
		Mix_PlayChannel(0, ResourceManager::GetChunk(name), 0);
}