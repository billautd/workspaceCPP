#version 330 core
in vec2 fTexCoords;

out vec4 fragColor;

uniform sampler2D textureSampler;

void main() {
    //fragColor = vec4(vec3(1.0 - texture(textureSampler, fTexCoords)), 1.0);
    fragColor = texture(textureSampler, fTexCoords);
}