#include "pch.h"
#include "Button.h"
#include "ButtonScript.h"

namespace Core
{
    namespace UI
    {
        Button::Button(std::string text, glm::vec2 position, glm::vec2 dim, float roundness, glm::vec4 color, glm::vec4 textColor, uint32_t textSize, std::string fontType, std::shared_ptr<Core::Scene> scene, std::function<void(std::shared_ptr<Core::Entity>)> callback)
        {
            std::shared_ptr<ButtonScript> script = std::make_shared<ButtonScript>();
            script->SetCallback(callback);
            
            Entity button(scene);
            button.AddComponent<UIComponent>(text, textColor, textSize, fontType);
            button.AddComponent<TransformComponent>(glm::vec3(position.x, position.y, 0), glm::vec3(dim.x, dim.y, 0.0f), 0.0, roundness);
            button.AddComponent<ColorComponent>(color);
            button.AddComponent<NativeScriptComponent>(script, std::make_shared<Entity>(button));
            button.AddComponent<UITypeComponent>(UIType::BUTTON);
            script->OnCreate();
        }

        Button::Button(std::string text, glm::vec2 position, glm::vec2 dim, float roundness, glm::vec4 color, glm::vec4 textColor, uint32_t textSize, std::string fontType, std::string imagePath, std::shared_ptr<Core::Scene> scene, std::function<void(std::shared_ptr<Core::Entity>)> callback)
        {
            std::shared_ptr<ButtonScript> script = std::make_shared<ButtonScript>();
            script->SetCallback(callback);
            
            Entity button(scene);
            button.AddComponent<UIComponent>(text, textColor, textSize, fontType);
            button.AddComponent<TransformComponent>(glm::vec3(position.x, position.y, 0), glm::vec3(dim.x, dim.y, 0.0f), 0.0, roundness);
            button.AddComponent<ColorComponent>(color);
            button.AddComponent<NativeScriptComponent>(script, std::make_shared<Entity>(button));
            button.AddComponent<UITypeComponent>(UIType::BUTTON);
            button.AddComponent<SpriteComponent>(std::make_shared<Texture2D>(LoadTexture(imagePath.c_str())));
            script->OnCreate();
        }

        Button::Button(std::string text, glm::vec2 position, glm::vec2 dim, std::shared_ptr<ButtonMaterial> material, std::function<void(std::shared_ptr<Core::Entity>)> callback, std::string imagePath)
        {
            std::shared_ptr<ButtonScript> script = std::make_shared<ButtonScript>();
            script->SetCallback(callback);
            
            Entity button(material->Scene);
            button.AddComponent<UIComponent>(text, material->TextColor, material->TextSize, material->FontType);
            button.AddComponent<TransformComponent>(glm::vec3(position.x, position.y, 0), glm::vec3(dim.x, dim.y, 0.0f), 0.0, material->Roundness);
            button.AddComponent<ColorComponent>(material->Color);
            button.AddComponent<NativeScriptComponent>(script, std::make_shared<Entity>(button));
            button.AddComponent<UITypeComponent>(UIType::BUTTON);
            
            if(imagePath != "NONE")
                button.AddComponent<SpriteComponent>(std::make_shared<Texture2D>(LoadTexture(imagePath.c_str())));
            
            script->OnCreate();
            
        }

    }
}
