#version 330 core

in vec2 texturePos;

out vec4 fragColor;

uniform sampler2D texture1;

void main() {
	fragColor = texture(texture1, texturePos);
	//fragColor = vec4(1.0f, 1.0f, 1.0f, 1.0f);
};

