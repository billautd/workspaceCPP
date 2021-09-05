#version 430 core
//vec2 position, vec2 texCoords
layout(location = 0) in vec4 vertex;

out vec2 texCoords;

layout(std140, binding = 0) uniform Matrices{
	mat4 projection;
}; 

uniform mat4 model;

void main(){
	texCoords = vertex.zw;
	gl_Position = projection * model * vec4(vertex.xy, 1.0f, 1.0f);
}