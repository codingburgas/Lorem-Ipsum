#include "LandingScreen.h"
#include  "../Screens.h"

void LandingScreen::RegisterCallback(std::shared_ptr<Core::Entity> e)
{
   m_SwitchScreens(m_Screens->RegisterScreen);
}

void LandingScreen::InitRenderElements()
{
    std::shared_ptr<Core::UI::ButtonMaterial> buttonMaterial = std::make_shared<Core::UI::ButtonMaterial>();
    buttonMaterial->Color = {0.49, 0.53, 0.99, 1.0f};
    buttonMaterial->Roundness = 0.25f;
    buttonMaterial->TextSize = 26;
    buttonMaterial->Scene = m_Scene;

    Core::UI::Text("Lorem Ipsum", {GetScreenWidth() / 2 - MeasureText("Loream Ipsum", 62) / 2, GetScreenHeight() / 2 - 100}, {0.0, 0.0, 0.0, 1.0}, 64, "black", m_Scene);
    Core::UI::Text("Digital School", {GetScreenWidth() / 2 - MeasureText("Digital School", 26) / 2, GetScreenHeight() / 2 }, {0.0, 0.0, 0.0, 1.0}, 26, "regular", m_Scene);
    
    Core::UI::Button("Continue", {GetScreenWidth() / 2 - 90, GetScreenHeight() / 2 + 50}, {180, 40}, buttonMaterial, LandingScreen::RegisterCallback);
}