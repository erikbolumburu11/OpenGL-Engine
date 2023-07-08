#pragma once
#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <Shape.hpp>

struct Renderer {
	void Draw(Shape shape, float deltaTime) {
		glUseProgram(shape.material.shader.ID);

		shape.model = glm::rotate(shape.model, (float)glfwGetTime() * glm::radians(50.0f), glm::vec3(0.5f, 1.0f, 0.0f));  
		static float currentPos = 0.0f;
		currentPos += 0.3f * deltaTime;
		shape.view = glm::translate(shape.view, glm::vec3(0.0f, sin(currentPos), 0.0f));  

		shape.material.shader.setMat4("model", shape.model);
		shape.material.shader.setMat4("view", shape.view);
		shape.material.shader.setMat4("projection", shape.projection);

		glBindTexture(GL_TEXTURE_2D, shape.material.texture.ID);
		glBindVertexArray(shape.VAO);

		glDrawArrays(GL_TRIANGLES, 0, 36);

	}
};