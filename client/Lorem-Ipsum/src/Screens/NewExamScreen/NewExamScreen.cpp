#include "NewExamScreen.h"
#include "../Screens.h"

#include <cpr/cpr.h>
#define RAPIDJSON_HAS_STDSTRING 1
#include <rapidjson/document.h>
#include <rapidjson/writer.h>
#include <rapidjson/prettywriter.h>

void NewExamScreen::InitRenderElements()
{
    SideBar();
    MainContent();
}

void NewExamScreen::OnScreenChange()
{
    
}

void NewExamScreen::HandleOverviewCallback(std::shared_ptr<Core::Entity> e)
{
    m_SwitchScreens(m_Screens->OverviewScreen);
}

void NewExamScreen::HandleSettingsCallback(std::shared_ptr<Core::Entity> e)
{
    m_SwitchScreens(m_Screens->SettingsScreen);
}

void callbakNexam(std::shared_ptr<Core::Entity> e) {}

void NewExamScreen::HandleCreateExamCallback(std::shared_ptr<Core::Entity> e)
{
    if(m_ExamName.empty())
        return;

    rapidjson::Document d;
    d.SetObject();
    d.AddMember( "title", m_ExamName, d.GetAllocator());
    d.AddMember( "theme_id", m_SelectedThemeId, d.GetAllocator());

    rapidjson::StringBuffer buffer;
    rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
    d.Accept(writer);

    cpr::Response r = cpr::Post(
        cpr::Url{m_BaseUrl + "/test/create"},
        cpr::Header{{"Authorization", m_Token}},
        cpr::Body{buffer.GetString()}
    );

    if(r.status_code != 200)
    {
        return;
    }

    m_SwitchScreens(m_Screens->ThemesScreen);
}

void NewExamScreen::HandleEnterExamNameCallback(std::string input, std::shared_ptr<Core::Entity>  e)
{
   m_ExamName = input; 
}

void NewExamScreen::SideBar()
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
    Core::UI::Button("Statistics", {35, 204}, {180, 45}, p_UnselectedButtonMaterial, callbakNexam, "assets/icons/stats-icon.png");

    Core::UI::Text("Account", {40, 271}, {0.42, 0.42, 0.44, 1.0}, 20, "regualar", m_Scene);

    Core::UI::Button("Messages", {35, 316}, {180, 45}, p_UnselectedButtonMaterial, callbakNexam, "assets/icons/chat-icon.png");
    Core::UI::Button("Settings", {35, 363}, {180, 45}, p_UnselectedButtonMaterial, HandleSettingsCallback, "assets/icons/settings-icon.png");
}

void NewExamScreen::MainContent()
{
    std::shared_ptr<Core::UI::ButtonMaterial> p_ButtonMaterial = std::make_shared<Core::UI::ButtonMaterial>();
    p_ButtonMaterial->Roundness = 0.25f;
    p_ButtonMaterial->Color = {0.49f, 0.53f, 0.98f, 1.0f};
    p_ButtonMaterial->TextColor = {1.0f, 1.0f, 1.0f, 1.0f};
    p_ButtonMaterial->TextSize = 18;
    p_ButtonMaterial->Scene = m_Scene;
    
    Core::UI::Text("Add new exam to the course", {300, 100}, {0.0, 0.0, 0.0, 1.0}, 24, "regular", m_Scene);

    Core::UI::Input({300, 180}, {400, 40}, 0.25, {0.84, 0.84, 0.84, 1.0f}, {0.0, 0.0, 0.0, 1.0f}, 28, "regular", m_Scene, HandleEnterExamNameCallback);
    
    Core::UI::Button("Create Exam", {300 + (GetScreenWidth() - 400) / 2 - 180 / 2, 260}, {180, 30}, p_ButtonMaterial, HandleCreateExamCallback);
}