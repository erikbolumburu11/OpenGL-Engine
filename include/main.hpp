#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <linmath.h/linmath.h>

#include <stdlib.h>
#include <stdio.h>
#include <iostream>

// Resize glViewport
void FramebufferSizeCallback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}

void ProcessInput(GLFWwindow* window) {
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
}
