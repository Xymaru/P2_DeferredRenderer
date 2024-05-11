#include "ImGuiPanel.h"
#include <imgui.h>

ImGuiPanel::ImGuiPanel() : 
	m_Active(false)
{

}

void ImGuiPanel::ImGuiRender()
{
	ImGui::Begin(m_PanelName.c_str());

	OnImGuiRender();

	ImGui::End();
}