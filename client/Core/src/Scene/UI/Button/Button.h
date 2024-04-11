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
         class Button
         {
         public:
             Button(std::string text, glm::vec2 position, glm::vec2 dim, float roundness, glm::vec4 color, glm::vec4 textColor, std::shared_ptr<Core::Scene> scene, std::function<void()> callback);
             ~Button() = default;
         };
    }
}