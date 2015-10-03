#version 150

uniform float u_time;

in vec2 a_position;
in vec3 a_color;

out vec3 color;

void main() {
	color = vec3((sin(u_time) + 1 + ((gl_VertexID+1) * 0.2)) * a_color);
	gl_Position = vec4(a_position, 0.0, 1.0);
}