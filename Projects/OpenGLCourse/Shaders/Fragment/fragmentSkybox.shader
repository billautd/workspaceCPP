#version 420 core
in vec3 fTexCoords;

out vec4 fragColor;

uniform samplerCube skybox;

void main() {
	fragColor = texture(skybox, fTexCoords);
}