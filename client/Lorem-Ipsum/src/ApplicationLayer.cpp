﻿#include "ApplicationLayer.h"

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
            
            DrawRectangleRounded(Rectangle({ transformComponent.Position.x, transformComponent.Position.y, transformComponent.Scale.x, transformComponent.Scale.y}), transformComponent.Roundness, 20, Color(colorComponent.Color.r, colorComponent.Color.g, colorComponent.Color.b, colorComponent.Color.a));
            DrawText(UIComponent.Text.c_str(), (transformComponent.Position.x + transformComponent.Scale.x / 2) - MeasureText(UIComponent.Text.c_str(), 24) / 2, transformComponent.Position.y + transformComponent.Scale.y / 2 - 12, 24, Color(UIComponent.Color.r, UIComponent.Color.g, UIComponent.Color.b, UIComponent.Color.a));
        }
    }
}

