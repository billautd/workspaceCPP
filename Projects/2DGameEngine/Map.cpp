#include "Map.h"
#include "Game.h"
#include "TileComponent.h"
#include <fstream>

void Map::LoadMap(const char* filePath) const {
	std::fstream mapFile;
	mapFile.open(filePath);

	for (unsigned int y{ 0 }; y < mapSizeY; y++) {
		for (unsigned int x{ 0 }; x < mapSizeX; x++) {
			char c{};
			mapFile.get(c);
			const unsigned int sourceRectY{ atoi(&c) * tileSize };
			mapFile.get(c);
			const unsigned int sourceRectX{ atoi(&c) * tileSize };
			AddTile(sourceRectX, sourceRectY, static_cast<unsigned int>(x * scale * tileSize), static_cast<unsigned int>(y * scale * tileSize));
			mapFile.ignore();
		}
	}
	mapFile.close();
}

void Map::AddTile(const unsigned int sourceX, const unsigned int sourceY, const unsigned int x, const unsigned int y) const {
	Game::entityManager.AddEntity(std::make_unique<Entity>("Tile", LayerTypeEnum::TILEMAP_LAYER))
		->AddComponent<TileComponent>(sourceX, sourceY, x, y, tileSize, scale, textureId);
}
