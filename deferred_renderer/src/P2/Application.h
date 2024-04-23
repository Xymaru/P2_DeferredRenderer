#pragma once
#include <Empathy/SimpleTypes.h>

#include <glm/glm.hpp>
#include <vector>

#include <P2/Input.h>
#include <P2/Window.h>

class Application {
private:
    // Loop
    f32  deltaTime;
    bool isRunning;

    Window m_Window;

    static Application* s_Instance;
public:
    bool Init();

    void Run();

    void Cleanup();

    Window* GetWindow() { return &m_Window; }

    static Application* GetInstance() { return s_Instance; }

    static void SetApplication(Application* app) { s_Instance = app; }
};