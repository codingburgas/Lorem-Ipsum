#pragma once
#include "Core.h"

#include "Screens/Screens.h"

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
    std::shared_ptr<Screens> m_Screens;

    std::shared_ptr<Fonts> m_MierFonts;

    std::shared_ptr<Camera2D> m_Camera;
};
