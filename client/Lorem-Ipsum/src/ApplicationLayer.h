#pragma once
#include "Core.h"

#include <raylib.h>

#include "Screens/LandingScreen.h"

class ApplicationLayer : public Core::Layer
{
public:
    void OnAttach() override;
    void OnUpdate() override;
    void OnUIRender() override;

private:
    std::shared_ptr<Core::Scene> m_BoundScene;

    std::shared_ptr<LandingScreen> m_LandingScreen;
};