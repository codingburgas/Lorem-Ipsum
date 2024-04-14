#pragma once
#include "../Screen.h"

class RegisterScreen : public Screen
{
public:
    RegisterScreen() { InitRenderElements(); }
    ~RegisterScreen() = default;

    void InitRenderElements() override;

private:
    static void LoginCallback();
};