﻿#include "pch.h"
#include "TextBoxInputScript.h"
#include "../../Entity.h"

namespace Core
{
    namespace UI
    {
        void TextBoxInputScript::onLateAttach()
        {
            m_Input[2999] = '\0';
        }

        void TextBoxInputScript::OnDestroy()
        {
            m_Input[0] = '\0';
            m_Entity->GetComponent<UIComponent>().Text = "";
        }
        
        void TextBoxInputScript::OnUpdate()
        {
            ColorComponent& colorComponent = m_Entity->GetComponent<ColorComponent>();
            TransformComponent& transformComponent = m_Entity->GetComponent<TransformComponent>();
            UIComponent& uiComponent = m_Entity->GetComponent<UIComponent>();
            
            if(CheckCollisionPointRec(GetMousePosition(), {transformComponent.Position.x, transformComponent.Position.y, transformComponent.Scale.x, transformComponent.Scale.y}))
                m_IsHovered = true;
            else
                m_IsHovered = false;

            if(m_IsHovered && IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
                m_Selected = true;
            else if(IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
                m_Selected = false;

            if(m_Selected)
            {
                m_Key = GetCharPressed();

                while(m_Key > 0)
                {
                    m_Input[m_LetterCount] = (char)m_Key;
                    m_Input[m_LetterCount + 1] = '\0';
                    m_LetterCount++;

                    m_Key = GetCharPressed();
                }
                
                if(IsKeyPressed(KEY_ENTER))
                {
                    m_Input[m_LetterCount] = '\n';
                    m_Input[m_LetterCount + 1] = '\0';
                    m_LetterCount++;
                }

                if(m_DeleteDelay == 0)
                {
                    if(IsKeyDown(KEY_BACKSPACE))
                    {
                        m_LetterCount--;
                        
                        if (m_LetterCount < 0)
                            m_LetterCount = 0;
                        
                        m_Input[m_LetterCount] = '\0';

                        m_DeleteDelay = 200;
                    }
                }
                else
                {
                    m_DeleteDelay -= 1;
                }

                uiComponent.Text = m_Input;

                m_Entity->GetComponent<UIBorderComponent>().Color = {152, 71, 255, 255};
                
                m_Callback(m_Input, m_Entity);
            }
            else
            {
                m_Entity->GetComponent<UIBorderComponent>().Color = {colorComponent.Color.r, colorComponent.Color.b, colorComponent.Color.g, colorComponent.Color.a};
            }
        }

    } 
}