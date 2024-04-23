#pragma once

class Window {
private:
	struct GLFWwindow* m_WindowHandle;
public:
	Window();
	~Window();

	bool Init();

	struct GLFWwindow* GetHandle() { return m_WindowHandle; }
};