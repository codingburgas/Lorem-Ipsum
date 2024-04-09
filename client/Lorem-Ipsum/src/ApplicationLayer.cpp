#include "ApplicationLayer.h"

void ApplicationLayer::OnAttach()
{
    m_LandingScreen = std::make_shared<LandingScreen>();
    
    m_BoundScene = m_LandingScreen->GetScene();
}

void ApplicationLayer::OnUpdate()
{
    ClearBackground(GetColor(0x312b47ff));

    DrawText("Hillo", 0, 0, 20, WHITE);
}
