#include "Application.h"

#include <Empathy/Debug.h>
#include <Empathy/Resources.h>

#include <glad/glad.h>

#include "scene/TestScene.h"

Application* Application::s_Instance = nullptr;

bool Application::Init()
{
    m_TargetResolution = { 1440, 810 };

    if (!m_Window.Init()) {
        return false;
    }

    if (!Input::Init()) {
        return false;
    }

    m_OpenGLInfo.version = (const char*)glGetString(GL_VERSION);
    m_OpenGLInfo.renderer = (const char*)glGetString(GL_RENDERER);
    m_OpenGLInfo.vendor = (const char*)glGetString(GL_VENDOR);
    m_OpenGLInfo.shading_lang_version = (const char*)glGetString(GL_SHADING_LANGUAGE_VERSION);

    glGetIntegerv(GL_NUM_EXTENSIONS, &m_OpenGLInfo.num_extensions);

    m_OpenGLInfo.extensions.resize(m_OpenGLInfo.num_extensions);
    for (i32 i = 0; i < m_OpenGLInfo.num_extensions; i++) {
        m_OpenGLInfo.extensions[i] = (const char*)glGetStringi(GL_EXTENSIONS, (u32)i);
    }

    m_TestScene = new TestScene();
    m_TestScene->Init();

    if (!m_ImGuiLayer.Init()) {
        return false;
    }

    return true;
}

void Application::Run()
{
    while (!Input::Quit()) {
        // Update input
        Input::Update();

        // Clear window color
        m_Window.PreUpdate();

        // Update imgui layer
        m_ImGuiLayer.PreUpdate();

        //----- Update loop
        m_TestScene->Update();

        //----- Render loop

        m_TestScene->Render();

        //-----------------

        // Update window buffer
        ivec2 w_size = m_Window.GetWindowSize();
        glViewport(0, 0, w_size.x, w_size.y);

        m_ImGuiLayer.PostUpdate();
        m_Window.PostUpdate();
    }
}

void Application::Cleanup()
{
    delete m_TestScene;

    Input::Cleanup();
    m_ImGuiLayer.Cleanup();
    m_Window.Cleanup();
}