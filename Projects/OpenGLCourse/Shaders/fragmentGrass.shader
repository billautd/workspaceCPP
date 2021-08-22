#version 420 core
in vec2 fTexCoords;

out vec4 fragColor;

uniform sampler2D textureSampler;

void main() {
	vec4 texColor = texture(textureSampler, fTexCoords);
	if (texColor.a < 0.01f)
		discard;

	fragColor = texColor;
}