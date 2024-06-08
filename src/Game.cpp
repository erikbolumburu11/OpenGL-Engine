#include "Game.hpp"
#include <TestMenu.hpp>
#include <Components/Transform.hpp>
#include <Components/Light.hpp>
#include <shapes/cube.hpp>

void FramebufferSizeCallback(GLFWwindow* window, int width, int height);

void Game::Start()
{
	glfwInit();

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	//Coordinates Start At The Bottom Left Corner
	window = glfwCreateWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "OpenGL Engine", NULL, NULL);
	if (!window) {
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
	}
	glfwMakeContextCurrent(window);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		std::cout << "Failed to initialize GLAD" << std::endl;
		glfwTerminate();
	}

	ImGui::CreateContext();
	ImGui_ImplGlfw_InitForOpenGL(window, true);
	ImGui_ImplOpenGL3_Init("#version 330");

	glEnable(GL_DEPTH_TEST);  

	glfwSetFramebufferSizeCallback(window, FramebufferSizeCallback);



	////////////////
	// SCENE INIT //
	////////////////

	// Create Camera
	{
		entt::entity cameraEntity = registry.create();
		Components::Camera::Camera& cam = registry.emplace<Components::Camera::Camera>(cameraEntity);
		Components::Transform& transform = registry.emplace<Components::Transform>(cameraEntity, 
			glm::vec3(0, 0, 6), glm::vec3(1), glm::vec3(1)
		);
		activeCamera = &cam;
	}

	resourceManager.materials["BasicMaterial"].shader = Shader("res/gfx/BasicVertShader.vert", "res/gfx/BasicFragShader.frag");
	resourceManager.materials["BasicMaterial"].diffuse = Texture("res/tex/container/container.png");
	resourceManager.materials["BasicMaterial"].specular = Texture("res/tex/container/containerSpecular.png");
	resourceManager.materials["BasicMaterial"].shader.UseShader();
	resourceManager.materials["BasicMaterial"].shader.SetInt("material.diffuse", 0);
	resourceManager.materials["BasicMaterial"].shader.SetInt("material.specular", 1);
	resourceManager.materials["BasicMaterial"].shininess = 64;

	// Create Cubes
	Components::ShapeData sd(cubeVertices, resourceManager.materials["BasicMaterial"]);
	registry.on_construct<Components::Shape>().connect<&Components::OnShapeConstructed>(sd); 
	for (int i = -1; i < 2; i++)
	{
		const auto cube = registry.create();	
		Components::Shape& shape = registry.emplace<Components::Shape>(cube);
		Components::Transform& transform = registry.emplace<Components::Transform>(cube, 
			glm::vec3(i * 2, 0, 0), glm::vec3(1), glm::vec3(1)
		);
	}

	// Create Lights

	// Directional Light
	{
		entt::entity dirLightEntity = registry.create();
		Components::Lights::DirectionalLight& light = registry.emplace<Components::Lights::DirectionalLight>(dirLightEntity,
			glm::vec3(0.1f), glm::vec3(0.5f), glm::vec3(1)
		);
		Components::Transform& transform = registry.emplace<Components::Transform>(dirLightEntity, 
			glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(-0.3f), glm::vec3(1)
		);
	}
	// Point Lights

	while (!glfwWindowShouldClose(window))
	{
		Update();

		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();

		glClearColor(0.025f, 0.025f, 0.025f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		Render();

		ImGui::Render();
		ImGui::EndFrame();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData()); // Not running this function hides ImGui UI!!!

		glfwSwapBuffers(window);
	}
	
	glfwTerminate();
}

void Game::Update()
{
	float currentFrame = static_cast<float>(glfwGetTime());
	deltaTime = currentFrame - lastFrame;
	lastFrame = currentFrame;

	Components::Camera::CameraUpdate(window, activeCamera, registry, deltaTime);

	glfwPollEvents();
}

void Game::Render()
{
	auto shapes = registry.view<Components::Shape>();
	shapes.each([&](Components::Shape& shape){
		renderer.Draw(shape, Components::Camera::GetViewMatrix(activeCamera, registry), registry, activeCamera, deltaTime);
	});

	TestMenu(*this);
}

void FramebufferSizeCallback(GLFWwindow* window, int width, int height) {
	glViewport(0, 0, width, height);
}