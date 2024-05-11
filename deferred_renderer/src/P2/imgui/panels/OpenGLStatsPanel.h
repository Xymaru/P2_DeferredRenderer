#pragma once

#include "../ImGuiPanel.h"

#include <P2/Application.h>

class OpenGLStatsPanel : public ImGuiPanel {
private:
	Application::OpenGLInfo* m_OpenGLInfo;
public:
	OpenGLStatsPanel();

	void OnImGuiRender() override;
};