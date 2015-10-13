#pragma once
class Model
{
public:
	Model(GLchar *path) {
		this->loadModel(path);
	}
	void loadModel(std::string path);
	void Draw(Shader shader);

private:
	std::vector<Mesh::Texture> textures_loaded;
	std::vector<Mesh> meshes;
	std::string directory;

	void processNode(aiNode* node, const aiScene* scene);
	Mesh processMesh(aiMesh* mesh, const aiScene* scene);
	std::vector<Mesh::Texture> loadMaterialTextures(aiMaterial* mat, aiTextureType type, std::string typeName);
	GLuint loadTextureFromFile(std::string directory, std::string name);
};

