#include "Application.h"

#include <Empathy/Debug.h>

Application* Application::s_Instance = nullptr;

bool Application::Init()
{
    if (!m_Window.Init()) {
        return false;
    }

    if (!Input::Init()) {
        return false;
    }

    return true;
}

void Application::Run()
{
    while (!Input::Quit()) {
        // Clear window color
        m_Window.PreUpdate();

        // Update input
        Input::Update();



        // Update window buffer
        m_Window.PostUpdate();
    }
}

void Application::Cleanup()
{
    Input::Cleanup();
}