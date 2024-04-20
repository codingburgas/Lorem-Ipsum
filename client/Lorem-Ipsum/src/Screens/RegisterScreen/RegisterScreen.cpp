#include "RegisterScreen.h"
#include "../Screens.h"
#include <cpr/cpr.h>

#define RAPIDJSON_HAS_STDSTRING 1
#include <rapidjson/document.h>
#include <rapidjson/writer.h>
#include <rapidjson/prettywriter.h>

void RegisterScreen::HandleRegister(std::shared_ptr<Core::Entity> e)
{
    if(m_RegisterInformation.UserName.empty()
        || m_RegisterInformation.Email.empty()
        || m_RegisterInformation.Name.empty()
        || m_RegisterInformation.Password.empty())
        return;
    
    rapidjson::Document userData;
    userData.SetObject();

    userData.AddMember<std::string>("username", m_RegisterInformation.UserName, userData.GetAllocator());
    userData.AddMember<std::string>("email", m_RegisterInformation.Email, userData.GetAllocator());
    userData.AddMember<std::string>("name", m_RegisterInformation.Name, userData.GetAllocator());
    userData.AddMember<std::string>("password", m_RegisterInformation.Password, userData.GetAllocator());

    rapidjson::StringBuffer userString;
    rapidjson::PrettyWriter<rapidjson::StringBuffer> writer(userString);
    userData.Accept(writer);
    
    cpr::Response r = cpr::Post(
        cpr::Url{m_BaseUrl + "/register"},
        cpr::Body{userString.GetString()}
        );

    if (r.status_code != 200)
    {
        return;
    }

    m_SwitchScreens(m_Screens->LoginScreen);
}

void RegisterScreen::LoginCallback(std::shared_ptr<Core::Entity> e)
{
    m_SwitchScreens(m_Screens->LoginScreen);    
}

void RegisterScreen::EnterNameCallback(std::string name, std::shared_ptr<Core::Entity> e)
{
    m_RegisterInformation.Name = name;
}

void RegisterScreen::EnterUserNameCallback(std::string username, std::shared_ptr<Core::Entity> e)
{
    m_RegisterInformation.UserName = username;
}

void RegisterScreen::EnterEmailCallback(std::string email, std::shared_ptr<Core::Entity> e)
{
    m_RegisterInformation.Email = email;
}

void RegisterScreen::EnterPasswordCallback(std::string password, std::shared_ptr<Core::Entity> e)
{
    m_RegisterInformation.Password = password;
}

void RegisterScreen::InitRenderElements()
{

    std::shared_ptr<Core::UI::InputMaterial> p_CredentialsInputMaterial = std::make_shared<Core::UI::InputMaterial>();
    p_CredentialsInputMaterial->Color = { 0.84, 0.84, 0.84, 1.0f };
    p_CredentialsInputMaterial->TextColor = { 0.0, 0.0, 0.0, 1.0f };
    p_CredentialsInputMaterial->TextSize = 28;
    p_CredentialsInputMaterial->Roundness = 0.4f;
    p_CredentialsInputMaterial->Scene = m_Scene;

    std::shared_ptr<Core::UI::ButtonMaterial> p_RegisterButtonMaterial = std::make_shared<Core::UI::ButtonMaterial>();
    p_RegisterButtonMaterial->Color = { 0.49, 0.53, 0.99, 1.0f };
    p_RegisterButtonMaterial->Roundness = 0.25;
    p_RegisterButtonMaterial->TextSize = 24;
    p_RegisterButtonMaterial->Scene = m_Scene;

    Core::UI::Button("Login", {GetScreenWidth() / 2 - 192, 85}, {190, 40}, 0.25, {1.0, 1.0, 1.0, 1.0f}, {0.0f, 0.0f, 0.0f, 1.0f}, 24, "regular", m_Scene, LoginCallback);
    Core::UI::Button("Register", {GetScreenWidth() / 2, 85}, {190, 40}, 0.25, {0.49, 0.53, 0.99, 1.0f}, {1.0f, 1.0f, 1.0f, 1.0f}, 24, "regular", m_Scene, HandleRegister);

    Core::UI::Text("Welcome", { GetScreenWidth() / 2 - 190, 165 }, { 0.0, 0.0, 0.0, 1.0 }, 48, "black", m_Scene);
    Core::UI::Text("Please register your account", { GetScreenWidth() / 2 - 190, 215 }, { 0.0, 0.0, 0.0, 1.0 }, 24, "thin", m_Scene);

    Core::UI::Text("Name", { GetScreenWidth() / 2 - 190, 265 }, { 0.0, 0.0, 0.0, 1.0 }, 20, "regular", m_Scene);
    Core::UI::Input({ GetScreenWidth() / 2 - 190, 297 }, { 380, 40 }, p_CredentialsInputMaterial, EnterNameCallback);

    Core::UI::Text("Username", { GetScreenWidth() / 2 - 190, 350 }, { 0.0, 0.0, 0.0, 1.0 }, 20, "regular", m_Scene);
    Core::UI::Input({ GetScreenWidth() / 2 - 190, 380 }, { 380, 40 }, p_CredentialsInputMaterial, EnterUserNameCallback);

    Core::UI::Text("Email", { GetScreenWidth() / 2 - 190, 435 }, { 0.0, 0.0, 0.0, 1.0 }, 20, "regular", m_Scene);
    Core::UI::Input({ GetScreenWidth() / 2 - 190, 465 }, { 380, 40 }, p_CredentialsInputMaterial, EnterEmailCallback);

    Core::UI::Text("Password", { GetScreenWidth() / 2 - 190, 520 }, { 0.0, 0.0, 0.0, 1.0 }, 20, "regular", m_Scene);
    Core::UI::Input({ GetScreenWidth() / 2 - 190, 550 }, { 380, 40 }, p_CredentialsInputMaterial, EnterPasswordCallback, true);

    Core::UI::Button("Register", { GetScreenWidth() / 2 - 190 / 2, 620 }, { 190, 40 }, p_RegisterButtonMaterial, HandleRegister);
}
