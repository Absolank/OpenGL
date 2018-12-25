#include <iostream>
#include <GLEW/glew.h>
#include <GLFW/glfw3.h>
#include <GLM/glm.hpp>

int main()
{
	GLFWwindow * window;
	if (!glfwInit())
	{
		std::cerr << "ERROR::FAILED_TO_INITIALIZE_GLFW\n";
	}
	window = glfwCreateWindow(800, 600, "OpenGL", NULL, NULL);
	glfwMakeContextCurrent(window);

	if (glewInit() == GLEW_OK)
	{
		std::cout << glGetString(GL_VERSION) << " " << glGetString(GL_VENDOR) << std::endl;
	}
	else
	{
		std::cerr << "ERROR::FAILED_TO_INITIALIZE_GLEW\n";
	}

	while (!glfwWindowShouldClose(window))
	{

		glClear(GL_COLOR_BUFFER_BIT);
		glfwSwapBuffers(window);
		glfwPollEvents();
	}
	return 0;
}