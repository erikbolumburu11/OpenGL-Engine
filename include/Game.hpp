#pragma once

#include <vector>

#include <glad/glad.h>
#include <entt/entt.hpp>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>

#include <ResourceManager.hpp>
#include <Renderer.hpp>

const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 600;

class Game {
public:
	void Start();

	ResourceManager& GetResourceManager() { return resourceManager; };
	Renderer& GetRenderer() { return renderer; };
	entt::registry& GetRegistry() { return registry; };
	float GetDeltaTime() { return deltaTime; };

private:
	void Update();
	void Render();

	GLFWwindow* window;
	ResourceManager resourceManager;
	Renderer renderer;
	entt::registry registry;
	float deltaTime = 0.0f;
	float lastFrame = 0.0f;
};