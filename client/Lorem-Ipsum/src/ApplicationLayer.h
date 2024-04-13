#pragma once
#include "Core.h"

#include "Screens/LandingScreen/LandingScreen.h"
#include "Screens/LoginScreen/LoginScreen.h"
#include "Screens/RegisterScreen/RegisterScreen.h"

#include <raylib.h>

class ApplicationLayer : public Core::Layer
{
public:
    void OnAttach() override;
    void OnUpdate() override;
    void OnUIRender() override;

private:
    static void SwitchScenes(std::shared_ptr<Screen> screen);
    void InitScreens();

    struct Fonts
    {
        std::shared_ptr<Font> Regular;
        std::shared_ptr<Font> Bold;
        std::shared_ptr<Font> Black;
        std::shared_ptr<Font> Thin;

        std::shared_ptr<Font> StringToFont(std::string font)
        {
            if (font == "bold") { return Bold; }
            else if (font == "black") { return Black; }
            else if (font == "thin") { return Thin; }

            return Regular;
        }
    };
    
private:
    inline static std::shared_ptr<Core::Scene> m_BoundScene;

    std::shared_ptr<LandingScreen> m_LandingScreen;
    std::shared_ptr<RegisterScreen> m_RegisterScreen;
    std::shared_ptr<LoginScreen> m_LoginScreen;

    std::shared_ptr<Fonts> m_MierFonts;
};
