#include "RegisterScreen.h"

void registerCallback() {}

void RegisterScreen::LoginCallback()
{
    m_SwitchBoundScene(m_LoginScreen);
}

void RegisterScreen::InitRenderElements()
{
    Core::UI::Button("Login", {GetScreenWidth() / 2 - 192, 85}, {190, 40}, 0.25, {1.0, 1.0, 1.0, 1.0f}, {0.0f, 0.0f, 0.0f, 1.0f}, 24, "regular", m_Scene, LoginCallback);
    Core::UI::Button("Register", {GetScreenWidth() / 2, 85}, {190, 40}, 0.25, {0.49, 0.53, 0.99, 1.0f}, {1.0f, 1.0f, 1.0f, 1.0f}, 24, "regular", m_Scene, registerCallback);
}
