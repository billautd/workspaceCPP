#version 430 core
//vec2 position, vec2 texCoords
layout(location = 0) in vec4 vertex;

in vec2 texCoords;

out vec4 color;

uniform sampler2D scene;
uniform vec2 offsets[9];
uniform int edgeKernel[9];
uniform float blurKernel[9];

uniform bool chaos;
uniform bool confuse;
uniform bool shake;

void main() {
	color = vec4(0.0f);
	vec3 samples[9];
	//Sample from texture offsets if using convolution matrix
	if (chaos || shake) {
		for (int i = 0; i < 9; i++)
			samples[i] = vec3(texture(scene, texCoords.st + offsets[i]));
	}

	//Process effects
	if (chaos) {
		for (int i = 0; i < 9; i++)
			color += vec4(samples[i] * edgeKernel[i], 0.0f);
		color.a = 1.0f;
	}
	else if (confuse) {
		color = vec4(1.0f - texture(scene, texCoords).rgb, 1.0f);
	}
	else if (shake) {
		for (int i = 0; i < 9; i++)
			color += vec4(samples[i] * blurKernel[i], 0.0f);
		color.a = 1.0f;
	}
	else {
		color = texture(scene, texCoords);
	}
}