#include "Map.h"
#include "TileComponent.h"
#include "Entity.h"
#include "EntityManager.h"
#include <fstream>

extern EntityManager entityManager;

Map::Map(std::string textureAssetId, float scale, unsigned int tileSize) : textureAssetId(textureAssetId), scale(scale), tileSize(tileSize) {}

void Map::LoadMap(std::string filePath, unsigned int mapTileSizeX, unsigned int mapTileSizeY) {
	std::fstream mapFile;
	mapFile.open(filePath);
	if (!mapFile) {
		std::cerr << "Cannot open map file at " << filePath << '\n';
	}

	mapSizeX = static_cast<int>(mapTileSizeX * tileSize * scale);
	mapSizeY = static_cast<int>(mapTileSizeY * tileSize * scale);

	for (unsigned int y = 0; y < mapTileSizeY; y++) {
		for (unsigned int x = 0; x < mapTileSizeX; x++) {
			char c;
			mapFile.get(c);
			int sourceRectY = atoi(&c) * tileSize;
			mapFile.get(c);
			int sourceRectX = atoi(&c) * tileSize;
			AddTile(sourceRectX, sourceRectY, static_cast<int>(x * scale * tileSize), static_cast<int>(y * scale * tileSize));
			//Bypass comma
			mapFile.ignore();
		}
	}
	mapFile.close();
}

void Map::AddTile(int sourceRectX, int sourceRectY, int x, int y) {
	Entity& newTile(entityManager.AddEntity("Tile", LayerType::TILE_LAYER));
	newTile.AddComponent<TileComponent>(textureAssetId, sourceRectX, sourceRectY, x, y, scale, tileSize);
}
