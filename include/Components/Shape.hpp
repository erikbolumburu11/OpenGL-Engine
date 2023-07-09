#pragma once
#include <glad/glad.h>
#include <vector>
#include <Material.hpp>

namespace Components {
	struct ShapeData {
		std::vector<float> vertices;
		Material mat;
		ShapeData(std::vector<float> _vertices, Material _mat){
			vertices = _vertices;
			mat = _mat;
		}
	};

	struct Shape {
		unsigned int VAO;
		Material material;

		glm::mat4 model;
		glm::mat4 projection;

		void Initialize(std::vector<float> vertices, Material mat);
	};

	void OnShapeConstructed(Components::ShapeData sd, entt::registry& reg, entt::entity e);
}