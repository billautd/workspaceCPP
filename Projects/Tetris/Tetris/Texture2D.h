#pragma once
#include "glad/glad.h"

class Texture2D {
public:
	Texture2D();
	~Texture2D() = default;

	//Generate texture from image data
	void Generate(GLuint width, GLuint height, unsigned char* data);
	//Binds texture as current active GL_TEXTURE_2D
	void Bind();
	//Deletes texture
	void Delete();

	//Utility
	GLuint GetID() { return id; }
	void SetInternalFormat(GLuint internalFormat) { this->internalFormat = internalFormat; }
	void SetImageFormat(GLuint imageFormat) { this->imageFormat = imageFormat; }

private:
	GLuint id{ 0 };

	GLuint width{ 0 };
	GLuint height{ 0 };

	GLuint internalFormat{ 0 };
	GLuint imageFormat{ 0 };
	GLuint wrapS{ 0 };
	GLuint wrapT{ 0 };
	GLuint filterMin{ 0 };
	GLuint filterMag{ 0 };
};

