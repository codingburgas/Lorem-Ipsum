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
        struct TextBoxMaterial
        {
            float Roundness = 0.0;
            glm::vec4 Color = {0.0f, 0.0f, 0.0f, 1.0f};
            glm::vec4 TextColor = {1.0f, 1.0f, 1.0f, 1.0f};
            uint32_t TextSize = 32;
            std::string FontType = "regular";
            std::shared_ptr<Core::Scene> Scene;
        };
        
        class TextedBox
        {
        public:
            TextedBox(std::string text, glm::vec2 position, glm::vec2 dim, float roundness, glm::vec4 color, glm::vec4 textColor, uint32_t textSize, std::string fontType, std::shared_ptr<Core::Scene> scene);
            TextedBox(std::string text, glm::vec2 position, glm::vec2 dim, std::shared_ptr<TextBoxMaterial> inputMaterial);
            ~TextedBox() = default;
        };
    }
}
