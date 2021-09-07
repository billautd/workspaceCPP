#pragma once
#include "glad\glad.h"
#include "glm.hpp"
#include "gtc/type_ptr.hpp"
#include <string>
#include "IUniqueId.h"

class Shader : public IUniqueId
{
public:
	void Use() const { glUseProgram(id); }
	void Delete() const { glDeleteProgram(id); }

	void SetBoolean(const std::string name, const bool value) const { glUniform1i(glGetUniformLocation(id, name.c_str()), value); }
	void SetInt(const std::string name, const int value) const { glUniform1i(glGetUniformLocation(id, name.c_str()), value); }
	void SetFloat(const std::string name, const float value) const { glUniform1f(glGetUniformLocation(id, name.c_str()), value); }
	void SetVec2(const std::string name, const float x, const float y) { glUniform2f(glGetUniformLocation(id, name.c_str()), x, y); }
	void SetVec2(const std::string name, const glm::vec2 value) { SetVec2(name, value.x, value.y); }
	void SetVec3(const std::string name, const float x, const float y, const float z) const { glUniform3f(glGetUniformLocation(id, name.c_str()), x, y, z); }
	void SetVec3(const std::string name, const glm::vec3 value) const { SetVec3(name, value.x, value.y, value.z); }
	void SetMat4(const std::string name, const glm::mat4 value) const { glUniformMatrix4fv(glGetUniformLocation(id, name.c_str()), 1, GL_FALSE, glm::value_ptr(value)); }
};
