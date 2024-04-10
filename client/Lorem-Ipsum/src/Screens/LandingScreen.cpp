#include "LandingScreen.h"

void buttonCallback()
{
    std::cout << "Button" << std::endl;
}

void LandingScreen::RenderElements()
{
    Core::UI::Button("I am a button", {GetScreenWidth() / 2 - 100, GetScreenHeight() / 2 - 25}, {200, 50}, 0.2f, {0.2, 0.2, 0.8, 1.0}, {1.0f, 1.0f, 1.0f, 1.0f}, m_Scene, buttonCallback);
}

void LandingScreen::RenderElementsOnResize()
{
    for (auto entity: m_Scene->GetEntities<Core::UIComponent>())
    {
        entity->Destroy();
    }

    RenderElements();
}
