#pragma once
#include <glad/glad.h>
#include <vector>
#include <Shader.hpp>

struct Shape {
	unsigned int VAO;
	Shader shaderProgram;
	vec4 color { 1.0, 1.0, 1.0, 1.0 };

	Shape(std::vector<float> vertices, std::vector<unsigned int> indices, Shader pShaderProgram, vec4 pColor) : shaderProgram(pShaderProgram) {
		unsigned int VBO;

		glGenVertexArrays(1, &VAO);
		glGenBuffers(1, &VBO);

		glBindVertexArray(VAO);

		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float), &vertices[0], GL_STATIC_DRAW);

		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
		glEnableVertexAttribArray(0);

		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
		glEnableVertexAttribArray(1);

		unsigned int EBO;
		glGenBuffers(1, &EBO);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), &indices[0], GL_STATIC_DRAW);
		color[0] = pColor[0];
		color[1] = pColor[1];
		color[2] = pColor[2];
		color[3] = pColor[3];
	}
};