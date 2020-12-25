#version 330 core

in VS_OUT{
	vec2 textureCoords;
} fs_in;

out vec4 color;

uniform sampler2D text;
uniform vec3 textColor;

void main()
{    
    vec4 sampled = vec4(1.0, 1.0, 1.0, texture(text, fs_in.textureCoords).r);
    color = vec4(textColor, 1.0) * sampled;
}  