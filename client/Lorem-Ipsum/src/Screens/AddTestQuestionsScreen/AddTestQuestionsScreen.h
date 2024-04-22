#pragma once
#include "../Screen.h"

class AddTestQuestionsScreen : public Screen
{
public:
    AddTestQuestionsScreen() { InitRenderElements(); }
    ~AddTestQuestionsScreen() = default;

    void InitRenderElements() override;

    void OnScreenChange() override;

private:
    static void HandleOverviewCallback(std::shared_ptr<Core::Entity> e);
    static void HandleSettingsCallback(std::shared_ptr<Core::Entity> e);
    static void HandleCreateQuestionCallback(std::shared_ptr<Core::Entity> e);
    
    static void HandleEnterQuestionCallback(std::string input, std::shared_ptr<Core::Entity> e);
    static void HandleEnterAnswerCallback(std::string input, std::shared_ptr<Core::Entity> e);
    
    static void HandleEnterOptionAnswerACallback(std::string input, std::shared_ptr<Core::Entity> e);
    static void HandleEnterOptionAnswerBCallback(std::string input, std::shared_ptr<Core::Entity> e);
    static void HandleEnterOptionAnswerCCallback(std::string input, std::shared_ptr<Core::Entity> e);
    static void HandleEnterOptionAnswerDCallback(std::string input, std::shared_ptr<Core::Entity> e);

    static void HandleEditQuestionCallback(std::shared_ptr<Core::Entity> e);

    inline static std::string m_Question = "";
    inline static std::string m_Answer = "";
    inline static std::string m_CorrectAnswer = "";
    
    inline static std::string m_OptionAnswerA = "";
    inline static std::string m_OptionAnswerB = "";
    inline static std::string m_OptionAnswerC = "";
    inline static std::string m_OptionAnswerD = "";

    inline static std::string m_TestName = "";

    void SideBar();
    void MainContent();
};
