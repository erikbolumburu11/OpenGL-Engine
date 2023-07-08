#pragma once
#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <Shape.hpp>

struct Renderer {
	glm::mat4 view = glm::mat4(1);

	void Draw(Components::Shape shape, float deltaTime) {
		glUseProgram(shape.material.shader.ID);

		shape.model = glm::translate(shape.model, glm::vec3(shape.worldPosition));  
		shape.model = glm::rotate(shape.model, (float)glfwGetTime() * glm::radians(100.0f), glm::vec3(1));  

		view = glm::lookAt(glm::vec3(0.0f, 0.0f, 6.0f), 
  		   glm::vec3(0.0f, 0.0f, 0.0f), 
  		   glm::vec3(0.0f, 1.0f, 0.0f));

		shape.material.shader.setMat4("model", shape.model);
		shape.material.shader.setMat4("view", view);
		shape.material.shader.setMat4("projection", shape.projection);

		glBindTexture(GL_TEXTURE_2D, shape.material.texture.ID);
		glBindVertexArray(shape.VAO);

		glDrawArrays(GL_TRIANGLES, 0, 36);

	}
};