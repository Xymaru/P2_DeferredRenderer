#pragma once

#include <Empathy/SimpleTypes.h>
#include "KeyCode.h"
#include "MouseCode.h"

enum KeyState {
    KEY_UP,     // Released
    KEY_DOWN,   // Pressed
    KEY_PRESS,  // Repeat
    KEY_IDLE    // Idle state
};

enum MouseState {
    MOUSE_UP,
    MOUSE_DOWN,
    MOUSE_IDLE
};

class Input {
private:
    static ivec2 m_MousePosition;
    static ivec2 m_RelativeMousePosition;

    static bool m_WindowQuit;

    static int* m_KeyStates;
    static int* m_MouseStates;

    static void KeyCallback(struct GLFWwindow* window, int key, int scancode, int action, int mods);
    static void CursorPosCallback(struct GLFWwindow* window, double x, double y);
    static void MouseButtonCallback(struct GLFWwindow* window, int button, int action, int mods);
    static void WindowCloseCallback(struct GLFWwindow* window);

    Input() = default;
public:
    static bool Quit() { return IsKeyDown(KeyCode::ESCAPE) || m_WindowQuit; }

    static bool IsKeyDown(KeyCode key) { return m_KeyStates[key] == KEY_DOWN; }
    static bool IsKeyUp(KeyCode key) { return m_KeyStates[key] == KEY_UP; }

    static bool IsKeyPressed(KeyCode key) { return m_KeyStates[key] == KEY_PRESS || m_KeyStates[key] == KEY_DOWN; }

    static bool IsMouseDown(int button) { return m_MouseStates[button] == MOUSE_DOWN; }
    static bool IsMouseUp(int button) { return m_MouseStates[button] == MOUSE_UP; }

    static void MouseHideAndLock();
    static void MouseShowAndUnlock();

    static ivec2 GetMousePosition() { return m_MousePosition; }
    static ivec2 GetRelativeMousePosition() { return m_RelativeMousePosition; }

    static ivec2 GetRelativeMousePositionNormalized();

    static bool Init();

    static void Update();

    static void Cleanup();
};