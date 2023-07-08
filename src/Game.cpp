#include "Game.hpp"
#include <TestMenu.hpp>
#include <shapes/cube.hpp>

void FramebufferSizeCallback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}

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

	resourceManager.materials["BasicMaterial"].shader = Shader("res/gfx/BasicVertShader.vert", "res/gfx/BasicFragShader.frag");
	resourceManager.materials["BasicMaterial"].texture = Texture("res/tex/wall.jpg");

	// Generate Cubes
	Components::ShapeData sd(glm::vec3(0, 1, 0), cubeVertices, resourceManager.materials["BasicMaterial"]);
	registry.on_construct<Components::Shape>().connect<&Components::OnShapeConstructed>(sd);
	for (int i = -1; i < 2; i++)
	{
		const auto cube = registry.create();	
		Components::Shape& shape = registry.emplace<Components::Shape>(cube);
		shape.worldPosition = glm::vec3(i * 2, 0, 0);
	}

	Update();
}

void Game::Update()
{
	while (!glfwWindowShouldClose(window))
	{

        float currentFrame = static_cast<float>(glfwGetTime());
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

		glfwPollEvents();

		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();

		glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		Render();

		TestMenu();

		ImGui::Render();
		ImGui::EndFrame();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glfwTerminate();
}

void Game::Render()
{
	auto shapes = registry.view<Components::Shape>();
	shapes.each([&](Components::Shape shape){
		renderer.Draw(shape, deltaTime);
	});
}
