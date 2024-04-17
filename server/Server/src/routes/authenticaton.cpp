#include "authentication.hpp"
#include <rapidjson/document.h>
#include "../dataAccess/models/userModels.hpp"
#include "../businessLogic/authService.hpp"
#include "../dataAccess/repos/userHeader.hpp"

void AuthenticationHandler::RegisterUser(const Pistache::Rest::Request& request, Pistache::Http::ResponseWriter response) {
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

void AuthenticationHandler::GetUser(const Pistache::Rest::Request& request, Pistache::Http::ResponseWriter response) 
{
    std::string token = request.headers().getRaw("Authorization").value();

    if (!UserService::ValidateToken(token)) {
        response.headers().add<Pistache::Http::Header::AccessControlAllowOrigin>("*");
        response.send(Pistache::Http::Code::Unauthorized, "Unauthorized");
        return;
    }


    User user = UserService::GetUser(token);

    std::string userJson = R"(
{
    "id": )" + std::to_string(user.id) + R"(,
    "name": ")" + user.name + R"(",
    "username": ")" + user.username + R"(",
    "email": ")" + user.email + R"(",
    "country": ")" + user.country + R"("
}
    )";

    response.headers().add<Pistache::Http::Header::AccessControlAllowOrigin>("*");
    response.send(Pistache::Http::Code::Ok, userJson);
}

void AuthenticationHandler::LoginUser(const Pistache::Rest::Request& request, Pistache::Http::ResponseWriter response) {
    rapidjson::Document document;
    document.Parse(request.body().c_str());

    UserLoginInput userInputModel;
    userInputModel.username = document["username"].GetString();
    userInputModel.password = document["password"].GetString();

    std::string token = UserService::LoginUser(userInputModel);

    response.headers().add<Pistache::Http::Header::AccessControlAllowOrigin>("*");
    response.send(Pistache::Http::Code::Ok, "{\"token\": \"" + token + "\"}");
}