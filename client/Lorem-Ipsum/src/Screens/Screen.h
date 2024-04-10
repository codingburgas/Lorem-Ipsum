#pragma once
#include "Core.h"

class Screen
{
public:
   Screen() { m_Scene = std::make_shared<Core::Scene>(); }
   virtual ~Screen() = default;

   virtual void RenderElements() = 0;
   virtual void RenderElementsOnResize() = 0;

   std::shared_ptr<Core::Scene> GetScene() { return m_Scene; }
   
protected:
   std::shared_ptr<Core::Scene> m_Scene;
};
