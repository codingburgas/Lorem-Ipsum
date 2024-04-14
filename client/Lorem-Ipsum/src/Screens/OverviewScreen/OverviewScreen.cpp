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
    std::shared_ptr<Core::UI::ButtonMaterial> p_OverviewButtonMaterial = std::make_shared<Core::UI::ButtonMaterial>();
    p_OverviewButtonMaterial->Color = {0.0f, 0.46f, 0.98f, 1.0f};
    p_OverviewButtonMaterial->Roundness = 0.25f;
    p_OverviewButtonMaterial->TextSize = 22;
    p_OverviewButtonMaterial->Scene = m_Scene;

    std::shared_ptr<Core::UI::ButtonMaterial> p_UnselectedButtonMaterial = std::make_shared<Core::UI::ButtonMaterial>();
    p_UnselectedButtonMaterial->Color = {1.0f, 1.0f, 1.0f, 1.0f};
    p_UnselectedButtonMaterial->Roundness = 0.25f;
    p_UnselectedButtonMaterial->TextColor = {0.7f, 0.7f, 0.7f, 1.0f};
    p_UnselectedButtonMaterial->TextSize = 22;
    p_UnselectedButtonMaterial->Scene = m_Scene;
    
    Core::UI::Text("Menu", {40, 120}, {0.42, 0.42, 0.44, 1.0}, 20, "regualar", m_Scene);

    Core::UI::Button("Overview", {35, 157}, {180, 45}, p_OverviewButtonMaterial, overviewCallback, "assets/icons/home-icon.png");
    Core::UI::Button("Courses", {35, 204}, {180, 45}, p_UnselectedButtonMaterial, overviewCallback, "assets/icons/book-icon.png");
    Core::UI::Button("Planning", {35, 251}, {180, 45}, p_UnselectedButtonMaterial, overviewCallback, "assets/icons/chart-icon.png");
    Core::UI::Button("Statistics", {35, 296}, {180, 45}, p_UnselectedButtonMaterial, overviewCallback, "assets/icons/stats-icon.png");
    
    Core::UI::Text("Account", {40, 371}, {0.42, 0.42, 0.44, 1.0}, 20, "regualar", m_Scene);
    
    Core::UI::Button("Messages", {35, 436}, {180, 45}, p_UnselectedButtonMaterial, overviewCallback, "assets/icons/chat-icon.png");
    Core::UI::Button("Settings", {35, 483}, {180, 45}, p_UnselectedButtonMaterial, overviewCallback, "assets/icons/settings-icon.png");
}

void OverviewScreen::MainContent()
{
    Core::UI::Text(TextFormat("Welcom back to Lorem Ipsum, %s!", "Ivan"), {310, 125}, {0.0, 0.0, 0.0, 1.0}, 32, "regualar", m_Scene);
    Core::UI::Text("Join", {310, 230}, {0.0, 0.0, 0.0, 1.0}, 32, "regualar", m_Scene);
}
