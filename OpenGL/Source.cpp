#include <iostream>
#include <GLEW/glew.h>
#include <GLM/glm.hpp>
#include <GLM/gtc/matrix_transform.hpp>
#include <GLM/gtc/type_ptr.hpp>
#include "Window.h"
#include "Camera.h"
#include "Shader.h"
#include "Texture.h"
#include "STB/stb_image.h"


void printMat(glm::mat4& matrix);


int main()
{
	Window window(800, 600, "OpenGL", true);
	/*
	float vertices[] = {
		-0.5f, -0.5f, 0.0f,  0.f, 0.f,  
		 0.5f, -0.5f, 0.0f,  1.f, 0.f,
		 0.5f,  0.5f, 0.0f,  1.f, 1.f,    
		-0.5f,  0.5f, 0.0f,  0.f, 1.f, 
	};

	unsigned int index[] = { 0, 1, 2, 2, 3, 0};*/

	float vertices[] = {
		-0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
		 0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
		 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
		 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
		-0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, 0.0f,

		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
		 0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
		 0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
		 0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
		-0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,

		-0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
		-0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
		-0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

		 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
		 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
		 0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
		 0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
		 0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
		 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

		-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
		 0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
		 0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
		 0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,

		-0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
		 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
		 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
		 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
		-0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
		-0.5f,  0.5f, -0.5f,  0.0f, 1.0f
	};
	// world space positions of our cubes
	glm::vec3 cubePositions[] = {
		glm::vec3(0.0f,  0.0f,  0.0f),
		glm::vec3(2.0f,  5.0f, -15.0f),
		glm::vec3(-1.5f, -2.2f, -2.5f),
		glm::vec3(-3.8f, -2.0f, -12.3f),
		glm::vec3(2.4f, -0.4f, -3.5f),
		glm::vec3(-1.7f,  3.0f, -7.5f),
		glm::vec3(1.3f, -2.0f, -2.5f),
		glm::vec3(1.5f,  2.0f, -2.5f),
		glm::vec3(1.5f,  0.2f, -1.5f),
		glm::vec3(-1.3f,  1.0f, -1.5f)
	};


	unsigned int VBO;
	unsigned int VAO;
	unsigned int IBO;
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	//glGenBuffers(1, &IBO);

	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);
	
	/*glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(index), index, GL_STATIC_DRAW);*/

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	//glBindVertexArray(0);

	Shader simple_shader;
	simple_shader.SetResourcePathAndCompile("shaders/vertex.vert", "shaders/fragment.frag");
	//glBindVertexArray(VAO);
	simple_shader.UnBindShaderProgram();
	simple_shader.BindShaderProgram();

	glBindVertexArray(VAO);
	//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);

	Texture texte("res/awesomeface.png");
	texte.Bind();

	std::string s_projection = "projection", s_model = "model", s_view = "view";
	glm::mat4 model(1.f);
	glm::mat4 view(1.f);
	glm::mat4 projection(1.f);


	model = glm::rotate(model, glm::radians(-55.0f), glm::vec3(1.0f, 0.0f, 0.0f));
	printMat(model);

	view = glm::translate(view, glm::vec3(0.0f, 0.0f, -3.0f));
	printMat(view);
	projection = glm::perspective(glm::radians(45.0f), (4.f / 3.f), 0.1f, 100.0f);
	glm::mat4 orthogonal_projection = glm::ortho(0.f, 800.f, 0.f,600.f, 0.1f, 100.f);

	simple_shader.SetUniform(s_model, model);
	simple_shader.SetUniform(s_view, view);
	simple_shader.SetUniform(s_projection, projection);

	Camera cam;
	Window::PushMouseCallbacks(cam);

	WINDOW_BEGIN(window)

		glClearColor(0.4f, 0.5f, 0.4f, 1.f);
		glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
		glm::mat4 viw = cam.GetViewMatrix();
		simple_shader.SetUniform(s_view, viw);
		glDrawArrays(GL_TRIANGLES, 0, 36);
		if (window.isKeyPressed(KEY::W))
			cam.MoveForward(window.GetDeltaTime());
		if (window.isKeyPressed(KEY::S))
			cam.MoveBackward(window.GetDeltaTime());
		if (window.isKeyPressed(KEY::A))
			cam.MoveLeft(window.GetDeltaTime());
		if (window.isKeyPressed(KEY::D))
			cam.MoveRight(window.GetDeltaTime());
		//glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, NULL);
		window.SwapBuffers();
		window.PollEvents();


	WINDOW_END(window)

	return 0;
}

void printMat(glm::mat4 & matrix)
{
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
			std::cout << matrix[i][j];
		std::cout << std::endl;
	}
}
