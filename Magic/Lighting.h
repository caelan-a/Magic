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
		glm::vec3 direction;
		Colour colour;

		void uploadUniforms(GLuint shaderID);
	};

	class PointLight {
		bool isOn = true;
		GLuint id;
		glm::vec3 position;

		Colour colour;
		Attenuation attenuation;

		void uploadUniforms(GLuint shader);
	};

	class SpotLight {

	};

	class lightScene {
		DirectionalLight globalLight;
		PointLight pointLights[NR_POINT_LIGHTS];

		void addDirectionalL();
		void addPointL();
	};
}