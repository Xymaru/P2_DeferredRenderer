#pragma once
#include <Empathy/SimpleTypes.h>

#include <glm/glm.hpp>
#include <vector>

#include <P2/Input.h>
#include <P2/Window.h>
#include <P2/imgui/ImGuiLayer.h>

#include "entity/Entity.h"

class Application {
public:
    struct OpenGLInfo {
        std::string version;
        std::string renderer;
        std::string vendor;
        std::string shading_lang_version;
        i32 num_extensions;
        std::vector<std::string> extensions;
    };
private:
    OpenGLInfo m_OpenGLInfo;

    ImGuiLayer m_ImGuiLayer;
    Window m_Window;

    Entity* entity;

    static Application* s_Instance;
public:
    bool Init();

    void Run();

    void Cleanup();

    Window* getWindow() { return &m_Window; }

    OpenGLInfo* getOpenGLInfo() { return &m_OpenGLInfo; }

    static Application* GetInstance() { return s_Instance; }

    static void SetApplication(Application* app) { s_Instance = app; }
};