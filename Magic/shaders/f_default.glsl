#version 150

uniform float u_time;
uniform float u_alpha = 1.0;
uniform vec3 u_tint = vec3(1.0,1.0,1.0);
uniform sampler2D u_tex;

in vec2 texcoords;

out vec4 outColor;

void main() {
	outColor = texture(u_tex, texcoords) * vec4(tint, 1.0) * alpha;
}