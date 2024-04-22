#include "NewThemeScreen.h"
#include "../Screens.h"
#include "cpr/cpr.h"

#define RAPIDJSON_HAS_STDSTRING 1
#include <rapidjson/document.h>
#include <rapidjson/writer.h>
#include <rapidjson/prettywriter.h>

void NewThemeScreen::HandleOverviewCallback(std::shared_ptr<Core::Entity> e)
{
    m_SwitchScreens(m_Screens->OverviewScreen);
}

void NewThemeScreen::HandleSettingsCallback(std::shared_ptr<Core::Entity> e)
{
    m_SwitchScreens(m_Screens->SettingsScreen);
}

void NewThemeScreen::HandleCreateThemeCallback(std::shared_ptr<Core::Entity> e)
{
    rapidjson::Document d;
    d.SetObject();
    d.AddMember( "title", m_ThemeName, d.GetAllocator());
    d.AddMember( "info", m_ThemeDescription, d.GetAllocator());
    d.AddMember( "course_id", m_SelectedCourse, d.GetAllocator());

    rapidjson::StringBuffer buffer;
    rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
    d.Accept(writer);

    cpr::Response r = cpr::Post(
        cpr::Url{m_BaseUrl + "/theme/create"},
        cpr::Header{{"Authorization", m_Token}},
        cpr::Body{buffer.GetString()}
    );

    if(r.status_code != 200)
    {
        return;
    }

    m_SwitchScreens(m_Screens->ThemesScreen);
}

void NewThemeScreen::OnScreenChange()
{
    
}

void NewThemeScreen::HanldeEdinThemeNameCallback(std::string input, std::shared_ptr<Core::Entity> e)
{
    m_ThemeName = input;
}

void NewThemeScreen::HanldeEdinThemeDescriptionCallback(std::string input, std::shared_ptr<Core::Entity> e)
{
    m_ThemeDescription = input;
}


void NewThemeScreen::InitRenderElements()
{
    SideBar();
    MainContent();
}

void callbackNT(std::shared_ptr<Core::Entity> e) {}

void NewThemeScreen::SideBar()
{
    std::shared_ptr<Core::UI::ButtonMaterial> p_SettingsButtonMaterial = std::make_shared<Core::UI::ButtonMaterial>();
    p_SettingsButtonMaterial->Color = {0.0f, 0.46f, 0.98f, 1.0f};
    p_SettingsButtonMaterial->Roundness = 0.25f;
    p_SettingsButtonMaterial->TextSize = 22;
    p_SettingsButtonMaterial->Scene = m_Scene;

    std::shared_ptr<Core::UI::ButtonMaterial> p_UnselectedButtonMaterial = std::make_shared<Core::UI::ButtonMaterial>();
    p_UnselectedButtonMaterial->Color = {1.0f, 1.0f, 1.0f, 1.0f};
    p_UnselectedButtonMaterial->Roundness = 0.25f;
    p_UnselectedButtonMaterial->TextColor = {0.7f, 0.7f, 0.7f, 1.0f};
    p_UnselectedButtonMaterial->TextSize = 22;
    p_UnselectedButtonMaterial->Scene = m_Scene;

    Core::UI::Text("Menu", {40, 120}, {0.42, 0.42, 0.44, 1.0}, 20, "regualar", m_Scene);

    Core::UI::Button("Overview", {35, 157}, {180, 45}, p_SettingsButtonMaterial, HandleOverviewCallback, "assets/icons/home-icon.png");
    Core::UI::Button("Statistics", {35, 204}, {180, 45}, p_UnselectedButtonMaterial, callbackNT, "assets/icons/stats-icon.png");

    Core::UI::Text("Account", {40, 271}, {0.42, 0.42, 0.44, 1.0}, 20, "regualar", m_Scene);

    Core::UI::Button("Messages", {35, 316}, {180, 45}, p_UnselectedButtonMaterial, callbackNT, "assets/icons/chat-icon.png");
    Core::UI::Button("Settings", {35, 363}, {180, 45}, p_UnselectedButtonMaterial, HandleSettingsCallback, "assets/icons/settings-icon.png");   
}

void NewThemeScreen::MainContent()
{
    std::shared_ptr<Core::UI::ButtonMaterial> p_ButtonMaterial = std::make_shared<Core::UI::ButtonMaterial>();
    p_ButtonMaterial->Roundness = 0.25f;
    p_ButtonMaterial->Color = {0.49f, 0.53f, 0.98f, 1.0f};
    p_ButtonMaterial->TextColor = {1.0f, 1.0f, 1.0f, 1.0f};
    p_ButtonMaterial->TextSize = 18;
    p_ButtonMaterial->Scene = m_Scene;
    
    Core::UI::Text("Add new theme to the course", {300, 100}, {0.0, 0.0, 0.0, 1.0}, 24, "regular", m_Scene);
    
    Core::UI::Text("Theme Name", {300, 140}, {0.0, 0.0, 0.0, 1.0}, 24, "regular", m_Scene);
    Core::UI::Input({300, 180}, {400, 40}, 0.25, {0.84, 0.84, 0.84, 1.0f}, {0.0, 0.0, 0.0, 1.0f}, 28, "regular", m_Scene, HanldeEdinThemeNameCallback);
    
    Core::UI::Text("Enter Theme Content", {300, 242}, {0.0, 0.0, 0.0, 1.0}, 24, "regular", m_Scene);
    Core::UI::TextedBoxInput({300, 300}, {GetScreenWidth() - 400, GetScreenHeight() - 400}, 0.0, {0.84, 0.84, 0.84, 1.0f}, {0.0, 0.0, 0.0, 1.0f}, 22, "regular", HanldeEdinThemeDescriptionCallback, m_Scene);

    Core::UI::Button("Create Theme", {300 + (GetScreenWidth() - 400) / 2 - 180 / 2, GetScreenHeight() - 50}, {180, 30}, p_ButtonMaterial, HandleCreateThemeCallback);
}
