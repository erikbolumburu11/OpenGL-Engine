#pragma once
#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <Components/Shape.hpp>

struct Renderer {
	glm::mat4 view = glm::mat4(1);

	void Draw(Components::Shape shape, glm::mat4 viewMat, float deltaTime) {
		glUseProgram(shape.material.shader.ID);

		shape.model = glm::translate(shape.model, glm::vec3(shape.worldPosition));  

		shape.material.shader.setMat4("model", shape.model);
		shape.material.shader.setMat4("view", viewMat);
		shape.material.shader.setMat4("projection", shape.projection);

		glBindTexture(GL_TEXTURE_2D, shape.material.texture.ID);
		glBindVertexArray(shape.VAO);

		glDrawArrays(GL_TRIANGLES, 0, 36);

	}
};