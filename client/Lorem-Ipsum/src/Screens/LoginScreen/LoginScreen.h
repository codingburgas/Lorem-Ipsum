#pragma once
#include "../Screen.h"

class LoginScreen : public Screen
{
public:
    LoginScreen() { InitRenderElements();}
    ~LoginScreen() = default;

    void InitRenderElements() override;
    
private:
    
    struct UserLoginInput
    {
        std::string UserName;
        std::string Password;
    };

    inline static UserLoginInput m_LoginInformation;
    
    static void RegisterCallback();
    static void HandleLogin();
    static void EnterUsernameCallback(std::string username);
    static void EnterPasswordCallback(std::string password);
};