#pragma once

#include "ImGuiPanel.h"
#include <vector>

class ImGuiLayer {
private:
	struct ImGuiContext* m_Context;

	std::vector<ImGuiPanel*> m_Panels;

	void DrawMainMenuBar();
public:
	ImGuiLayer();
	~ImGuiLayer();

	bool Init();

	void PreUpdate();

	void PostUpdate();

	void Cleanup();
};