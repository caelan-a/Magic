#version 430

layout(location = 0) in vec3 a_position;

const float width = 1.004;

uniform float time;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main() {
	float scale = width + (0.01 * sin(6.0 * time) + 0.01);
	gl_Position = projection * view * model * vec4(scale * a_position.x, a_position.y +0.014, scale * a_position.z, 1.0);
}