#pragma once
#include "../Screen.h"

class LoginScreen : public Screen
{
public:
    LoginScreen() { InitRenderElements();}
    ~LoginScreen() = default;

    void InitRenderElements() override;
    
private:
    static void RegisterCallback();
    static void HandleLogin();
    static void EnterUsernameCallback(std::string username);
    static void EnterPasswordCallback(std::string password);
};