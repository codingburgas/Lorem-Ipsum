#pragma once
#include "../Screen.h"

class OverviewScreen : public Screen
{
public:
    OverviewScreen() { InitRenderElements(); }
    ~OverviewScreen() = default;

    void InitRenderElements() override;

private:
    static void HandleSettings();
    static void HandleOrganizatoinsCallback();
    
    void NavBar();
    void SideBar();
    void MainContent();
};