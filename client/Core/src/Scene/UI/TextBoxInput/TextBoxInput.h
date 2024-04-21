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
        struct TextBoxInputMaterial
        {
            float Roundness = 0.0;
            glm::vec4 Color = {0.0f, 0.0f, 0.0f, 1.0f};
            glm::vec4 TextColor = {1.0f, 1.0f, 1.0f, 1.0f};
            uint32_t TextSize = 32;
            std::string FontType = "regular";
            std::shared_ptr<Core::Scene> Scene;
        };
        
        class TextedBoxInput
        {
        public:
            TextedBoxInput(glm::vec2 position, glm::vec2 dim, float roundness, glm::vec4 color, glm::vec4 textColor, uint32_t textSize, std::string fontType, std::function<void(std::string, std::shared_ptr<Core::Entity>)> callback, std::shared_ptr<Core::Scene> scene);
            TextedBoxInput(glm::vec2 position, glm::vec2 dim, std::function<void(std::string, std::shared_ptr<Core::Entity>)> callback, std::shared_ptr<TextBoxInputMaterial> inputMaterial);
            ~TextedBoxInput() = default;
        };
    }
}
