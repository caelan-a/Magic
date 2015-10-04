#version 430

layout(location = 0) in vec3 a_position;
layout(location = 1) in vec2 a_texcoords;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

out vec2 texcoords;

void main() {
	texcoords = vec2(a_texcoords.x, 1.0 - a_texcoords.y);
	gl_Position = projection * view * model * vec4(a_position, 1.0);
}