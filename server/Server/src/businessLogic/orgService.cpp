#include "orgService.hpp"
#include "authService.hpp"

std::string generateCode(size_t length){
    auto randchar = []() -> char{
        const char charset[] =
            "0123456789"
            "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
            "abcdefghijklmnopqrstuvwxyz";
        const size_t maxIndex = (sizeof(charset) -1);
        return charset[rand()% maxIndex];
    };
    std::string code;
    code.reserve(length);
    for(size_t i = 0; i < length; i++){
        code.push_back(randchar());
    }
    return code;
}

Organisation OrganisationService::RegisterOrganisation(OrganisationInput input, std::string token)
{
    input.code = generateCode(6);
    User user = UserService::GetUser(token);
    input.ownerId = user.id;

    Organisation org = OrganisationRepository::CreateOrganisation(input);

    return org;
}

Organisation OrganisationService::RemoveOrganisation(OrganisationInput input, std::string token)
{
    Organisation org = OrganisationRepository::CreateOrganisation(input);

    return org;
}

std::vector<Organisation> OrganisationService::GetOrganisations(std::string token)
{
    User user = UserService::GetUser(token);
    std::vector<Organisation> orgs = OrganisationRepository::ReadOrganisations(user.id);

    return orgs;
}

Organisation OrganisationService::GetOrganisation(int id)
{
    Organisation org = OrganisationRepository::ReadOrganisation(id);

    return org;
}

void OrganisationService::JoinOrganisation(std::string code, std::string token)
{
    Organisation org = OrganisationRepository::ReadOrganisationByCode(code);
    User user = UserService::GetUser(token);

    OrganisationRepository::AddUserToOrganisation(user.id, org.id);
}