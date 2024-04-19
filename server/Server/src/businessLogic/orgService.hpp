#include "../dataAccess/repos/organisationHeader.hpp"
#include "argon2.h"
#include <cstring>
#include <algorithm>
#include <ctime>
#include <cstdlib>
#include <random>

class OrganisationService{
public:
    static Organisation RegisterOrganisation(OrganisationInput input);
    static Organisation RemoveOrganisation(OrganisationInput input);
    //static void JoinOrganisation(std::string code);
};