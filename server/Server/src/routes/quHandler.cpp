#include "quHandler.hpp"

#define RAPIDJSON_HAS_STDSTRING 1
#include <rapidjson/document.h>
#include <rapidjson/writer.h>
#include <rapidjson/stringbuffer.h>
#include "../dataAccess/models/questionModel.hpp"
#include "../businessLogic/courseService.hpp"
#include "../businessLogic/testService.hpp"
#include "../businessLogic/themeService.hpp"
#include "../businessLogic/authService.hpp"
#include "../businessLogic/questionService.hpp"
#include "../dataAccess/repos/themeHeader.hpp"


void QuestionHandler::CreateQuestion(const Pistache::Rest::Request& request, Pistache::Http::ResponseWriter response) 
{
    std::string token = request.headers().getRaw("Authorization").value();

    if (!UserService::ValidateToken(token)) {
        response.headers().add<Pistache::Http::Header::AccessControlAllowOrigin>("*");
        response.send(Pistache::Http::Code::Unauthorized, "Unauthorized");
        return;
    }   

    rapidjson::Document document;
    document.Parse(request.body().c_str());
 
    QuestionInput quInputModel;
    quInputModel.testId = document["test_id"].GetInt();
    quInputModel.question = document["question"].GetString();
    quInputModel.correctAnswer = document["correct_answer"].GetString();
    quInputModel.answerA = document["answer_a"].GetString();
    quInputModel.answerB = document["answer_b"].GetString();
    quInputModel.answerC = document["answer_c"].GetString();
    quInputModel.answerD = document["answer_d"].GetString();

    Question qu = QuestionsService::RegisterQuestion(quInputModel, quInputModel.testId);
 
    response.headers().add<Pistache::Http::Header::AccessControlAllowOrigin>("*");
    response.send(Pistache::Http::Code::Ok, "Question created!");
}

void QuestionHandler::GetQuestion(const Pistache::Rest::Request& request, Pistache::Http::ResponseWriter response) 
{
    std::string token = request.headers().getRaw("Authorization").value();

    if (!UserService::ValidateToken(token)) {
        response.headers().add<Pistache::Http::Header::AccessControlAllowOrigin>("*");
        response.send(Pistache::Http::Code::Unauthorized, "Unauthorized");
        return;
    }

    uint32_t questionId = request.param(":id").as<int>();

    Question qu = QuestionsService::GetQuestion(questionId);

    rapidjson::Document document;
    document.SetObject();

    document.AddMember("id", qu.id, document.GetAllocator());
    document.AddMember("test_id", qu.testId, document.GetAllocator());
    document.AddMember("question", rapidjson::Value().SetString(qu.question.c_str(), qu.question.size(), document.GetAllocator()), document.GetAllocator());
    document.AddMember("correct_answer", rapidjson::Value().SetString(qu.correctAnswer.c_str(), qu.correctAnswer.size(), document.GetAllocator()), document.GetAllocator());
    document.AddMember("answer_a", rapidjson::Value().SetString(qu.answerA.c_str(), qu.answerA.size(), document.GetAllocator()), document.GetAllocator());
    document.AddMember("answer_b", rapidjson::Value().SetString(qu.answerB.c_str(), qu.answerB.size(), document.GetAllocator()), document.GetAllocator());
    document.AddMember("answer_c", rapidjson::Value().SetString(qu.answerC.c_str(), qu.answerC.size(), document.GetAllocator()), document.GetAllocator());
    document.AddMember("answer_d", rapidjson::Value().SetString(qu.answerD.c_str(), qu.answerD.size(), document.GetAllocator()), document.GetAllocator());
    

    rapidjson::StringBuffer strbuf;
    rapidjson::Writer<rapidjson::StringBuffer> writer(strbuf);
    document.Accept(writer);

    response.headers().add<Pistache::Http::Header::AccessControlAllowOrigin>("*");
    response.send(Pistache::Http::Code::Ok, strbuf.GetString());
}


void QuestionHandler::GetQuestions(const Pistache::Rest::Request& request, Pistache::Http::ResponseWriter response) 
{
    std::string token = request.headers().getRaw("Authorization").value();

    if (!UserService::ValidateToken(token)) {
        response.headers().add<Pistache::Http::Header::AccessControlAllowOrigin>("*");
        response.send(Pistache::Http::Code::Unauthorized, "Unauthorized");
        return;
    }
    
    uint32_t id = request.param(":id").as<int>();;
    
    std::vector<Question> quest = QuestionsService::GetQuestions(id);
    rapidjson::Document document;
    document.SetArray();
    for (size_t i = 0; i < quest.size(); i++) {
        rapidjson::Value qu(rapidjson::kObjectType);
        qu.AddMember("id", quest[i].id, document.GetAllocator());
        qu.AddMember("test_id", quest[i].testId, document.GetAllocator());
        qu.AddMember("question", rapidjson::Value().SetString(quest[i].question.c_str(), quest[i].question.size(), document.GetAllocator()), document.GetAllocator());
        qu.AddMember("correct_answer", rapidjson::Value().SetString(quest[i].correctAnswer.c_str(), quest[i].correctAnswer.size(), document.GetAllocator()), document.GetAllocator());
        qu.AddMember("anwer_a", rapidjson::Value().SetString(quest[i].answerA.c_str(), quest[i].answerA.size(), document.GetAllocator()), document.GetAllocator());
        qu.AddMember("anwer_b", rapidjson::Value().SetString(quest[i].answerB.c_str(), quest[i].answerB.size(), document.GetAllocator()), document.GetAllocator());
        qu.AddMember("anwer_c", rapidjson::Value().SetString(quest[i].answerC.c_str(), quest[i].answerC.size(), document.GetAllocator()), document.GetAllocator());
        qu.AddMember("anwer_d", rapidjson::Value().SetString(quest[i].answerD.c_str(), quest[i].answerD.size(), document.GetAllocator()), document.GetAllocator());
        

        document.PushBack(qu, document.GetAllocator());
    }

    rapidjson::StringBuffer strbuf;
    rapidjson::Writer<rapidjson::StringBuffer> writer(strbuf);
    document.Accept(writer);

    response.headers().add<Pistache::Http::Header::AccessControlAllowOrigin>("*");
    response.send(Pistache::Http::Code::Ok, strbuf.GetString());
}