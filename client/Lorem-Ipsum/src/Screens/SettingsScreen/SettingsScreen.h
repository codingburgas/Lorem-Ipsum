#pragma once
#include "../Screen.h"

class SettingsScreen : public Screen
{
public:
    SettingsScreen() { InitRenderElements(); }
    ~SettingsScreen() = default;

    void InitRenderElements() override;

private:
    static void HandleOverview();
    
    void SettingsPanel();
    void SideBar();
    void PersonalInformationPanel();
};