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
         class Avatar
         {
         public:
             Avatar(glm::vec2 position, std::string imagePath, std::shared_ptr<Core::Scene> scene);
             ~Avatar() = default;
         };
    } 
}