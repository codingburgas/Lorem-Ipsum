#include "LandingScreen.h"

void LandingScreen::RegisterCallback()
{
    m_SwitchBoundScene(m_RegisterScreen);
}

void LandingScreen::LoginCallback()
{
    std::cout << "Login" << std::endl;
}

void LandingScreen::InitRenderElements()
{
    Core::UI::Button("Register", {GetScreenWidth() / 2 - 100, GetScreenHeight() / 2 - 25 * 2 - 2}, {200, 50}, 0.2f, {0.2, 0.2, 0.8, 1.0}, {1.0f, 1.0f, 1.0f, 1.0f}, 24, m_Scene, LandingScreen::RegisterCallback);
    Core::UI::Button("Login", {GetScreenWidth() / 2 - 100, GetScreenHeight() / 2 + 2}, {200, 50}, 0.2f, {0.2, 0.2, 0.8, 1.0}, {1.0f, 1.0f, 1.0f, 1.0f}, 24, m_Scene, LoginCallback);
}