#pragma once
#include "../Screen.h"

class LoginScreen : public Screen
{
public:
    LoginScreen() = default;
    ~LoginScreen() = default;

    void InitRenderElements() override;

    void SetRegisterScreen(std::shared_ptr<Screen> registerScreen) { m_RegisterScreen = registerScreen; }
    
private:
    static void RegisterCallback();
    static void HandleLogin();
    static void EnterUsernameCallback(std::string username);
    static void EnterPasswordCallback(std::string password);
private:
    inline static std::shared_ptr<Screen> m_RegisterScreen;
};