#include "pch.h"
#include "TextBoxInput.h"
#include "TextBoxInputScript.h"

namespace Core 
{
    namespace UI 
    {
        TextedBoxInput::TextedBoxInput(glm::vec2 position, glm::vec2 dim, float roundness, glm::vec4 color, glm::vec4 textColor, uint32_t textSize, std::string fontType, std::function<void(std::string, std::shared_ptr<Core::Entity>)> callback, std::shared_ptr<Core::Scene> scene)
        {
            std::shared_ptr<TextBoxInputScript> script = std::make_shared<TextBoxInputScript>();
            script->SetCallback(callback);
            
            Entity input(scene);
            input.AddComponent<UIComponent>("", glm::vec4(textColor.r, textColor.g, textColor.b, textColor.a), textSize, fontType);
            input.AddComponent<TransformComponent>(glm::vec3(position.x, position.y, 0), glm::vec3(dim.x, dim.y, 0.0f), 0.0, roundness);
            input.AddComponent<ColorComponent>(color);
            input.AddComponent<UITypeComponent>(UIType::TEXTBOX);
            input.AddComponent<NativeScriptComponent>(script, std::make_shared<Entity>(input));
            input.AddComponent<UIBorderComponent>(color);
        }

        TextedBoxInput::TextedBoxInput(glm::vec2 position, glm::vec2 dim, std::function<void(std::string, std::shared_ptr<Core::Entity>)> callback, std::shared_ptr<TextBoxInputMaterial> inputMaterial)
        {
            std::shared_ptr<TextBoxInputScript> script = std::make_shared<TextBoxInputScript>();
            script->SetCallback(callback);
            
            Entity input(inputMaterial->Scene);
            input.AddComponent<UIComponent>("", glm::vec4(inputMaterial->TextColor.r, inputMaterial->TextColor.g, inputMaterial->TextColor.b, inputMaterial->TextColor.a), inputMaterial->TextSize, inputMaterial->FontType);
            input.AddComponent<TransformComponent>(glm::vec3(position.x, position.y, 0), glm::vec3(dim.x, dim.y, 0.0f), 0.0, inputMaterial->Roundness);
            input.AddComponent<ColorComponent>(inputMaterial->Color);
            input.AddComponent<UITypeComponent>(UIType::TEXTBOX);
            input.AddComponent<NativeScriptComponent>(script, std::make_shared<Entity>(input));
            input.AddComponent<UIBorderComponent>(inputMaterial->Color);
        }
    } 
}
