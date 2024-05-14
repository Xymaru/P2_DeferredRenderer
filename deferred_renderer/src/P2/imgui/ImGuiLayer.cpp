#include "ImGuiLayer.h"

#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>

#include <GLFW/glfw3.h>

#include <P2/Application.h>
#include <Empathy/Debug.h>

#include "panels/OpenGLStatsPanel.h"
#include "panels/FrameBufferStats.h"

ImGuiLayer::ImGuiLayer() : 
    m_Context(nullptr)
{
}

ImGuiLayer::~ImGuiLayer()
{
    size_t p_size = m_Panels.size();

    for (size_t i = 0; i < p_size; i++) {
        delete m_Panels[i];
    }
}

void ImGuiLayer::DrawMainMenuBar()
{
    size_t p_size = m_Panels.size();

    if (ImGui::BeginMainMenuBar()) {
        if (ImGui::BeginMenu("View")) {
            for (size_t i = 0; i < p_size; i++)
            {
                if (ImGui::MenuItem(m_Panels[i]->getName(), "", m_Panels[i]->IsActive())) {
                    m_Panels[i]->SwitchActive();
                }
            }
            ImGui::EndMenu();
        }

        ImGui::EndMainMenuBar();
    }
}

bool ImGuiLayer::Init()
{
    Window* window = Application::GetInstance()->getWindow();

    IMGUI_CHECKVERSION();

    m_Context = ImGui::CreateContext();

    ImGuiIO& io = ImGui::GetIO();

    ImGui::StyleColorsDark();

    if (!ImGui_ImplGlfw_InitForOpenGL(window->GetHandle(), false)) {
        return false;
    }

    if (!ImGui_ImplOpenGL3_Init(window->getGLSLVersion())) {
        return false;
    }

    EM_INFO("ImGui successfully initialized!");

    // Imgui panels
    m_Panels.push_back(new OpenGLStatsPanel());
    m_Panels.push_back(new FrameBufferStats());

    return true;
}

void ImGuiLayer::PreUpdate()
{
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();

    //ImGui::ShowDemoWindow();

    DrawMainMenuBar();

    size_t p_size = m_Panels.size();
    for (size_t i = 0; i < p_size; i++) {
        if (m_Panels[i]->IsActive()) {
            m_Panels[i]->ImGuiRender();
        }
    }
}

void ImGuiLayer::PostUpdate()
{
    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

void ImGuiLayer::Cleanup()
{
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext(m_Context);
}