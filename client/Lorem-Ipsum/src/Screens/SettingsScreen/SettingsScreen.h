#pragma once
#include "../Screen.h"

class SettingsScreen : public Screen
{
public:
    SettingsScreen() { InitRenderElements(); }
    ~SettingsScreen() = default;

    void InitRenderElements() override;
    
    void OnScreenChange() override;

private:
    
    static void HandleOverview(std::shared_ptr<Core::Entity> e);
    
    void SettingsPanel();
    void SideBar();
    void PersonalInformationPanel();

    std::string m_FirstName = " ";
    std::string m_LastName = " ";
    std::string m_Email = " ";
};