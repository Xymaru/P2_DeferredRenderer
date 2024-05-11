#include "Input.h"
#include <GLFW/glfw3.h>

#include "Application.h"

#include <Empathy/Debug.h>

#define KEY_STATE_SIZE GLFW_KEY_LAST
#define MOUSE_STATE_SIZE GLFW_MOUSE_BUTTON_LAST

int* Input::m_KeyStates = nullptr;
int* Input::m_MouseStates = nullptr;

bool Input::m_WindowQuit = false;
ivec2 Input::m_MousePosition = { 0, 0 };

void Input::KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	m_KeyStates[key] = action;
}

void Input::CursorPosCallback(GLFWwindow* window, double x, double y)
{
	m_MousePosition = { (int)x, (int)y };
}

void Input::MouseButtonCallback(GLFWwindow* window, int button, int action, int mods)
{
	m_MouseStates[button] = action;
}

void Input::WindowCloseCallback(GLFWwindow* window)
{
	m_WindowQuit = true;
}

bool Input::Init()
{
	Window* window = Application::GetInstance()->getWindow();
	GLFWwindow* whandle = window->GetHandle();

	glfwSetKeyCallback(whandle, &Input::KeyCallback);
	glfwSetCursorPosCallback(whandle, &Input::CursorPosCallback);
	glfwSetMouseButtonCallback(whandle, &Input::MouseButtonCallback);
	glfwSetWindowCloseCallback(whandle, &Input::WindowCloseCallback);

	m_KeyStates = new int[KEY_STATE_SIZE] { KEY_IDLE };
	m_MouseStates = new int[MOUSE_STATE_SIZE] { MOUSE_IDLE };

	return true;
}

void Input::Update()
{
	// Reset key states
	memset(m_KeyStates, KEY_IDLE, KEY_STATE_SIZE * sizeof(KeyCode));
	memset(m_MouseStates, MOUSE_IDLE, MOUSE_STATE_SIZE * sizeof(MouseCode));

	// Update input events
	glfwPollEvents();
}

void Input::Cleanup()
{
	//delete[] m_KeyStates;
	//delete[] m_MouseStates;
}