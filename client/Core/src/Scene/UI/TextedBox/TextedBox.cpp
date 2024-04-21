#include "pch.h"
#include "TextedBox.h"

namespace Core 
{
    namespace UI 
    {
        TextedBox::TextedBox(std::string text, glm::vec2 position, glm::vec2 dim, float roundness, glm::vec4 color, glm::vec4 textColor, uint32_t textSize, std::string fontType, std::shared_ptr<Core::Scene> scene)
        {
            Entity input(scene);
            input.AddComponent<UIComponent>(text, glm::vec4(textColor.r, textColor.g, textColor.b, textColor.a), textSize, fontType);
            input.AddComponent<TransformComponent>(glm::vec3(position.x, position.y, 0), glm::vec3(dim.x, dim.y, 0.0f), 0.0, roundness);
            input.AddComponent<ColorComponent>(color);
            input.AddComponent<UITypeComponent>(UIType::TEXTBOX);
            input.AddComponent<UIBorderComponent>(color);
        }

        TextedBox::TextedBox(std::string text, glm::vec2 position, glm::vec2 dim, std::shared_ptr<TextBoxMaterial> inputMaterial)
        {
            Entity input(inputMaterial->Scene);
            input.AddComponent<UIComponent>(text, glm::vec4(inputMaterial->TextColor.r, inputMaterial->TextColor.g, inputMaterial->TextColor.b, inputMaterial->TextColor.a), inputMaterial->TextSize, inputMaterial->FontType);
            input.AddComponent<TransformComponent>(glm::vec3(position.x, position.y, 0), glm::vec3(dim.x, dim.y, 0.0f), 0.0, inputMaterial->Roundness);
            input.AddComponent<ColorComponent>(inputMaterial->Color);
            input.AddComponent<UITypeComponent>(UIType::TEXTBOX);
            input.AddComponent<UIBorderComponent>(inputMaterial->Color);
        }
    } 
}
