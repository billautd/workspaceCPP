#pragma once
#include "Entity.h" 
#include "SpriteComponent.h"
#include "Constants.h"
#include "ResourceManager.h"
#include "CollisionUtils.h"
#include "TextComponent.h"
#include <functional>

class Label : public Entity {
public:
	Label(glm::vec2 position, std::string text, std::string name = "Label", LayerEnum layer = LayerEnum::UI_LAYER);

private:
	TransformComponent* transform{ nullptr };
	TextComponent* text{ nullptr };
};