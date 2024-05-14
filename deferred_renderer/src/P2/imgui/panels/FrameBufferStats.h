#pragma once

#include "../ImGuiPanel.h"

#include <P2/Application.h>

class FrameBufferStats : public ImGuiPanel {
private:
	Scene* m_CurrentScene;
public:
	FrameBufferStats();

	void OnImGuiRender() override;
};