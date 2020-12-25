#version 330 core
out vec4 color;

in VS_OUT{
	vec2 textureCoords;
} fs_in;

uniform sampler2D image;
uniform vec3 spriteColor;
uniform float alpha;

void main(){
	color = vec4(spriteColor, alpha) * texture(image, fs_in.textureCoords);
}