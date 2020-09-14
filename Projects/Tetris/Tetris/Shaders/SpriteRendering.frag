#version 330 core
out vec4 color;

in VS_OUT{
	vec2 textureCoords;
} fs_in;

uniform sampler2D image;
uniform vec3 spriteColor;

void main(){
	color = vec4(spriteColor, 1.0f) * texture(image, fs_in.textureCoords);
}