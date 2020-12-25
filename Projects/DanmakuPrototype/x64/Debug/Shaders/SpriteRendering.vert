#version 330 core

layout(location = 0) in vec4 vertex;

uniform mat4 projection;
uniform mat4 model;

out VS_OUT{
	vec2 textureCoords;
} vs_out;

void main(){
	vs_out.textureCoords = vertex.zw;
	gl_Position = projection * model * vec4(vertex.xy, 0.0f, 1.0f);
}
