#pragma once
#include "Core.h"

class LandingScreen;
class RegisterScreen;
class LoginScreen;
class OverviewScreen;

struct Screens
{
   std::shared_ptr<LandingScreen> LandingScreen;
   std::shared_ptr<RegisterScreen> RegisterScreen;
   std::shared_ptr<LoginScreen> LoginScreen;
   std::shared_ptr<OverviewScreen> OverviewScreen;
};

class Screen
{
public:
   Screen() { m_Scene = std::make_shared<Core::Scene>(); }
   virtual ~Screen() = default;

   virtual void InitRenderElements() = 0;
    
   void InitRenderElementsOnResize();

   std::shared_ptr<Core::Scene> GetScene() { return m_Scene; }

   static void SetScreens(std::shared_ptr<Screens> screens) { m_Screens = screens; }
   static void SetSwitchScreen(std::function<void(std::shared_ptr<Screen>)> switchScreen) { m_SwitchScreens = switchScreen; }
   
protected: 
   std::shared_ptr<Core::Scene> m_Scene;
   
   inline static std::shared_ptr<Screens> m_Screens;
   inline static std::function<void(std::shared_ptr<Screen>)> m_SwitchScreens;
};
