#version 430

uniform float u_alpha = 1.0;
uniform vec3 u_tint = vec3(1.0,1.0,1.0);
uniform sampler2D u_tex;

in vec2 texcoords;

out vec4 outColor;

void main() {
	outColor = texture(u_tex, texcoords)  * vec4(u_tint, 1.0) * u_alpha;
}