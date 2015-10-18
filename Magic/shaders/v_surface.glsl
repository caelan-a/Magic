#version 430

layout(location = 0) in vec3 position;
layout(location = 1) in vec2 texCoords;

out vec2 TexCoords;

void main() {
	TexCoords = vec2(texCoords.x, 1.0 - texCoords.y);
	gl_Position = vec4(position.x, position.y, position.z, 1.0);
}