#pragma once
#include "glm/glm.hpp"
#include "glad/glad.h"
#include "GameObject.h"
#include <vector>

struct Particle {
	glm::vec2 position{};
	glm::vec2 velocity{};
	glm::vec4 color{ 1.0f };
	GLfloat life{};

	Particle() = default;
};

class ParticleGenerator {
public:
	ParticleGenerator();
	ParticleGenerator(Shader& shader, Texture2D& texture, GLuint amount);
	void Update(GLfloat dt, GameObject& object, glm::vec2 offset, GLuint newParticlesAmount);
	void Render();
private:
	Shader shader{};
	Texture2D texture{};
	GLuint VAO{};

	GLuint amount{};
	std::vector<Particle> particles{};
	void Init();

	GLuint FirstUnusedParticle();
	void RespawnParticle(Particle& particle, GameObject& object, glm::vec2 offset);

};