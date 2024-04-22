#pragma once
#include "../../Components.h"
#include "Scene/Entity.h"

namespace Core 
{
    namespace UI 
    {
        class ButtonScript : public NativeScript
        {
        public:
            void OnUpdate() override;
            void OnCreate() override;

            void SetCallback(std::function<void(std::shared_ptr<Core::Entity>)> func) { m_Callback = func; }
        private:
            std::function<void(std::shared_ptr<Core::Entity>)> m_Callback;
            std::shared_ptr<ColorComponent> m_InitialColor;

            bool m_IsHovered = false;
        };
    }
}
