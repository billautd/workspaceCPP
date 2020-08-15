#version 330 core

layout(location = 0) in vec3 vPos;
layout(location = 1) in vec3 vNormal;
layout(location = 2) in vec2 vTexturePos;


out vec3 normal;
out vec2 texturePos;
out vec3 fragmentPos;
out vec3 lightPos;

uniform vec3 vLightPos;
uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main() {
	gl_Position = projection * view * model * vec4(vPos, 1.0f);
	normal = vNormal;
	fragmentPos = vec3(view * model * vec4(vPos, 1.0f));
	texturePos = vTexturePos;
	lightPos = vec3(view * vec4(vLightPos, 1.0f));
};