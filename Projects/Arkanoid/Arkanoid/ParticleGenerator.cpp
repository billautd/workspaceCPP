#include "ParticleGenerator.h"
#include "Constants.h"

ParticleGenerator::ParticleGenerator() {
	this->Init();
}

ParticleGenerator::ParticleGenerator(Shader& shader, Texture2D& texture, GLuint amount) : shader(shader), texture(texture), amount(amount) {
	this->Init();
}

void ParticleGenerator::Init() {
	for (GLuint i{ 0 }; i < amount; i++)
		particles.emplace_back(Particle());

	GLuint VBO{};

	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glBindVertexArray(VAO);
	{
		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(QUAD_TEXTURE_VERTICES), QUAD_TEXTURE_VERTICES, GL_STATIC_DRAW);

		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(GL_FLOAT), (void*)0);
	}
	glBindVertexArray(0);
}

GLuint lastUsedParticle{ 0 };
GLuint ParticleGenerator::FirstUnusedParticle() {
	for (GLuint i{ lastUsedParticle }; i < amount; i++) {
		if (particles.at(i).life <= 0.0f) {
			lastUsedParticle = i;
			return i;
		}
	}
	for (GLuint i{ 0 }; i < lastUsedParticle; i++) {
		if (particles.at(i).life <= 0.0f) {
			lastUsedParticle = i;
			return i;
		}
	}

	lastUsedParticle = 0;
	return 0;
}

void ParticleGenerator::RespawnParticle(Particle& particle, GameObject& object, glm::vec2 offset) {
	GLfloat random{ (rand() % 100 - 50) / 10.0f };
	GLfloat randomColor = 0.5f + (rand() % 100) / 100.0f;
	particle.position = object.GetPosition() + random + offset;
	particle.color = glm::vec4(randomColor, randomColor, randomColor, 1.0f);
	particle.life = 1.0f;
	particle.velocity = object.GetVelocity() * 0.1f;

}

void ParticleGenerator::Update(GLfloat dt, GameObject& object, glm::vec2 offset, GLuint newParticlesAmount) {
	for (GLuint i{ 0 }; i < newParticlesAmount; i++) {
		GLuint unusedParticle = FirstUnusedParticle();
		RespawnParticle(particles.at(unusedParticle), object, offset);
	}
	//Update particles
	for (GLuint i{ 0 }; i < amount; i++) {
		Particle& p = particles.at(i);
		p.life -= dt;
		if (p.life > 0.0f) {
			p.position -= p.velocity * dt;
			p.color.a -= dt * 2.5f;
		}
	}
}

void ParticleGenerator::Render() {
	glBlendFunc(GL_SRC_ALPHA, GL_ONE);
	shader.Use();
	for (GLuint i{ 0 }; i < amount; i++) {
		Particle& p = particles.at(i);
		shader.SetVector2f("offset", p.position);
		shader.SetVector4f("color", p.color);
		texture.Bind();
		glBindVertexArray(VAO); {
			glDrawArrays(GL_TRIANGLES, 0, 6);
		}
		glBindVertexArray(0);
	}
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}
