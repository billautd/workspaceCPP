#include "GameLevel.h"
#include "ResourceManager.h"

void GameLevel::Load(const char* file, GLuint levelWidth, GLuint levelHeight) {
	//Clear old data
	this->bricks.clear();

	//Load
	GLuint tileCode;
	GameLevel level;
	std::string line;
	std::ifstream fstream(file);
	std::vector<std::vector<GLuint>> tileData;
	if (fstream) {
		while (std::getline(fstream, line)) {
			std::istringstream sstream(line);
			std::vector<GLuint> row;
			while (sstream >> tileCode)
				row.emplace_back(tileCode);
			tileData.emplace_back(row);
		}
		if (tileData.size() > 0)
			this->Init(tileData, levelWidth, levelHeight);
	}
	fstream.close();
}

void GameLevel::Draw(SpriteRenderer& renderer) {
	for (size_t i = 0; i < this->bricks.size(); ++i) {
		GameObject tile = this->bricks.at(i);
		if (!tile.IsDestroyed())
			tile.Draw(renderer);
	}
}

bool GameLevel::IsCompleted() {
	for (GameObject& tile : this->bricks) {
		if (!tile.IsDestroyed() && !tile.IsSolid())
			return false;
	}
	return true;
}

void GameLevel::Init(std::vector<std::vector<GLuint>> tileData, GLuint levelWidth, GLuint levelHeight) {
	//Dimensions
	size_t height = tileData.size();
	size_t width = tileData.at(0).size();
	GLfloat unitWidth = levelWidth / static_cast<GLfloat>(width);
	GLfloat unitHeight = levelHeight / static_cast<GLfloat>(height);

	//Init level tiles
	for (size_t y = 0; y < height; y++) {
		for (size_t x = 0; x < width; x++) {
			//If solid (id = 1)
			GLuint tileId = tileData.at(y).at(x);
			if (tileId == 1) {
				glm::vec2 pos(unitWidth * x, unitHeight * y);
				glm::vec2 size(unitWidth, unitHeight);
				GameObject obj(pos, size, ResourceManager::GetTexture("solidTile"), glm::vec3(0.8f, 0.8f, 0.7f));
				obj.SetSolid(true);
				this->bricks.emplace_back(obj);
			}
			//If destroyable tile (id > 1)
			else if (tileId > 1) {
				glm::vec2 pos(unitWidth * x, unitHeight * y);
				glm::vec2 size(unitWidth, unitHeight);
				glm::vec3 color{};
				if (tileId == 2)
					color = glm::vec3(0.2f, 0.6f, 1.0f);
				else if (tileId == 3)
					color = glm::vec3(0.0f, 0.7f, 0.0f);
				else if (tileId == 4)
					color = glm::vec3(0.8f, 0.8f, 0.4f);
				else if (tileId == 5)
					color = glm::vec3(1.0f, 0.5f, 0.0f);

				GameObject obj(pos, size, ResourceManager::GetTexture("nonSolidTile"), color);
				this->bricks.emplace_back(obj);
			}
		}
	}
}
