#include "Application.h"

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
        Input::Update();
    }
}

void Application::Cleanup()
{
    Input::Cleanup();
}