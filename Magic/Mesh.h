#pragma once
class Mesh {
public:
	struct Vertex {
		glm::vec3 position;
		glm::vec3 normal;
		glm::vec2 texcoords;
	};

	struct Texture {
		GLuint id;
		std::string type;
		aiString path;
	};

	std::vector<Vertex> vertices;
	std::vector<GLuint> indices;
	std::vector<Texture> textures;

	Mesh(std::vector<Vertex> vertices, std::vector<GLuint> indices, std::vector<Texture> textures);
	void Draw(Shader shader);
private:
	GLuint VAO, VBO, EBO;
	void setupMesh();
};

