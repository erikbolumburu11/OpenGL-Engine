#define STB_IMAGE_IMPLEMENTATION
#include <vector>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>
#include <main.hpp>
#include <Shape.hpp>
#include <Game.hpp>
#include <TestMenu.hpp>
#include <shapes/cube.hpp>

// Resize glViewport
void FramebufferSizeCallback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}

void ProcessInput(GLFWwindow* window) {
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
}

float lastFrame = 0.0f;

int main() {
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	//Coordinates Start At The Bottom Left Corner
	GLFWwindow* window = glfwCreateWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "OpenGL Engine", NULL, NULL);
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

	Game game;

	game.resourceManager.materials["BasicMaterial"].shader = Shader("res/gfx/BasicVertShader.vert", "res/gfx/BasicFragShader.frag");
	game.resourceManager.materials["BasicMaterial"].texture = Texture("res/tex/wall.jpg");

	Shape shape1(vertices, game.resourceManager.materials["BasicMaterial"]);

	while (!glfwWindowShouldClose(window))
	{

        float currentFrame = static_cast<float>(glfwGetTime());
        game.deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

		glfwPollEvents();

		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();

		ProcessInput(window);

		glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


		game.renderer.Draw(shape1, game.deltaTime);

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