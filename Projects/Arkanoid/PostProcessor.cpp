#include "PostProcessor.h"
#include <iostream>

void PostProcessor::BeginRender()
{
	glBindFramebuffer(GL_FRAMEBUFFER, msfbo);
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);
}

void PostProcessor::EndRender()
{
	glBindFramebuffer(GL_READ_FRAMEBUFFER, msfbo);
	glBindFramebuffer(GL_DRAW_FRAMEBUFFER, fbo);
	glBlitFramebuffer(0, 0, width, height, 0, 0, width, height, GL_COLOR_BUFFER_BIT, GL_NEAREST);

	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void PostProcessor::Render(const GLfloat time)
{
	shader.Use();
	shader.SetFloat("time", time);
	shader.SetInteger("confuse", confuse);
	shader.SetInteger("shake", shake);
	shader.SetInteger("chaos", chaos);

	//Render texture quad
	glActiveTexture(GL_TEXTURE0);
	texture.Bind();
	glBindVertexArray(vao);
	{
		glDrawArrays(GL_TRIANGLES, 0, 6);
	}
	glBindVertexArray(0);
}

void PostProcessor::InitRenderData()
{
	InitFramebuffers();

	//Configure vao/vbo
	GLuint vbo{};
	const GLfloat vertices[] {
		// pos        // tex
		-1.0f, -1.0f, 0.0f, 0.0f,
		 1.0f,  1.0f, 1.0f, 1.0f,
		-1.0f,  1.0f, 0.0f, 1.0f,

		-1.0f, -1.0f, 0.0f, 0.0f,
		 1.0f, -1.0f, 1.0f, 0.0f,
		 1.0f,  1.0f, 1.0f, 1.0f
	};

	glGenVertexArrays(1, &vao);
	glGenBuffers(1, &vbo);

	glBindVertexArray(vao);
	{
		glBindBuffer(GL_ARRAY_BUFFER, vbo);
		glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(GL_FLOAT), (void*)0);
	}
	glBindVertexArray(0);
}

void PostProcessor::InitFramebuffers() {
	//Init renderbuffer/frambuffer object
	glGenFramebuffers(1, &msfbo);
	glGenFramebuffers(1, &fbo);
	glGenRenderbuffers(1, &rbo);
	//Init renderbuffer storage with a multisampled color buffer (don't need a depth/stencil buffer)
	glBindFramebuffer(GL_FRAMEBUFFER, msfbo);
	{
		glBindRenderbuffer(GL_RENDERBUFFER, rbo);
		glRenderbufferStorageMultisample(GL_RENDERBUFFER, 4, GL_RGB, width, height);
		glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_RENDERBUFFER, rbo);
		if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
			std::cerr << "ERROR::POSTPROCESSOR : Failed to initialize MSFBO" << std::endl;
	}

	//Also init the FBO/texture to blit multisampled color-buffer to, used for shader operations (for effects)
	glBindFramebuffer(GL_FRAMEBUFFER, fbo);
	{
		texture.Generate(width, height, nullptr);
		//Attach texture to framebuffer as color attachment
		glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, texture.id, 0);
		if(glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
			std::cerr << "ERROR::POSTPROCESSOR : Failed to initialize FBO" << std::endl;
	}
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}
