#pragma once
#include <map>
#include <string>
#include "Shader.h"

class ShaderManager
{
private:
	static std::map<std::string, Shader> shaders;

	static const Shader& LoadShader(const char* vertexPath, const char* vertexSource,
		const char* fragmentPath, const char* fragmentSource,
		const char* geometryPath, const char* geometrySource);
	static void CheckCompileErrors(const GLuint object, const std::string type, const char* path);
public:
	static const Shader& GetShader(const std::string name) { return shaders.at(name); }
	static const Shader& LoadShaderFromPath(const std::string name, const char* vertexPath, const char* fragmentPath, const char* geometryPath);

	static void Clear() { shaders.clear(); }

};
