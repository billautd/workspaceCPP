#version 330 core

in vec3 color;
in vec2 texCoord;

out vec4 fragColor;

uniform sampler2D textureUnit1;
uniform sampler2D textureUnit2;

void main() {
	fragColor = mix(texture(textureUnit1, texCoord), texture(textureUnit2, vec2(1.0f - texCoord.x, texCoord.y)), 0.2f);
};

