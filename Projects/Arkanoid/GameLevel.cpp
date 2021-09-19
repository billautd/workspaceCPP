#include "GameLevel.h"
#include "ResourceManager.h"
#include <fstream>
#include <sstream>

void GameLevel::Load(const char* file, const GLuint levelWidth, const GLuint levelHeight)
{
    bricks.clear();
    //Load from file
    std::ifstream stream(file);
    std::string line;
    std::vector<std::vector<GLuint>> tileData;
    if (stream) {
        while (std::getline(stream, line)) {
            std::istringstream sstream(line);
            std::vector<GLuint> row;
            GLuint tileCode;
            while (sstream >> tileCode) 
                row.push_back(tileCode);
            tileData.emplace_back(row);
        }
        if (!tileData.empty())
            Init(tileData, levelWidth, levelHeight);
    }
    stream.close();
}

void GameLevel::Draw(SpriteRenderer& renderer)
{
    for (auto& brick : bricks) {
        if (!brick.isDestroyed)
            brick.Draw(renderer);
    }
}

bool GameLevel::IsCompleted()
{
    for (const auto& brick : bricks) {
        if(!brick.isSolid && !brick.isDestroyed)
            return false;
    }
    return true;
}

void GameLevel::Init(const std::vector<std::vector<GLuint>> tileData, const GLuint levelWidth, const GLuint levelHeight)
{
    GLuint height{ static_cast<GLuint>(tileData.size()) };
    GLuint width{ static_cast<GLuint>(tileData[0].size()) };
    GLfloat unitWidth{ levelWidth / static_cast<GLfloat>(width) };
    GLfloat unitHeight{ levelHeight / static_cast<GLfloat>(height) };

    //Init level tiles based on tileData
    for (GLuint y{ 0 }; y < height; y++) {
        for (GLuint x{ 0 }; x < width; x++) {
            GLuint tileId{ tileData[y][x] };
            if (tileId >= 1){
                GameObject brick;
                brick.size = glm::vec2(unitWidth, unitHeight);
                brick.position = glm::vec2(unitWidth * x, unitHeight * y);
                glm::vec3 color{ glm::vec3(1.0f) };
                std::string textureId{ "block" };
                //Solid
                if (tileId == 1) {
                    color = glm::vec3(0.8f, 0.8f, 0.7f);
                    textureId = "blockSolid";
                    brick.isSolid = true;
                }
                //Not solid, determine color
                else if (tileId == 2)
                    color = glm::vec3(0.2f, 0.6f, 1.0f);
                else if (tileId == 3)
                    color = glm::vec3(0.0f, 0.7f, 0.0f);
                else if (tileId == 4)
                    color = glm::vec3(0.8f, 0.8f, 0.4f);
                else if (tileId == 5)
                    color = glm::vec3(1.0f, 0.5f, 0.0f);
                brick.color = color;
                brick.sprite = ResourceManager::GetTexture2D(textureId);
                bricks.emplace_back(brick);
            }
        }
    }
}
