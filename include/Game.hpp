#pragma once

#include <vector>

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

#include <entt/entt.hpp>

#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>

#include <constants.hpp>

#include <ResourceManager.hpp>
#include <LightManager.hpp>
#include <Renderer.hpp>
#include <Components/Camera.hpp>


class Game {
public:
	void Start();

	ResourceManager& GetResourceManager() { return resourceManager; };
	LightManager& GetLightManager() { return lightManager; };
	Renderer& GetRenderer() { return renderer; };
	entt::registry& GetRegistry() { return registry; };
	float GetDeltaTime() { return deltaTime; };
	Components::Camera::Camera* GetActiveCamera() { if(activeCamera) return activeCamera; };

	void SetActiveCamera(Components::Camera::Camera* cam) { activeCamera = cam; };

	Game(){
		lightManager = LightManager(registry);
	}

private:
	void Update();
	void Render();

	GLFWwindow* window;
	Renderer renderer;

	LightManager lightManager;
	ResourceManager resourceManager;
	entt::registry registry;

	Components::Camera::Camera* activeCamera;

	float deltaTime = 0.0f;
	float lastFrame = 0.0f;
};