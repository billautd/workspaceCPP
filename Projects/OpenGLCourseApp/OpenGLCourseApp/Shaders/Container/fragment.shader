#version 330 core
out vec4 fragColor;

struct Material {
	sampler2D diffuse;
	sampler2D specular;
	sampler2D emission;
	float shininess;
};

struct Light {
	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
};

in vec2 texturePos;
in vec3 fragmentPos;
in vec3 normal;
in vec3 lightPos;

uniform vec3 lightColor;

uniform Material material;
uniform Light light;

void main() {
	//Ambient
	vec3 ambient = light.ambient * texture(material.diffuse, texturePos).rgb;

	//Diffuse
	vec3 norm = normalize(normal);
	vec3 lightDir = normalize(lightPos - fragmentPos);
	float diff = max(dot(norm, lightDir), 0.0f);
	vec3 diffuse = light.diffuse * diff * texture(material.diffuse, texturePos).rgb;

	//Specular
	vec3 viewDir = normalize(-fragmentPos);
	vec3 reflectDir = reflect(-lightDir, norm);
	float spec = pow(max(dot(viewDir, reflectDir), 0.0f), material.shininess);
	vec3 specular = light.specular * spec * texture(material.specular, texturePos).rgb;

	//Emission
	vec3 emission = texture(material.emission, texturePos).rgb;

	fragColor = vec4(ambient + diffuse + emission + specular, 1.0f);
};

