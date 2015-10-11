#pragma once
namespace Lighting {
	static const int NR_POINT_LIGHTS = 1;

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
		glm::vec3 direction;
		Colour colour;
		void uploadUniforms(GLuint shaderID);
		DirectionalLight(glm::vec3 direction, Colour colour);
		DirectionalLight();

	};

	class PointLight {
	public:
		glm::vec3 position;
		Colour colour;
		Attenuation attenuation;
		void uploadUniforms(GLuint shader, GLuint id);
		PointLight(glm::vec3 position, Colour colour, Attenuation attenuation);
		PointLight();
	};

	class LightScene {
	public:
		DirectionalLight globalLight;
		PointLight pointLights[NR_POINT_LIGHTS];

		LightScene();
		void setDirectionalLight(glm::vec3 direction, Colour colour);
		void addPointLight(glm::vec3 position, Colour colour, Attenuation attenuation, GLuint id);
		void uploadUniforms(GLuint shaderID);
		void cleanup();
	};
}