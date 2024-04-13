﻿#include "ApplicationLayer.h"

void ApplicationLayer::OnAttach()
{
    InitScreens();
    
    m_BoundScene = m_LoginScreen->GetScene();

    Fonts fonts;
    fonts.Regular = std::make_shared<Font>(LoadFontEx("assets/fonts/MierA-Book.ttf", 64, 0, NULL));
    fonts.Bold = std::make_shared<Font>(LoadFontEx("assets/fonts/MierA-Bold.ttf", 64, 0, NULL));
    fonts.Black = std::make_shared<Font>(LoadFontEx("assets/fonts/MierA-Black.ttf", 64, 0, NULL));
    fonts.Thin = std::make_shared<Font>(LoadFontEx("assets/fonts/MierA-Thin.ttf", 64, 0, NULL));

    SetTextureFilter(fonts.Regular->texture, TEXTURE_FILTER_BILINEAR);
    SetTextureFilter(fonts.Bold->texture, TEXTURE_FILTER_BILINEAR);
    SetTextureFilter(fonts.Black->texture, TEXTURE_FILTER_BILINEAR);
    SetTextureFilter(fonts.Thin->texture, TEXTURE_FILTER_BILINEAR);

    m_MierFonts = std::make_shared<Fonts>(fonts);
    
    for (auto entity: m_BoundScene->GetEntities<Core::NativeScriptComponent>())
    {
        Core::NativeScriptComponent& script = entity->GetComponent<Core::NativeScriptComponent>();

        script.Instance->onLateAttach();
    }
}

void ApplicationLayer::InitScreens()
{
    m_LandingScreen = std::make_shared<LandingScreen>();
    m_RegisterScreen = std::make_shared<RegisterScreen>();
    m_LoginScreen = std::make_shared<LoginScreen>();
    
    m_LandingScreen->SetRegisterScreen(m_RegisterScreen);
    m_LandingScreen->SetLoginScreen(m_LoginScreen);
    m_LoginScreen->SetRegisterScreen(m_RegisterScreen);
    m_RegisterScreen->SetLoginScreen(m_LoginScreen);
    
    m_LandingScreen->SetSwitchBoundScene(SwitchScenes);
    
    m_LandingScreen->InitRenderElements();
    m_RegisterScreen->InitRenderElements();
    m_LoginScreen->InitRenderElements();
}

void ApplicationLayer::SwitchScenes(std::shared_ptr<Screen> screen)
{
    m_BoundScene = screen->GetScene();
}

void ApplicationLayer::OnUpdate()
{
    for (auto entity: m_BoundScene->GetEntities<Core::NativeScriptComponent>())
    {
        Core::NativeScriptComponent& script = entity->GetComponent<Core::NativeScriptComponent>();

        script.Instance->OnUpdate();
    }
}

void ApplicationLayer::OnUIRender()
{
    if(IsWindowResized())
    {
        m_LandingScreen->InitRenderElementsOnResize();
        m_LoginScreen->InitRenderElementsOnResize();
        m_RegisterScreen->InitRenderElementsOnResize();

        for (auto entity: m_BoundScene->GetEntities<Core::NativeScriptComponent>())
        {
            Core::NativeScriptComponent& script = entity->GetComponent<Core::NativeScriptComponent>();
    
            script.Instance->onLateAttach();
        }
    }
    
    ClearBackground(RAYWHITE);
    
    for (auto entity: m_BoundScene->GetEntities<Core::UIComponent>())
    {
        Core::UIComponent& UIComponent = entity->GetComponent<Core::UIComponent>();
        Core::TransformComponent& transformComponent = entity->GetComponent<Core::TransformComponent>();
        
        if(entity->HasComponent<Core::ColorComponent>())
        {
            Core::ColorComponent& colorComponent = entity->GetComponent<Core::ColorComponent>();
            
            if(entity->GetComponent<Core::UITypeComponent>().Type == Core::UIType::BUTTON)
            {
                DrawRectangleRounded(Rectangle({ transformComponent.Position.x, transformComponent.Position.y, transformComponent.Scale.x, transformComponent.Scale.y}), transformComponent.Roundness, 20, Color(colorComponent.Color.r, colorComponent.Color.g, colorComponent.Color.b, colorComponent.Color.a));
                DrawTextEx(*m_MierFonts->StringToFont(UIComponent.FontType), UIComponent.Text.c_str(), {(transformComponent.Position.x + transformComponent.Scale.x / 2) - MeasureTextEx(*m_MierFonts->StringToFont(UIComponent.FontType), UIComponent.Text.c_str(), UIComponent.TextSize, 0).x / 2, transformComponent.Position.y + transformComponent.Scale.y / 2 - UIComponent.TextSize / 2}, UIComponent.TextSize, 0, Color(UIComponent.Color.r, UIComponent.Color.g, UIComponent.Color.b, UIComponent.Color.a));
            }
            else if (entity->GetComponent<Core::UITypeComponent>().Type == Core::UIType::INPUT)
            {
                Core::UIBorderComponent& border = entity->GetComponent<Core::UIBorderComponent>();
                
                DrawRectangleRounded(Rectangle({ transformComponent.Position.x, transformComponent.Position.y, transformComponent.Scale.x, transformComponent.Scale.y}), transformComponent.Roundness, 20, Color(colorComponent.Color.r, colorComponent.Color.g, colorComponent.Color.b, colorComponent.Color.a));
                DrawRectangleRoundedLines(Rectangle({ transformComponent.Position.x, transformComponent.Position.y, transformComponent.Scale.x, transformComponent.Scale.y}), transformComponent.Roundness, 20, 1.5, Color(border.Color.r, border.Color.g, border.Color.b, border.Color.a));

                if (UIComponent.IsSecure)
                {
                    UIComponent.Text = std::string(UIComponent.Text.size(), '*');
                }
                
                if(MeasureTextEx(*m_MierFonts->StringToFont(UIComponent.FontType), UIComponent.Text.c_str(), UIComponent.TextSize, 0).x > transformComponent.Scale.x)
                {
                    int textWidth = MeasureTextEx(*m_MierFonts->StringToFont(UIComponent.FontType), UIComponent.Text.c_str(), UIComponent.TextSize, 0).x;
                    int letterWidth = textWidth / UIComponent.Text.length();
                    std::string subStr = UIComponent.Text.substr(ceil((textWidth - transformComponent.Scale.x) / letterWidth) + 1);

                    DrawTextEx(*m_MierFonts->StringToFont(UIComponent.FontType), subStr.c_str(), {transformComponent.Position.x - 5 - (MeasureTextEx(*m_MierFonts->StringToFont(UIComponent.FontType), subStr.c_str(), UIComponent.TextSize, 0).x - transformComponent.Scale.x + 5), transformComponent.Position.y + transformComponent.Scale.y / 2 - UIComponent.TextSize / 2 }, UIComponent.TextSize, 0, Color(UIComponent.Color.r, UIComponent.Color.g, UIComponent.Color.b, UIComponent.Color.a));
                }
                else
                {
                    DrawTextEx(*m_MierFonts->StringToFont(UIComponent.FontType), UIComponent.Text.c_str(), {transformComponent.Position.x + 5, transformComponent.Position.y + transformComponent.Scale.y / 2 - UIComponent.TextSize / 2}, UIComponent.TextSize, 0, Color(UIComponent.Color.r, UIComponent.Color.g, UIComponent.Color.b, UIComponent.Color.a));
                }
            }
        }
        
        if (entity->GetComponent<Core::UITypeComponent>().Type == Core::UIType::TEXT)
        {
            DrawTextEx(*m_MierFonts->StringToFont(UIComponent.FontType), UIComponent.Text.c_str(), {transformComponent.Position.x, transformComponent.Position.y}, UIComponent.TextSize, 0,Color(UIComponent.Color.r, UIComponent.Color.g, UIComponent.Color.b, UIComponent.Color.a));
        }
    }
}
