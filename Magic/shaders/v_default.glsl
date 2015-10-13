#version 430

layout(location = 0) in vec3 a_position;
layout(location = 1) in vec2 a_texcoords;
layout(location = 2) in vec3 a_normal;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

out vec2 texcoords;
out vec3 Normal;
out vec3 FragPos;

void main() {
	FragPos = vec3(model * vec4(a_position, 1.0)); 
	Normal = mat3(transpose(inverse(model))) * a_normal;
	texcoords = a_texcoords;
	gl_Position = projection * view * model * vec4(a_position, 1.0);
}