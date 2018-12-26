#include <iostream>
#include <GLEW/glew.h>
#include <GLFW/glfw3.h>
#include <GLM/glm.hpp>
#include "Shader.h"
int main()
{
	GLFWwindow * window;
	if (!glfwInit())
	{
		std::cerr << "ERROR::FAILED_TO_INITIALIZE_GLFW\n";
	}
	glfwWindowHint(GLFW_SAMPLES, 4);
	

	window = glfwCreateWindow(800, 600, "OpenGL", NULL, NULL);
	glfwWindowHint(GL_SAMPLES, 4);
	glfwMakeContextCurrent(window);

	if (glewInit() == GLEW_OK)
	{
		std::cout << glGetString(GL_VERSION) << " " << glGetString(GL_VENDOR) << std::endl;
	}
	else
	{
		std::cerr << "ERROR::FAILED_TO_INITIALIZE_GLEW\n";
	}
	
	float vertices[] = {
		-0.5f, -0.5f, 0.0f, 1.f, 0.f, 0.f,  
		 0.5f, -0.5f, 0.0f, 0.f, 1.f, 0.f,
		 0.5f,  0.5f, 0.0f, 0.f, 0.f, 1.f,    
		-0.5f,  0.5f, 0.0f, 0.f, 1.f, 0.f, 
	};

	unsigned int index[] = { 0, 1, 2, 2, 3, 0};


	unsigned int VBO, VAO, IBO;
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &IBO);

	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);
	
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(index), index, GL_STATIC_DRAW);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

	Shader simple_shader;
	simple_shader.SetResourcePathAndCompile("shaders/vertex.vert", "shaders/fragment.frag");
	simple_shader.UnBindShaderProgram();

	while (!glfwWindowShouldClose(window))
	{

		glClear(GL_COLOR_BUFFER_BIT);

		simple_shader.BindShaderProgram();
		glBindVertexArray(VAO);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, NULL);
		glfwSwapBuffers(window);
		glfwPollEvents();
	}
	glfwTerminate();
	glfwDestroyWindow(window);
	return 0;
}