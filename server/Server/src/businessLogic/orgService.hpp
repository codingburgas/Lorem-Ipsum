#include "../dataAccess/repos/organisationHeader.hpp"
#include "argon2.h"
#include <cstring>
#include <algorithm>
#include <ctime>
#include <cstdlib>
#include <random>

class OrganisationService{
public:
    static Organisation RegisterOrganisation(OrganisationInput input, std::string token);
    static Organisation RemoveOrganisation(OrganisationInput input, std::string token);
    static std::vector<Organisation> GetOrganisations(std::string token);
    static Organisation GetOrganisation(int id);
    static void JoinOrganisation(std::string code, std::string token);
};