#pragma once
#include <map>
#include <string>
#include "Texture2D.h"

class Textures2DManager
{
private:
	static std::map<std::string, Texture2D> textures2D;

public:
	static const Texture2D& Generate(const std::string name, const std::string path);
	static const Texture2D& GetTexture2D(const std::string name) { return textures2D.at(name); }
	static void Clear() { textures2D.clear(); }
};

