#pragma once
#include "IUniqueId.h"

class Texture2D : public IUniqueId
{
public:
	GLint width{ 0 };
	GLint height{ 0 };
	GLuint internalFormat{ GL_RGB };
	GLuint imageFormat{ GL_RGB };
	GLuint wrapS{ GL_REPEAT };
	GLuint wrapT{ GL_REPEAT };
	GLuint filterMin{ GL_LINEAR };
	GLuint filterMag{ GL_LINEAR };

	void Bind() const {glBindTexture(GL_TEXTURE_2D, id);}
};

