#include "GLUtils.h"
#include "glad/glad.h"
#include <iostream>

void GLUtils::GetGLError() {
	switch (glGetError()) {
		case GL_NO_ERROR:                      std::cout << "NO GL ERROR\n"; break;
		case GL_INVALID_ENUM:                  std::cout << "INVALID_ENUM\n"; break;
		case GL_INVALID_VALUE:                 std::cout << "INVALID_VALUE\n"; break;
		case GL_INVALID_OPERATION:             std::cout << "INVALID_OPERATION\n"; break;
		case GL_STACK_OVERFLOW:                std::cout << "STACK_OVERFLOW\n"; break;
		case GL_STACK_UNDERFLOW:               std::cout << "STACK_UNDERFLOW\n"; break;
		case GL_OUT_OF_MEMORY:                 std::cout << "OUT_OF_MEMORY\n"; break;
		case GL_INVALID_FRAMEBUFFER_OPERATION: std::cout << "INVALID_FRAMEBUFFER_OPERATION\n";
	}
}
