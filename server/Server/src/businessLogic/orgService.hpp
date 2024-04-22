#pragma once
#include "../dataAccess/repos/organisationHeader.hpp"
#include "argon2.h"
#include <cstring>
#include <algorithm>
#include <ctime>
#include <cstdlib>
#include <random>


std::string generateCode(size_t length);

class OrganisationService{
public:
    static Organisation RegisterOrganisation(OrganisationInput input, std::string token);
    static Organisation RemoveOrganisation(OrganisationInput input, std::string token);
    static std::vector<Organisation> GetOrganisations(std::string token);
    static Organisation GetOrganisation(int id, std::string token);
    static void JoinOrganisation(std::string code, std::string token);
};