#pragma once
class Model
{
public:
	Model(GLchar *path) {
		this->loadModel(path);
	}
	void loadModel(std::string path);
	void Draw(Shader shader, bool hasOutline)
	{
		for (GLuint i = 0; i < this->meshes.size(); i++)
			this->meshes[i].Draw(shader, hasOutline);
	}
	std::vector<Mesh> getMeshes();

private:
	std::vector<Texture> textures_loaded;
	std::vector<Mesh> meshes;
	std::string directory;

	void processNode(aiNode* node, const aiScene* scene);
	Mesh processMesh(aiMesh* mesh, const aiScene* scene);
	std::vector<Texture> loadMaterialTextures(aiMaterial* mat, aiTextureType type, std::string typeName);
};

