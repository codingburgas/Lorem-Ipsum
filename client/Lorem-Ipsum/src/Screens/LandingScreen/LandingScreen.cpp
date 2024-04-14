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
    std::shared_ptr<Core::UI::ButtonMaterial> buttonMaterial = std::make_shared<Core::UI::ButtonMaterial>();
    buttonMaterial->Color = {0.2, 0.2, 0.8, 1.0};
    buttonMaterial->Roundness = 0.2f;
    buttonMaterial->TextSize = 32;
    buttonMaterial->Scene = m_Scene;
    
    Core::UI::Button("Register", {GetScreenWidth() / 2 - 100, GetScreenHeight() / 2 - 25 * 2 - 2}, {200, 50}, buttonMaterial, LandingScreen::RegisterCallback);
    Core::UI::Button("Login", {GetScreenWidth() / 2 - 100, GetScreenHeight() / 2 + 2}, {200, 50}, buttonMaterial, LoginCallback);
}