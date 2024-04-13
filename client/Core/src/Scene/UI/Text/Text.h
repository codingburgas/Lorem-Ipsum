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
         class Text
         {
         public:
             Text(std::string text, glm::vec2 position, glm::vec4 color, uint32_t textSize, std::string fontType, std::shared_ptr<Core::Scene> scene);
             ~Text() = default;
         };
    } 
}
