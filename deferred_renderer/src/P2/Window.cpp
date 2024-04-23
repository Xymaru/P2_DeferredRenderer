#include "Window.h"
#include <GLFW/glfw3.h>
#include <Empathy/Debug.h>

Window::Window()
{
}

Window::~Window()
{
}

bool Window::Init()
{
	const char** infoLog = NULL;
	int error_no = 0;

	if (!glfwInit()) {
		error_no = glfwGetError(infoLog);

		//EM_ERROR("glfwInit() failed with code [{0}] and error: [{1}]", error_no, *infoLog);
		return false;
	}

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	m_WindowHandle = glfwCreateWindow(640, 480, "P2_DeferredRenderer", NULL, NULL);

	if (!m_WindowHandle) {
		error_no = glfwGetError(infoLog);

		//EM_ERROR("glfwInit() failed with code [{0}] and error: [{1}]", error_no, *infoLog);
		return false;
	}

	EM_INFO("Window module initialized");

	return true;
}

void Window::Update()
{
	glfwSwapBuffers(m_WindowHandle);
}
