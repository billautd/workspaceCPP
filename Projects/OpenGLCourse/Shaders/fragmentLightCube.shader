#version 330 core
out vec4 fragColor;

in vec3 fNormal;
in vec3 fFragPos;

uniform vec3 cameraPos;
uniform samplerCube skybox;

void main() {
	vec3 I = normalize(fFragPos - cameraPos);
	vec3 R = reflect(I, normalize(fNormal));
	fragColor = vec4(texture(skybox, R).rgb, 1.0f);
}