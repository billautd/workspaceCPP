#include "Texture2D.h"

Texture2D::Texture2D() :
	internalFormat(GL_RGB), imageFormat(GL_RGB), wrapS(GL_REPEAT), wrapT(GL_REPEAT), filterMin(GL_LINEAR), filterMag(GL_LINEAR) {
	glGenTextures(1, &this->id);
}

void Texture2D::Generate(GLuint width, GLuint height, unsigned char* data) {
	this->width = width;
	this->height = height;

	//Create
	glBindTexture(GL_TEXTURE_2D, this->id);
	glTexImage2D(GL_TEXTURE_2D, 0, this->internalFormat, width, height, 0, this->imageFormat, GL_UNSIGNED_BYTE, data);

	//Set texture wrap and filter
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, this->wrapS);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, this->wrapT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, this->filterMin);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, this->filterMag);
	//Unbind
	glBindTexture(GL_TEXTURE_2D, 0);

}

void Texture2D::Bind() {
	glBindTexture(GL_TEXTURE_2D, this->id);

}

void Texture2D::Delete() {
	glDeleteTextures(1, &this->id);
	this->id = 0;
	this->width = 0;
	this->height = 0;
	this->internalFormat = 0;
	this->imageFormat = 0;
	this->wrapS = 0;
	this->wrapT = 0;
	this->filterMin = 0;
	this->filterMag = 0;
}
