#include "FrameBufferStats.h"
#include <imgui.h>

FrameBufferStats::FrameBufferStats()
{
	m_PanelName = "Framebuffer Stats";
	m_CurrentScene = Application::GetInstance()->getCurrentScene();
}

void FrameBufferStats::OnImGuiRender()
{
	ImVec2 texture_size = { 256, 144 };
	ImVec2 texture_uv1 = { 1, 0 };
	ImVec2 texture_uv2 = { 0, 1 };

	ImGui::Text("Albedo");
	ImGui::Image((ImTextureID)m_CurrentScene->getAlbedoTexture(), texture_size, texture_uv2, texture_uv1);

	ImGui::Text("Normals");
	ImGui::Image((ImTextureID)m_CurrentScene->getNormalsTexture(), texture_size, texture_uv2, texture_uv1);

	ImGui::Text("Position");
	ImGui::Image((ImTextureID)m_CurrentScene->getPositionTexture(), texture_size, texture_uv2, texture_uv1);	

	ImGui::Text("Depth");
	ImGui::Image((ImTextureID)m_CurrentScene->getDepthTexture(), texture_size, texture_uv2, texture_uv1);
}