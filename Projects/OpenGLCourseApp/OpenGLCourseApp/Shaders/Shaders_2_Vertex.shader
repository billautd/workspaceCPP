#version 330 core

layout(location = 0) in vec3 pos;
layout(location = 1) in vec3 color;

out vec3 vertexColor;

uniform float xOffset;

void main() {
	//Move triangle to the right
	gl_Position = vec4(pos.x + xOffset, pos.y, pos.z, 1.0f);
	vertexColor = color;
}