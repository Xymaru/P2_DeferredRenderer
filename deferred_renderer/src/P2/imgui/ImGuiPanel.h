#pragma once

#include <string>

class ImGuiPanel {
protected:
	std::string m_PanelName;
	bool m_Active;

	virtual void OnImGuiRender() = 0;
public:
	ImGuiPanel();

	void ImGuiRender();

	const char* getName() { return m_PanelName.c_str(); }

	bool IsActive() { return m_Active; }
	void SwitchActive() { m_Active = !m_Active; }
	void SetActive(bool active) { m_Active = active; }
};