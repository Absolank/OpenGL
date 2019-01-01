#include "Window.h"
#include <GLEW/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
void APIENTRY DebugCallback(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar* message, const void* userParam) {

	std::cout << "---------------------opengl-callback-start------------" << std::endl;
	std::cout << "message: " << message << std::endl;
	std::cout << "type: ";
	switch (type) {
	case GL_DEBUG_TYPE_ERROR:
		std::cout << "ERROR";
		break;
	case GL_DEBUG_TYPE_DEPRECATED_BEHAVIOR:
		std::cout << "DEPRECATED_BEHAVIOR";
		break;
	case GL_DEBUG_TYPE_UNDEFINED_BEHAVIOR:
		std::cout << "UNDEFINED_BEHAVIOR";
		break;
	case GL_DEBUG_TYPE_PORTABILITY:
		std::cout << "PORTABILITY";
		break;
	case GL_DEBUG_TYPE_PERFORMANCE:
		std::cout << "PERFORMANCE";
		break;
	case GL_DEBUG_TYPE_OTHER:
		std::cout << "OTHER";
		break;
	}
	std::cout << std::endl;

	std::cout << "id: " << id << std::endl;
	std::cout << "severity: ";
	switch (severity) {
	case GL_DEBUG_SEVERITY_LOW:
		std::cout << "LOW";
		break;
	case GL_DEBUG_SEVERITY_MEDIUM:
		std::cout << "MEDIUM";
		break;
	case GL_DEBUG_SEVERITY_HIGH:
		std::cout << "HIGH";
		break;
	}
	std::cout << std::endl;
	std::cout << "---------------------opengl-callback-end--------------" << std::endl;
}
void Window::WindowResize(GLFWwindow *  window, int  width, int  height)
{

}

void Window::Mouse(GLFWwindow * window, double xpos, double ypos)
{

}
void Window::Tick()
{
	//if (isTicking)
	//{
		__curr_time = glfwGetTime();
		__delta_time = __curr_time - __p_time_;
		__p_time_ = __curr_time;
	//}
}
double Window::GetTime()
{
	return glfwGetTime();
}
double Window::GetDeltaTime()
{
	return __delta_time;
}
void Window::BeginTicking()
{
	Tick();
}
Window::Window(int Width, int Height, const char * WindowName, bool InitGlew)
{
	if (!glfwInit())
	{
		std::cout << "ERROR::CANNOT_INITIALIZE_GLFW\n";
	}
	else
	{
		glfwWindowHint(GL_SAMPLES, 4);
		glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GL_TRUE);
		__window_ = glfwCreateWindow(800, 600, "OpenGL", NULL, NULL);
		MakeContextCurrent();

		glfwSetWindowSizeCallback(__window_, WindowResize);
		glfwSetCursorPosCallback(__window_, Mouse);
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
	}
}


Window::~Window()
{
	glfwDestroyWindow(__window_);
	glfwTerminate();
}

void Window::MakeContextCurrent()
{
	if (__window_ != nullptr)
		glfwMakeContextCurrent(__window_);
	else
		std::cout << "ERROR::MAKING_WINDOW_CURRENT_CONTEXT\n" ;
}

bool Window::isKeyPressed(KEY KEY_ID)
{
	if (glfwGetKey(__window_, KEY_ID) == GLFW_PRESS)
		return true;
	return false;
}

bool Window::isKeyReleased(KEY KEY_ID)
{
	if (glfwGetKey(__window_, KEY_ID) == GLFW_RELEASE)
		return true;
	return false;
}
bool Window::isKeyRepeated(KEY KEY_ID)
{
	if (glfwGetKey(__window_, KEY_ID) == GLFW_REPEAT)
		return true;
	return false;
}

bool Window::windowShouldClose()
{
	return glfwWindowShouldClose(__window_);
}

void Window::SwapBuffers()
{
	glfwSwapBuffers(__window_);
}

void Window::PollEvents()
{
	glfwPollEvents();
}
