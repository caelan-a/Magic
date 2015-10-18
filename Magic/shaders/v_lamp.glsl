#version 430

layout(location = 0) in vec3 a_position;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main() {
	gl_Position = projection * view * model * 1.1f * vec4(a_position, 1.0);
}