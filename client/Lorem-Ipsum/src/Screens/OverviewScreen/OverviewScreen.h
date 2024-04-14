#pragma once
#include "../Screen.h"

class OverviewScreen : public Screen
{
public:
    OverviewScreen() { InitRenderElements(); }
    ~OverviewScreen() = default;

    void InitRenderElements() override;

private:
    void NavBar();
    void SideBar();
    void MainContent();
};