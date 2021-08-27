#version 420 core
#define OFFSET_SIZE 100
layout(location = 0) in vec3 pos;
layout(location = 1) in vec2 texCoords;

out vec2 fTexCoords;

layout(std140, binding = 0) uniform Matrices{
	mat4 projection;
	mat4 view;
};

uniform vec2 offsets[OFFSET_SIZE];

void main() {
	vec2 offset = offsets[gl_InstanceID];
	mat4 model = mat4(
		1.0f, 0.0f, 0.0f, offset.x,
		0.0f, 1.0f, 0.0f, 0.0f,
		0.0f, 0.0f, 1.0, offset.y,
		0.0f, 0.0f, 0.0f, 1.0f);
	gl_Position = projection * view * model * vec4(pos, 1.0f);
	fTexCoords = texCoords;
}