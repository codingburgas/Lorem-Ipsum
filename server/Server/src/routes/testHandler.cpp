#include "testHandler.hpp"

#define RAPIDJSON_HAS_STDSTRING 1
#include <rapidjson/document.h>
#include <rapidjson/writer.h>
#include <rapidjson/stringbuffer.h>
#include "../dataAccess/models/themeModels.hpp"
#include "../businessLogic/courseService.hpp"
#include "../businessLogic/testService.hpp"
#include "../businessLogic/themeService.hpp"
#include "../businessLogic/authService.hpp"
#include "../dataAccess/repos/themeHeader.hpp"


void TestHandler::CreatTest(const Pistache::Rest::Request& request, Pistache::Http::ResponseWriter response) 
{
    std::string token = request.headers().getRaw("Authorization").value();

    if (!UserService::ValidateToken(token)) {
        response.headers().add<Pistache::Http::Header::AccessControlAllowOrigin>("*");
        response.send(Pistache::Http::Code::Unauthorized, "Unauthorized");
        return;
    }   

    rapidjson::Document document;
    document.Parse(request.body().c_str());
 
    TestInput testInputModel;
    testInputModel.title = document["title"].GetString();
    testInputModel.themeId = document["theme_id"].GetInt();

    Test test = TestService::RegisterTest(testInputModel, testInputModel.themeId);
 
    response.headers().add<Pistache::Http::Header::AccessControlAllowOrigin>("*");
    response.send(Pistache::Http::Code::Ok, "Theme created!");
}

void TestHandler::GetTest(const Pistache::Rest::Request& request, Pistache::Http::ResponseWriter response) 
{
    std::string token = request.headers().getRaw("Authorization").value();

    if (!UserService::ValidateToken(token)) {
        response.headers().add<Pistache::Http::Header::AccessControlAllowOrigin>("*");
        response.send(Pistache::Http::Code::Unauthorized, "Unauthorized");
        return;
    }

    uint32_t testId = request.param(":id").as<int>();

    Test test = TestService::GetTest(testId);

    rapidjson::Document document;
    document.SetObject();

    document.AddMember("id", test.id, document.GetAllocator());
    document.AddMember("title", rapidjson::Value().SetString(test.title.c_str(), test.title.size(), document.GetAllocator()), document.GetAllocator());
    document.AddMember("theme_id", test.themeId, document.GetAllocator());

    rapidjson::StringBuffer strbuf;
    rapidjson::Writer<rapidjson::StringBuffer> writer(strbuf);
    document.Accept(writer);

    response.headers().add<Pistache::Http::Header::AccessControlAllowOrigin>("*");
    response.send(Pistache::Http::Code::Ok, strbuf.GetString());
}


void TestHandler::GetTests(const Pistache::Rest::Request& request, Pistache::Http::ResponseWriter response) 
{
    std::string token = request.headers().getRaw("Authorization").value();

    if (!UserService::ValidateToken(token)) {
        response.headers().add<Pistache::Http::Header::AccessControlAllowOrigin>("*");
        response.send(Pistache::Http::Code::Unauthorized, "Unauthorized");
        return;
    }
    
    uint32_t id = request.param(":id").as<int>();;
    
    std::vector<Test> test = TestService::GetTests(id);
    rapidjson::Document document;
    document.SetArray();
    for (size_t i = 0; i < test.size(); i++) {
        rapidjson::Value tt(rapidjson::kObjectType);
        tt.AddMember("id", test[i].id, document.GetAllocator());
        tt.AddMember("title", rapidjson::Value().SetString(test[i].title.c_str(), test[i].title.size(), document.GetAllocator()), document.GetAllocator());
        tt.AddMember("theme_id", test[i].id, document.GetAllocator());

        document.PushBack(tt, document.GetAllocator());
    }

    rapidjson::StringBuffer strbuf;
    rapidjson::Writer<rapidjson::StringBuffer> writer(strbuf);
    document.Accept(writer);

    response.headers().add<Pistache::Http::Header::AccessControlAllowOrigin>("*");
    response.send(Pistache::Http::Code::Ok, strbuf.GetString());
}