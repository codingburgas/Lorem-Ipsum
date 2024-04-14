#include "LoginScreen.h"
#include "../Screens.h"

void LoginScreen::HandleLogin()
{
    m_SwitchScreens(m_Screens->OverviewScreen);
}

void LoginScreen::RegisterCallback()
{
   m_SwitchScreens(m_Screens->RegisterScreen); 
}

void LoginScreen::EnterUsernameCallback(std::string username)
{
    
}

void LoginScreen::EnterPasswordCallback(std::string password)
{
    
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