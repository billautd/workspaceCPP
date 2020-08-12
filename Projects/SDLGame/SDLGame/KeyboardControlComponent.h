#pragma once
#include "Component.h"
#include "TransformComponent.h"
#include "SpriteComponent.h"

class KeyboardControlComponent: public Component {
private:
	std::string upKey{ "" };
	std::string downKey{ "" };
	std::string leftKey{ "" };
	std::string rightKey{ "" };
	std::string shootKey{ "" };
	TransformComponent* transform{ nullptr };
	SpriteComponent* sprite{ nullptr };
public:
	KeyboardControlComponent() = default;
	~KeyboardControlComponent() = default;
	KeyboardControlComponent(std::string upKey, std::string downKey, std::string leftKey, std::string rightKey, std::string shootKey) {
		this->upKey = GetSDLKeyStringCode(upKey);
		this->downKey = GetSDLKeyStringCode(downKey);
		this->leftKey = GetSDLKeyStringCode(leftKey);
		this->rightKey = GetSDLKeyStringCode(rightKey);
		this->shootKey = GetSDLKeyStringCode(shootKey);
	}
	std::string getUpKey() const { return upKey; }
	std::string getDownKey() const { return downKey; }
	std::string getLeftKey() const { return leftKey; }
	std::string getRightKey() const { return rightKey; }

	std::string GetSDLKeyStringCode(std::string key) const{
		if (key.compare("up") == 0) return "1073741906";
		if (key.compare("down") == 0) return "1073741905";
		if (key.compare("left") == 0) return "1073741904";
		if (key.compare("right") == 0) return "1073741903";
		if (key.compare("space") == 0) return "32";
		return std::to_string(static_cast<int>(key[0]));
	}

	void Initialize() override {
		transform = GetOwner()->GetComponent<TransformComponent>();
		sprite = GetOwner()->GetComponent<SpriteComponent>();
	}

	void Update(float deltaTime) override {
		if (Game::event.type == SDL_KEYDOWN) {
			std::string keyCode = std::to_string(Game::event.key.keysym.sym);
			if (keyCode.compare(upKey) == 0) {
				transform->SetVelocity(0,-200);
				sprite->Play("AnimationUp");
			}
			if (keyCode.compare(downKey) == 0) {
				transform->SetVelocity(0, 200);
				sprite->Play("AnimationDown");
			}
			if (keyCode.compare(leftKey) == 0) {
				transform->SetVelocity(-200, 0);
				sprite->Play("AnimationLeft");
			}
			if (keyCode.compare(rightKey) == 0) {
				transform->SetVelocity(200, 0);
				sprite->Play("AnimationRight");
			}
			if (keyCode.compare(shootKey) == 0) {
				//TODO ShootKey
			}
		}
		if (Game::event.type == SDL_KEYUP) {
			std::string keyCode = std::to_string(Game::event.key.keysym.sym);
			if (keyCode.compare(upKey) == 0 || keyCode.compare(downKey) == 0) 
				transform->SetVelocity(static_cast<int>(transform->GetVelocity().x), 0);
			if (keyCode.compare(leftKey) == 0 || keyCode.compare(rightKey) == 0) 
				transform->SetVelocity(0, static_cast<int>(transform->GetVelocity().y));
			if (keyCode.compare(shootKey) == 0) {
				//TODO ShootKey
			}
		}
	}

	void Render() override {

	}
};
