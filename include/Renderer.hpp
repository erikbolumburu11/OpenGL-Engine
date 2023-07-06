#pragma once
#include <glad/glad.h>
#include <Shape.hpp>

struct Renderer {
	void Draw(Shape shape) {
		int vertexColorLocation2 = glGetUniformLocation(shape.material.shader.ID, "color");
		glUseProgram(shape.material.shader.ID);
		// glUniform4f(vertexColorLocation2, shape.material.color[0], shape.material.color[1], shape.material.color[2], shape.material.color[3]);
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, shape.material.texture1.ID);
		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, shape.material.texture2.ID);
		glBindVertexArray(shape.VAO);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
	}
};