#include "stdafx.h"
#include "Surface.h"

Surface::Surface(Texture tex)
{
	this->texture = tex;
}

void Surface::draw()
{
	shader.Use();
	glBindVertexArray(vao);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texture.id);
	glUniform1i(glGetUniformLocation(shader.id, "tex"), GL_TEXTURE0);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
	glBindTexture(GL_TEXTURE_2D, 0);
	glBindVertexArray(0);
	shader.Disable();
}
