#version 420 core
#define NBR_POINT_LIGHTS 4 

struct Material {
	sampler2D diffuse;
	sampler2D specular;
	float shininess;
};

struct DirLight {
	vec3 direction;

	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
};

struct PointLight {
	vec3 position;

	vec3 ambient;
	vec3 diffuse;
	vec3 specular;

	float Kconstant;
	float Klinear;
	float Kquadratic;
};

layout(std140, binding = 1) uniform ViewPos{
	vec3 viewPos;
};

out vec4 fragColor;

in vec2 fTexCoords;
in vec3 fNormal;
in vec3 fFragPos;

uniform Material material;
uniform DirLight dirLight;
uniform PointLight pointLights[NBR_POINT_LIGHTS];

vec3 CalcDirLight(DirLight dirLight, vec3 norm, vec3 viewDir) {
	//Maps
	vec3 diffuseMap = vec3(texture(material.diffuse, fTexCoords));
	vec3 specularMap = vec3(texture(material.specular, fTexCoords));

	//Diffuse
	vec3 lightDir = normalize(-dirLight.direction);
	float diff = max(dot(norm, lightDir), 0.0f);

	//Specular
	vec3 reflectDir = reflect(-lightDir, norm);
	float spec = pow(max(dot(viewDir, reflectDir), 0.0f), material.shininess);

	vec3 ambient = dirLight.ambient * diffuseMap;
	vec3 diffuse = diff * dirLight.diffuse * diffuseMap;
	vec3 specular = spec * dirLight.specular * specularMap;
	//Result
	return ambient + diffuse + specular;
}

vec3 CalcPointLight(PointLight pointLight, vec3 norm, vec3 viewDir) {
	//Maps
	vec3 diffuseMap = vec3(texture(material.diffuse, fTexCoords));
	vec3 specularMap = vec3(texture(material.specular, fTexCoords));

	//Diffuse
	vec3 lightDir = normalize(pointLight.position - fFragPos);
	float diff = max(dot(norm, lightDir), 0.0f);

	//Specular
	vec3 reflectDir = reflect(-lightDir, fNormal);
	float spec = pow(max(dot(viewDir, reflectDir), 0.0f), material.shininess);

	//Attenuation
	float distance = length(pointLight.position - fFragPos);
	float attenuation = 1.0f / (pointLight.Kconstant + distance * pointLight.Klinear + distance * distance * pointLight.Kquadratic);

	vec3 ambient = pointLight.ambient * diffuseMap;
	vec3 diffuse = diff * pointLight.diffuse * diffuseMap;
	vec3 specular = spec * pointLight.specular * specularMap;

	return ambient + diffuse + specular;
}

void main() {

	//Properties
	vec3 norm = normalize(fNormal);
	vec3 viewDir = normalize(viewPos - fFragPos);

	//Directional lighting
	vec3 lightResult = CalcDirLight(dirLight, norm, viewDir);

	//Point lighting
	for (int i = 0; i < NBR_POINT_LIGHTS; i++)
		lightResult += CalcPointLight(pointLights[i], norm, viewDir);


	//Result
	fragColor = vec4(lightResult, 1.0f);
}