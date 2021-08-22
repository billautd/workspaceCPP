#version 420 core
out vec4 fragColor;

in vec3 fNormal;
in vec3 fFragPos;

layout(std140, binding = 1) uniform ViewPos{
	vec3 viewPos;
};
uniform samplerCube skybox;

void main() {
	vec3 I = normalize(fFragPos - viewPos);
	vec3 R = reflect(I, normalize(fNormal));
	fragColor = vec4(texture(skybox, R).rgb, 1.0f);
}