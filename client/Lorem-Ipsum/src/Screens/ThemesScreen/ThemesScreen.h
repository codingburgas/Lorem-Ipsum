#pragma once
#include "../Screen.h"

class ThemesScreen : public Screen
{
public:
    ThemesScreen() { InitRenderElements(); }
    ~ThemesScreen() = default;

    void InitRenderElements() override;

    void OnScreenChange() override;

private:
    static void HandleOverviewCallback(std::shared_ptr<Core::Entity> e);
    static void HandleSettingsCallback(std::shared_ptr<Core::Entity> e);
    static void HandleCreateThemeCallback(std::shared_ptr<Core::Entity> e);
    static void HandleSelectThemeCallback(std::shared_ptr<Core::Entity> e);
    
    static void HanldeEdinThemeCallback(std::string input, std::shared_ptr<Core::Entity> e);

    std::string m_CourseName = "";

    struct Theme
    {
        std::string Name = " ";
        std::string Description = " ";
        int id = 0;
    };

    inline static std::vector<Theme> m_Themes;
    inline static Theme m_SelectedTheme;
    
    void SideBar();
    void MainContent();
};