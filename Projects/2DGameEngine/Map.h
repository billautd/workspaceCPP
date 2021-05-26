#pragma once
#include <string>

class Map
{
private:
	const std::string textureId{ "" };
	const float scale{ 1.0f };
	const unsigned int tileSize{ 0 };
	const unsigned int mapSizeX{ 0 };
	const unsigned int mapSizeY{ 0 };
public:
	Map(const std::string textureId, const unsigned int mapSizeX, const unsigned int mapSizeY, const unsigned int tileSize, const float scale = 1.0f) :
		mapSizeX(mapSizeX), mapSizeY(mapSizeY), textureId(textureId), tileSize(tileSize), scale(scale) {}
	void LoadMap(const char* filePath) const;
	void AddTile(const unsigned int sourceX, const unsigned int sourceY, const unsigned int x, const unsigned int y) const;

	const int GetMapSizePixelsX() const { return static_cast<int>(mapSizeX * tileSize * scale); }
	const int GetMapSizePixelsY() const { return static_cast<int>(mapSizeY * tileSize * scale); }
};

