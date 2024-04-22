#pragma once
#include "../Screen.h"

class CreateCourseScreen : public Screen
{
public:
    CreateCourseScreen() { InitRenderElements(); }
    ~CreateCourseScreen() = default;

    void InitRenderElements() override;

    void OnScreenChange() override;
    
private:
    static void HandleOverviewCallback(std::shared_ptr<Core::Entity> e);
    static void HandleSettingsCallback(std::shared_ptr<Core::Entity> e);
    static void HandleCreateCourseCallback(std::shared_ptr<Core::Entity> e);
    static void HandleEnterCourseNameCallback(std::string name, std::shared_ptr<Core::Entity> e);

    inline static std::string m_CourseName = "";

    void SideBar();
    void MainContent();
};