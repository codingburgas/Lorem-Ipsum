#pragma once
#include "Core.h"

#include "Screens/LandingScreen/LandingScreen.h"
#include "Screens/RegisterScreen/RegisterScreen.h"

class ApplicationLayer : public Core::Layer
{
public:
    void OnAttach() override;
    void OnUpdate() override;
    void OnUIRender() override;

private:
    static void SwitchScenes(std::shared_ptr<Screen> screen);
    void InitScreens();
    
private:
    inline static std::shared_ptr<Core::Scene> m_BoundScene;

    std::shared_ptr<LandingScreen> m_LandingScreen;
    std::shared_ptr<RegisterScreen> m_RegisterScreen;
};
