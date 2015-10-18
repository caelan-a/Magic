#version 430

in vec3 texDir;

uniform samplerCube cubemap;

out vec4 outColor;

void main() {
	//outColor = vec4(1.0, 0.0, 1.0, 1.0);
	outColor = texture(cubemap, texDir);
}