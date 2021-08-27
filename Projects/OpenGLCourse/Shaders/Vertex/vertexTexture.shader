#version 420 core
layout(location = 0) in vec3 pos;
layout(location = 1) in vec2 texCoords;

out vec2 fTexCoords;

layout(std140, binding = 0) uniform Matrices{
	mat4 projection;
	mat4 view;
};

uniform mat4 model;

void main() {
	gl_Position = projection * view * model * vec4(pos, 1.0f);
	fTexCoords = texCoords;
}