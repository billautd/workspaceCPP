#pragma once
#include "Shader.h"
#include "Component.h"
#include "Texture2D.h"
#include "Constants.h"
#include "Entity.h"

class SpriteComponent : public Component
{
public:
	SpriteComponent(Shader& shader, Texture2D& texture, bool isFixed, glm::vec3 color = glm::vec3(1.0f), GLfloat alpha = 1.0f)
		: shader(shader), texture(texture), isFixed(isFixed), alpha(alpha), color(color) {
		InitRenderData();
	};

	void Init() override;
	void Update(GLfloat dt) override;
	void Render() override;

	Shader& GetShader() { return shader; }
	Texture2D& GetTexture() { return texture; }
	bool IsFixed() { return isFixed; }
	glm::vec3 GetColor() { return color; }
	GLfloat GetAlpha() { return alpha; }
private:
	Shader shader{};
	GLuint quadVAO{ 0 };

	TransformComponent* transform{ nullptr };
	Texture2D& texture;
	GLfloat alpha{ 1.0f };
	glm::vec3 color{ glm::vec3(1.0f) };

	bool isFixed{ false };

	void InitRenderData();
};

