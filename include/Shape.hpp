#pragma once
#include <glad/glad.h>
#include <vector>
#include <Material.hpp>

struct ShapeData {
    glm::vec3 pos;
    std::vector<float> vertices;
    Material mat;
    ShapeData(glm::vec3 _pos, std::vector<float> _vertices, Material _mat){
		pos = _pos;
		vertices = _vertices;
		mat = _mat;
	}
};

struct Shape {
	unsigned int VAO;
	Material material;
	glm::vec3 worldPosition;

	glm::mat4 model;
	glm::mat4 view;
	glm::mat4 projection;

	void Initialize(std::vector<float> vertices, glm::vec3 pos, Material mat);
};

void OnShapeConstructed(ShapeData sd, entt::registry& reg, entt::entity e);