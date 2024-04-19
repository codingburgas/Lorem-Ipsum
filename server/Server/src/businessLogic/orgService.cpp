#include "orgService.hpp"
#include "authService.hpp"

std::string generateCode(size_t length){
    auto randchar = []() -> char{
        const char charset[] =
            "0123456789"
            "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
            "abcdefghijklmnopqrstuvwxyz"
            "!@#$%^&*()_+-={}[]:;'?/<>,.~`";
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

std::vector<Organisation> OrganisationService::GetOrganisations()
{
    std::vector<Organisation> orgs = OrganisationRepository::ReadOrganisations();

    return orgs;
}

Organisation OrganisationService::GetOrganisation(int id)
{
    Organisation org = OrganisationRepository::ReadOrganisation(id);

    return org;
}