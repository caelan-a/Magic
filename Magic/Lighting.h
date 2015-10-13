#pragma once
namespace Lighting {
	static const int NR_POINT_LIGHTS = 4;

	struct Colour {
		glm::vec3 ambient;
		glm::vec3 diffuse;
		glm::vec3 specular;
	};

	struct Attenuation {
		float constant;
		float quadratic;
		float linear;
	};

	class DirectionalLight {
	public:
		GLuint shaderID;

		glm::vec3 direction;
		Colour colour;
		void uploadUniforms();
		DirectionalLight(GLuint shaderID, glm::vec3 direction, Colour colour);
		DirectionalLight();
	};

	class PointLight {
	public:
		GLuint shaderID;
		GLuint id;

		glm::vec3 position;
		Colour colour;
		Attenuation attenuation;
		void uploadUniforms();
		void setPosition(glm::vec3 position);
		PointLight(GLuint shaderID, GLuint id, glm::vec3 position, Colour colour, Attenuation attenuation);
		PointLight();
	};

	class LightScene {
	public:
		DirectionalLight globalLight;
		PointLight pointLights[NR_POINT_LIGHTS];

		LightScene();
		void setDirectionalLight(GLuint shaderID, glm::vec3 direction, Colour colour);
		void addPointLight(GLuint shaderID, GLuint id, glm::vec3 position, Colour colour, Attenuation attenuation);
		void uploadUniforms();
		void cleanup();
	};
}