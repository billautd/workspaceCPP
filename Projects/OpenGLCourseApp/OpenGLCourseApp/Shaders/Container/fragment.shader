#version 330 core
out vec4 fragColor;

struct Material {
	sampler2D diffuse;
	sampler2D specular;
	sampler2D emission;
	float shininess;
};

#define NBR_POINT_LIGHTS 4
struct PointLight {
	vec3 position;

	vec3 ambient;
	vec3 diffuse;
	vec3 specular;

	float constant;
	float linear;
	float quadratic;
};

struct DirLight {
	vec3 direction;

	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
};

struct SpotLight {
	vec3 position;
	vec3 direction;

	vec3 ambient;
	vec3 diffuse;
	vec3 specular;

	float constant;
	float linear;
	float quadratic;
	float cutOff;
	float outerCutOff;
};

in vec2 texturePos;
in vec3 fragmentPos;
in vec3 normal;

uniform vec3 lightColor;
uniform vec3 viewPos;

uniform Material material;
uniform PointLight pointLights[NBR_POINT_LIGHTS];
uniform DirLight dirLight;
uniform SpotLight spotLight;

vec3 CalcDirLight(DirLight light, vec3 normal, vec3 viewDir) {
	vec3 lightDir = normalize(-light.direction);

	//Ambient
	vec3 ambient = light.ambient * vec3(texture(material.diffuse, texturePos));
	//Diffuse
	float diff = max(dot(normal, lightDir), 0.0f);
	vec3 diffuse = diff * light.diffuse * vec3(texture(material.diffuse, texturePos));
	//Specular
	vec3 reflectDir = normalize(reflect(-lightDir, normal));
	float spec = pow(max(dot(viewDir, reflectDir), 0.0f), material.shininess);
	vec3 specular = spec * light.specular * vec3(texture(material.specular, texturePos));

	return (ambient + diffuse + specular);
}

vec3 CalcPointLight(PointLight light, vec3 normal, vec3 fragPos, vec3 viewDir) {
	vec3 lightDir = normalize(light.position - fragPos);

	//Ambient
	vec3 ambient = light.ambient * vec3(texture(material.diffuse, texturePos));
	//Diffuse
	float diff = max(dot(normal, lightDir), 0.0f);
	vec3 diffuse = diff * light.diffuse * vec3(texture(material.diffuse, texturePos));
	//Specular
	vec3 reflectDir = normalize(reflect(-lightDir, normal));
	float spec = pow(max(dot(viewDir, reflectDir), 0.0f), material.shininess);
	vec3 specular = spec * light.specular * vec3(texture(material.specular, texturePos));

	//Attenuation
	float distance = length(light.position - fragPos);
	float attenuation = 1.0f / (light.constant + light.linear * distance + light.quadratic * distance * distance);

	return attenuation * (ambient + diffuse + specular);
}

vec3 CalcSpotLight(SpotLight light, vec3 normal, vec3 fragPos, vec3 viewDir) {
	vec3 lightDir = normalize(-light.direction);
	vec3 spotDir = normalize(light.position - fragPos);
	float theta = dot(lightDir, spotDir);
	float epsilon = light.cutOff - light.outerCutOff;
	float intensity = clamp((theta - light.outerCutOff) / epsilon, 0.0f, 1.0f);

	if (theta > light.outerCutOff) {
		PointLight spotToPoint = PointLight(
			spotLight.position,
			spotLight.ambient,
			intensity * spotLight.diffuse,
			intensity * spotLight.specular,
			spotLight.constant,
			spotLight.linear,
			spotLight.quadratic);

		return CalcPointLight(spotToPoint, normal, fragPos, viewDir);
	}
	else
		return light.ambient * vec3(texture(material.diffuse, texturePos));
}

void main() {
	vec3 norm = normalize(normal);
	vec3 viewDir = normalize(viewPos - fragmentPos);

	//1. DirLight
	vec3 result = CalcDirLight(dirLight, norm, viewDir);
	//2. Point Lights
	for (int i = 0; i < NBR_POINT_LIGHTS; i++)
		result += CalcPointLight(pointLights[i], norm, fragmentPos, viewDir);

	//3.SpotLight
	result += CalcSpotLight(spotLight, norm, fragmentPos, viewDir);

	fragColor = vec4(result, 1.0f);
};

