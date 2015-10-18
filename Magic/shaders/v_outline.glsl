#version 430

layout(location = 0) in vec3 a_position;

const float width = 1.05;

uniform float time;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main() {
	float scale = width + (0.02 * sin(6.0 * time) + 0.05);
	gl_Position = projection * view * model * vec4(scale * a_position, 1.0);
}