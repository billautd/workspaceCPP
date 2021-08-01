#pragma once
#include "glad/glad.h"
#include "glm.hpp"
#include "gtc/type_ptr.hpp"
#include <string>
#include "Material.h"
#include "DirLight.h"
#include "PointLight.h"

class Shader
{
private:
	GLuint id{ 0 };

	void CompileAndLinkShaders(const char* vertexShaderCode, const char* fragmentShaderCode);

public:
	Shader(const char* vertexPath, const char* fragmentPath);

	void Use() const { glUseProgram(id); }
	void Delete() const { glDeleteProgram(id); }

	void SetBoolean(const std::string name, const bool value) const { glUniform1i(glGetUniformLocation(id, name.c_str()), value); }
	void SetInt(const std::string name, const int value) const { glUniform1i(glGetUniformLocation(id, name.c_str()), value); }
	void SetFloat(const std::string name, const float value) const { glUniform1f(glGetUniformLocation(id, name.c_str()), value); }
	void SetVec3(const std::string name, const float x, const float y, const float z) const { glUniform3f(glGetUniformLocation(id, name.c_str()), x, y, z); }
	void SetVec3(const std::string name, const glm::vec3 value) const { SetVec3(name, value.x, value.y, value.z); }
	void SetMat4(const std::string name, const glm::mat4 value) const { glUniformMatrix4fv(glGetUniformLocation(id, name.c_str()), 1, GL_FALSE, glm::value_ptr(value)); }
	void SetDirLight(const DirLight& dirLight, const std::string name) const;
	void SetPointLight(const PointLight& dirLight, const std::string name) const;
};
