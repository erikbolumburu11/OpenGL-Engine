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

        entt::entity camEntity = entt::to_entity(reg, *cam);
        glm::vec3 camPos = reg.get<Components::Transform>(camEntity).pos;

		shape.model = glm::translate(glm::mat4(1.0f), glm::vec3(pos));  

		shape.material.shader.setMat4("model", shape.model);
		shape.material.shader.setMat4("view", viewMat);
		shape.material.shader.setMat4("projection", shape.projection);

		shape.material.shader.setVec3("viewPos", camPos);

		shape.material.shader.SetFloat("material.shininess", shape.material.shininess);

		//////////////////////
		// DIRECTIONAL LIGHT//
		//////////////////////
		entt::entity dirLightEnt;
		Components::Lights::DirectionalLight dirLight;
		auto lights = reg.view<Components::Lights::DirectionalLight>();
		lights.each([&](Components::Lights::DirectionalLight& light){
			dirLight = light;
			dirLightEnt = entt::to_entity(reg, light);
		});

		shape.material.shader.setVec3("dirLight.direction", reg.get<Components::Transform>(dirLightEnt).rot);
		shape.material.shader.setVec3("dirLight.ambient",  dirLight.ambient);
		shape.material.shader.setVec3("dirLight.diffuse",  dirLight.diffuse);
		shape.material.shader.setVec3("dirLight.specular", dirLight.specular); 

		///////////////////////
		///// POINT LIGHTS/////
		///////////////////////
		int i = 0;
		auto pointLights = reg.view<Components::Lights::PointLight, Components::Transform>();
		pointLights.each([&](Components::Lights::PointLight& light, Components::Transform& transform){
			std::string pointLight = "pointLights[" + std::to_string(i) + "]";
			shape.material.shader.setVec3(pointLight + ".position", transform.pos);
			shape.material.shader.setVec3(pointLight + ".ambient",  light.ambient);
			shape.material.shader.setVec3(pointLight + ".diffuse",  light.diffuse);
			shape.material.shader.setVec3(pointLight + ".specular", light.specular); 
			shape.material.shader.SetFloat(pointLight + ".constant", light.constant); 
			shape.material.shader.SetFloat(pointLight + ".linear", light.linear); 
			shape.material.shader.SetFloat(pointLight + ".quadratic", light.quadratic); 
			i++;
		});


		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, shape.material.diffuse.ID);

		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, shape.material.specular.ID);

		glBindVertexArray(shape.VAO);

		glDrawArrays(GL_TRIANGLES, 0, 36);

	}
};