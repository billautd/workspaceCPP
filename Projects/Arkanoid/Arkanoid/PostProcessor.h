#pragma once
#include "Texture2D.h"
#include "glad/glad.h"
#include "Shader.h"

class PostProcessor {
public:
	PostProcessor(Shader shader, GLuint width, GLuint height);

	//Prepares postprocessor's framebuffer operations before rendering
	void BeginRender();
	//Should be called after rendering, so it stores all the rendered data into a texture object
	void EndRender();
	//Renders the postprocessor texture (as a screen-encompassing large sprite)
	void Render(GLfloat time);


	bool GetShake() { return shake; }
	void SetShake(bool shake) { this->shake = shake; }
	bool GetChaos() { return chaos; }
	void SetChaos(bool chaos) { this->chaos = chaos; }
	bool GetConfuse() { return confuse; }
	void SetConfuse(bool confuse) { this->confuse = confuse; }

private:
	Shader postProcessingShader{};
	Texture2D texture{};
	GLuint width{ 0 };
	GLuint height{ 0 };
	bool chaos{ false };
	GLfloat chaosStrength{ 0.05f };
	bool confuse{ false };
	bool shake{ false };
	GLfloat shakeStrength{ 0.002f };

	//Render state
	GLuint MSFBO{ 0 };
	GLuint FBO{ 0 };
	GLuint RBO{ 0 };
	GLuint VAO{ 0 };

	//Init quad for rendering postprocessing texture
	void InitRenderData();
};

