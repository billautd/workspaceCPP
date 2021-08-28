#version 420 core
#define OFFSET_SIZE 400
layout(location = 0) in vec3 pos;
layout(location = 1) in vec2 texCoords;
layout(location = 2) in mat4 instancedModel;

out vec2 fTexCoords;

layout(std140, binding = 0) uniform Matrices{
	mat4 projection;
	mat4 view;
};

void main() {
	gl_Position = projection * view * instancedModel * vec4(pos, 1.0f);
	fTexCoords = texCoords;
}