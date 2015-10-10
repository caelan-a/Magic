#version 430

uniform vec3 cameraPos;
uniform vec3 lightPos;
uniform vec3 ambientColour;
uniform sampler2D u_tex;

in vec3 FragPos;
in vec3 Normal;
in vec2 texcoords;

out vec4 outColor;

void main() {
	float ambientStrength = 0.005f;
	vec3 ambient = ambientStrength * ambientColour;
	
	vec3 norm = normalize(Normal);
	vec3 lightDir = normalize(lightPos - FragPos);
	float diff = max(dot(norm, lightDir), 0.0);
	vec3 diffuse = diff * ambientColour;

	float specularIntensity = 0.5f;
	vec3 viewDir = normalize(cameraPos - FragPos);
	vec3 reflectDir = reflect(-lightDir, norm);
	float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32);
	vec3 specular = specularIntensity * spec * ambientColour;  

	outColor = texture(u_tex, texcoords) * vec4(ambient + diffuse + specular, 1.0);

}