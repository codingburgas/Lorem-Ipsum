#include "CoursesScreen.h"
#include "../Screens.h"
#include <cpr/cpr.h>
#define RAPIDJSON_HAS_STDSTRING 1
#include <rapidjson/document.h>
#include <rapidjson/writer.h>
#include <rapidjson/prettywriter.h>

void CoursesScreen::InitRenderElements()
{
    SideBar();
    MainContent();
}

void CoursesScreen::OnScreenChange()
{
    cpr::Response r = cpr::Get(
        cpr::Url{m_BaseUrl + "/organizations/" + std::to_string(m_SelectedOrganization)},
        cpr::Header{{"Authorization", m_Token}}
        );

    if(r.status_code != 200)
        return;
    
    rapidjson::Document organizationDocument;
    organizationDocument.Parse(r.text);

    m_OrgRole = organizationDocument["role"].GetString();
    m_Code = organizationDocument["code"].GetString();

    cpr::Response coursesResponse = cpr::Get(
        cpr::Url{m_BaseUrl + "/course"},
        cpr::Header{{"Authorization", m_Token}}
        );

    if(coursesResponse.status_code != 200)
        return;

    rapidjson::Document coursesDocument;
    coursesDocument.Parse(coursesResponse.text);

    m_Courses.clear();
    for (const auto& v : coursesDocument.GetArray()) {
        Course course;
        course.subject = v["subject"].GetString();
        course.id = v["id"].GetInt();
        course.name = v["name"].GetString();
        
        m_Courses.push_back(course);
    }

    InitRenderElementsOnResize();
}

void callback(std::shared_ptr<Core::Entity> e) {}

void CoursesScreen::HandleOverviewCallback(std::shared_ptr<Core::Entity> e)
{
    m_SwitchScreens(m_Screens->OverviewScreen);
}

void CoursesScreen::HandleSettingsCallback(std::shared_ptr<Core::Entity> e)
{
    m_SwitchScreens(m_Screens->SettingsScreen);
}

void CoursesScreen::HandleCreateCourseCallback(std::shared_ptr<Core::Entity> e)
{
    m_SwitchScreens(m_Screens->CreateCourseScreen);
}

void CoursesScreen::HandleJoinCourseCallback(std::shared_ptr<Core::Entity> e)
{
    m_SwitchScreens(m_Screens->JoinCourseScreen);    
}

void CoursesScreen::MainContent()
{
    Core::UI::Text("Courses", {315, 140}, {0.0, 0.0, 0.0, 1.0}, 38, "bold", m_Scene);
    
    std::shared_ptr<Core::UI::ButtonMaterial> p_ButtonMaterial = std::make_shared<Core::UI::ButtonMaterial>();
    p_ButtonMaterial->Roundness = 0.25f;
    p_ButtonMaterial->Color = {0.49f, 0.53f, 0.98f, 1.0f};
    p_ButtonMaterial->TextColor = {1.0f, 1.0f, 1.0f, 1.0f};
    p_ButtonMaterial->TextSize = 18;
    p_ButtonMaterial->Scene = m_Scene;

    Core::UI::Button("Join Course", {GetScreenWidth() - 200, 20}, {180, 30}, p_ButtonMaterial, HandleJoinCourseCallback);
    
    p_ButtonMaterial->Color = {0.0f, 0.46f, 0.98f, 1.0f};

    if(m_OrgRole == "owner" || m_OrgRole == "teacher")
    {
        Core::UI::Button("Create Course", {GetScreenWidth() - 410, 20}, {180, 30}, p_ButtonMaterial, HandleCreateCourseCallback);
        Core::UI::Text(TextFormat("Code: %s", m_Code.c_str()), {GetScreenWidth() - 480 - MeasureText(TextFormat("Code: ", m_Code.c_str()), 20), 30}, {0.0, 0.0, 0.0, 1.0}, 20, "bold", m_Scene);
    }

    std::shared_ptr<Core::UI::ButtonMaterial> p_CourseButtonMaterail = std::make_shared<Core::UI::ButtonMaterial>();
    p_CourseButtonMaterail->Roundness = 0.25f;
    p_CourseButtonMaterail->TextColor = {0.49f, 0.53f, 0.98f, 1.0f};
    p_CourseButtonMaterail->Color = {1.0f, 1.0f, 1.0f, 1.0f};
    p_CourseButtonMaterail->TextSize = 32;
    p_CourseButtonMaterail->FontType = "bold";
    p_CourseButtonMaterail->Scene = m_Scene;
    
    for(std::size_t i = 0; i < m_Courses.size(); i++)
    {
        Core::UI::Button(m_Courses[i].name.c_str(), {315, 250 + i * 150}, {230, 140}, p_CourseButtonMaterail, callback);
        Core::UI::Text(TextFormat("Welcome back to your courses, %s", m_User->Name.c_str()), {585, 280 + i * 150}, {0.0, 0.0, 0.0, 1.0}, 18, "bold", m_Scene);
        Core::UI::Text(TextFormat("Continue working on your %s course.", m_Courses[i].subject.c_str()), {585, 320 + i * 150}, {0.0, 0.0, 0.0, 1.0}, 18, "regular", m_Scene);
        Core::UI::Text("Click on the button to see course contents", {585, 340 + i * 150}, {0.0, 0.0, 0.0, 1.0}, 18, "regular", m_Scene);
    }
}

void CoursesScreen::SideBar()
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
     Core::UI::Button("Statistics", {35, 204}, {180, 45}, p_UnselectedButtonMaterial, callback, "assets/icons/stats-icon.png");
     
     Core::UI::Text("Account", {40, 271}, {0.42, 0.42, 0.44, 1.0}, 20, "regualar", m_Scene);
     
     Core::UI::Button("Messages", {35, 316}, {180, 45}, p_UnselectedButtonMaterial, callback, "assets/icons/chat-icon.png");
     Core::UI::Button("Settings", {35, 363}, {180, 45}, p_UnselectedButtonMaterial, HandleSettingsCallback, "assets/icons/settings-icon.png");
}