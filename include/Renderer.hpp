#pragma once
#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <Shape.hpp>

struct Renderer {
	void Draw(Shape shape) {
		glUseProgram(shape.material.shader.ID);

        shape.transform = glm::rotate(shape.transform, (float)glfwGetTime(), glm::vec3(0.0f, 0.0f, 1.0f));

		unsigned int transformLoc = glGetUniformLocation(shape.material.shader.ID, "transform");
		glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(shape.transform));

		glBindTexture(GL_TEXTURE_2D, shape.material.texture.ID);
		glBindVertexArray(shape.VAO);

		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
	}
};