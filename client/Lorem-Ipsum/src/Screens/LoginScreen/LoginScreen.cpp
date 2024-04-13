#include "LoginScreen.h"

void LoginScreen::HandleLogin()
{
    
}

void LoginScreen::RegisterCallback()
{
    m_SwitchBoundScene(m_RegisterScreen);
}

void LoginScreen::EnterUsernameCallback(std::string username)
{
    
}

void LoginScreen::EnterPasswordCallback(std::string password)
{
    
}

void LoginScreen::InitRenderElements()
{
    Core::UI::Button("Login", {GetScreenWidth() / 2 - 190, 85}, {190, 40}, 0.25, {0.49, 0.53, 0.99, 1.0f}, {1.0f, 1.0f, 1.0f, 1.0f}, 24, "regular", m_Scene, HandleLogin);
    Core::UI::Button("Register", {GetScreenWidth() / 2, 85}, {190, 40}, 0.25, {1.0f, 1.0f, 1.0f, 1.0f}, {0.0f, 0.0f, 0.0f, 1.0f}, 24, "regular", m_Scene, RegisterCallback);

    Core::UI::Text("Welcom", {GetScreenWidth() / 2 - 190, 165}, {0.0, 0.0, 0.0, 1.0}, 48, "black", m_Scene);
    Core::UI::Text("Please login to your account", {GetScreenWidth() / 2 - 190, 85 + 40 + 40 + 50}, {0.0, 0.0, 0.0, 1.0}, 24, "thin", m_Scene);

    Core::UI::Text("Username", {GetScreenWidth() / 2 - 190, 265}, {0.0, 0.0, 0.0, 1.0}, 20, "regular", m_Scene);
    Core::UI::Input({GetScreenWidth() / 2 - 190, 297}, {380, 40}, 0.4, {0.84, 0.84, 0.84, 1.0f}, {0.0, 0.0, 0.0, 1.0f}, 28, "regular", m_Scene, EnterUsernameCallback);

    Core::UI::Text("Password", {GetScreenWidth() / 2 - 190, 372}, {0.0, 0.0, 0.0, 1.0}, 20, "regular", m_Scene);
    Core::UI::Input({GetScreenWidth() / 2 - 190, 404}, {380, 40}, 0.4, {0.84, 0.84, 0.84, 1.0f}, {0.0, 0.0, 0.0, 1.0f}, 28, "regular", m_Scene, EnterPasswordCallback, true);

    Core::UI::Button("Log In", {GetScreenWidth() / 2 - 190 / 2, 520}, {190, 40}, 0.25, {0.49, 0.53, 0.99, 1.0f}, {1.0f, 1.0f, 1.0f, 1.0f}, 24, "bold", m_Scene, HandleLogin);
}