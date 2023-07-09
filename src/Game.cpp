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

	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

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
	resourceManager.materials["BasicMaterial"].texture = Texture("res/tex/wall.jpg");

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

	// Create Light
	{
		entt::entity lightEntity = registry.create();
		Components::LightSource& light = registry.emplace<Components::LightSource>(lightEntity, glm::vec3(1.0f, 0.0f, 1.0f));
		Components::Transform& transform = registry.emplace<Components::Transform>(lightEntity, 
			glm::vec3(1, 1, 1), glm::vec3(1), glm::vec3(1)
		);
	}

	while (!glfwWindowShouldClose(window))
	{
		Update();

		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();

		glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		Render();

		ImGui::Render();
		ImGui::EndFrame();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

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
		renderer.Draw(shape, Components::Camera::GetViewMatrix(activeCamera, registry), registry, deltaTime);
	});

	TestMenu();
}

void FramebufferSizeCallback(GLFWwindow* window, int width, int height) {
	glViewport(0, 0, width, height);
}