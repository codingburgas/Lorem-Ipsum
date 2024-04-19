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
    
    static void LoginCallback(std::shared_ptr<Core::Entity> e);
    static void HandleRegister(std::shared_ptr<Core::Entity> e);

    static void EnterNameCallback(std::string name, std::shared_ptr<Core::Entity> e);
    static void EnterUserNameCallback(std::string username, std::shared_ptr<Core::Entity> e);
    static void EnterEmailCallback(std::string email, std::shared_ptr<Core::Entity> e);
    static void EnterPasswordCallback(std::string password, std::shared_ptr<Core::Entity> e);
};