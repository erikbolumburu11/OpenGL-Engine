#include <vector>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>
#include <main.hpp>
#include <Shape.hpp>
#include <Game.hpp>
#include <TestMenu.hpp>

std::vector<float> vertices1 = {
	// positions         // colors
	 0.5f, -0.5f, 0.0f,  1.0f, 0.0f, 0.0f,   // bottom right
	-0.5f, -0.5f, 0.0f,  0.0f, 1.0f, 0.0f,   // bottom left
	 0.0f,  0.5f, 0.0f,  0.0f, 0.0f, 1.0f    // top 
};

std::vector<unsigned int> indices = {  // note that we start from 0!
	0, 1, 3,   // first triangle
};

int main() {
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	//Coordinates Start At The Bottom Left Corner
	GLFWwindow* window = glfwCreateWindow(800, 600, "OpenGL Engine", NULL, NULL);
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

	glfwSetFramebufferSizeCallback(window, FramebufferSizeCallback);

	Game game;

	game.resourceManager.shaderPrograms["BasicShader"] = Shader("res/gfx/BasicVertShader.vert", "res/gfx/BasicFragShader.frag");

	vec4 col1{ 0, 0, 1, 1 };
	Shape shape1(vertices1, indices, game.resourceManager.shaderPrograms["BasicShader"], col1);

	while (!glfwWindowShouldClose(window))
	{
		glfwPollEvents();

		// ImGui
		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();

		ProcessInput(window);
		// Draw Stuff
		glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		game.renderer.Draw(shape1);

		TestMenu();

		ImGui::Render();
		ImGui::EndFrame();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glfwTerminate();
	return 0;
}