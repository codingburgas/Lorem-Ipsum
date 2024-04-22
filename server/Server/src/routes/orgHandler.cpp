#include "orgHandler.hpp"

#define RAPIDJSON_HAS_STDSTRING 1
#include <rapidjson/document.h>
#include <rapidjson/writer.h>
#include <rapidjson/stringbuffer.h>
#include "../dataAccess/models/organisationModels.hpp"
#include "../businessLogic/orgService.hpp"
#include "../businessLogic/authService.hpp"
#include "../dataAccess/repos/organisationHeader.hpp"
 
void OrganizationsHandler::CreateOrganisation(const Pistache::Rest::Request& request, Pistache::Http::ResponseWriter response) 
{
    std::string token = request.headers().getRaw("Authorization").value();

    if (!UserService::ValidateToken(token)) {
          response.headers().add<Pistache::Http::Header::AccessControlAllowOrigin>("http://localhost");
        response.send(Pistache::Http::Code::Unauthorized, "Unauthorized");
        return;
    }   

    rapidjson::Document document;
    document.Parse(request.body().c_str());
 
    OrganisationInput orgInputModel;
    orgInputModel.name = document["name"].GetString();
 
    Organisation org = OrganisationService::RegisterOrganisation(orgInputModel, token);
 
      response.headers().add<Pistache::Http::Header::AccessControlAllowOrigin>("http://localhost");
    response.send(Pistache::Http::Code::Ok, "Organisation created!");
}

void OrganizationsHandler::GetOrganisations(const Pistache::Rest::Request& request, Pistache::Http::ResponseWriter response) 
{
    std::string token = request.headers().getRaw("Authorization").value();

    if (!UserService::ValidateToken(token)) {
          response.headers().add<Pistache::Http::Header::AccessControlAllowOrigin>("http://localhost");
        response.send(Pistache::Http::Code::Unauthorized, "Unauthorized");
        return;
    }

    std::vector<Organisation> orgs = OrganisationService::GetOrganisations(token);
    rapidjson::Document document;
    document.SetArray();
    for (size_t i = 0; i < orgs.size(); i++) {
        rapidjson::Value org(rapidjson::kObjectType);
        org.AddMember("id", orgs[i].id, document.GetAllocator());
        org.AddMember("name", rapidjson::Value().SetString(orgs[i].name.c_str(), orgs[i].name.size(), document.GetAllocator()), document.GetAllocator());
        document.PushBack(org, document.GetAllocator());
    }

    rapidjson::StringBuffer strbuf;
    rapidjson::Writer<rapidjson::StringBuffer> writer(strbuf);
    document.Accept(writer);

      response.headers().add<Pistache::Http::Header::AccessControlAllowOrigin>("http://localhost");
    response.send(Pistache::Http::Code::Ok, strbuf.GetString());
}

void OrganizationsHandler::GetOrganisation(const Pistache::Rest::Request& request, Pistache::Http::ResponseWriter response) 
{
    std::string token = request.headers().getRaw("Authorization").value();

    if (!UserService::ValidateToken(token)) {
          response.headers().add<Pistache::Http::Header::AccessControlAllowOrigin>("http://localhost");
        response.send(Pistache::Http::Code::Unauthorized, "Unauthorized");
        return;
    }

    uint32_t orgId = request.param(":id").as<int>();

    Organisation org = OrganisationService::GetOrganisation(orgId, token);

    rapidjson::Document document;
    document.SetObject();

    document.AddMember("id", org.id, document.GetAllocator());
    document.AddMember("name", rapidjson::Value().SetString(org.name.c_str(), org.name.size(), document.GetAllocator()), document.GetAllocator());
    document.AddMember("code", rapidjson::Value().SetString(org.code.c_str(), org.code.size(), document.GetAllocator()), document.GetAllocator());
    document.AddMember("ownerId", org.ownerId, document.GetAllocator());
    document.AddMember("role", rapidjson::Value().SetString(org.role.c_str(), org.role.size(), document.GetAllocator()), document.GetAllocator());

    rapidjson::StringBuffer strbuf;
    rapidjson::Writer<rapidjson::StringBuffer> writer(strbuf);
    document.Accept(writer);

      response.headers().add<Pistache::Http::Header::AccessControlAllowOrigin>("http://localhost");
    response.send(Pistache::Http::Code::Ok, strbuf.GetString());
}

void OrganizationsHandler::JoinOrganisation(const Pistache::Rest::Request& request, Pistache::Http::ResponseWriter response) 
{
    std::string token = request.headers().getRaw("Authorization").value();

    if (!UserService::ValidateToken(token)) {
          response.headers().add<Pistache::Http::Header::AccessControlAllowOrigin>("http://localhost");
        response.send(Pistache::Http::Code::Unauthorized, "Unauthorized");
        return;
    }

    rapidjson::Document document;
    document.Parse(request.body().c_str());

    std::string code = document["code"].GetString();

    OrganisationService::JoinOrganisation(code, token);

      response.headers().add<Pistache::Http::Header::AccessControlAllowOrigin>("http://localhost");
    response.send(Pistache::Http::Code::Ok, "Joined organisation!");
}