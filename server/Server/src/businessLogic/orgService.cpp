#include "orgService.hpp"

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

Organisation OrganisationService::RegisterOrganisation(OrganisationInput input)
{
    input.code = generateCode(6);


    Organisation org = OrganisationRepository::CreateOrganisation(input);

    return org;
}

Organisation OrganisationService::RemoveOrganisation(OrganisationInput input)
{
    Organisation org = OrganisationRepository::CreateOrganisation(input);

    return org;
}