#pragma once
#include "../Screen.h"

class NewThemeScreen : public Screen
{
public:
    NewThemeScreen() { InitRenderElements(); }
    ~NewThemeScreen() = default;

    void InitRenderElements() override;

    void OnScreenChange() override;

private:
    static void HandleOverviewCallback(std::shared_ptr<Core::Entity> e);
    static void HandleSettingsCallback(std::shared_ptr<Core::Entity> e);
    static void HandleCreateThemeCallback(std::shared_ptr<Core::Entity> e);
    
    static void HanldeEdinThemeNameCallback(std::string input, std::shared_ptr<Core::Entity> e);
    static void HanldeEdinThemeDescriptionCallback(std::string input, std::shared_ptr<Core::Entity> e);

    inline static std::string m_ThemeName = "";
    inline static std::string m_ThemeDescription = "";
    
    void SideBar();
    void MainContent();
};
