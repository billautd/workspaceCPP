#pragma once
#include "IModelObject.h"

class Texture2D : public IModelObject
{
public:
	GLuint width{ 0 };
	GLuint height{ 0 };
	GLuint internalFormat{ GL_RGB };
	GLuint imageFormat{ GL_RGB };
	GLuint wrapS{ GL_REPEAT };
	GLuint wrapT{ GL_REPEAT };
	GLuint filterMin{ GL_LINEAR };
	GLuint filterMag{ GL_LINEAR };

	void Bind() const {glBindTexture(GL_TEXTURE_2D, id);}
};

