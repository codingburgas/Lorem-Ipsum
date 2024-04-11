#pragma once
#include "../../Components.h"
#include "pch.h"

namespace Core 
{
    namespace UI 
    {
        class InputScript : public NativeScript
        {
        public:
            void OnUpdate() override;
            void onLateAttach() override;

            void SetCallback(std::function<void(std::string)> func) { m_Callback = func; }
        private:
            std::function<void(std::string)> m_Callback;

            bool m_IsHovered = false;

            char m_Input[200];
            int32_t m_LetterCount = 0;
            int32_t m_Key;
        };
    }
}