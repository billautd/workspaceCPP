#version 330 core

layout(location = 0) in vec4 vertex;

out VS_OUT{
	vec2 textureCoords;
} vs_out;

uniform bool chaos;
uniform float chaosStrength;
uniform bool confuse;
uniform bool shake;
uniform float shakeStrength;
uniform float time;

void main(){
	gl_Position = vec4(vertex.xy, 0.0f, 1.0f);
	vec2 texture = vertex.zw;
	if(chaos){
		vec2 pos = vec2(texture.x + cos(time*2) * chaosStrength, texture.y + sin(time*2) * chaosStrength);
		vs_out.textureCoords = pos;
	}
	else if(confuse){
		vs_out.textureCoords = vec2(1.0f - texture.x, 1.0f - texture.y);
	}
	else{
		vs_out.textureCoords = texture;
	}
	if(shake){
		gl_Position.x += cos(time*10) * shakeStrength;
		gl_Position.y += cos(time*15) * shakeStrength;
	}

}
