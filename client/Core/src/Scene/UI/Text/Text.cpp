#include "pch.h"
#include "Text.h"

namespace Core 
{
    namespace UI 
    {
        Text::Text(std::string text, glm::vec2 position, glm::vec4 color, std::shared_ptr<Core::Scene> scene)
        {
            Entity textElement(scene);
            
            textElement.AddComponent<UIComponent>(text, color);
            textElement.AddComponent<TransformComponent>(glm::vec3(position.x, position.y, 0), glm::vec3(0.0f, 0.0f, 0.0f), 0.0, 0.0f);
            textElement.AddComponent<UITypeComponent>(UIType::TEXT);
        }

    } 
}
