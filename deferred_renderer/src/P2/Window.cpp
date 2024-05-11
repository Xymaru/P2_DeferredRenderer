#include "Window.h"

#include <glad/glad.c>
#include <GLFW/glfw3.h>

#include <Empathy/Debug.h>
#include <P2/Application.h>

void Window::FramebufferSizeCallback(GLFWwindow* window, int width, int height)
{
	Application::GetInstance()->getWindow()->m_WindowSize = { width, height };

	
}

void Window::RendererDebugCallback(u32 src, u32 type, u32 id, u32 severity, i32 len, const char* msg, const void* uparam)
{
	if (severity == GL_DEBUG_SEVERITY_NOTIFICATION) return;

	EM_ERROR("OpenGL error: {} with param {}", msg, uparam);
}

Window::Window() :
	m_WindowHandle(nullptr),
	m_WindowSize({ 800, 600 })
{
}

Window::~Window()
{
}

bool Window::Init()
{
	std::string error_msg = "Unknown";
	const char** infoLog = NULL;
	int error_no = 0;

	if (!glfwInit()) {
		error_no = glfwGetError(infoLog);

		if (infoLog) {
			error_msg = *infoLog;
		}

		EM_ERROR("glfwInit() failed with code [{0}] and error: [{1}]", error_no, error_msg.c_str());
		return false;
	}

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	m_WindowHandle = glfwCreateWindow(m_WindowSize.x, m_WindowSize.y, "P2_DeferredRenderer", NULL, NULL);

	if (!m_WindowHandle) {
		error_no = glfwGetError(infoLog);

		if (infoLog) {
			error_msg = *infoLog;
		}

		EM_ERROR("glfwCreateWindow() failed with code [{0}] and error: [{1}]", error_no, error_msg.c_str());

		return false;
	}

	glfwMakeContextCurrent(m_WindowHandle);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		EM_ERROR("Failed to initialize glad.");
		return false;
	}

	glEnable(GL_DEBUG_OUTPUT);
	glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
	glDebugMessageCallback(&Window::RendererDebugCallback, NULL);

	glEnable(GL_DEPTH_TEST);

	glClearColor(.1f, .1f, .1f, 1.0f);

	EM_INFO("Window module initialized");

	return true;
}

void Window::PreUpdate()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Window::PostUpdate()
{
	glfwSwapBuffers(m_WindowHandle);
}

void Window::Cleanup()
{
	glfwDestroyWindow(m_WindowHandle);
	glfwTerminate();
}
