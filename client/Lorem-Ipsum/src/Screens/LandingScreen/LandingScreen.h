#pragma once
#include "../Screen.h"

class LandingScreen : public Screen
{
public:
    LandingScreen() { InitRenderElements(); }
    ~LandingScreen() = default;

    void InitRenderElements() override;

private:
    static void RegisterCallback();
    static void LoginCallback();
};