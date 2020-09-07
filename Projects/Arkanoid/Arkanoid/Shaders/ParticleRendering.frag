#version 330 core

in VS_OUT{
	vec2 textureCoords;
	vec4 particleColor;
} fs_in;

out vec4 color;

uniform sampler2D sprite;

void main(){
	color = texture(sprite, fs_in.textureCoords) * fs_in.particleColor;
}