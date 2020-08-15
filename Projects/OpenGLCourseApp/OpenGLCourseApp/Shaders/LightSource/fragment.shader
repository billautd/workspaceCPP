#version 330 core

in vec3 normal;

out vec4 fragColor;

uniform vec3 lightColor;

void main() {
	fragColor = vec4(lightColor, 1.0f);
};

