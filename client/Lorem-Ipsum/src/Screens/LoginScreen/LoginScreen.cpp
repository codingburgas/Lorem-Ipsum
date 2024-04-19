#include "LoginScreen.h"
#include "../Screens.h"
#include <cpr/cpr.h>

#define RAPIDJSON_HAS_STDSTRING 1
#include <rapidjson/document.h>
#include <rapidjson/writer.h>
#include <rapidjson/prettywriter.h>

void LoginScreen::HandleLogin(std::shared_ptr<Core::Entity> e)
{
    rapidjson::Document userData;
    userData.SetObject();

    userData.AddMember<std::string>("username", m_LoginInformation.UserName, userData.GetAllocator());
    userData.AddMember<std::string>("password", m_LoginInformation.Password, userData.GetAllocator());

    rapidjson::StringBuffer userString;
    rapidjson::PrettyWriter<rapidjson::StringBuffer> writer(userString);
    userData.Accept(writer);
    
    cpr::Response r = cpr::Post(
        cpr::Url{m_BaseUrl + "/login"},
        cpr::Body{userString.GetString()}
        );

    if(r.status_code != 200)
    {
        return;
    }

    rapidjson::Document document;
    document.Parse(r.text.c_str());

    m_Token = document["token"].GetString();

    cpr::Response userResponse = cpr::Get(
            cpr::Url{m_BaseUrl + "/user"},
            cpr::Header{{"Authorization", m_Token}}
        );

    rapidjson::Document userDocument;
    userDocument.Parse(userResponse.text.c_str());

    m_User = std::make_shared<User>();
    m_User->Name = userDocument["name"].GetString();
    m_User->Email = userDocument["email"].GetString();
    m_User->Username = userDocument["username"].GetString();
    
    m_SwitchScreens(m_Screens->OverviewScreen);

    m_Screens->SettingsScreen->OnScreenChange();
    m_Screens->OrganizationScreen->OnScreenChange();
    m_Screens->OverviewScreen->OnScreenChange();
}

void LoginScreen::RegisterCallback(std::shared_ptr<Core::Entity> e)
{
   m_SwitchScreens(m_Screens->RegisterScreen); 
}

void LoginScreen::EnterUsernameCallback(std::string username, std::shared_ptr<Core::Entity> e)
{
    m_LoginInformation.UserName = username;
}

void LoginScreen::EnterPasswordCallback(std::string password, std::shared_ptr<Core::Entity> e)
{
   m_LoginInformation.Password = password; 
}

void LoginScreen::InitRenderElements()
{
    std::shared_ptr<Core::UI::ButtonMaterial> p_LoginButtonMaterial = std::make_shared<Core::UI::ButtonMaterial>();
    p_LoginButtonMaterial->Color = {0.49, 0.53, 0.99, 1.0f};
    p_LoginButtonMaterial->Roundness = 0.25;
    p_LoginButtonMaterial->TextSize = 24;
    p_LoginButtonMaterial->Scene = m_Scene;

    std::shared_ptr<Core::UI::ButtonMaterial> p_RegisterButtonMaterial = std::make_shared<Core::UI::ButtonMaterial>();
    p_RegisterButtonMaterial->Color = {1.0, 1.0, 1.0, 1.0};
    p_RegisterButtonMaterial->TextColor = {0.0f, 0.0f, 0.0, 1.0};
    p_RegisterButtonMaterial->Roundness = 0.25;
    p_RegisterButtonMaterial->TextSize = 24;
    p_RegisterButtonMaterial->Scene = m_Scene;

    std::shared_ptr<Core::UI::InputMaterial> p_CredentialsInputMaterial = std::make_shared<Core::UI::InputMaterial>();
    p_CredentialsInputMaterial->Color = {0.84, 0.84, 0.84, 1.0f};
    p_CredentialsInputMaterial->TextColor = {0.0, 0.0, 0.0, 1.0f};
    p_CredentialsInputMaterial->TextSize = 28;
    p_CredentialsInputMaterial->Roundness = 0.4f;
    p_CredentialsInputMaterial->Scene = m_Scene;
    
    Core::UI::Button("Login", {GetScreenWidth() / 2 - 190, 85}, {190, 40}, p_LoginButtonMaterial, HandleLogin);
    Core::UI::Button("Register", {GetScreenWidth() / 2, 85}, {190, 40}, p_RegisterButtonMaterial, RegisterCallback);

    Core::UI::Text("Welcome", {GetScreenWidth() / 2 - 190, 165}, {0.0, 0.0, 0.0, 1.0}, 48, "black", m_Scene);
    Core::UI::Text("Please login to your account", {GetScreenWidth() / 2 - 190, 215}, {0.0, 0.0, 0.0, 1.0}, 24, "thin", m_Scene);

    Core::UI::Text("Username", {GetScreenWidth() / 2 - 190, 265}, {0.0, 0.0, 0.0, 1.0}, 20, "regular", m_Scene);
    Core::UI::Input({GetScreenWidth() / 2 - 190, 297}, {380, 40}, p_CredentialsInputMaterial, EnterUsernameCallback);

    Core::UI::Text("Password", {GetScreenWidth() / 2 - 190, 372}, {0.0, 0.0, 0.0, 1.0}, 20, "regular", m_Scene);
    Core::UI::Input({GetScreenWidth() / 2 - 190, 404}, {380, 40}, p_CredentialsInputMaterial, EnterPasswordCallback, true);

    Core::UI::Button("Log In", {GetScreenWidth() / 2 - 190 / 2, 520}, {190, 40}, p_LoginButtonMaterial, HandleLogin);
}