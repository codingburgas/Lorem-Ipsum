#include "LandingScreen.h"

#include "Scene/UI/Input/Input.h"
#include "Scene/UI/Text/Text.h"

void buttonCallback()
{
    std::cout << "Button" << std::endl;
}

void inputCallback(std::string input)
{
    // std::cout << input << std::endl;
}

void LandingScreen::RenderElements()
{
    Core::UI::Button("I am a button", {GetScreenWidth() / 2 - 100, GetScreenHeight() / 2 - 25}, {200, 50}, 0.2f, {0.2, 0.2, 0.8, 1.0}, {1.0f, 1.0f, 1.0f, 1.0f}, m_Scene, buttonCallback);
    // Core::UI::Input({0, 0}, {200, 50}, 0.2f, {0.7, 0.7, 0.7, 1.0}, {0.0f, 0.0f, 0.0f, 1.0f}, m_Scene, inputCallback);
    Core::UI::Text("This is the text component", {0, 0}, {0.2, 0.8, 0.3, 1.0}, m_Scene);
}