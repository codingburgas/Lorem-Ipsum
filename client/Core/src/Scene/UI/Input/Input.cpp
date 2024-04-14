#include "pch.h"
#include "Input.h"
#include "InputScript.h"

namespace Core 
{
    namespace UI 
    {
        Input::Input(glm::vec2 position, glm::vec2 dim, float roundness, glm::vec4 color, glm::vec4 textColor, uint32_t textSize, std::string fontType, std::shared_ptr<Core::Scene> scene, std::function<void(std::string)> callback, bool isSecure)
        {
            std::shared_ptr<InputScript> script = std::make_shared<InputScript>();
            script->SetCallback(callback);
            
            Entity input(scene);
            input.AddComponent<UIComponent>("", glm::vec4(textColor.r, textColor.g, textColor.b, textColor.a), textSize, fontType, isSecure);
            input.AddComponent<TransformComponent>(glm::vec3(position.x, position.y, 0), glm::vec3(dim.x, dim.y, 0.0f), 0.0, roundness);
            input.AddComponent<ColorComponent>(color);
            input.AddComponent<NativeScriptComponent>(script, std::make_shared<Entity>(input));
            input.AddComponent<UITypeComponent>(UIType::INPUT);
            input.AddComponent<UIBorderComponent>(color);
        }

        Input::Input(glm::vec2 position, glm::vec2 dim, std::shared_ptr<InputMaterial> inputMaterial, std::function<void(std::string)> callback, bool isSecure)
        {
            std::shared_ptr<InputScript> script = std::make_shared<InputScript>();
            script->SetCallback(callback);
            
            Entity input(inputMaterial->Scene);
            input.AddComponent<UIComponent>("", glm::vec4(inputMaterial->TextColor.r, inputMaterial->TextColor.g, inputMaterial->TextColor.b, inputMaterial->TextColor.a), inputMaterial->TextSize, inputMaterial->FontType, isSecure);
            input.AddComponent<TransformComponent>(glm::vec3(position.x, position.y, 0), glm::vec3(dim.x, dim.y, 0.0f), 0.0, inputMaterial->Roundness);
            input.AddComponent<ColorComponent>(inputMaterial->Color);
            input.AddComponent<NativeScriptComponent>(script, std::make_shared<Entity>(input));
            input.AddComponent<UITypeComponent>(UIType::INPUT);
            input.AddComponent<UIBorderComponent>(inputMaterial->Color);
        }
    } 
}
