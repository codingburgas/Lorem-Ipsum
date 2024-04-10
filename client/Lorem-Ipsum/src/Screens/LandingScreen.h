#pragma once
#include "Screen.h"

class LandingScreen : public Screen
{
public:
    LandingScreen() = default;
    ~LandingScreen() = default;

    void RenderElements() override;
    void RenderElementsOnResize() override;
};
