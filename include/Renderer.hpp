#pragma once
#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <entt/entity/registry.hpp>

#include <Components/Transform.hpp>
#include <Components/Camera.hpp>
#include <Components/Light.hpp>
#include <Components/Shape.hpp>

struct Renderer {
	glm::mat4 view = glm::mat4(1);

	void Draw(Components::Shape& shape, glm::mat4 viewMat, entt::registry& reg, Components::Camera::Camera* cam, float deltaTime) {
		glUseProgram(shape.material.shader.ID);

        entt::entity shapeEntity = entt::to_entity(reg, shape);
        glm::vec3 pos = reg.get<Components::Transform>(shapeEntity).pos;

        entt::entity camEntity = entt::to_entity(reg, cam);
        glm::vec3 camPos = reg.get<Components::Transform>(shapeEntity).pos;

		shape.model = glm::translate(glm::mat4(1.0f), glm::vec3(pos));  

		shape.material.shader.setMat4("model", shape.model);
		shape.material.shader.setMat4("view", viewMat);
		shape.material.shader.setMat4("projection", shape.projection);

		entt::entity lightEnt;
		auto lights = reg.view<Components::LightSource>();
		lights.each([&](Components::LightSource& light){
			lightEnt = entt::to_entity(reg, light);
		});

		shape.material.shader.setVec3("lightColor", reg.get<Components::LightSource>(lightEnt).color);
		shape.material.shader.setVec3("lightPos", reg.get<Components::Transform>(lightEnt).pos);
		shape.material.shader.setVec3("viewPos", camPos);

		glBindTexture(GL_TEXTURE_2D, shape.material.texture.ID);
		glBindVertexArray(shape.VAO);

		glDrawArrays(GL_TRIANGLES, 0, 36);

	}
};