#version 150

in vec2 a_position;
in vec2 a_texcoords;

out vec2 texcoords;

void main() {
	texcoords = vec2(a_texcoords.x, 1.0 - a_texcoords.y);
	gl_Position = vec4(a_position, 0.0, 1.0);
}