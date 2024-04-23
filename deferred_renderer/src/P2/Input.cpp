#include "Input.h"
#include <GLFW/glfw3.h>

#include "Application.h"

#include <Empathy/Debug.h>

#define KEY_STATE_SIZE GLFW_KEY_LAST

int* Input::m_KeyStates = nullptr;

void Input::KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	m_KeyStates[key] = action;
}

bool Input::Init()
{
	Window* window = Application::GetInstance()->GetWindow();

	glfwSetKeyCallback(window->GetHandle(), &Input::KeyCallback);

	m_KeyStates = new int[KEY_STATE_SIZE] { KEY_IDLE };

	return true;
}

void Input::Update()
{
	// Reset key states
	memset(m_KeyStates, KEY_IDLE, KEY_STATE_SIZE * sizeof(KeyCode));

	glfwPollEvents();
}

void Input::Cleanup()
{
	delete[] m_KeyStates;
}