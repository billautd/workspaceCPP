#include "ParticleRenderer.h"

void ParticleRenderer::Update(const GLfloat dt, const GameObject& object, const GLuint newParticles, const glm::vec2 offset)
{
	//Add new particles
	for (GLuint i{ 0 }; i < newParticles; i++) {
		GLuint unusedParticle{ FirstUnusedParticle() };
		RespawnParticle(particles[unusedParticle], object, offset);
	}
	//Update all particles
	for (GLuint i{ 0 }; i < amount; i++) {
		Particle& p{ particles[i] };
		p.life -= dt;
		if (p.life > 0.0f) {
			p.position -= p.velocity * dt;
			p.color.a -= dt * 5.0f;
		}
	}
}

void ParticleRenderer::Draw()
{
	//Use additive blending to give it a glow effect
	glBlendFunc(GL_SRC_ALPHA, GL_ONE);
	shader.Use();
	for (const auto& p : particles) {
		if (p.life > 0.0f) {
			shader.SetVector2f("offset", p.position);
			shader.SetFloat("scale", PARTICLE_SCALE);
			shader.SetVector4f("particleColor", p.color);
			texture.Bind();
			glBindVertexArray(vao);
			{
				glDrawArrays(GL_TRIANGLES, 0, 6);
			}
			glBindVertexArray(0);
		}
	}
	//Reset blend
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

void ParticleRenderer::Init()
{
	//Set up mesh and attribute
	GLuint vbo{};
	const GLfloat particleQuad[] = {
		0.0f, 1.0f, 0.0f, 1.0f,
		1.0f, 0.0f, 1.0f, 0.0f,
		0.0f, 0.0f, 0.0f, 0.0f,

		0.0f, 1.0f, 0.0f, 1.0f,
		1.0f, 1.0f, 1.0f, 1.0f,
		1.0f, 0.0f, 1.0f, 0.0f
	};

	glGenVertexArrays(1, &vao);
	glGenBuffers(1, &vbo);
	glBindVertexArray(vao);
	{
		glBindBuffer(GL_ARRAY_BUFFER, vbo);
		glBufferData(GL_ARRAY_BUFFER, sizeof(Particle), particleQuad, GL_STATIC_DRAW);

		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), (void*)0);

		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}
	glBindVertexArray(0);

	for (GLuint i{ 0 }; i < amount; i++)
		particles.emplace_back(Particle());
}


GLuint lastUnusedParticle{};
const GLuint ParticleRenderer::FirstUnusedParticle()
{
	//First search from last unused particle
	for (GLuint i{ lastUnusedParticle }; i < amount; i++) {
		if (particles[i].life <= 0.0f) {
			lastUnusedParticle = i;
			return i;
		}
	}

	//Otherwise do linear search
	for (GLuint i{ 0 }; i < lastUnusedParticle; i++) {
		if (particles[i].life <= 0.0f) {
			lastUnusedParticle = i;
			return i;
		}
	}

	lastUnusedParticle = 0;
	return 0;
}

void ParticleRenderer::RespawnParticle(Particle& particle, const GameObject& object, const glm::vec2 offset)
{
	GLfloat random = ((rand() % 100) - 50.0f) / 10.0f;
	GLfloat rColor = 0.5f + ((rand() % 100) / 100.0f);
	particle.position = object.position + random + offset;
	particle.color = glm::vec4(rColor, rColor, rColor, 1.0f);
	particle.life = 1.0f;
	particle.velocity = object.velocity * 0.1f;
}
