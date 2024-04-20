#pragma once
#include "../Screen.h"

class JoinCourseScreen : public Screen
{
public:
    JoinCourseScreen() { InitRenderElements(); }
    ~JoinCourseScreen() = default;

    void InitRenderElements() override;

    void OnScreenChange() override;
    
private:
    static void HandleOverviewCallback(std::shared_ptr<Core::Entity> e);
    static void HandleSettingsCallback(std::shared_ptr<Core::Entity> e);
    static void HandleJoinCourseCallback(std::shared_ptr<Core::Entity> e);
    static void HandleEnterCourseCodeCallback(std::string name, std::shared_ptr<Core::Entity> e);

    inline static std::string m_CourseCode = "";

    void SideBar();
    void MainContent();
};