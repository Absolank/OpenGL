#include <GLM/glm.hpp>
#include "Debugger.h"
#include "Shader.h"
#include "Texture.h"
#include "STB/stb_image.h"
int main()
{
	GLFWwindow * window;
	if (!glfwInit())
	{
		std::cerr << "ERROR::FAILED_TO_INITIALIZE_GLFW\n";
	}
	glfwWindowHint(GLFW_SAMPLES, 4);
	

	glfwWindowHint(GL_SAMPLES, 4);
	glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GL_TRUE);
	window = glfwCreateWindow(800, 600, "OpenGL", NULL, NULL);
	glfwMakeContextCurrent(window);
	

	if (glewInit() == GLEW_OK)
	{
		std::cout << glGetString(GL_VERSION) << " " << glGetString(GL_VENDOR) << std::endl;
		if (glDebugMessageCallback) {
			std::cout << "Register OpenGL debug callback " << std::endl;
			glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
			glDebugMessageCallback(DebugCallback, nullptr);
			GLuint unusedIds = 0;
			glDebugMessageControl(GL_DONT_CARE,
				GL_DONT_CARE,
				GL_DONT_CARE,
				0,
				&unusedIds,
				true);
		}
		else
			std::cout << "glDebugMessageCallback not available" << std::endl;
	}
	else
	{
		std::cerr << "ERROR::FAILED_TO_INITIALIZE_GLEW\n";
	}
	

	float vertices[] = {
		-0.5f, -0.5f, 0.0f,  0.f, 0.f,  
		 0.5f, -0.5f, 0.0f,  1.f, 0.f,
		 0.5f,  0.5f, 0.0f,  1.f, 1.f,    
		-0.5f,  0.5f, 0.0f,  0.f, 1.f, 
	};

	unsigned int index[] = { 0, 1, 2, 2, 3, 0};


	unsigned int VBO;
	unsigned int VAO;
	unsigned int IBO;
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &IBO);

	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);
	
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(index), index, GL_STATIC_DRAW);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	//glBindVertexArray(0);


	Shader simple_shader;
	simple_shader.SetResourcePathAndCompile("shaders/vertex.vert", "shaders/fragment.frag");
	//glBindVertexArray(VAO);
	simple_shader.UnBindShaderProgram();
	simple_shader.BindShaderProgram();

	glBindVertexArray(VAO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);

	Texture texte("res/awesomeface.png");
	texte.Bind();
	
	float prev_time = glfwGetTime();
	float delta_time = 0.f;
	float curr_time = 0.f;
	float x = 0.f;
	while (!glfwWindowShouldClose(window))
	{
		curr_time = glfwGetTime();
		delta_time = curr_time - prev_time;
		prev_time = curr_time;

		glClear(GL_COLOR_BUFFER_BIT);
		glRotatef(x, 0.f, 0.f, 1.f);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, NULL);
		x += delta_time;
		std::cout << x << " ";
		glfwSwapBuffers(window);
		glfwPollEvents();
	}
	glfwTerminate();
	glfwDestroyWindow(window);
	return 0;
}