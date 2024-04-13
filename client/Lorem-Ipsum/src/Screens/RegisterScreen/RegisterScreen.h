#pragma once
#include "../Screen.h"

class RegisterScreen : public Screen
{
public:
    RegisterScreen() = default;
    ~RegisterScreen() = default;

    void InitRenderElements() override;

    void SetLoginScreen(std::shared_ptr<Screen> login) { m_LoginScreen = login; }
private:
    static void LoginCallback();
private:
    inline static std::shared_ptr<Screen> m_LoginScreen;
};