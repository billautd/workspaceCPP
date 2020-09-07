#version 330 core
layout(location = 0) in vec4 vertex; //vec2 position, vec2 textureCoords

out VS_OUT{
	vec2 textureCoords;
	vec4 particleColor;
}vs_out;

uniform mat4 projection;
uniform vec2 offset;
uniform vec4 color;

void main(){
	float scale = 10.0f;
	vs_out.textureCoords = vertex.zw;
	vs_out.particleColor = color;
	gl_Position = projection * vec4((vertex.xy * scale) + offset, 0.0f, 1.0f);
}