#include "KeyboardComponent.h"

void KeyboardComponent::Init() {
	transform = GetOwner().GetComponent<TransformComponent>();
	sprite = GetOwner().GetComponent<SpriteComponent>();
}

void KeyboardComponent::Update(const float deltaTime) {
	if (Game::event.type == SDL_KEYDOWN) {
		const std::string keyCode = std::to_string(Game::event.key.keysym.sym);

		if (keyCode.compare(upKey) == 0) {
			transform->SetVelY(-200);
			transform->SetVelX(0);
			sprite->Play("upAnimation");
		}
		if (keyCode.compare(downKey) == 0) {
			transform->SetVelY(200);
			transform->SetVelX(0);
			sprite->Play("downAnimation");
		}
		if (keyCode.compare(leftKey) == 0) {
			transform->SetVelY(0);
			transform->SetVelX(-200);
			sprite->Play("leftAnimation");
		}
		if (keyCode.compare(rightKey) == 0) {
			transform->SetVelY(0);
			transform->SetVelX(200);
			sprite->Play("rightAnimation");
		}
		if (keyCode.compare(shootKey) == 0) {

		}
	}
	if (Game::event.type == SDL_KEYUP) {
		const std::string keyCode = std::to_string(Game::event.key.keysym.sym);

		if (keyCode.compare(upKey) == 0 || keyCode.compare(downKey) == 0) {
			transform->SetVelY(0);
		}
		if (keyCode.compare(leftKey) == 0 || keyCode.compare(rightKey) == 0) {
			transform->SetVelX(0);
		}
		if (keyCode.compare(shootKey) == 0) {

		}
	}
}