#include "Label.h"

Label::Label(glm::vec2 position, std::string text, std::string name, LayerEnum layer) : Entity(name, layer) {
	SetEntityType(EntityTypeEnum::LABEL);
	transform = AddComponent<TransformComponent>(position, glm::vec2(), glm::vec2());
	this->text = AddComponent<TextComponent>(ResourceManager::GetShader("TextRendering"), text, "logopixies");
}