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
        // Update input
        Input::Update();



        // Update window buffer
        m_Window.Update();
    }
}

void Application::Cleanup()
{
    Input::Cleanup();
}