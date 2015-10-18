#pragma once
class Mesh {
public:
	struct Vertex {
		glm::vec3 position;
		glm::vec3 normal;
		glm::vec2 texcoords;
	};

	std::vector<Vertex> vertices;
	std::vector<GLuint> indices;
	std::vector<Texture> textures;

	Mesh(std::vector<Vertex> vertices, std::vector<GLuint> indices, std::vector<Texture> textures);
	void Draw(Shader shader, bool hasOutline);
	void setTextures(std::vector<Texture> textures);
private:
	GLuint VAO, VBO, EBO;
	void setupMesh();
};

