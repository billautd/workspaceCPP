#pragma once
#include <map>
#include <string>
#include "Shader.h"

class ShaderManager
{
private:
	static std::map<std::string, Shader> shaders;

	static void CheckCompileErrors(unsigned int object, std::string type);
public:
	static const Shader& GetShader(const std::string name) { return shaders.at(name); }
	static const Shader& LoadShader(const std::string name, const char* vertexSource, const char* fragmentSource, const char* geometrySource);
	static void Clear() { shaders.clear(); }

};
