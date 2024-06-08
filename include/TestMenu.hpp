#pragma once
#include <entt/entity/registry.hpp>
#include <imgui.h>

void LightControls(Game& game){
	if(ImGui::Button("Create Blue Light")){
		game.GetLightManager().CreatePointLight(game.GetRegistry(),
			Components::Lights::PointLight {
				false,
				1.0f, 0.22f, 0.20f,
				glm::vec3(0.025f), glm::vec3(0.0f, 0.0f, 1.0f), glm::vec3(0.0f, 0.0f, 1.0f)
			}, 
			Components::Transform {
				glm::vec3(-2.0f, -0.5f, -1.0f), glm::vec3(1), glm::vec3(1)
			}
		);
	}
	if(ImGui::Button("Create Red Light")){
		game.GetLightManager().CreatePointLight(game.GetRegistry(),
			Components::Lights::PointLight {
				false,
				1.0f, 0.22f, 0.20f,
				glm::vec3(0.025f), glm::vec3(1.0f, 0.0f, 0.0f), glm::vec3(1.0f, 0.0f, 0.0f)
			}, 
			Components::Transform {
				glm::vec3(2.0f, -0.5f, -1.0f), glm::vec3(1), glm::vec3(1)
			}
		);
	}
}

void TestMenu(Game& game) {
	ImGui::Begin("Test Menu");
	LightControls(game);
	ImGui::End();
}
