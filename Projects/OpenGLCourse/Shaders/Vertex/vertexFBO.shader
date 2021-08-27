#version 420 core
layout(location = 0) in vec3 pos;
layout(location = 1) in vec2 texCoords;

out vec2 fTexCoords;

void main() {
	gl_Position = vec4(pos.x, pos.y, 0.0f, 1.0f);
	fTexCoords = texCoords;
}