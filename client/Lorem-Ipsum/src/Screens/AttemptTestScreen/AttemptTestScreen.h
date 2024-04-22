#pragma once
#include "../Screen.h"

class AttemptTestScreen : public Screen
{
public:
    AttemptTestScreen() { InitRenderElements(); }
    ~AttemptTestScreen() = default;

    void InitRenderElements() override;

    void OnScreenChange() override;

private:
    static void HandleOverviewCallback(std::shared_ptr<Core::Entity> e);
    static void HandleSettingsCallback(std::shared_ptr<Core::Entity> e);

    static void HandleSelectQuestionAnswerCallback(std::shared_ptr<Core::Entity> e);
    static void HandleSumitTestCallback(std::shared_ptr<Core::Entity> e);

    struct Question
    {
        int QuestionId;
        std::string QuestionText;
        std::string Answer;
        std::string OptionA;
        std::string OptionB;
        std::string OptionC;
        std::string OptionD;
    };

    inline static std::vector<Question> m_Questions;

    inline static std::vector<uint32_t> m_SelectedAnswers;
    
    void SideBar();
    void MainContent();
};