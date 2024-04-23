#pragma once

#include <Empathy/SimpleTypes.h>
#include "KeyCode.h"

enum KeyState {
    KEY_UP,     // Released
    KEY_DOWN,   // Pressed
    KEY_PRESS,  // Repeat
    KEY_IDLE    // Idle state
};

class Input {
private:
    static int* m_KeyStates;

    static void KeyCallback(struct GLFWwindow* window, int key, int scancode, int action, int mods);

    Input() = default;
public:
    static bool Quit() { return IsKeyDown(KeyCode::ESCAPE); }

    static bool IsKeyDown(KeyCode key) { return m_KeyStates[key] == KEY_DOWN; }
    static bool IsKeyUp(KeyCode key) { return m_KeyStates[key] == KEY_UP; }

    static bool IsKeyPressed(KeyCode key) { return m_KeyStates[key] == KEY_PRESS; }

    static bool Init();

    static void Update();

    static void Cleanup();
};