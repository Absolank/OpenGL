#version 330 core
out vec4 FragColor;

in vec3 FragPos;
in vec3 Normal;

struct Material{
	vec3 position;
	vec3 ambient;
	vec3 diffuse;
	vec3 specular;

	float shininess;
};

struct Light{
	vec3 position;
	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
};

uniform vec3 viewPos;
uniform Light light;
uniform Material material;
void main()
{
	vec3 ambient = light.ambient * material.ambient;

	vec3 norm = normalize(Normal);
	vec3 lightDir = normalize(light.position - FragPos);
	float diffuse_factor = max(dot(norm, lightDir), 0.0);
	vec3 diffuse = light.diffuse * material.diffuse * diffuse_factor;

	vec3 viewDir = normalize(viewPos - FragPos);
	vec3 reflectDir = reflect(-lightDir, norm);
	float specular_factor = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
	vec3 specular = light.specular * material.specular * specular_factor;
	
	vec3 result = ambient + diffuse + specular;
	FragColor = vec4(result, 1.0);
}