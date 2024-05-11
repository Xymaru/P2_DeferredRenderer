#pragma once

#include <Empathy/SimpleTypes.h>

class Window {
private:
	struct GLFWwindow* m_WindowHandle;

	ivec2 m_WindowSize;

	static void FramebufferSizeCallback(struct GLFWwindow* window, int width, int height);

	static void RendererDebugCallback(u32 src, u32 type, u32 id, u32 severity, i32 len, const char* msg, const void* uparam);
public:
	Window();
	~Window();

	bool Init();

	void PreUpdate();
	void PostUpdate();

	void Cleanup();

	const char* getGLSLVersion() { return "#version 430"; }
	struct GLFWwindow* GetHandle() { return m_WindowHandle; }
	ivec2 GetWindowSize() { return m_WindowSize; }
};