#pragma once
#include "../Screen.h"

class OrganizationScreen : public Screen
{
public:
    OrganizationScreen() { InitRenderElements(); }
    ~OrganizationScreen() = default;

    void InitRenderElements() override;

private:
    inline static std::string m_OrganizationName;
    inline static std::string m_OrganizationCode;
    
    static void HandleOverviewCallback(std::shared_ptr<Core::Entity> e);
    static void HandleSettingsCallback(std::shared_ptr<Core::Entity> e);
    static void HandleOrganizationName(std::string orgName, std::shared_ptr<Core::Entity> e);
    static void HandleOrganizationCode(std::string code, std::shared_ptr<Core::Entity> e);
    static void HandleCreateaOrganizationCallback(std::shared_ptr<Core::Entity> e);
    static void HandleJoinOrganizationCallback(std::shared_ptr<Core::Entity> e);
    
    
    void SideBar();
    void MainContent();
};