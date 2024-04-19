#include "OrganizatonsScreen.h"
#include "../Screens.h"
#include <cpr/cpr.h>

#define RAPIDJSON_HAS_STDSTRING 1
#include <rapidjson/document.h>
#include <rapidjson/writer.h>
#include <rapidjson/prettywriter.h>

void OrganizationScreen::HandleOverviewCallback(std::shared_ptr<Core::Entity> e)
{
    m_SwitchScreens(m_Screens->OverviewScreen);
}

void OrganizationScreen::HandleSettingsCallback(std::shared_ptr<Core::Entity> e)
{
    m_SwitchScreens(m_Screens->SettingsScreen);    
}

void OrganizationScreen::HandleOrganizationName(std::string orgName, std::shared_ptr<Core::Entity> e)
{
    m_OrganizationName = orgName;
}

void OrganizationScreen::HandleCreateaOrganizationCallback(std::shared_ptr<Core::Entity> e)
{
    rapidjson::Document organizationData;
    organizationData.SetObject();

    organizationData.AddMember<std::string>("name", m_OrganizationName, organizationData.GetAllocator());

    rapidjson::StringBuffer organizationString;
    rapidjson::PrettyWriter<rapidjson::StringBuffer> writer(organizationString);
    organizationData.Accept(writer);
    
    cpr::Response r = cpr::Post(
        cpr::Url{m_BaseUrl + "/organizations/create"},
        cpr::Body{organizationString.GetString()},
        cpr::Header{{"Authorization", m_Token}}
        );

    if(r.status_code != 200)
    {
        return;
    }


    m_Screens->OverviewScreen->OnScreenChange();
    m_SwitchScreens(m_Screens->OverviewScreen);
}

void OrganizationScreen::HandleJoinOrganizationCallback(std::shared_ptr<Core::Entity> e)
{
    rapidjson::Document organizationData;
    organizationData.SetObject();

    organizationData.AddMember<std::string>("code", m_OrganizationCode, organizationData.GetAllocator());

    rapidjson::StringBuffer organizationString;
    rapidjson::PrettyWriter<rapidjson::StringBuffer> writer(organizationString);
    organizationData.Accept(writer);
    
    cpr::Response r = cpr::Post(
        cpr::Url{m_BaseUrl + "/organizations/join"},
        cpr::Body{organizationString.GetString()},
        cpr::Header{{"Authorization", m_Token}}
        );

    if(r.status_code != 200)
    {
        return;
    }

    m_Screens->OverviewScreen->OnScreenChange();
    m_SwitchScreens(m_Screens->OverviewScreen);
}

void OrganizationScreen::InitRenderElements()
{
    SideBar();
    MainContent();
}

void OrganizationScreen::HandleOrganizationCode(std::string code, std::shared_ptr<Core::Entity> e)
{
    m_OrganizationCode = code;
}

void callback(std::shared_ptr<Core::Entity> e){}

void OrganizationScreen::SideBar()
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

void OrganizationScreen::MainContent()
{
    Core::UI::Text("Create organization", {280, 150}, {0.0, 0.0, 0.0, 1.0}, 32, "black", m_Scene);
    Core::UI::Text("Welcome to Lorem Ipsum organizations!", {280, 200}, {0.4, 0.4, 0.4, 1.0}, 18, "bold", m_Scene);

    Core::UI::Text("Create your first organization and share the token", {280, 250}, {0.4, 0.4, 0.4, 1.0}, 18, "regular", m_Scene);
    Core::UI::Text("given after completing this step with your working", {280, 270}, {0.4, 0.4, 0.4, 1.0}, 18, "regular", m_Scene);
    Core::UI::Text("team.", {280, 290}, {0.4, 0.4, 0.4, 1.0}, 18, "regular", m_Scene);

    Core::UI::Text("Enter name for your organization", {280, 380}, {0.4, 0.4, 0.4, 1.0}, 22, "regular", m_Scene);
     
    Core::UI::Input({280, 410}, {350, 35}, 0.25, {0.91, 0.91, 0.91, 1.0}, {0.0, 0.0, 0.0, 1.0}, 22, "regular", m_Scene, HandleOrganizationName);

    std::shared_ptr<Core::UI::ButtonMaterial> p_ConfirmButtonMaterial = std::make_shared<Core::UI::ButtonMaterial>();
    p_ConfirmButtonMaterial->Color = {0.34, 0.52, 0.92, 1.0};
    p_ConfirmButtonMaterial->Roundness = 0.3;
    p_ConfirmButtonMaterial->Scene = m_Scene;
    p_ConfirmButtonMaterial->TextSize = 20;

    Core::UI::Button("Confirm", {405, 480}, {80, 45}, p_ConfirmButtonMaterial, HandleCreateaOrganizationCallback);

    
    Core::UI::Text("Join organization", {GetScreenWidth() / 2 + 100, 150}, {0.0, 0.0, 0.0, 1.0}, 32, "black", m_Scene);
    Core::UI::Text("Welcome to Lorem Ipsum organizations!", {GetScreenWidth() / 2 + 100, 200}, {0.4, 0.4, 0.4, 1.0}, 18, "bold", m_Scene);

    Core::UI::Text("Enter the token given by your administrator to join", {GetScreenWidth() / 2 + 100, 250}, {0.4, 0.4, 0.4, 1.0}, 18, "regular", m_Scene);
    Core::UI::Text("your organization.", {GetScreenWidth() / 2 + 100, 270}, {0.4, 0.4, 0.4, 1.0}, 18, "regular", m_Scene);

    Core::UI::Text("Token", {GetScreenWidth() / 2 + 100, 380}, {0.4, 0.4, 0.4, 1.0}, 22, "regular", m_Scene);
     
    Core::UI::Input({GetScreenWidth() / 2 + 100, 410}, {350, 35}, 0.25, {0.91, 0.91, 0.91, 1.0}, {0.0, 0.0, 0.0, 1.0}, 22, "regular", m_Scene, HandleOrganizationCode);

    Core::UI::Button("Confirm", {GetScreenWidth() / 2 + 235, 480}, {80, 45}, p_ConfirmButtonMaterial, HandleJoinOrganizationCallback);
}



