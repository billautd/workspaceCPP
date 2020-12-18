#pragma once
#include <string>
#include "ResourceManager.h"

class MusicPlayer {
public:
	void PlayMusic(std::string name, bool loop);
	void PlaySound(std::string name);
};

