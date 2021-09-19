#pragma once
#include "Particle.h"
#include <vector>
#include "Shader.h"
#include "Texture2D.h"
#include "Constants.h"
#include "GameObject.h"

class ParticleRenderer
{
public:
	ParticleRenderer(Shader shader, Texture2D texture) : shader(shader), texture(texture) { Init(); };
	~ParticleRenderer() {};
	 
	void Update(const GLfloat dt, const GameObject& object, const GLuint newParticles, const glm::vec2 offset = glm::vec2(0.0f));
	void Draw();
private:
	//Particles
	std::vector<Particle> particles{};
	const GLuint amount{ MAX_PARTICLES };

	//Rendering
	Shader shader{};
	Texture2D texture{};
	GLuint vao{};

	//Init buffer and vertex attrivutes
	void Init();
	//Returns first particle index that's currently unused <=> life <= 0.0f
	//0 if no inactive particle
	const GLuint FirstUnusedParticle();
	//Respawns particle
	void RespawnParticle(Particle& particle, const GameObject& object, const glm::vec2 = glm::vec2(0.0f));
};

