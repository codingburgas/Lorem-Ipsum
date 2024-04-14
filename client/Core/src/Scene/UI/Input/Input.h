#pragma once
#include "pch.h"

#include "../../Components.h"
#include "Scene/Scene.h"
#include "../../Entity.h"

#include <raylib.h>

namespace Core
{
    namespace UI
    {
        struct InputMaterial
        {
            float Roundness = 0.0;
            glm::vec4 Color = {0.0f, 0.0f, 0.0f, 1.0f};
            glm::vec4 TextColor = {1.0f, 1.0f, 1.0f, 1.0f};
            uint32_t TextSize = 32;
            std::string FontType = "regular";
            std::shared_ptr<Core::Scene> Scene;
        };
        
        class Input
        {
        public:
            Input(glm::vec2 position, glm::vec2 dim, float roundness, glm::vec4 color, glm::vec4 textColor, uint32_t textSize, std::string fontType, std::shared_ptr<Core::Scene> scene, std::function<void(std::string)> callback, bool isSecure = false);
            Input(glm::vec2 position, glm::vec2 dim, std::shared_ptr<InputMaterial> inputMaterial, std::function<void(std::string)> callback, bool isSecure = false);
            ~Input() = default;
        };
    }
}
