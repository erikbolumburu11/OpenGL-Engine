#pragma once
#include <glad/glad.h>
#include <vector>
#include <Material.hpp>

struct Shape {
	unsigned int VAO;
	Material material;
	glm::mat4 model;
	glm::mat4 view;
	glm::mat4 projection;

	Shape(std::vector<float> vertices, Material mat);
};
