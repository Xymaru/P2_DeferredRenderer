#include "OpenGLStatsPanel.h"
#include <imgui.h>

OpenGLStatsPanel::OpenGLStatsPanel()
{
	m_PanelName = "OpenGL Stats";
	m_OpenGLInfo = Application::GetInstance()->getOpenGLInfo();
}

void OpenGLStatsPanel::OnImGuiRender()
{
	ImGui::Text("Version: %s", m_OpenGLInfo->version.c_str());
	ImGui::Text("Renderer: %s", m_OpenGLInfo->renderer.c_str());
	ImGui::Text("Vendor: %s", m_OpenGLInfo->vendor.c_str());
	ImGui::Text("Shading language version: %s", m_OpenGLInfo->shading_lang_version.c_str());

	if (ImGui::TreeNode("Extensions")) {
		for (i32 i = 0; i < m_OpenGLInfo->num_extensions; i++) {
			ImGui::Text("%s", m_OpenGLInfo->extensions[i].c_str());
		}

		ImGui::TreePop();
	}
}