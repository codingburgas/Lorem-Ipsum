#pragma once
#include "Core.h"

class Screen
{
public:
   Screen() { m_Scene = std::make_shared<Core::Scene>(); }
   virtual ~Screen() = default;

   virtual void InitRenderElements() = 0;
    
   void InitRenderElementsOnResize();

   std::shared_ptr<Core::Scene> GetScene() { return m_Scene; }
   
   void SetSwitchBoundScene(std::function<void(std::shared_ptr<Screen>)> switchBoundScene) { m_SwitchBoundScene = switchBoundScene; }
   
protected:
   std::shared_ptr<Core::Scene> m_Scene;
   inline static std::function<void(std::shared_ptr<Screen>)> m_SwitchBoundScene;
};
