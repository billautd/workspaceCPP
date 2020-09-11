#include "PostProcessor.h"
#include <iostream>
#include "Constants.h"
#include "Utils.h"

PostProcessor::PostProcessor(Shader shader, GLuint width, GLuint height) : postProcessingShader(shader), width(width), height(height) {
	//Init RBO, FBO
	glGenFramebuffers(1, &this->MSFBO);
	glGenFramebuffers(1, &this->FBO);
	glGenRenderbuffers(1, &this->RBO);

	//Init RB storage and bind it to MSFBO color buffer (without depth/stencil buffer)
	glBindFramebuffer(GL_FRAMEBUFFER, this->MSFBO);
	glBindRenderbuffer(GL_RENDERBUFFER, this->RBO);
	glRenderbufferStorageMultisample(GL_RENDERBUFFER, 4, GL_RGB, width, height); //Allocate storage for RBO of the texture's size
	glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_RENDERBUFFER, this->RBO); //Attach MS RBO to framebuffer
	if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
		std::cerr << "ERROR::POSTPROCESSOR: Failed to initialize MSFBO\n";

	//Also init the FBO/texture to blit MS color buffer to 
	//Used for shader operations (postprocessing effects)
	glBindFramebuffer(GL_FRAMEBUFFER, this->FBO);
	this->texture.Generate(width, height, NULL);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, this->texture.GetId(), 0);
	if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
		std::cerr << "ERROR::POSTPROCESSOR: Failed to initialize FBO\n";

	glBindFramebuffer(GL_FRAMEBUFFER, 0);

	//Init render data and uniforms
	this->InitRenderData();
	this->postProcessingShader.SetInteger("scene", 0, true);
	GLfloat offset = 1.0f / 300.0f;
	GLfloat offsets[9][2]{
		{ -offset, -offset },  // top left
		{ 0.0f, -offset },     // top center
		{ offset, -offset },   // top right
		{ -offset, 0.0f },     // center left
		{ 0.0f, 0.0f },        // center center
		{ offset, 0.0f },      // center right
		{ -offset, offset },   // bottom left
		{ 0.0f, offset },      // bottom center
		{ offset, offset },    // bottom right
	};
	glUniform2fv(glGetUniformLocation(this->postProcessingShader.GetId(), "offsets"), 9, (GLfloat*)offsets);
	int edge_kernel[9]{
		-1, -1, -1,
		-1,  8, -1,
		-1, -1, -1
	};

	glUniform1iv(glGetUniformLocation(this->postProcessingShader.GetId(), "edge_kernel"), 9, edge_kernel);

	GLfloat blur_kernel[9]{
		1.0f, 2.0f, 1.0f,
		2.0f, 4.0f, 2.0f,
		1.0f, 2.0f, 1.0f
	};
	Utils::normalizeArray(blur_kernel);

	glUniform1fv(glGetUniformLocation(this->postProcessingShader.GetId(), "blur_kernel"), 9, blur_kernel);
}

void PostProcessor::BeginRender() {
	glBindFramebuffer(GL_FRAMEBUFFER, this->MSFBO);
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);
}

void PostProcessor::EndRender() {
	// now resolve multisampled color-buffer into intermediate FBO to store to texture
	glBindFramebuffer(GL_READ_FRAMEBUFFER, this->MSFBO);
	glBindFramebuffer(GL_DRAW_FRAMEBUFFER, this->FBO);
	glBlitFramebuffer(0, 0, this->width, this->height, 0, 0, this->width, this->height, GL_COLOR_BUFFER_BIT, GL_NEAREST);
	glBindFramebuffer(GL_FRAMEBUFFER, 0); // binds both READ and WRITE framebuffer to default framebuffer
}

void PostProcessor::Render(GLfloat time) {
	this->postProcessingShader.Use();
	//Set uniforms
	this->postProcessingShader.SetFloat("time", time);
	this->postProcessingShader.SetInteger("confuse", this->confuse);
	this->postProcessingShader.SetInteger("chaos", this->chaos);
	this->postProcessingShader.SetFloat("chaosStrength", this->chaosStrength);
	this->postProcessingShader.SetInteger("shake", this->shake);
	this->postProcessingShader.SetFloat("shakeStrength", this->shakeStrength);

	//Render texture quad
	glActiveTexture(GL_TEXTURE0);
	this->texture.Bind();
	glBindVertexArray(this->VAO);
	glDrawArrays(GL_TRIANGLES, 0, 6);
	glBindVertexArray(0);
}

void PostProcessor::InitRenderData() {
	//Configure VAO/VBO
	GLuint VBO{ 0 };
	GLfloat vertices[]{
		//pos         //tex
		-1.0f, -1.0f, 0.0f, 0.0f,
		 1.0f,  1.0f, 1.0f, 1.0f,
		-1.0f,  1.0f, 0.0f, 1.0f,

		-1.0f, -1.0f, 0.0f, 0.0f,
		 1.0f, -1.0f, 1.0f, 0.0f,
		 1.0f,  1.0f, 1.0f, 1.0f
	};

	glGenVertexArrays(1, &this->VAO);
	glGenBuffers(1, &VBO);
	glBindVertexArray(this->VAO); {
		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), (void*)0);

		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}
	glBindVertexArray(0);
}
