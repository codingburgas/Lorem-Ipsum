#include "AttemptTestScreen.h"
#include "../Screens.h"
#include <cpr/cpr.h>

#define RAPIDJSON_HAS_STDSTRING 1
#include <rapidjson/document.h>
#include <rapidjson/writer.h>
#include <rapidjson/prettywriter.h>

void AttemptTestScreen::InitRenderElements()
{
    SideBar();
    MainContent();
}

void AttemptTestScreen::OnScreenChange()
{
    cpr::Response r = cpr::Get(
        cpr::Url{m_BaseUrl + "/questions/" + std::to_string(m_SelectedExamId)},
        cpr::Header{{"Authorization", m_Token}}
    );

    if(r.status_code != 200)
        return;

    rapidjson::Document questionsDocument;
    questionsDocument.Parse(r.text);

    m_Questions.clear();
    for (const auto& v : questionsDocument.GetArray()) {
        Question question;
        question.QuestionId = v["id"].GetInt();
        question.QuestionText = v["question"].GetString();
        question.Answer = v["correct_answer"].GetString();
        question.OptionA = v["anwer_a"].GetString();
        question.OptionB = v["anwer_b"].GetString();
        question.OptionC = v["anwer_c"].GetString();
        question.OptionD = v["anwer_d"].GetString();
        
        m_Questions.push_back(question);
    }

    InitRenderElementsOnResize();
}

void callbackATCallaback(std::shared_ptr<Core::Entity> e) {}

void AttemptTestScreen::SideBar()
{
    std::shared_ptr<Core::UI::ButtonMaterial> p_SettingsButtonMaterial = std::make_shared<Core::UI::ButtonMaterial>();
    p_SettingsButtonMaterial->Color = {0.0f, 0.46f, 0.98f, 1.0f};
    p_SettingsButtonMaterial->Roundness = 0.25f;
    p_SettingsButtonMaterial->TextSize = 22;
    p_SettingsButtonMaterial->Scene = m_Scene;

    std::shared_ptr<Core::UI::ButtonMaterial> p_UnselectedButtonMaterial = std::make_shared<Core::UI::ButtonMaterial>();
    p_UnselectedButtonMaterial->Color = {1.0f, 1.0f, 1.0f, 1.0f};
    p_UnselectedButtonMaterial->Roundness = 0.25f;
    p_UnselectedButtonMaterial->TextColor = {0.7f, 0.7f, 0.7f, 1.0f};
    p_UnselectedButtonMaterial->TextSize = 22;
    p_UnselectedButtonMaterial->Scene = m_Scene;

    Core::UI::Text("Menu", {40, 120}, {0.42, 0.42, 0.44, 1.0}, 20, "regualar", m_Scene);

    Core::UI::Button("Overview", {35, 157}, {180, 45}, p_SettingsButtonMaterial, HandleOverviewCallback, "assets/icons/home-icon.png");
    Core::UI::Button("Statistics", {35, 204}, {180, 45}, p_UnselectedButtonMaterial, callbackATCallaback, "assets/icons/stats-icon.png");

    Core::UI::Text("Account", {40, 271}, {0.42, 0.42, 0.44, 1.0}, 20, "regualar", m_Scene);

    Core::UI::Button("Messages", {35, 316}, {180, 45}, p_UnselectedButtonMaterial, callbackATCallaback, "assets/icons/chat-icon.png");
    Core::UI::Button("Settings", {35, 363}, {180, 45}, p_UnselectedButtonMaterial, HandleSettingsCallback, "assets/icons/settings-icon.png");
}

void AttemptTestScreen::HandleSelectQuestionAnswerCallback(std::shared_ptr<Core::Entity> e)
{
    if(e->HasComponent<Core::UIMetaInformation>())
    {
        uint32_t questionId = std::stoi(e->GetComponent<Core::UIMetaInformation>().Meta.substr(0, e->GetComponent<Core::UIMetaInformation>().Meta.find("&")));
        std::string answer = e->GetComponent<Core::UIMetaInformation>().Meta.substr(e->GetComponent<Core::UIMetaInformation>().Meta.find("&") + 1);

        rapidjson::Document document;
        document.SetObject();

        document.AddMember("answer", answer, document.GetAllocator());
        document.AddMember("question_id", questionId, document.GetAllocator());

        rapidjson::StringBuffer buffer;
        rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
        document.Accept(writer);

        cpr::Response r = cpr::Post(
            cpr::Url{m_BaseUrl + "/answer/create"},
            cpr::Header{{"Authorization", m_Token}},
            cpr::Body{buffer.GetString()}
        );

        if(r.status_code != 200)
            return;

        m_SelectedAnswers.push_back(questionId);

        m_SwitchScreens(m_Screens->AttemptTestScreen);
    }
}

void AttemptTestScreen::HandleSumitTestCallback(std::shared_ptr<Core::Entity> e)
{
    cpr::Response r = cpr::Post(
        cpr::Url{m_BaseUrl + "/score/create/" + std::to_string(m_SelectedExamId)},
        cpr::Header{{"Authorization", m_Token}}
    );

    if(r.status_code != 200)
        return;
    
    m_SwitchScreens(m_Screens->ThemesScreen);
}

void AttemptTestScreen::MainContent()
{
    std::shared_ptr<Core::UI::ButtonMaterial> p_ButtonMaterial = std::make_shared<Core::UI::ButtonMaterial>();
    p_ButtonMaterial->Roundness = 0.25f;
    p_ButtonMaterial->Color = {0.49f, 0.53f, 0.98f, 1.0f};
    p_ButtonMaterial->TextColor = {1.0f, 1.0f, 1.0f, 1.0f};
    p_ButtonMaterial->TextSize = 18;
    p_ButtonMaterial->Scene = m_Scene;
    
    Core::UI::Text("Attempt Test", {230, 100}, {0.0, 0.0, 0.0, 1.0}, 32, "bold", m_Scene);
    Core::UI::Text("Question answer once selected cannot be changed later", {230, 130}, {0.8, 0.2, 0.3, 1.0}, 26, "bold", m_Scene);

    for(size_t i = 0; i < m_Questions.size(); i++)
    {
        Core::UI::Text(m_Questions[i].QuestionText, {230, 190 + i * 150}, {0.0, 0.0, 0.0, 1.0}, 24, "regualar", m_Scene);

        bool isIncluded = false;
        for(auto& j : m_SelectedAnswers)
        {
            if(j == m_Questions[i].QuestionId)
            {
                isIncluded = true;
                break;
            }
        }

        if(!isIncluded)
        {
            p_ButtonMaterial->Color = {0.49f, 0.53f, 0.98f, 1.0f};
            Core::UI::Button::ButtonWithMeta(m_Questions[i].OptionA, {230, 230 + i * 150}, {MeasureText(m_Questions[i].OptionA.c_str(), p_ButtonMaterial->TextSize) + 10, 45}, p_ButtonMaterial, HandleSelectQuestionAnswerCallback, std::to_string(m_Questions[i].QuestionId) + "&a");
            Core::UI::Button::ButtonWithMeta(m_Questions[i].OptionB, {230, 285 + i * 150}, {MeasureText(m_Questions[i].OptionB.c_str(), p_ButtonMaterial->TextSize) + 10, 45}, p_ButtonMaterial, HandleSelectQuestionAnswerCallback), std::to_string(m_Questions[i].QuestionId) + "&b";
            
            Core::UI::Button::ButtonWithMeta(m_Questions[i].OptionC, {GetScreenWidth() - 230,  230 + i * 150}, {MeasureText(m_Questions[i].OptionC.c_str(), p_ButtonMaterial->TextSize) + 10, 45}, p_ButtonMaterial, HandleSelectQuestionAnswerCallback, std::to_string(m_Questions[i].QuestionId) + "&c");
            Core::UI::Button::ButtonWithMeta(m_Questions[i].OptionD, {GetScreenWidth() - 230, 285 + i * 150}, {MeasureText(m_Questions[i].OptionD.c_str(), p_ButtonMaterial->TextSize) + 10, 45}, p_ButtonMaterial, HandleSelectQuestionAnswerCallback, std::to_string(m_Questions[i].QuestionId) + "&d");
        }
        else
        {
            p_ButtonMaterial->Color = {0.7, 0.7, 0.7, 1.0};
            Core::UI::Button::ButtonWithMeta(m_Questions[i].OptionA, {230, 230 + i * 150}, {MeasureText(m_Questions[i].OptionA.c_str(), p_ButtonMaterial->TextSize) + 10, 45}, p_ButtonMaterial, callbackATCallaback, std::to_string(m_Questions[i].QuestionId) + "&a");
            Core::UI::Button::ButtonWithMeta(m_Questions[i].OptionB, {230, 285 + i * 150}, {MeasureText(m_Questions[i].OptionB.c_str(), p_ButtonMaterial->TextSize) + 10, 45}, p_ButtonMaterial, callbackATCallaback), std::to_string(m_Questions[i].QuestionId) + "&b";
            
            Core::UI::Button::ButtonWithMeta(m_Questions[i].OptionC, {GetScreenWidth() - 230,  230 + i * 150}, {MeasureText(m_Questions[i].OptionC.c_str(), p_ButtonMaterial->TextSize) + 10, 45}, p_ButtonMaterial, callbackATCallaback, std::to_string(m_Questions[i].QuestionId) + "&c");
            Core::UI::Button::ButtonWithMeta(m_Questions[i].OptionD, {GetScreenWidth() - 230, 285 + i * 150}, {MeasureText(m_Questions[i].OptionD.c_str(), p_ButtonMaterial->TextSize) + 10, 45}, p_ButtonMaterial, callbackATCallaback, std::to_string(m_Questions[i].QuestionId) + "&d");
        }
    }

    p_ButtonMaterial->Color = {0.49f, 0.53f, 0.98f, 1.0f};
    Core::UI::Button("Submit", {GetScreenWidth() / 2 - 45, m_Questions.size() * 150 + 290}, {180, 45}, p_ButtonMaterial, HandleSumitTestCallback);
}

void AttemptTestScreen::HandleOverviewCallback(std::shared_ptr<Core::Entity> e)
{
    m_SwitchScreens(m_Screens->OverviewScreen);
}

void AttemptTestScreen::HandleSettingsCallback(std::shared_ptr<Core::Entity> e)
{
    m_SwitchScreens(m_Screens->SettingsScreen);
}
