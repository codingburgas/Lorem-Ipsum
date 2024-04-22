#pragma once
#include "../Screen.h"

class OverviewScreen : public Screen
{
public:
    OverviewScreen() { InitRenderElements(); }
    ~OverviewScreen() = default;

    void InitRenderElements() override;

    void OnScreenChange() override;

private:
    struct Organization
    {
        uint32_t id;
        std::string name; 
    };
    
    static void HandleSettings(std::shared_ptr<Core::Entity> e);
    static void HandleOrganizatoinsCallback(std::shared_ptr<Core::Entity> e);
    static void HandleOrganizationSelectedCallback(std::shared_ptr<Core::Entity> e);

    inline static std::vector<Organization> m_Organizations;
    
    void NavBar();
    void SideBar();
    void MainContent();
};