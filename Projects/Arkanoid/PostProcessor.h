#pragma once
#include "Shader.h"
#include "Texture2D.h"

class PostProcessor
{
public:
	PostProcessor(Shader shader, const GLuint width, const GLuint height) : shader(shader), width(width), height(height){ InitRenderData(); }
	~PostProcessor() {};

	GLuint width{};
	GLuint height{};

	//Effects
	bool confuse{false};
	bool shake{ false };
	bool chaos{ false };

	//Prepares the postprocessor's framebuffer operations before rendering the game
	void BeginRender();

	//Should be called after rendering the game, so it stores all the rendered data into a texture object
	void EndRender();

	//Renders the postprocessor's texture quad (as a screen-encompassing large sprite)
	void Render(const GLfloat time);

private:
	//Rendering
	Shader shader{};
	Texture2D texture{};

	GLuint msfbo{}; //Multisampled frame buffer object
	GLuint fbo{}; //Regular FBO, used for blitting MS color-buffer to texture
	GLuint rbo{}; //Used for multisampled color buffer
	GLuint vao{};

	//Initialize quad for rendering postprocessing texture
	void InitRenderData();

	//Initialize framebuffer
	void InitFramebuffers();
};

