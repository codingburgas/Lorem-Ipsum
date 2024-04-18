#pragma once
#include "../Screen.h"

class RegisterScreen : public Screen
{
public:
    RegisterScreen() { InitRenderElements(); }
    ~RegisterScreen() = default;

    void InitRenderElements() override;

private:

    struct UserRegisterInput
    {
        std::string Name;
        std::string UserName;
        std::string Email;
        std::string Password;
    };

    inline static UserRegisterInput m_RegisterInformation;
    
    static void LoginCallback();
    static void HandleRegister();

    static void EnterNameCallback(std::string name);
    static void EnterUserNameCallback(std::string username);
    static void EnterEmailCallback(std::string email);
    static void EnterPasswordCallback(std::string password);
};