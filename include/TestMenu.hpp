#pragma once
#include <entt/entity/registry.hpp>
#include <imgui.h>

void TestMenu(entt::entity& lightSource, entt::registry& reg) {
	ImGui::Begin("Test Menu");
	
	ImGui::SliderFloat("X Position", &reg.get<Components::Transform>(lightSource).pos.x, -3.0f, 3.0f);
	float* data = glm::value_ptr(reg.get<Components::LightSource>(lightSource).color);
	ImGui::ColorEdit3("Color", data);

	ImGui::End();
}