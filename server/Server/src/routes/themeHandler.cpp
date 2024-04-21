#include "themeHandler.hpp"

#define RAPIDJSON_HAS_STDSTRING 1
#include <rapidjson/document.h>
#include <rapidjson/writer.h>
#include <rapidjson/stringbuffer.h>
#include "../dataAccess/models/themeModels.hpp"
#include "../businessLogic/courseService.hpp"
#include "../businessLogic/themeService.hpp"
#include "../businessLogic/authService.hpp"
#include "../dataAccess/repos/themeHeader.hpp"


void ThemeHandler::CreateTheme(const Pistache::Rest::Request& request, Pistache::Http::ResponseWriter response) 
{
    std::string token = request.headers().getRaw("Authorization").value();

    if (!UserService::ValidateToken(token)) {
        response.headers().add<Pistache::Http::Header::AccessControlAllowOrigin>("*");
        response.send(Pistache::Http::Code::Unauthorized, "Unauthorized");
        return;
    }   

    rapidjson::Document document;
    document.Parse(request.body().c_str());
 
    ThemeInput thInputModel;
    thInputModel.title = document["title"].GetString();
    thInputModel.unitInfo = document["info"].GetString();
    thInputModel.courseId = document["course_id"].GetInt();

    int id = thInputModel.id;
    Theme them = ThemeService::RegisterTheme(thInputModel, id);
 
    response.headers().add<Pistache::Http::Header::AccessControlAllowOrigin>("*");
    response.send(Pistache::Http::Code::Ok, "Theme created!");
}

void ThemeHandler::GetTheme(const Pistache::Rest::Request& request, Pistache::Http::ResponseWriter response) 
{
    std::string token = request.headers().getRaw("Authorization").value();

    if (!UserService::ValidateToken(token)) {
        response.headers().add<Pistache::Http::Header::AccessControlAllowOrigin>("*");
        response.send(Pistache::Http::Code::Unauthorized, "Unauthorized");
        return;
    }

    uint32_t themeId = request.param(":id").as<int>();

    Theme th = ThemeService::GetTheme(themeId);

    rapidjson::Document document;
    document.SetObject();

    document.AddMember("id", th.id, document.GetAllocator());
    document.AddMember("title", rapidjson::Value().SetString(th.title.c_str(), th.title.size(), document.GetAllocator()), document.GetAllocator());
    document.AddMember("info", rapidjson::Value().SetString(th.unitInfo.c_str(), th.unitInfo.size(), document.GetAllocator()), document.GetAllocator());
    document.AddMember("course_id", th.courseId, document.GetAllocator());

    rapidjson::StringBuffer strbuf;
    rapidjson::Writer<rapidjson::StringBuffer> writer(strbuf);
    document.Accept(writer);

    response.headers().add<Pistache::Http::Header::AccessControlAllowOrigin>("*");
    response.send(Pistache::Http::Code::Ok, strbuf.GetString());
}


void ThemeHandler::GetThemes(const Pistache::Rest::Request& request, Pistache::Http::ResponseWriter response) 
{
    std::string token = request.headers().getRaw("Authorization").value();

    if (!UserService::ValidateToken(token)) {
        response.headers().add<Pistache::Http::Header::AccessControlAllowOrigin>("*");
        response.send(Pistache::Http::Code::Unauthorized, "Unauthorized");
        return;
    }
    
    Course cor;
    int id = cor.id;
    
    std::vector<Theme> theme = ThemeService::GetThemes(id);
    rapidjson::Document document;
    document.SetArray();
    for (size_t i = 0; i < theme.size(); i++) {
        rapidjson::Value th(rapidjson::kObjectType);
        th.AddMember("id", theme[i].id, document.GetAllocator());
        th.AddMember("name", rapidjson::Value().SetString(theme[i].title.c_str(), theme[i].title.size(), document.GetAllocator()), document.GetAllocator());
        th.AddMember("info", rapidjson::Value().SetString(theme[i].unitInfo.c_str(), theme[i].unitInfo.size(), document.GetAllocator()), document.GetAllocator());

        document.PushBack(th, document.GetAllocator());
    }

    rapidjson::StringBuffer strbuf;
    rapidjson::Writer<rapidjson::StringBuffer> writer(strbuf);
    document.Accept(writer);

    response.headers().add<Pistache::Http::Header::AccessControlAllowOrigin>("*");
    response.send(Pistache::Http::Code::Ok, strbuf.GetString());
}