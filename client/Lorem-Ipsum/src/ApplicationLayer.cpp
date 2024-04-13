#include "ApplicationLayer.h"

void ApplicationLayer::OnAttach()
{
    m_LandingScreen = std::make_shared<LandingScreen>();
    m_LandingScreen->RenderElements();
    
    m_BoundScene = m_LandingScreen->GetScene();

    for (auto entity: m_BoundScene->GetEntities<Core::NativeScriptComponent>())
    {
        Core::NativeScriptComponent& script = entity->GetComponent<Core::NativeScriptComponent>();

        script.Instance->onLateAttach();
    }
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
        m_LandingScreen->RenderElementsOnResize();

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
                DrawText(UIComponent.Text.c_str(), (transformComponent.Position.x + transformComponent.Scale.x / 2) - MeasureText(UIComponent.Text.c_str(), UIComponent.TextSize) / 2, transformComponent.Position.y + transformComponent.Scale.y / 2 - UIComponent.TextSize / 2, UIComponent.TextSize, Color(UIComponent.Color.r, UIComponent.Color.g, UIComponent.Color.b, UIComponent.Color.a));
            }
            else if (entity->GetComponent<Core::UITypeComponent>().Type == Core::UIType::INPUT)
            {
                Core::UIBorderComponent& border = entity->GetComponent<Core::UIBorderComponent>();
                
                DrawRectangleRounded(Rectangle({ transformComponent.Position.x, transformComponent.Position.y, transformComponent.Scale.x, transformComponent.Scale.y}), transformComponent.Roundness, 20, Color(colorComponent.Color.r, colorComponent.Color.g, colorComponent.Color.b, colorComponent.Color.a));
                DrawRectangleRoundedLines(Rectangle({ transformComponent.Position.x, transformComponent.Position.y, transformComponent.Scale.x, transformComponent.Scale.y}), transformComponent.Roundness, 20, 1.5, Color(border.Color.r, border.Color.g, border.Color.b, border.Color.a));
                
                if(MeasureText(UIComponent.Text.c_str(), UIComponent.TextSize) > transformComponent.Scale.x)
                {
                    int textWidth = MeasureText(UIComponent.Text.c_str(), UIComponent.TextSize);
                    int letterWidth = textWidth / UIComponent.Text.length();
                    std::string subStr = UIComponent.Text.substr(ceil((textWidth - transformComponent.Scale.x) / letterWidth) + 1);

                    DrawText(subStr.c_str(), transformComponent.Position.x - 5 - (MeasureText(subStr.c_str(), UIComponent.TextSize) - transformComponent.Scale.x + 5), transformComponent.Position.y + transformComponent.Scale.y / 2 - UIComponent.TextSize / 2, UIComponent.TextSize, Color(UIComponent.Color.r, UIComponent.Color.g, UIComponent.Color.b, UIComponent.Color.a));
                }
                else
                {
                    DrawText(UIComponent.Text.c_str(), transformComponent.Position.x + 5, transformComponent.Position.y + transformComponent.Scale.y / 2 - UIComponent.TextSize / 2, UIComponent.TextSize, Color(UIComponent.Color.r, UIComponent.Color.g, UIComponent.Color.b, UIComponent.Color.a));
                }
                
            }
        }
        
        if (entity->GetComponent<Core::UITypeComponent>().Type == Core::UIType::TEXT)
        {
            DrawText(UIComponent.Text.c_str(), transformComponent.Position.x, transformComponent.Position.y, UIComponent.TextSize, Color(UIComponent.Color.r, UIComponent.Color.g, UIComponent.Color.b, UIComponent.Color.a));
        }
    }
}

