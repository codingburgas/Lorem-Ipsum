#include "LandingScreen.h"
#include  "../Screens.h"

void LandingScreen::RegisterCallback()
{
    
}

void LandingScreen::LoginCallback()
{
   m_SwitchScreens(m_Screens->LoginScreen);
}

void LandingScreen::InitRenderElements()
{
    Core::UI::Button("Register", {GetScreenWidth() / 2 - 100, GetScreenHeight() / 2 - 25 * 2 - 2}, {200, 50}, 0.2f, {0.2, 0.2, 0.8, 1.0}, {1.0f, 1.0f, 1.0f, 1.0f}, 32, "regular", m_Scene, LandingScreen::RegisterCallback);
    Core::UI::Button("Login", {GetScreenWidth() / 2 - 100, GetScreenHeight() / 2 + 2}, {200, 50}, 0.2f, {0.2, 0.2, 0.8, 1.0}, {1.0f, 1.0f, 1.0f, 1.0f}, 32, "regular", m_Scene, LoginCallback);
}