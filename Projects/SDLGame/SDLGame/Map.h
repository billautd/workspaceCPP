#pragma once
#include <string>

class Map {
private:
	std::string textureAssetId{ "" };
	float scale{ 0 };
	unsigned int tileSize{ 0 };
	unsigned int mapSizeX{ 0 };
	unsigned int mapSizeY{ 0 };
public:
	Map() = default;
	~Map() = default;
	Map(std::string textureAssetId, float scale, unsigned int tileSize);
	void LoadMap(std::string filePath, unsigned int mapTileSizeX, unsigned int mapTileSizeY);
	void AddTile(int sourceX, int sourceY, int x, int y);

	unsigned int GetMapSizeX() const { return mapSizeX; }
	unsigned int GetMapSizeY() const { return mapSizeY; }
};