#pragma once
#include "../Screen.h"

class EditTestQuestionScreen : public Screen
{
public:
    EditTestQuestionScreen() { InitRenderElements(); }
    ~EditTestQuestionScreen() = default;

    void InitRenderElements() override;

    void OnScreenChange() override;

private:
    struct Question
    {
        uint32_t id;
        std::string question;
        std::string answer;
        std::string optionA;
        std::string optionB;
        std::string optionC;
        std::string optionD;
    };
    
    static void HandleOverviewCallback(std::shared_ptr<Core::Entity> e);
    static void HandleSettingsCallback(std::shared_ptr<Core::Entity> e);
    static void HandleDeleteQuestionCallback(std::shared_ptr<Core::Entity> e);

    inline static std::vector<Question> m_Questions;

    void SideBar();
    void MainContent();
};