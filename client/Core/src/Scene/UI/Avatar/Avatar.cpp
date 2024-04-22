#include "pch.h"
#include "Avatar.h"

namespace Core 
{
    namespace UI 
    {
        Avatar::Avatar(glm::vec2 position, std::string imagePath, std::shared_ptr<Core::Scene> scene)
        {
            Entity avatarElement(scene);

            Image image = LoadImage(imagePath.c_str());
            ImageResize(&image, 48, 48);
            // ImageDrawCircleV(&image, {32, 32}, 32, WHITE);
            
            avatarElement.AddComponent<UIComponent>();
            avatarElement.AddComponent<TransformComponent>(glm::vec3(position.x, position.y, 0), glm::vec3(0.0f, 0.0f, 0.0f), 0.0, 0.0f);
            avatarElement.AddComponent<SpriteComponent>(std::make_shared<Texture2D>(LoadTextureFromImage(image)));
            avatarElement.AddComponent<UITypeComponent>(UIType::AVATAR);
        }

    }
}