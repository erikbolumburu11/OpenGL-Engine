#pragma once
#include <glad/glad.h>
#include <vector>
#include <Material.hpp>

struct Shape {
	unsigned int VAO;
	Material material;
	glm::mat4 transform;

	Shape(std::vector<float> vertices, std::vector<unsigned int> indices, Material mat, glm::vec4 pColor);
};
