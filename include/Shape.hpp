#pragma once
#include <glad/glad.h>
#include <vector>
#include <Material.hpp>

struct Shape {
	unsigned int VAO;
	Material material;

	Shape(std::vector<float> vertices, std::vector<unsigned int> indices, Material mat, vec4 pColor);
};
