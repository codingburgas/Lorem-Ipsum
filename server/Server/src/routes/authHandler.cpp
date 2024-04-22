#include "authHandler.hpp"
#define RAPIDJSON_HAS_STDSTRING 1
#include <rapidjson/document.h>
#include <rapidjson/writer.h>
#include <rapidjson/stringbuffer.h>
#include "../dataAccess/models/userModels.hpp"
#include "../businessLogic/authService.hpp"
#include "../dataAccess/repos/userHeader.hpp"

void AuthHandler::RegisterUser(const Pistache::Rest::Request& request, Pistache::Http::ResponseWriter response) {
    rapidjson::Document document;
    document.Parse(request.body().c_str());

    UserInput userInputModel;
    userInputModel.username = document["username"].GetString();
    userInputModel.password = document["password"].GetString();
    userInputModel.email = document["email"].GetString();
    userInputModel.name = document["name"].GetString();
    userInputModel.country = "Bulgaria";

    User user = UserService::RegisterUser(userInputModel);

    response.headers().add<Pistache::Http::Header::AccessControlAllowOrigin>("*");
    response.send(Pistache::Http::Code::Ok, "User created!");
}

void AuthHandler::AuthHandler::GetUser(const Pistache::Rest::Request& request, Pistache::Http::ResponseWriter response) 
{
    std::string token = request.headers().getRaw("Authorization").value();

    if (!UserService::ValidateToken(token)) {
        response.headers().add<Pistache::Http::Header::AccessControlAllowOrigin>("*");
        response.send(Pistache::Http::Code::Unauthorized, "Unauthorized");
        return;
    }

    User user = UserService::GetUser(token);

    rapidjson::Document document;
    document.SetObject();
    document.AddMember("id", user.id, document.GetAllocator());
    document.AddMember("name", rapidjson::Value().SetString(user.name.c_str(), user.name.size(), document.GetAllocator()), document.GetAllocator());
    document.AddMember("username", rapidjson::Value().SetString(user.username.c_str(), user.username.size(), document.GetAllocator()), document.GetAllocator());
    document.AddMember("email", rapidjson::Value().SetString(user.email.c_str(), user.email.size(), document.GetAllocator()), document.GetAllocator());
    document.AddMember("country", rapidjson::Value().SetString(user.country.c_str(), user.country.size(), document.GetAllocator()), document.GetAllocator());

    rapidjson::StringBuffer strbuf;
    rapidjson::Writer<rapidjson::StringBuffer> writer(strbuf);
    document.Accept(writer);

    response.headers().add<Pistache::Http::Header::AccessControlAllowOrigin>("*");
    response.send(Pistache::Http::Code::Ok, strbuf.GetString());
}

void AuthHandler::AuthHandler::LoginUser(const Pistache::Rest::Request& request, Pistache::Http::ResponseWriter response) {
    rapidjson::Document document;
    document.Parse(request.body().c_str());

    UserLoginInput userInputModel;
    userInputModel.username = document["username"].GetString();
    userInputModel.password = document["password"].GetString();

    std::string token = UserService::LoginUser(userInputModel);

    response.headers().add<Pistache::Http::Header::AccessControlAllowOrigin>("*");
    response.send(Pistache::Http::Code::Ok, "{\"token\": \"" + token + "\"}");
}