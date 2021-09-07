#version 430 core
layout(location = 0) in vec2 pos;
layout(location = 1) in vec2 texCoords;

out vec2 fTexCoords;

uniform mat4 projection;
uniform mat4 model;

void main() {
	gl_Position = projection * model * vec4(pos, 0.0f, 1.0f);
	fTexCoords = texCoords;
}