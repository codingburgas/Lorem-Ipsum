#pragma once
#include "../../Components.h"

namespace Core 
{
    namespace UI 
    {
        class ButtonScript : public NativeScript
        {
        public:
            void OnUpdate() override;
            void onLateAttach() override;

            void SetCallback(std::function<void()> func) { m_Callback = func; }
        private:
            std::function<void()> m_Callback;
            std::shared_ptr<ColorComponent> m_InitialColor;

            bool m_IsHovered = false;
        };
    }
}