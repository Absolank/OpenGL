#include "Window.h"
#include <GLEW/glew.h>
#include <GLFW/glfw3.h>
#include <GLM/glm.hpp>
#include <iostream>
#include <functional>
#include <vector>
#include "Camera.h"
#include "imgui/imgui_impl_opengl3.h"
#include "imgui/imgui_impl_glfw.h"


static float clear_color[] = { .45f, .55f, .60f, 1.f };
void MouseCallback::Mouse(double x, double y){}


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


void Window::MouseCallbacks(double xpos, double ypos)
{
	double xoffset = xpos - Window::mouse_x;
	double yoffset = mouse_y - ypos;
	mouse_x = xpos;
	mouse_y = ypos;

	delta_mouse_x = xoffset;
	delta_mouse_y = yoffset;

	//mou->Mouse(xoffset, yoffset);
	for (MouseCallback * m_callback : __mouse_callbacks_)
	{
		m_callback->Mouse(xoffset, yoffset);
	}
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
void Window::PushMouseCallbacks(MouseCallback & mouse_callback)
{
	__mouse_callbacks_.emplace_back(&mouse_callback);
}
double Window::GetTime()
{
	return glfwGetTime();
}
double Window::GetMouseX()
{
	return mouse_x;
}
double Window::GetDeltaX()
{
	return delta_mouse_x;
}
double Window::GetMouseY()
{
	return mouse_y;
}
double Window::GetDeltaY()
{
	return delta_mouse_y;
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
	//mouse_x = Width/2;
	//mouse_y = Height/2;
	if (!glfwInit())
	{
		std::cout << "ERROR::CANNOT_INITIALIZE_GLFW\n";
	}
	else
	{
		glfwWindowHint(GL_SAMPLES, 16);
		glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GL_TRUE);
		//GLFWmonitor * monitor = glfwGetPrimaryMonitor();
		__window_ = glfwCreateWindow(Width, Height, "OpenGL", NULL, NULL);
		glfwSetInputMode(__window_, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

		MakeContextCurrent();
		glfwSetWindowSizeCallback(__window_,
		[](GLFWwindow *  window, int  width, int  height)
		{
			glViewport(0, 0, width, height);
		});
		glfwSetWindowUserPointer(__window_, (void *)this);
		glfwSetCursorPosCallback(__window_, 
		[](GLFWwindow * window, double xpos, double ypos)
		{
			Window * window_obj = (Window *)glfwGetWindowUserPointer(window);
			window_obj->MouseCallbacks(xpos, ypos);
		});
		glEnable(GL_DEPTH_TEST);
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

				/*ImGui::CreateContext();
				ImGui_ImplGlfw_InitForOpenGL(__window_, true);
				ImGui::StyleColorsDark();*/
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
	//ImGui_ImplGlfw_Shutdown();
	//ImGui::DestroyContext();
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
	/*static float f = 0.f;
	static int counter = 0;
	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplGlfw_NewFrame();
	ImGui::NewFrame();

	ImGui::Begin("OpenGL");
	ImGui::SliderFloat("float", &f, 0.f, 1.f);
	ImGui::ColorEdit3("clear color", (float*)&clear_color);
	ImGui::Checkbox("Demo Window", &show_demo_window);
	ImGui::Checkbox("Another Window", &show_another_window);
	if (ImGui::Button("Button"))
		counter++;
	ImGui::SameLine();
	ImGui::Text("counter = %d", counter);
	ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
	ImGui::End();*/

	return glfwWindowShouldClose(__window_);
}

void Window::SwapBuffers()
{
	/*ImGui::Render();
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());*/
	glfwSwapBuffers(__window_);
}

void Window::PollEvents()
{
	glfwPollEvents();
}
