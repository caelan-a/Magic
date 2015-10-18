#version 430

uniform sampler2D tex;

in vec2 TexCoords;

out vec4 color;


void main() {
	// color = vec4(1.0, 0.0, 1.0, 1.0);
	color = texture(tex, TexCoords);
}