#include "ThemesScreen.h"
#include "../Screens.h"
#include <cpr/cpr.h>

#define RAPIDJSON_HAS_STDSTRING 1
#include <rapidjson/document.h>
#include <rapidjson/writer.h>
#include <rapidjson/prettywriter.h>

void ThemesScreen::InitRenderElements()
{
    SideBar();
    MainContent();
}

void ThemesScreen::OnScreenChange()
{
    cpr::Response r = cpr::Get(
        cpr::Url{m_BaseUrl + "/course/" + std::to_string(m_SelectedCourse)},
        cpr::Header{{"Authorization", m_Token}}
    );

    if(r.status_code != 200)
        return;

    rapidjson::Document d;
    d.Parse(r.text.c_str());

    m_CourseName = d["name"].GetString();

    cpr::Response themesResponse = cpr::Get(
        cpr::Url{m_BaseUrl + "/themes/" + std::to_string(m_SelectedCourse)},
        cpr::Header{{"Authorization", m_Token}}
    );
    
    if(themesResponse.status_code != 200)
        return;        

    rapidjson::Document themesDocument;
    themesDocument.Parse(themesResponse.text);

    m_Themes.clear();
    for (const auto& v : themesDocument.GetArray()) {
        Theme theme;
        theme.Description = v["info"].GetString();
        theme.id = v["id"].GetInt();
        theme.Name = v["name"].GetString();
        
        m_Themes.push_back(theme);
    }

    InitRenderElementsOnResize();
}

void ThemesScreen::HandleOverviewCallback(std::shared_ptr<Core::Entity> e)
{
    m_SwitchScreens(m_Screens->OverviewScreen);
}

void ThemesScreen::HandleSettingsCallback(std::shared_ptr<Core::Entity> e)
{
    m_SwitchScreens(m_Screens->SettingsScreen);
}

void ThemesScreen::HandleCreateThemeCallback(std::shared_ptr<Core::Entity> e)
{
    m_SwitchScreens(m_Screens->NewThemeScreen);
}

void ThemesScreen::HanldeEdinThemeCallback(std::string input, std::shared_ptr<Core::Entity> e)
{
    
}

void ThemesScreen::HandleSelectThemeCallback(std::shared_ptr<Core::Entity> e)
{
    for(auto i: m_Themes)
    {
        if(i.Name == e->GetComponent<Core::UIComponent>().Text)
        {
            m_SelectedTheme = i;
            break;
        }
    }

    m_SwitchScreens(m_Screens->ThemesScreen);
}

void callbackTCallaback(std::shared_ptr<Core::Entity> e) {}

void ThemesScreen::SideBar()
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
     Core::UI::Button("Statistics", {35, 204}, {180, 45}, p_UnselectedButtonMaterial, callbackTCallaback, "assets/icons/stats-icon.png");
     
     Core::UI::Text("Account", {40, 271}, {0.42, 0.42, 0.44, 1.0}, 20, "regualar", m_Scene);
     
     Core::UI::Button("Messages", {35, 316}, {180, 45}, p_UnselectedButtonMaterial, callbackTCallaback, "assets/icons/chat-icon.png");
     Core::UI::Button("Settings", {35, 363}, {180, 45}, p_UnselectedButtonMaterial, HandleSettingsCallback, "assets/icons/settings-icon.png");
}

void ThemesScreen::MainContent()
{
    Core::UI::Text(m_CourseName, {300, 140}, {0.0, 0.0, 0.0, 1.0}, 38, "bold", m_Scene);

    Core::UI::TextedBox(m_SelectedTheme.Description, {300, 200}, {500, GetScreenHeight()}, 0.0f, {1.0f, 1.0f, 1.0f, 1.0f}, {0.0f, 0.0f, 0.0f, 1.0f}, 20, "regular", m_Scene);
    
   Core::UI::Text("Course Content", {GetScreenWidth() - 200 - MeasureText("Course Content", 32), 140}, {0.0, 0.0, 0.0, 1.0}, 32, "regular", m_Scene);

    if(m_OrgRole == "owner" || m_OrgRole == "teacher")
    {
        std::shared_ptr<Core::UI::ButtonMaterial> p_ButtonMaterial = std::make_shared<Core::UI::ButtonMaterial>();
        p_ButtonMaterial->Roundness = 0.25f;
        p_ButtonMaterial->Color = {0.49f, 0.53f, 0.98f, 1.0f};
        p_ButtonMaterial->TextColor = {1.0f, 1.0f, 1.0f, 1.0f};
        p_ButtonMaterial->TextSize = 18;
        p_ButtonMaterial->Scene = m_Scene;

        for(std::size_t i = 0; i < m_Themes.size(); i++)
        {
            if(m_SelectedTheme.id == m_Themes[i].id)
            {
                p_ButtonMaterial->TextColor = {1.0f, 1.0f, 1.0f, 1.0f};
                p_ButtonMaterial->Color = {0.49f, 0.53f, 0.98f, 1.0f};
            }
            else
            {
                p_ButtonMaterial->Color = {1.0f, 1.0f, 1.0f, 1.0f};
                p_ButtonMaterial->TextColor = {0.0f, 0.0f, 0.0f, 1.0f};
            }
            
            Core::UI::Button(m_Themes[i].Name.c_str(), {GetScreenWidth() - 400, 200 + i * 60}, {300, 50}, p_ButtonMaterial, HandleSelectThemeCallback);
        }
        
        if(m_OrgRole == "owner" || m_OrgRole == "teacher")
        {
            p_ButtonMaterial->Color = {0.49f, 0.53f, 0.98f, 1.0f};
            p_ButtonMaterial->TextColor = {1.0f, 1.0f, 1.0f, 1.0f};
            Core::UI::Button("Create Theme", {GetScreenWidth() - 340, 210 + m_Themes.size() * 60}, {180, 30}, p_ButtonMaterial, HandleCreateThemeCallback);
        }
    }

   Core::UI::Text("Exams", {GetScreenWidth() - 200 - MeasureText("Course Content", 32), 280 + m_Themes.size() * 60}, {0.0, 0.0, 0.0, 1.0}, 32, "regular", m_Scene);
}
