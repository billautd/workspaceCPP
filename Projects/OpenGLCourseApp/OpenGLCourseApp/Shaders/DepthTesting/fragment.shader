#version 330 core

in vec2 texturePos;

out vec4 fragColor;

uniform sampler2D texture1;

void main() {
	vec4 texColor = texture(texture1, texturePos);
	if (texColor.a < 0.1f)
		discard;
	fragColor = texColor;
};

