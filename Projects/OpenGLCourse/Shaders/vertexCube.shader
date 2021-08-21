#version 330 core
layout(location = 0) in vec3 pos;
layout(location = 1) in vec2 texCoords;
layout(location = 2) in vec3 normal;

out vec2 fTexCoords;
out vec3 fNormal;
out vec3 fFragPos;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main() {
	gl_Position = projection * view * model * vec4(pos, 1.0f);
	fTexCoords = texCoords;
	fFragPos = vec3(model * vec4(pos, 1.0f));
	fNormal = mat3(transpose(inverse(model))) * normal;
}