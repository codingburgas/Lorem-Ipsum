#include "CreateCourseScreen.h"
#include "../Screens.h"
#include <cpr/cpr.h>

#define RAPIDJSON_HAS_STDSTRING 1
#include <rapidjson/document.h>
#include <rapidjson/writer.h>
#include <rapidjson/prettywriter.h>

void CreateCourseScreen::InitRenderElements()
{
    SideBar();
    MainContent();
}

void CreateCourseScreen::OnScreenChange()
{
    
}

void CreateCourseScreen::HandleOverviewCallback(std::shared_ptr<Core::Entity> e)
{
    m_SwitchScreens(m_Screens->OverviewScreen);
}

void CreateCourseScreen::HandleSettingsCallback(std::shared_ptr<Core::Entity> e)
{
    m_SwitchScreens(m_Screens->SettingsScreen);
}

void CreateCourseScreen::HandleCreateCourseCallback(std::shared_ptr<Core::Entity> e)
{
    rapidjson::Document d;
    d.SetObject();
    d.AddMember( "name", m_CourseName, d.GetAllocator());
    d.AddMember("subject", m_CourseName, d.GetAllocator());
    d.AddMember("org_id", m_SelectedOrganization, d.GetAllocator());

    rapidjson::StringBuffer buffer;
    rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
    d.Accept(writer);

    cpr::Response r = cpr::Post(
        cpr::Url{m_BaseUrl + "/course/create"},
        cpr::Header{{"Authorization", m_Token}},
        cpr::Body{buffer.GetString()}
    );

    if(r.status_code != 200)
    {
        return;
    }

    m_SwitchScreens(m_Screens->CoursesScreen);
}

void CreateCourseScreen::HandleEnterCourseNameCallback(std::string name, std::shared_ptr<Core::Entity> e)
{
    m_CourseName = name;
}

void CreateCourseScreen::MainContent()
{
    Core::UI::Text("Create Courses", {315, 140}, {0.0, 0.0, 0.0, 1.0}, 38, "bold", m_Scene);
    
    Core::UI::Text("Welcome to Lorem Ipsum courses!", {GetScreenWidth() / 2 - MeasureText("Welcome to Lorem Ipsum courses!", 22) / 2 + 180 / 2, 245}, {0.4, 0.4, 0.4, 1.0}, 22, "bold", m_Scene);
    Core::UI::Text("Create your course and share the token given after completing this step with your working team.", {GetScreenWidth() / 2 - MeasureText("Create your course and share the token given after completing this step with your working team.", 22) / 2 + 350 / 2, 320}, {0.4, 0.4, 0.4, 1.0}, 22, "regular", m_Scene);
    Core::UI::Text("Enter name for your course", {GetScreenWidth() / 2 - MeasureText("Enter name for your course", 22) / 2 + 180 / 2, 400}, {0.4, 0.4, 0.4, 1.0}, 22, "regular", m_Scene);

    std::shared_ptr<Core::UI::InputMaterial> p_InputMaterial = std::make_shared<Core::UI::InputMaterial>();
    p_InputMaterial->Color = {0.91f, 0.91f, 0.91f, 1.0f};
    p_InputMaterial->TextColor = {0.0f, 0.0f, 0.0f, 1.0f};
    p_InputMaterial->TextSize = 20;
    p_InputMaterial->Roundness = 0.25f;
    p_InputMaterial->Scene = m_Scene;

    Core::UI::Input({GetScreenWidth() / 2 - 200 + 180 / 2, 450}, {400, 40}, p_InputMaterial, HandleEnterCourseNameCallback);

    std::shared_ptr<Core::UI::ButtonMaterial> p_ConfirmButton = std::make_shared<Core::UI::ButtonMaterial>();
    p_ConfirmButton->Color = {0.34f, 0.52f, 0.92f, 1.0f};
    p_ConfirmButton->Roundness = 0.25f;
    p_ConfirmButton->TextSize = 20;
    p_ConfirmButton->Scene = m_Scene;

    Core::UI::Button("Confirm", {GetScreenWidth() / 2 - 100 + 180 / 2, 520}, {200, 40}, p_ConfirmButton, HandleCreateCourseCallback); 
}

void callbackCcourse(std::shared_ptr<Core::Entity> e) {}

void CreateCourseScreen::SideBar()
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
    Core::UI::Button("Statistics", {35, 204}, {180, 45}, p_UnselectedButtonMaterial, callbackCcourse, "assets/icons/stats-icon.png");

    Core::UI::Text("Account", {40, 271}, {0.42, 0.42, 0.44, 1.0}, 20, "regualar", m_Scene);

    Core::UI::Button("Messages", {35, 316}, {180, 45}, p_UnselectedButtonMaterial, callbackCcourse, "assets/icons/chat-icon.png");
    Core::UI::Button("Settings", {35, 363}, {180, 45}, p_UnselectedButtonMaterial, HandleSettingsCallback, "assets/icons/settings-icon.png");   
}



