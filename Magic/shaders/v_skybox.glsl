#version 430

layout(location = 0) in vec3 a_position;

uniform mat4 view;
uniform mat4 projection;

out vec3 texDir;

void main() {
	texDir = a_position;
	gl_Position = projection * view * vec4(a_position, 1.0);
}