#include "OverviewScreen.h"

void overviewCallback() {}

void OverviewScreen::InitRenderElements()
{
    NavBar();
    SideBar();
    MainContent();
}

void OverviewScreen::NavBar()
{
    Core::UI::Text("Lorem Ipsum", {35, 25}, {0.0, 0.0, 0.0, 1.0}, 32, "regular", m_Scene);

    Core::UI::Avatar({GetScreenWidth() - 68, 20}, "assets/test-avatar.png", m_Scene);
}

void OverviewScreen::SideBar()
{
    Core::UI::Text("Menu", {40, 120}, {0.42, 0.42, 0.44, 1.0}, 20, "regualar", m_Scene);

    Core::UI::Button("Overview", {35, 157}, {180, 45}, 0.25, {0.0f, 0.46f, 0.98f, 1.0f}, {1.0f, 1.0f, 1.0f, 1.0f}, 22, "regular", "assets/icons/home-icon.png", m_Scene, overviewCallback);
    Core::UI::Button("Courses", {35, 204}, {180, 45}, 0.25, {1.0f, 1.0f, 1.0f, 1.0f}, {0.7f, 0.7f, 0.7f, 1.0f}, 22, "regular", "assets/icons/book-icon.png", m_Scene, overviewCallback);
    Core::UI::Button("Planning", {35, 251}, {180, 45}, 0.25, {1.0f, 1.0f, 1.0f, 1.0f}, {0.7f, 0.7f, 0.7f, 1.0f}, 22, "regular", "assets/icons/chart-icon.png", m_Scene, overviewCallback);
    Core::UI::Button("Statistics", {35, 296}, {180, 45}, 0.25, {1.0f, 1.0f, 1.0f, 1.0f}, {0.7f, 0.7f, 0.7f, 1.0f}, 22, "regular", "assets/icons/stats-icon.png", m_Scene, overviewCallback);
    
    Core::UI::Text("Account", {40, 371}, {0.42, 0.42, 0.44, 1.0}, 20, "regualar", m_Scene);
    
    Core::UI::Button("Messages", {35, 436}, {180, 45}, 0.25, {1.0f, 1.0f, 1.0f, 1.0f}, {0.7f, 0.7f, 0.7f, 1.0f}, 22, "regular", "assets/icons/chat-icon.png", m_Scene, overviewCallback);
    Core::UI::Button("Settings", {35, 483}, {180, 45}, 0.25, {1.0f, 1.0f, 1.0f, 1.0f}, {0.7f, 0.7f, 0.7f, 1.0f}, 22, "regular", "assets/icons/settings-icon.png", m_Scene, overviewCallback);
}

void OverviewScreen::MainContent()
{
    Core::UI::Text(TextFormat("Welcom back to Lorem Ipsum, %s!", "Ivan"), {310, 125}, {0.0, 0.0, 0.0, 1.0}, 32, "regualar", m_Scene);
    Core::UI::Text("Join", {310, 230}, {0.0, 0.0, 0.0, 1.0}, 32, "regualar", m_Scene);
}
