#pragma once
#include "glad/glad.h"

class Texture2D {
public:
	//C/D
	Texture2D();
	~Texture2D() = default;

	//Generates texture from image data
	void Generate(GLuint width, GLuint height, unsigned char* data);
	//Binds texture as curretn active GL_TEXTURE_2D
	void Bind() const;
	//Deletes texture
	void Delete();

	//Utility
	GLuint GetId() { return this->id; }
	void SetInternalFormat(GLuint internalFormat) { this->internalFormat = internalFormat; }
	void SetImageFormat(GLuint imageFormat) { this->imageFormat = imageFormat; }
private:
	//Texture id
	GLuint id{ 0 };
	//Texture image dimensions
	GLuint width{ 0 };
	GLuint height{ 0 };
	//Texture format
	GLuint internalFormat{ 0 };
	GLuint imageFormat{ 0 };
	//Texture config
	GLuint wrapS{ 0 };
	GLuint wrapT{ 0 };
	GLuint filterMin{ 0 };
	GLuint filterMag{ 0 };

};

