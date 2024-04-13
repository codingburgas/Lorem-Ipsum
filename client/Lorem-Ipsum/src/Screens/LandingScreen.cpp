#include "LandingScreen.h"

#include "Scene/UI/Input/Input.h"
#include "Scene/UI/Text/Text.h"

void buttonCallback()
{
    std::cout << "Button" << std::endl;
}

void inputCallback(std::string input)
{
    std::cout << input << std::endl;
}

void LandingScreen::RenderElements()
{
    Core::UI::Button("I am a buttodan", {GetScreenWidth() / 2 - 100, GetScreenHeight() / 2 - 25}, {200, 50}, 0.2f, {0.2, 0.2, 0.8, 1.0}, {1.0f, 1.0f, 1.0f, 1.0f}, 24, m_Scene, buttonCallback);
    Core::UI::Input({500, 28}, {200, 50}, 0.2f, {0.7, 0.7, 0.7, 1.0}, {0.0f, 0.0f, 0.0f, 1.0f}, 24, m_Scene, inputCallback);
    Core::UI::Input({5, 50 + 28 + 4}, {200, 50}, 0.2f, {0.7, 0.7, 0.7, 1.0}, {0.0f, 0.0f, 0.0f, 1.0f}, 24, m_Scene, inputCallback);
    Core::UI::Text("This is the text component", {5, 0}, {0.2, 0.8, 0.3, 1.0}, 24, m_Scene);
}