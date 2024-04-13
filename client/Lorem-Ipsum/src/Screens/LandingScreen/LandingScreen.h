#pragma once
#include "../Screen.h"

class LandingScreen : public Screen
{
public:
    LandingScreen() = default;
    ~LandingScreen() = default;

    void InitRenderElements() override;

    void SetRegisterScreen(std::shared_ptr<Screen> registerScreen) { m_RegisterScreen = registerScreen; }
    void SetLoginScreen(std::shared_ptr<Screen> login) { m_LoginScreen = login; }

private:
    static void RegisterCallback();
    static void LoginCallback();

private:
    inline static std::shared_ptr<Screen> m_RegisterScreen;
    inline static std::shared_ptr<Screen> m_LoginScreen;
};