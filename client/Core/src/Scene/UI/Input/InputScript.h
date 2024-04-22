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
            void OnDestroy() override;

            void SetCallback(std::function<void(std::string, std::shared_ptr<Core::Entity> e)> func) { m_Callback = func; }
        private:
            std::function<void(std::string, std::shared_ptr<Core::Entity> e)> m_Callback;

            bool m_IsHovered = false;
            bool m_Selected = false;

            char m_Input[200];
            int32_t m_LetterCount = 0;
            int32_t m_Key;

            uint32_t m_DeleteDelay = 200;
        };
    }
}