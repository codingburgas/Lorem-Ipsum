#pragma once
#include "../Screen.h"

class OrganizationScreen : public Screen
{
public:
    OrganizationScreen() { InitRenderElements(); }
    ~OrganizationScreen() = default;

    void InitRenderElements() override;

private:
    static void HandleOverviewCallback();
    static void HandleSettingsCallback();
    static void HandleOrganizationName(std::string orgName);
    static void HandleCreateaOrganizationCallback();
    static void HandleJoinOrganizationCallback();
    
    void SideBar();
    void MainContent();
};