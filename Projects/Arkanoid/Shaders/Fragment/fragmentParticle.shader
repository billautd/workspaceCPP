#version 430 core

in vec2 texCoords;
out vec4 color;

uniform vec4 particleColor;
uniform sampler2D sprite;

void main() {
	color = texture(sprite, texCoords) * particleColor;
}