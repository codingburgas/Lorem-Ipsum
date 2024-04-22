#pragma once
#include "../Screen.h"

class NewExamScreen : public Screen
{
public:
    NewExamScreen() { InitRenderElements(); }
    ~NewExamScreen() = default;

    void InitRenderElements() override;

    void OnScreenChange() override;

private:
    static void HandleOverviewCallback(std::shared_ptr<Core::Entity> e);
    static void HandleSettingsCallback(std::shared_ptr<Core::Entity> e);

    static void HandleCreateExamCallback(std::shared_ptr<Core::Entity> e);
    static void HandleEnterExamNameCallback(std::string input, std::shared_ptr<Core::Entity> e);

    inline static std::string m_ExamName = "";

    void SideBar();
    void MainContent();
};