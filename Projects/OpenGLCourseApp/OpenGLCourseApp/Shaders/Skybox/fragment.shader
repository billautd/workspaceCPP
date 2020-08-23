#version 330 core

in vec3 texturePos;

out vec4 fragColor;

uniform samplerCube skybox;

void main() {
	fragColor = texture(skybox, texturePos);
};

