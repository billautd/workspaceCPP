#version 330 core

in vec2 texCoord;

out vec4 fragColor;

uniform sampler2D textureUnit1;
uniform sampler2D textureUnit2;

void main() {
	fragColor = mix(texture(textureUnit1, texCoord), texture(textureUnit2, texCoord), 0.2f);
};

