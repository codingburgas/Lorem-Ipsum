#pragma once
#include "../Screen.h"

class RegisterScreen : public Screen
{
public:
    RegisterScreen() = default;
    ~RegisterScreen() = default;

    void InitRenderElements() override;
};