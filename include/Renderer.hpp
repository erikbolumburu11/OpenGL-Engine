#pragma once
#include <glad/glad.h>
#include <Shape.hpp>

struct Renderer {
	void Draw(Shape shape) {
		int vertexColorLocation2 = glGetUniformLocation(shape.material.shader.ID, "color");
		glUseProgram(shape.material.shader.ID);
		// glUniform4f(vertexColorLocation2, shape.material.color[0], shape.material.color[1], shape.material.color[2], shape.material.color[3]);
		glBindVertexArray(shape.VAO);
		glDrawArrays(GL_TRIANGLES, 0, 3);
	}
};