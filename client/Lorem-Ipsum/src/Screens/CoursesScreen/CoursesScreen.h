#pragma once
#include "../Screen.h"

class CoursesScreen : public Screen
{
public:
    CoursesScreen() { InitRenderElements(); }
    ~CoursesScreen() = default;

    void InitRenderElements() override;

    void OnScreenChange() override;
    
private:
    struct Course
    {
        uint32_t id;
        std::string name;
        std::string subject;
    };
    
    static void HandleOverviewCallback(std::shared_ptr<Core::Entity> e);
    static void HandleSettingsCallback(std::shared_ptr<Core::Entity> e);
    static void HandleCreateCourseCallback(std::shared_ptr<Core::Entity> e);
    static void HandleJoinCourseCallback(std::shared_ptr<Core::Entity> e);
    static void HandleCourseCallback(std::shared_ptr<Core::Entity> e);

    void SideBar();
    void MainContent();

    inline static std::string m_Code = "";

    inline static std::vector<Course> m_Courses;
};