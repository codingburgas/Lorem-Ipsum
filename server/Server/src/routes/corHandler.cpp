#include "corHandler.hpp"

#define RAPIDJSON_HAS_STDSTRING 1
#include <rapidjson/document.h>
#include <rapidjson/writer.h>
#include <rapidjson/stringbuffer.h>
#include "../dataAccess/models/courseModels.hpp"
#include "../businessLogic/courseService.hpp"
#include "../businessLogic/authService.hpp"
#include "../dataAccess/repos/courseHeader.hpp"
 
void CourseHandler::CreateCourse(const Pistache::Rest::Request& request, Pistache::Http::ResponseWriter response) 
{
    std::string token = request.headers().getRaw("Authorization").value();

    if (!UserService::ValidateToken(token)) {
        response.headers().add<Pistache::Http::Header::AccessControlAllowOrigin>("*");
        response.send(Pistache::Http::Code::Unauthorized, "Unauthorized");
        return;
    }   

    rapidjson::Document document;
    document.Parse(request.body().c_str());
 
    CourseInput corInputModel;
    corInputModel.name = document["name"].GetString();
    corInputModel.subject = document["subject"].GetString();

    OrganisationInput orgInputModel;
    orgInputModel.id = document["org_id"].GetInt();
    int id = orgInputModel.id;

    Course course = CourseService::RegisterCourse(corInputModel, token, id);
 
    response.headers().add<Pistache::Http::Header::AccessControlAllowOrigin>("*");
    response.send(Pistache::Http::Code::Ok, "Course created!");
}


void CourseHandler::GetCourses(const Pistache::Rest::Request& request, Pistache::Http::ResponseWriter response) 
{
    std::string token = request.headers().getRaw("Authorization").value();

    if (!UserService::ValidateToken(token)) {
        response.headers().add<Pistache::Http::Header::AccessControlAllowOrigin>("*");
        response.send(Pistache::Http::Code::Unauthorized, "Unauthorized");
        return;
    }

    std::vector<Course> course = CourseService::GetCourses(token);
    rapidjson::Document document;
    document.SetArray();
    for (size_t i = 0; i < course.size(); i++) {
        rapidjson::Value cor(rapidjson::kObjectType);
        cor.AddMember("id", course[i].id, document.GetAllocator());
        cor.AddMember("name", rapidjson::Value().SetString(course[i].name.c_str(), course[i].name.size(), document.GetAllocator()), document.GetAllocator());
        cor.AddMember("subject", rapidjson::Value().SetString(course[i].subject.c_str(), course[i].subject.size(), document.GetAllocator()), document.GetAllocator());

        document.PushBack(cor, document.GetAllocator());
    }

    rapidjson::StringBuffer strbuf;
    rapidjson::Writer<rapidjson::StringBuffer> writer(strbuf);
    document.Accept(writer);

    response.headers().add<Pistache::Http::Header::AccessControlAllowOrigin>("*");
    response.send(Pistache::Http::Code::Ok, strbuf.GetString());
}

void CourseHandler::GetCourse(const Pistache::Rest::Request& request, Pistache::Http::ResponseWriter response) 
{
    std::string token = request.headers().getRaw("Authorization").value();

    if (!UserService::ValidateToken(token)) {
        response.headers().add<Pistache::Http::Header::AccessControlAllowOrigin>("*");
        response.send(Pistache::Http::Code::Unauthorized, "Unauthorized");
        return;
    }

    uint32_t corId = request.param(":id").as<int>();

    Course cor = CourseRepository::ReadCourse(corId);

    rapidjson::Document document;
    document.SetObject();

    document.AddMember("id", cor.id, document.GetAllocator());
    document.AddMember("name", rapidjson::Value().SetString(cor.name.c_str(), cor.name.size(), document.GetAllocator()), document.GetAllocator());
    document.AddMember("subject", rapidjson::Value().SetString(cor.subject.c_str(), cor.subject.size(), document.GetAllocator()), document.GetAllocator());
    document.AddMember("code", rapidjson::Value().SetString(cor.code.c_str(), cor.code.size(), document.GetAllocator()), document.GetAllocator());
    document.AddMember("organisationId", cor.organisationId, document.GetAllocator());
    document.AddMember("ownerId", cor.ownerId, document.GetAllocator());

    rapidjson::StringBuffer strbuf;
    rapidjson::Writer<rapidjson::StringBuffer> writer(strbuf);
    document.Accept(writer);

    response.headers().add<Pistache::Http::Header::AccessControlAllowOrigin>("*");
    response.send(Pistache::Http::Code::Ok, strbuf.GetString());
}



void CourseHandler::JoinCourse(const Pistache::Rest::Request& request, Pistache::Http::ResponseWriter response) 
{
    std::string token = request.headers().getRaw("Authorization").value();

    if (!UserService::ValidateToken(token)) {
        response.headers().add<Pistache::Http::Header::AccessControlAllowOrigin>("*");
        response.send(Pistache::Http::Code::Unauthorized, "Unauthorized");
        return;
    }

    rapidjson::Document document;
    document.Parse(request.body().c_str());

    std::string code = document["code"].GetString();

    CourseService::JoinCourse(code, token);

    response.headers().add<Pistache::Http::Header::AccessControlAllowOrigin>("*");
    response.send(Pistache::Http::Code::Ok, "Joined course!");
}

void CourseHandler::GetCourseByOrg(const Pistache::Rest::Request& request, Pistache::Http::ResponseWriter response) 
{
    std::string token = request.headers().getRaw("Authorization").value();

    if (!UserService::ValidateToken(token)) {
        response.headers().add<Pistache::Http::Header::AccessControlAllowOrigin>("*");
        response.send(Pistache::Http::Code::Unauthorized, "Unauthorized");
        return;
    }

    uint32_t orgId = request.param(":id").as<int>();

    std::vector<Course> course = CourseService::GetCoursesByOrg(orgId);
    
    rapidjson::Document document;
    document.SetArray();
    for (size_t i = 0; i < course.size(); i++) {
        rapidjson::Value cor(rapidjson::kObjectType);
        cor.AddMember("id", course[i].id, document.GetAllocator());
        cor.AddMember("name", rapidjson::Value().SetString(course[i].name.c_str(), course[i].name.size(), document.GetAllocator()), document.GetAllocator());
        cor.AddMember("subject", rapidjson::Value().SetString(course[i].subject.c_str(), course[i].subject.size(), document.GetAllocator()), document.GetAllocator());

        document.PushBack(cor, document.GetAllocator());
    }

    rapidjson::StringBuffer strbuf;
    rapidjson::Writer<rapidjson::StringBuffer> writer(strbuf);
    document.Accept(writer);

    response.headers().add<Pistache::Http::Header::AccessControlAllowOrigin>("*");
    response.send(Pistache::Http::Code::Ok, strbuf.GetString());
}