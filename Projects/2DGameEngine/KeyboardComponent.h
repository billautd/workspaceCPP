#pragma once
#include "SpriteComponent.h"
#include <string>
class KeyboardComponent : public Component
{
private:
	const std::string upKey{ "1073741906" };
	const std::string downKey{ "1073741905" };
	const std::string leftKey{ "1073741904" };
	const std::string rightKey{ "1073741903" };
	const std::string shootKey;
	TransformComponent* transform{ nullptr };
	SpriteComponent* sprite{ nullptr };
public:
	void Init() override;
	void Update(const float deltaTime) override;

};

