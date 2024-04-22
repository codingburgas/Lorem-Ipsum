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
    
    static void RegisterCallback(std::shared_ptr<Core::Entity> e);
    static void HandleLogin(std::shared_ptr<Core::Entity> e);
    static void EnterUsernameCallback(std::string username, std::shared_ptr<Core::Entity> e);
    static void EnterPasswordCallback(std::string password, std::shared_ptr<Core::Entity> e);
};