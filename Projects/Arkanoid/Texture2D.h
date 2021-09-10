#pragma once
#include "glad/glad.h"

class Texture2D
{
public:
	//Holds the id of the texture object, used for all texture operations to reference this specific texture
	GLuint id{};
	//Texture image dimensions
	GLuint width{};
	GLuint height{};
	//Texture fomrmat
	GLuint imageFormat{GL_RGB};
	GLuint internalFormat{GL_RGB};
	//Texture configuration
	GLuint wrapS{GL_REPEAT};
	GLuint wrapT{GL_REPEAT};
	GLuint filterMin{GL_LINEAR};
	GLuint filterMag{GL_LINEAR};

	Texture2D() { glGenTextures(1, &id); }
	~Texture2D(){}

	//Generates the texture from image data
	void Generate(const GLuint width, const GLuint height, const unsigned char* data);
	//Binds/Unbinds the texture as the current GL_TEXTURE_2D texture object
	void Bind() const { glBindTexture(GL_TEXTURE_2D, id); }
	void Unbind() const { glBindTexture(GL_TEXTURE_2D, 0); }
};

