#version 330 core

in vec2 texturePos;
in vec3 fragmentPos;
in vec3 normal;

out vec4 fragColor;

uniform vec3 objectColor;
uniform vec3 lightColor;
uniform float ambientStrength;
uniform float specularStrength;
uniform sampler2D texture1;
uniform sampler2D texture2;
uniform vec3 lightPos;
uniform vec3 viewPos;

void main() {
	//Ambient
	vec4 ambient = vec4(ambientStrength * lightColor, 1.0f);

	//Diffuse
	vec3 norm = normalize(normal);
	vec3 lightDir = normalize(lightPos - fragmentPos);
	vec4 diffuse = vec4(max(dot(norm, lightDir), 0.0f) * lightColor, 1.0f);

	//Specular
	vec3 viewDir = normalize(viewPos - fragmentPos);
	vec3 reflectDir = reflect(-lightDir, norm);
	float shininess = 32.0f;
	vec3 spec = pow(max(dot(viewDir, reflectDir), 0.0f), shininess) * specularStrength * lightColor;
	vec4 specular = vec4(spec, 1.0f);

	vec4 lighting = ambient + diffuse + specular;
	//Texture
	vec4 textureColor = mix(texture(texture1, texturePos), texture(texture2, texturePos), 0.2f);

	fragColor = vec4(1.0f, 0.5f, 0.31f, 1.0f) * lighting;
};

