#include "AddTestQuestionsScreen.h"
#include "../Screens.h"
#include <cpr/cpr.h>

#define RAPIDJSON_HAS_STDSTRING 1
#include <rapidjson/document.h>
#include <rapidjson/writer.h>
#include <rapidjson/prettywriter.h>

void callbackAddquestion(std::shared_ptr<Core::Entity> e) {}

void AddTestQuestionsScreen::InitRenderElements()
{
    SideBar();
    MainContent();
}

void AddTestQuestionsScreen::MainContent()
{
    Core::UI::Text(m_TestName.c_str(), {315, 100}, {0.0, 0.0, 0.0, 1.0f}, 30, "regular", m_Scene);
    Core::UI::Text("Enter your question", {GetScreenWidth() / 2 + 180 - MeasureText("Enter your question", 24), 150}, {0.0, 0.0, 0.0, 1.0f}, 24, "regular", m_Scene);
    Core::UI::Input({GetScreenWidth() / 2 - 148, 200}, {400, 50}, 0.25, {0.84, 0.84, 0.84, 1.0f}, {0.0, 0.0, 0.0, 1.0f}, 20, "regular", m_Scene, HandleEnterQuestionCallback);

    Core::UI::Text("Enter answer option A", {GetScreenWidth() / 2 + 185 - MeasureText("Enter answer option A", 24), 270}, {0.0, 0.0, 0.0, 1.0f}, 24, "regular", m_Scene);
    Core::UI::Input({GetScreenWidth() / 2 - 148, 310}, {400, 50}, 0.25, {0.84, 0.84, 0.84, 1.0f}, {0.0, 0.0, 0.0, 1.0f}, 20, "regular", m_Scene, HandleEnterOptionAnswerACallback);
    
    Core::UI::Text("Enter answer option B", {GetScreenWidth() / 2 + 185 - MeasureText("Enter answer option B", 24), 380}, {0.0, 0.0, 0.0, 1.0f}, 24, "regular", m_Scene);
    Core::UI::Input({GetScreenWidth() / 2 - 148, 420}, {400, 50}, 0.25, {0.84, 0.84, 0.84, 1.0f}, {0.0, 0.0, 0.0, 1.0f}, 20, "regular", m_Scene, HandleEnterOptionAnswerBCallback);

    Core::UI::Text("Enter answer option C", {GetScreenWidth() / 2 + 185 - MeasureText("Enter answer option C", 24), 490}, {0.0, 0.0, 0.0, 1.0f}, 24, "regular", m_Scene);
    Core::UI::Input({GetScreenWidth() / 2 - 148, 530}, {400, 50}, 0.25, {0.84, 0.84, 0.84, 1.0f}, {0.0, 0.0, 0.0, 1.0f}, 20, "regular", m_Scene, HandleEnterOptionAnswerCCallback);

    Core::UI::Text("Enter answer option D", {GetScreenWidth() / 2 + 185 - MeasureText("Enter answer option D", 24), 600}, {0.0, 0.0, 0.0, 1.0f}, 24, "regular", m_Scene);
    Core::UI::Input({GetScreenWidth() / 2 - 148, 640}, {400, 50}, 0.25, {0.84, 0.84, 0.84, 1.0f}, {0.0, 0.0, 0.0, 1.0f}, 20, "regular", m_Scene, HandleEnterOptionAnswerDCallback);
    
    Core::UI::Text("Enter answer a, b, c, d", {GetScreenWidth() / 2 + 185 - MeasureText("Enter answer a, b, c, d", 24), 710}, {0.0, 0.0, 0.0, 1.0f}, 24, "regular", m_Scene);
    Core::UI::Input({GetScreenWidth() / 2 - 148, 750}, {400, 50}, 0.25, {0.84, 0.84, 0.84, 1.0f}, {0.0, 0.0, 0.0, 1.0f}, 20, "regular", m_Scene, HandleEnterAnswerCallback);

    std::shared_ptr<Core::UI::ButtonMaterial> p_ButtonMaterial = std::make_shared<Core::UI::ButtonMaterial>();
    p_ButtonMaterial->Roundness = 0.25f;
    p_ButtonMaterial->Color = {0.49f, 0.53f, 0.98f, 1.0f};
    p_ButtonMaterial->TextColor = {1.0f, 1.0f, 1.0f, 1.0f};
    p_ButtonMaterial->TextSize = 18;
    p_ButtonMaterial->Scene = m_Scene;

    Core::UI::Button("Create Question", {GetScreenWidth() / 2 - 180 / 2 + 25, 850}, {180, 30}, p_ButtonMaterial, HandleCreateQuestionCallback);
    Core::UI::Button("Edit Questions", {GetScreenWidth() / 2 - 180 / 2 + 25, 890}, {180, 30}, p_ButtonMaterial, HandleEditQuestionCallback);
}

void AddTestQuestionsScreen::HandleEditQuestionCallback(std::shared_ptr<Core::Entity> e)
{
    m_SwitchScreens(m_Screens->EditTestQuestionScreen);
}

void AddTestQuestionsScreen::OnScreenChange()
{
    cpr::Response r = cpr::Get(
        cpr::Url{m_BaseUrl + "/test/" + std::to_string(m_SelectedExamId)},
        cpr::Header{{"Authorization", m_Token}}
    );

    if(r.status_code != 200)
        return;

    rapidjson::Document d;
    d.Parse(r.text);

    m_TestName = d["title"].GetString();

    InitRenderElementsOnResize();
}

void AddTestQuestionsScreen::HandleOverviewCallback(std::shared_ptr<Core::Entity> e)
{
    m_SwitchScreens(m_Screens->OverviewScreen);
}

void AddTestQuestionsScreen::HandleSettingsCallback(std::shared_ptr<Core::Entity> e)
{
    m_SwitchScreens(m_Screens->SettingsScreen);
}

void AddTestQuestionsScreen::HandleCreateQuestionCallback(std::shared_ptr<Core::Entity> e)
{
    rapidjson::Document d;
    d.SetObject();
    
    d.AddMember("test_id", m_SelectedExamId, d.GetAllocator());
    d.AddMember("question", m_Question, d.GetAllocator());
    d.AddMember("correct_answer", m_Answer, d.GetAllocator());
    d.AddMember("answer_a", m_OptionAnswerA, d.GetAllocator());
    d.AddMember("answer_b", m_OptionAnswerB, d.GetAllocator());
    d.AddMember("answer_c", m_OptionAnswerC, d.GetAllocator());
    d.AddMember("answer_d", m_OptionAnswerD, d.GetAllocator());

    rapidjson::StringBuffer buffer;
    rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
    d.Accept(writer);

    cpr::Response r = cpr::Post(
        cpr::Url{m_BaseUrl + "/question/create"},
        cpr::Header{{"Authorization", m_Token}},
        cpr::Body{buffer.GetString()}
    );

    if(r.status_code != 200)
    {
        return;
    }

    m_SwitchScreens(m_Screens->AddTestQuestionsScreen);
}

void AddTestQuestionsScreen::HandleEnterQuestionCallback(std::string input, std::shared_ptr<Core::Entity> e)
{
    m_Question = input;
}

void AddTestQuestionsScreen::HandleEnterAnswerCallback(std::string input, std::shared_ptr<Core::Entity> e)
{
    m_Answer = input;
}

void AddTestQuestionsScreen::HandleEnterOptionAnswerACallback(std::string input, std::shared_ptr<Core::Entity> e)
{
    m_OptionAnswerA = input;
}

void AddTestQuestionsScreen::HandleEnterOptionAnswerBCallback(std::string input, std::shared_ptr<Core::Entity> e)
{
    m_OptionAnswerB = input;
}

void AddTestQuestionsScreen::HandleEnterOptionAnswerCCallback(std::string input, std::shared_ptr<Core::Entity> e)
{
    m_OptionAnswerC = input;
}

void AddTestQuestionsScreen::HandleEnterOptionAnswerDCallback(std::string input, std::shared_ptr<Core::Entity> e)
{
    m_OptionAnswerD = input;
}

void AddTestQuestionsScreen::SideBar()
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
    Core::UI::Button("Statistics", {35, 204}, {180, 45}, p_UnselectedButtonMaterial, callbackAddquestion, "assets/icons/stats-icon.png");

    Core::UI::Text("Account", {40, 271}, {0.42, 0.42, 0.44, 1.0}, 20, "regualar", m_Scene);

    Core::UI::Button("Messages", {35, 316}, {180, 45}, p_UnselectedButtonMaterial, callbackAddquestion, "assets/icons/chat-icon.png");
    Core::UI::Button("Settings", {35, 363}, {180, 45}, p_UnselectedButtonMaterial, HandleSettingsCallback, "assets/icons/settings-icon.png");
}