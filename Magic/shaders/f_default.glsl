#version 430

struct Material {
	sampler2D diffuse;
    sampler2D specular;
    float shininess;
}; 

struct Light {
    vec3 position;
  
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

uniform Light light;  
uniform Material material;

uniform vec3 cameraPos;

in vec3 FragPos;
in vec3 Normal;
in vec2 texcoords;

out vec4 outColor;

void main() {
	//	Ambient
	vec3 ambient = light.ambient * vec3(texture(material.diffuse, texcoords));
	
	//	Diffuse
	vec3 norm = normalize(Normal);
	vec3 lightDir = normalize(light.position - FragPos);
	float diff = max(dot(norm, lightDir), 0.0);
	vec3 diffuse = light.diffuse * diff * vec3(texture(material.diffuse, texcoords));

	//	Specular
	vec3 viewDir = normalize(cameraPos - FragPos);
	vec3 reflectDir = reflect(-lightDir, norm);
	float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
	vec3 specular = light.specular * spec * vec3(texture(material.specular, texcoords));
	
	vec3 result = ambient + diffuse + specular;
	outColor = vec4(result, 1.0);
}