#include "OverviewScreen.h"
#include "../Screens.h"
#include <cpr/cpr.h>

#define RAPIDJSON_HAS_STDSTRING 1
#include <rapidjson/document.h>
#include <rapidjson/writer.h>
#include <rapidjson/prettywriter.h>

void overviewCallback(std::shared_ptr<Core::Entity> e) {}

void OverviewScreen::HandleOrganizationSelectedCallback(std::shared_ptr<Core::Entity> e)
{
    Core::UIComponent& ui = e->GetComponent<Core::UIComponent>();
    
    for(auto& i : m_Organizations)
    {
        if(i.name == ui.Text)
        {
            m_SelectedOrganization = i.id;
            break;
        }
    }

    m_SwitchScreens(m_Screens->CoursesScreen);
}

void OverviewScreen::OnScreenChange()
{
    cpr::Response r = cpr::Get(
        cpr::Url{m_BaseUrl + "/organizations"},
        cpr::Header{{"Authorization", m_Token}}
        );

    if(r.status_code != 200)
    {
        return;
    }

    rapidjson::Document organizationsDocument;
    organizationsDocument.Parse(r.text);

    m_Organizations.clear();
    for (const auto& v : organizationsDocument.GetArray()) {
        Organization org;
        org.id = v["id"].GetInt();
        org.name = v["name"].GetString();
        
        m_Organizations.push_back(org);
    }
    
    InitRenderElementsOnResize();
}

void OverviewScreen::HandleSettings(std::shared_ptr<Core::Entity> e)
{
    m_SwitchScreens(m_Screens->SettingsScreen);    
}

void OverviewScreen::HandleOrganizatoinsCallback(std::shared_ptr<Core::Entity> e)
{
    m_SwitchScreens(m_Screens->OrganizationScreen);
}

void OverviewScreen::InitRenderElements()
{
    NavBar();
    SideBar();
    MainContent();
}

void OverviewScreen::NavBar()
{
    Core::UI::Text("Lorem Ipsum", {35, 25}, {0.0, 0.0, 0.0, 1.0}, 32, "regular", m_Scene);

    // Core::UI::Avatar({GetScreenWidth() - 68, 20}, "assets/test-avatar.png", m_Scene);
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
    Core::UI::Button("Statistics", {35, 204}, {180, 45}, p_UnselectedButtonMaterial, overviewCallback, "assets/icons/stats-icon.png");
    
    Core::UI::Text("Account", {40, 271}, {0.42, 0.42, 0.44, 1.0}, 20, "regualar", m_Scene);
    
    Core::UI::Button("Messages", {35, 316}, {180, 45}, p_UnselectedButtonMaterial, overviewCallback, "assets/icons/chat-icon.png");
    Core::UI::Button("Settings", {35, 363}, {180, 45}, p_UnselectedButtonMaterial, HandleSettings, "assets/icons/settings-icon.png");
}

void OverviewScreen::MainContent()
{
    std::shared_ptr<Core::UI::ButtonMaterial> p_OrganizationButtonMaterial = std::make_shared<Core::UI::ButtonMaterial>();
    p_OrganizationButtonMaterial->Color = {0.0f, 0.46f, 0.98f, 1.0f};
    p_OrganizationButtonMaterial->Roundness = 0.5f;
    p_OrganizationButtonMaterial->FontType = "bold";
    p_OrganizationButtonMaterial->TextSize = 32;
    p_OrganizationButtonMaterial->Scene = m_Scene;
    
    Core::UI::Text(TextFormat("Welcome back to Lorem Ipsum!"), {310, 125}, {0.0, 0.0, 0.0, 1.0}, 32, "regualar", m_Scene);
    Core::UI::Text("Organizations", {360, 230}, {0.0, 0.0, 0.0, 1.0}, 20, "thin", m_Scene);

    for(std::size_t i = 0; i < m_Organizations.size(); i++)
        Core::UI::Button(m_Organizations[i].name, {350, 280 + 64 * i}, {180, 60}, p_OrganizationButtonMaterial, HandleOrganizationSelectedCallback);

    Core::UI::Text("Click to see your courses", {360, 300 + 64 * m_Organizations.size()}, {0.0, 0.0, 0.0, 1.0}, 16, "regular", m_Scene);

    Core::UI::Text("Join", {GetScreenWidth() - (280 + MeasureText("Join", 28)), 230}, {0.0, 0.0, 0.0, 1.0}, 28, "regular", m_Scene);

    std::shared_ptr<Core::UI::ButtonMaterial> p_JoinOrganizationButtonMaterial = std::make_shared<Core::UI::ButtonMaterial>();
    p_JoinOrganizationButtonMaterial->Color = {0.04f, 0.72f, 0.98f, 1.0f};
    p_JoinOrganizationButtonMaterial->Roundness = 0.5f;
    p_JoinOrganizationButtonMaterial->TextSize = 24;
    p_JoinOrganizationButtonMaterial->Scene = m_Scene;
    
    Core::UI::Button("Organization", {GetScreenWidth() - (280 + MeasureText("Join", 28)), 280}, {230, 50}, p_JoinOrganizationButtonMaterial, HandleOrganizatoinsCallback);

    Core::UI::Text("Statistics", {310, 360 + 64 * m_Organizations.size()}, {0.0, 0.0, 0.0, 1.0}, 28, "regular", m_Scene);

    int position = 13;
    int organizationMembers = 496;

    Core::UI::Text(std::to_string(position), {310, 400 + 64 * m_Organizations.size()}, {0.0f, 0.46f, 0.98f, 1.0f}, 46, "bold", m_Scene);
    Core::UI::Text(TextFormat("place in the organization out of %d", organizationMembers), {370, 406 + 64 * m_Organizations.size()}, {0.0f, 0.0f, 0.0f, 1.0f}, 20, "regular", m_Scene);

    // Core::UI::Text("Cource Activities", {GetScreenWidth() - (180 + MeasureText("Cource Activities", 28)), 476}, {0.0, 0.0, 0.0, 1.0}, 28, "regular", m_Scene);
}
