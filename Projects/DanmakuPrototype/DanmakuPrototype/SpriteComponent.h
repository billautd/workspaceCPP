#pragma once
#include "Shader.h"
#include "Texture2D.h"
#include "ResourceManager.h"
#include "TransformComponent.h"
#include "Entity.h"
class SpriteComponent : public Component
{
public:
	SpriteComponent(Shader& shader, Texture2D& texture, glm::vec2 size, bool isFixed, GLfloat alpha = 1.0f, glm::vec3 color = glm::vec3(1.0f), GLfloat rotation = 0.0f);
	~SpriteComponent() = default;

	void Init() override;
	void Update(GLfloat dt) override;
	void Render() override;
private:
	Shader shader{};
	GLuint quadVAO{ 0 };

	TransformComponent* transform;
	Texture2D& texture;
	glm::vec2 size{};
	GLfloat alpha{ 1.0f };
	glm::vec3 color{ glm::vec3(1.0f) };
	GLfloat rotation{ 0.0f };	//In degrees


	bool isFixed{ false };


	void InitRenderData();
};

