#version 430

uniform sampler2D splash;

in vec2 texCoords;

out vec4 outColor;

void main() {
	outColor = vec4(1.0, 1.0, 1.0, 1.0);
}