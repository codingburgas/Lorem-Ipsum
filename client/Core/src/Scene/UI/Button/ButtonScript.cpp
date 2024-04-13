#include "pch.h"
#include "ButtonScript.h"

#include "Scene/Entity.h"

namespace Core 
{
    namespace UI 
    {
        void ButtonScript::onLateAttach()
        {
            ColorComponent& colorComponent = m_Entity->GetComponent<ColorComponent>();
            m_InitialColor = std::make_shared<ColorComponent>();
            
            m_InitialColor->Color.r = colorComponent.Color.r;
            m_InitialColor->Color.g = colorComponent.Color.g;
            m_InitialColor->Color.b = colorComponent.Color.b;
            m_InitialColor->Color.a = colorComponent.Color.a;
        }
        
        void ButtonScript::OnUpdate()
        {
            ColorComponent& colorComponent = m_Entity->GetComponent<ColorComponent>();
            TransformComponent& transformComponent = m_Entity->GetComponent<TransformComponent>();
            
            if(CheckCollisionPointRec(GetMousePosition(), {transformComponent.Position.x, transformComponent.Position.y, transformComponent.Scale.x, transformComponent.Scale.y}))
                m_IsHovered = true;
            else
                m_IsHovered = false;

            if(m_IsHovered)
            {
                colorComponent.Color.r = m_InitialColor->Color.r - m_InitialColor->Color.r * 0.20f;
                colorComponent.Color.g = m_InitialColor->Color.g - m_InitialColor->Color.g * 0.20f;
                colorComponent.Color.b = m_InitialColor->Color.b - m_InitialColor->Color.b * 0.20f;

                if(IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
                {
                    m_Callback();
                }
            }
            else
            {
                colorComponent = *m_InitialColor;
            }
        }
    }
}
