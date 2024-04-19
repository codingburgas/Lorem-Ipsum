#pragma once
#include "Core.h"

class LandingScreen;
class RegisterScreen;
class LoginScreen;
class OverviewScreen;
class SettingsScreen;
class OrganizationScreen;

struct Screens
{
   std::shared_ptr<LandingScreen> LandingScreen;
   std::shared_ptr<RegisterScreen> RegisterScreen;
   std::shared_ptr<LoginScreen> LoginScreen;
   std::shared_ptr<OverviewScreen> OverviewScreen;
   std::shared_ptr<SettingsScreen> SettingsScreen;
   std::shared_ptr<OrganizationScreen> OrganizationScreen;
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
   virtual void OnScreenChange() {}

protected:
   
   struct User
   {
      std::string Username;
      std::string Email;
      std::string Name;
   };
   
   std::shared_ptr<Core::Scene> m_Scene;
   
   inline static std::shared_ptr<Screens> m_Screens;
   inline static std::function<void(std::shared_ptr<Screen>)> m_SwitchScreens;
   inline static std::string m_Token;
   inline static std::string m_BaseUrl = "http://localhost:3000";
   inline static std::shared_ptr<User> m_User;
    inline static uint32_t m_SelectedOrganization = 0;
};
