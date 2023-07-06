#pragma once
#include <glad/glad.h>
#include <Shape.hpp>

struct Renderer {
	void Draw(Shape shape) {
		int vertexColorLocation2 = glGetUniformLocation(shape.shaderProgram.ID, "color");
		glUseProgram(shape.shaderProgram.ID);
		glUniform4f(vertexColorLocation2, shape.color[0], shape.color[1], shape.color[2], shape.color[3]);
		glBindVertexArray(shape.VAO);
		glDrawArrays(GL_TRIANGLES, 0, 3);
	}
};