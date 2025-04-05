#include <iostream>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "renderer.h"

#define WIDTH 1200
#define HEIGHT 675

int main() {
	if (!glfwInit()) {
		std::cerr << "Failed to initialize GLFW\n" << std::endl;
		glfwTerminate();
		return -1;
	}

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);
	GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, "DOOM", NULL, NULL);
	glfwMakeContextCurrent(window);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		std::cout << "Failed to initialize GLAD\n" << std::endl;
		glfwDestroyWindow(window);
		glfwTerminate();
		return -1;
	}

	renderer_init(WIDTH, HEIGHT);

	char title[128] = "DOOM";
	float last = 0.0f;
	while (!glfwWindowShouldClose(window)) {
		float now	= glfwGetTime();
		float delta = now - last;
		last		= now;

		snprintf(title, 128, "DOOM | %.0f FPS", 1.0f / delta);
		glfwSetWindowTitle(window, title);


		glfwPollEvents();
		renderer_clear();
		glfwSwapBuffers(window);
	}

	glfwDestroyWindow(window);
	glfwTerminate();

	return 0;
}