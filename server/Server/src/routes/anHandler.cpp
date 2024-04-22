#include "anHandler.hpp"

#define RAPIDJSON_HAS_STDSTRING 1
#include <rapidjson/document.h>
#include <rapidjson/writer.h>
#include <rapidjson/stringbuffer.h>
#include "../dataAccess/models/questionModel.hpp"
#include "../businessLogic/courseService.hpp"
#include "../businessLogic/testService.hpp"
#include "../businessLogic/themeService.hpp"
#include "../businessLogic/authService.hpp"
#include "../businessLogic/answersService.hpp"
#include "../dataAccess/repos/questionsHeader.hpp"


void AnswersHandler::CreateAnswer(const Pistache::Rest::Request& request, Pistache::Http::ResponseWriter response) 
{
    std::string token = request.headers().getRaw("Authorization").value();

    if (!UserService::ValidateToken(token)) {
        response.headers().add<Pistache::Http::Header::AccessControlAllowOrigin>("*");
        response.send(Pistache::Http::Code::Unauthorized, "Unauthorized");
        return;
    }   

    rapidjson::Document document;
    document.Parse(request.body().c_str());
 
    AnswersInput answerInputModel;
    answerInputModel.answer = document["answer"].GetString();
    answerInputModel.questionId = document["question_id"].GetInt();
    

    Answers answer = AnswersService::RegisterAnswers(answerInputModel, answerInputModel.questionId, token);
 
    response.headers().add<Pistache::Http::Header::AccessControlAllowOrigin>("*");
    response.send(Pistache::Http::Code::Ok, "Answer created!");
}

void AnswersHandler::GetAnswer(const Pistache::Rest::Request& request, Pistache::Http::ResponseWriter response) 
{
    std::string token = request.headers().getRaw("Authorization").value();

    if (!UserService::ValidateToken(token)) {
        response.headers().add<Pistache::Http::Header::AccessControlAllowOrigin>("*");
        response.send(Pistache::Http::Code::Unauthorized, "Unauthorized");
        return;
    }

    uint32_t answerId = request.param(":id").as<int>();

    Answers an = AnswersService::GetAnswer(answerId);

    rapidjson::Document document;
    document.SetObject();

    document.AddMember("id", an.id, document.GetAllocator());
    document.AddMember("answer", rapidjson::Value().SetString(an.answer.c_str(), an.answer.size(), document.GetAllocator()), document.GetAllocator());
    document.AddMember("question_id", an.questionId, document.GetAllocator());
    document.AddMember("user_id", an.userId, document.GetAllocator());

    rapidjson::StringBuffer strbuf;
    rapidjson::Writer<rapidjson::StringBuffer> writer(strbuf);
    document.Accept(writer);

    response.headers().add<Pistache::Http::Header::AccessControlAllowOrigin>("*");
    response.send(Pistache::Http::Code::Ok, strbuf.GetString());
}
void AnswersHandler::GetAnswerByQuestionId(const Pistache::Rest::Request& request, Pistache::Http::ResponseWriter response) 
{
    std::string token = request.headers().getRaw("Authorization").value();

    if (!UserService::ValidateToken(token)) {
        response.headers().add<Pistache::Http::Header::AccessControlAllowOrigin>("*");
        response.send(Pistache::Http::Code::Unauthorized, "Unauthorized");
        return;
    }
    
    uint32_t quId = request.param(":id").as<int>();

    Answers an = AnswersService::GetAnswerByQuestionId(quId,token);
    
    rapidjson::Document document;
    document.SetObject();
    
    document.AddMember("id", an.id, document.GetAllocator());
    document.AddMember("answer", rapidjson::Value().SetString(an.answer.c_str(), an.answer.size(), document.GetAllocator()), document.GetAllocator());
    document.AddMember("question_id", an.questionId, document.GetAllocator());
    document.AddMember("user_id", an.userId, document.GetAllocator());

    rapidjson::StringBuffer strbuf;
    rapidjson::Writer<rapidjson::StringBuffer> writer(strbuf);
    document.Accept(writer);

    response.headers().add<Pistache::Http::Header::AccessControlAllowOrigin>("*");
    response.send(Pistache::Http::Code::Ok, strbuf.GetString());
}

void AnswersHandler::CreateScore(const Pistache::Rest::Request& request, Pistache::Http::ResponseWriter response) 
{
    std::string token = request.headers().getRaw("Authorization").value();

    if (!UserService::ValidateToken(token)) {
        response.headers().add<Pistache::Http::Header::AccessControlAllowOrigin>("*");
        response.send(Pistache::Http::Code::Unauthorized, "Unauthorized");
        return;
    }   

    uint32_t testId = request.param(":id").as<int>();

    AnswersService::CreateScore(testId, token);
 
    response.headers().add<Pistache::Http::Header::AccessControlAllowOrigin>("*");
    response.send(Pistache::Http::Code::Ok, "Score created!");
}

void AnswersHandler::GetScore(const Pistache::Rest::Request& request, Pistache::Http::ResponseWriter response) 
{
    std::string token = request.headers().getRaw("Authorization").value();

    if (!UserService::ValidateToken(token)) {
        response.headers().add<Pistache::Http::Header::AccessControlAllowOrigin>("*");
        response.send(Pistache::Http::Code::Unauthorized, "Unauthorized");
        return;
    }

    uint32_t testId = request.param(":id").as<int>();

    std::string score = AnswersService::GetScore(testId, token);

    rapidjson::Document document;
    document.SetObject();

    document.AddMember("score", rapidjson::Value().SetString(score.c_str(), score.size(), document.GetAllocator()), document.GetAllocator());
    
    rapidjson::StringBuffer strbuf;
    rapidjson::Writer<rapidjson::StringBuffer> writer(strbuf);
    document.Accept(writer);

    response.headers().add<Pistache::Http::Header::AccessControlAllowOrigin>("*");
    response.send(Pistache::Http::Code::Ok, strbuf.GetString());
}