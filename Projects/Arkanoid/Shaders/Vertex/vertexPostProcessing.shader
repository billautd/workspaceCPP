#version 430 core
//vec2 position, vec2 texCoords
layout(location = 0) in vec4 vertex;

out vec2 texCoords;

uniform bool chaos;
uniform bool confuse;
uniform bool shake;
uniform float time;

void main() {
	gl_Position = vec4(vertex.xy, 0.0f, 1.0f);
	vec2 texturePos = vertex.zw;
	if (chaos) {
		float strength = 0.3f;
		vec2 pos = vec2(texturePos.x + sin(time) * strength, texturePos.y + cos(time) * strength);
		texCoords = pos;
	}
	else if (confuse) {
		texCoords = vec2(1.0f) - texturePos;
	}
	else {
		texCoords = texturePos;
	}
	if (shake) {
		float strength = 0.01f;
		gl_Position.x += cos(time + 10) * strength;
		gl_Position.y += sin(time + 10) * strength;
	}
}