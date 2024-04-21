#include "ApplicationLayer.h"
#include "utils/DrawTextBoxed.h"

void ApplicationLayer::OnAttach()
{
    m_Camera.reset(new Camera2D{0});
    m_Camera->target = Vector2({0, 0});
    m_Camera->offset = Vector2({0, 0});
    m_Camera->rotation = 0.0f;
    m_Camera->zoom = 1.0f;
    
    InitScreens();
    
    m_BoundScene = m_Screens->LoginScreen->GetScene();

    Fonts fonts;
    fonts.Regular = std::make_shared<Font>(LoadFontEx("assets/fonts/MierA-Book.ttf", 64, 0, 256));
    fonts.Bold = std::make_shared<Font>(LoadFontEx("assets/fonts/MierA-Bold.ttf", 64, 0, 256));
    fonts.Black = std::make_shared<Font>(LoadFontEx("assets/fonts/MierA-Black.ttf", 64, 0, 256));
    fonts.Thin = std::make_shared<Font>(LoadFontEx("assets/fonts/MierA-Thin.ttf", 64, 0, 256));

    SetTextureFilter(fonts.Regular->texture, TEXTURE_FILTER_TRILINEAR);
    SetTextureFilter(fonts.Bold->texture, TEXTURE_FILTER_TRILINEAR);
    SetTextureFilter(fonts.Black->texture, TEXTURE_FILTER_TRILINEAR);
    SetTextureFilter(fonts.Thin->texture, TEXTURE_FILTER_TRILINEAR);

    m_MierFonts = std::make_shared<Fonts>(fonts);
    
    for (auto entity: m_BoundScene->GetEntities<Core::NativeScriptComponent>())
    {
        Core::NativeScriptComponent& script = entity->GetComponent<Core::NativeScriptComponent>();

        script.Instance->onLateAttach();
    }
}

void ApplicationLayer::InitScreens()
{
    m_Screens = std::make_shared<Screens>();

    Screen::SetScreens(m_Screens);
    Screen::SetSwitchScreen(SwitchScenes);
    
    m_Screens->LandingScreen = std::make_shared<LandingScreen>();
    m_Screens->RegisterScreen = std::make_shared<RegisterScreen>();
    m_Screens->LoginScreen = std::make_shared<LoginScreen>();
    m_Screens->OverviewScreen = std::make_shared<OverviewScreen>();
    m_Screens->SettingsScreen = std::make_shared<SettingsScreen>();
    m_Screens->OrganizationScreen = std::make_shared<OrganizationScreen>();
    m_Screens->CoursesScreen = std::make_shared<CoursesScreen>();
    m_Screens->CreateCourseScreen = std::make_shared<CreateCourseScreen>();
    m_Screens->JoinCourseScreen = std::make_shared<JoinCourseScreen>();
    m_Screens->ThemesScreen = std::make_shared<ThemesScreen>();
    m_Screens->NewThemeScreen = std::make_shared<NewThemeScreen>();
}

void ApplicationLayer::SwitchScenes(std::shared_ptr<Screen> screen)
{
    screen->InitRenderElementsOnResize();
    screen->OnScreenChange();
    m_BoundScene = screen->GetScene();
}

void ApplicationLayer::OnUpdate()
{
    
    for (auto entity: m_BoundScene->GetEntities<Core::NativeScriptComponent>())
    {
        if(m_BoundScene->HasEntity(entity->GetNativeEntity()))
        {
            Core::NativeScriptComponent& script = entity->GetComponent<Core::NativeScriptComponent>();

            script.Instance->OnUpdate();
        }
    }
}

void ApplicationLayer::OnUIRender()
{
    int lowestYPostion = 0;

    for (auto entity: m_BoundScene->GetEntities<Core::UIComponent>())
    {
        Core::TransformComponent& transformComponent = entity->GetComponent<Core::TransformComponent>();

        if (transformComponent.Position.y + transformComponent.Scale.y > lowestYPostion)
        {
            lowestYPostion = transformComponent.Position.y + transformComponent.Scale.y;
        }
    }

    if(lowestYPostion > GetScreenHeight() && m_Camera->offset.y <= 0)
    {
        if(m_Camera->offset.y * -1 + GetScreenHeight() < lowestYPostion + 100)
            m_Camera->offset.y += GetMouseWheelMove() * 100;
        else
            m_Camera->offset.y = (lowestYPostion + 99 - GetScreenHeight()) * -1;
    }
    else
    {
        m_Camera->offset.y = 0;
    }
    
    if(IsWindowResized())
    {
        m_Screens->LandingScreen->InitRenderElementsOnResize();
        m_Screens->LoginScreen->InitRenderElementsOnResize();
        m_Screens->RegisterScreen->InitRenderElementsOnResize();
        m_Screens->OverviewScreen->InitRenderElementsOnResize();
        m_Screens->SettingsScreen->InitRenderElementsOnResize();
        m_Screens->OrganizationScreen->InitRenderElementsOnResize();
        m_Screens->CoursesScreen->InitRenderElementsOnResize();
        m_Screens->CreateCourseScreen->InitRenderElementsOnResize();
        m_Screens->JoinCourseScreen->InitRenderElementsOnResize();
        m_Screens->ThemesScreen->InitRenderElementsOnResize();
        m_Screens->NewThemeScreen->InitRenderElementsOnResize();
        
        for (auto entity: m_BoundScene->GetEntities<Core::NativeScriptComponent>())
        {
            Core::NativeScriptComponent& script = entity->GetComponent<Core::NativeScriptComponent>();
    
            script.Instance->onLateAttach();
        }
    }

    BeginMode2D(*m_Camera);
    
    ClearBackground(RAYWHITE);
    
    for (auto entity: m_BoundScene->GetEntities<Core::UIComponent>())
    {
        Core::UIComponent& UIComponent = entity->GetComponent<Core::UIComponent>();
        Core::TransformComponent& transformComponent = entity->GetComponent<Core::TransformComponent>();
        
        if(entity->HasComponent<Core::ColorComponent>())
        {
            Core::ColorComponent& colorComponent = entity->GetComponent<Core::ColorComponent>();

            if(entity->GetComponent<Core::UITypeComponent>().Type == Core::UIType::TEXTBOX)
            {
                Core::UIBorderComponent& border = entity->GetComponent<Core::UIBorderComponent>();
                
                DrawRectangleRounded(Rectangle({ transformComponent.Position.x, transformComponent.Position.y, transformComponent.Scale.x, transformComponent.Scale.y}), transformComponent.Roundness, 20, Color(colorComponent.Color.r, colorComponent.Color.g, colorComponent.Color.b, colorComponent.Color.a));
                DrawTextBoxedSelectable(*m_MierFonts->StringToFont(UIComponent.FontType), UIComponent.Text.c_str(), {transformComponent.Position.x + 5, transformComponent.Position.y + 5, transformComponent.Scale.x, transformComponent.Scale.y}, UIComponent.TextSize, 0, 1, Color(UIComponent.Color.r, UIComponent.Color.g, UIComponent.Color.b, UIComponent.Color.a), 0, 0, WHITE, GRAY);
                
                DrawRectangleRoundedLines(Rectangle({ transformComponent.Position.x, transformComponent.Position.y, transformComponent.Scale.x, transformComponent.Scale.y}), transformComponent.Roundness, 20, 1.5, Color(border.Color.r, border.Color.g, border.Color.b, border.Color.a));
            }
            
            if(entity->GetComponent<Core::UITypeComponent>().Type == Core::UIType::BUTTON)
            {
                DrawRectangleRounded(Rectangle({ transformComponent.Position.x, transformComponent.Position.y, transformComponent.Scale.x, transformComponent.Scale.y}), transformComponent.Roundness, 20, Color(colorComponent.Color.r, colorComponent.Color.g, colorComponent.Color.b, colorComponent.Color.a));

                if(entity->HasComponent<Core::SpriteComponent>())
                {
                    Core::SpriteComponent& spriteComponent = entity->GetComponent<Core::SpriteComponent>();

                    if(UIComponent.Text != "")
                        DrawTexture(*spriteComponent.Texture, transformComponent.Position.x + 20, transformComponent.Position.y + transformComponent.Scale.y / 2 - 9, WHITE);
                    else
                        DrawTexture(*spriteComponent.Texture, transformComponent.Position.x + transformComponent.Scale.x / 2 - 7, transformComponent.Position.y + transformComponent.Scale.y / 2 - 8, WHITE);
                }
                
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

        if (entity->HasComponent<Core::SpriteComponent>() && entity->GetComponent<Core::UITypeComponent>().Type == Core::UIType::AVATAR)
        {
            Core::SpriteComponent& spriteComponent = entity->GetComponent<Core::SpriteComponent>();

            DrawTexture(*spriteComponent.Texture, transformComponent.Position.x, transformComponent.Position.y, WHITE);
        }
        
        if (entity->GetComponent<Core::UITypeComponent>().Type == Core::UIType::TEXT)
        {
            DrawTextEx(*m_MierFonts->StringToFont(UIComponent.FontType), UIComponent.Text.c_str(), {transformComponent.Position.x, transformComponent.Position.y}, UIComponent.TextSize, 0,Color(UIComponent.Color.r, UIComponent.Color.g, UIComponent.Color.b, UIComponent.Color.a));
        }
    }

    EndMode2D();
}
