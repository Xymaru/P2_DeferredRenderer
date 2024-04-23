#pragma once

class Window {
private:
	struct GLFWwindow* m_WindowHandle;
public:
	Window();
	~Window();

	bool Init();

	void Update();

	struct GLFWwindow* GetHandle() { return m_WindowHandle; }
};