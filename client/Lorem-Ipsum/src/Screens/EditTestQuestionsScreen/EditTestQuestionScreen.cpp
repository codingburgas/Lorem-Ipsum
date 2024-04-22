#include "EditTestQuestionScreen.h"
#include "../Screens.h"
#include <cpr/cpr.h>

#define RAPIDJSON_HAS_STDSTRING 1
#include <rapidjson/document.h>
#include <rapidjson/writer.h>
#include <rapidjson/prettywriter.h>

void EditTestQuestionScreen::InitRenderElements()
{
    SideBar();
    MainContent();
}

void EditTestQuestionScreen::OnScreenChange()
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
        question.id = v["id"].GetInt();
        question.question = v["question"].GetString();
        question.answer = v["correct_answer"].GetString();
        question.optionA = v["anwer_a"].GetString();
        question.optionB = v["anwer_b"].GetString();
        question.optionC = v["anwer_c"].GetString();
        question.optionD = v["anwer_d"].GetString();
        
        m_Questions.push_back(question);
    }

    InitRenderElementsOnResize();
}

void EditTestQuestionScreen::HandleOverviewCallback(std::shared_ptr<Core::Entity> e)
{
    m_SwitchScreens(m_Screens->OverviewScreen);
}

void EditTestQuestionScreen::HandleSettingsCallback(std::shared_ptr<Core::Entity> e)
{
    m_SwitchScreens(m_Screens->SettingsScreen); 
}

void EditTestQuestionScreen::HandleDeleteQuestionCallback(std::shared_ptr<Core::Entity> e)
{
    cpr::Response r = cpr::Delete(
        cpr::Url{m_BaseUrl + "/question/" + e->GetComponent<Core::UIMetaInformation>().Meta},
        cpr::Header{{"Authorization", m_Token}}
    );

    if(r.status_code != 200)
    {
        return;
    }

    m_SwitchScreens(m_Screens->EditTestQuestionScreen);
}

void callbackeq(std::shared_ptr<Core::Entity> e)
{
}

void EditTestQuestionScreen::SideBar()
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

    Core::UI::Text("Account", {40, 271}, {0.42, 0.42, 0.44, 1.0}, 20, "regualar", m_Scene);

    Core::UI::Button("Settings", {35, 316}, {180, 45}, p_UnselectedButtonMaterial, HandleSettingsCallback, "assets/icons/settings-icon.png");
}

void EditTestQuestionScreen::MainContent()
{
    std::shared_ptr<Core::UI::ButtonMaterial> p_ButtonMaterial = std::make_shared<Core::UI::ButtonMaterial>();
    p_ButtonMaterial->Roundness = 0.25f;
    p_ButtonMaterial->Color = {0.49f, 0.53f, 0.98f, 1.0f};
    p_ButtonMaterial->TextColor = {1.0f, 1.0f, 1.0f, 1.0f};
    p_ButtonMaterial->TextSize = 18;
    p_ButtonMaterial->Scene = m_Scene;

    Core::UI::Text("Questions", {300, 100}, {0.0, 0.0, 0.0, 1.0}, 36, "bold", m_Scene); 
    
    for(size_t i = 0; i < m_Questions.size(); i++)
    {
        Core::UI::Text(m_Questions[i].question.c_str(), {300, 250 + i * 230 }, {0.0, 0.0, 0.0, 1.0}, 18, "bold", m_Scene);
        Core::UI::Text("A) " + m_Questions[i].optionA, {300, 280 + i * 230 }, {0.0, 0.0, 0.0, 1.0}, 18, "regular", m_Scene);
        Core::UI::Text("B) " + m_Questions[i].optionB, {300, 310 + i * 230 }, {0.0, 0.0, 0.0, 1.0}, 18, "regular", m_Scene);
        Core::UI::Text("C) " + m_Questions[i].optionC, {300, 340 + i * 230 }, {0.0, 0.0, 0.0, 1.0}, 18, "regular", m_Scene);
        Core::UI::Text("D) " + m_Questions[i].optionD, {300, 370 + i * 230 }, {0.0, 0.0, 0.0, 1.0}, 18, "regular", m_Scene);

        Core::UI::Text("Answer: " + m_Questions[i].answer, {300, 400 + i * 230 }, {0.0, 0.0, 0.0, 1.0}, 18, "regular", m_Scene);

        Core::UI::Button::ButtonWithMeta("Delete", {300, 430 + i * 230}, {100, 30}, p_ButtonMaterial, HandleDeleteQuestionCallback, std::to_string(i));
    }
}