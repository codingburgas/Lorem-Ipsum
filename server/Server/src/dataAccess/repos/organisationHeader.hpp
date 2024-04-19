#pragma once
#include <iostream>
#include <string>
#include "../models/organisationModels.hpp"
#include "../models/userModels.hpp"

#include "../db.hpp"
#include <soci/session.h>

class OrganisationRepository{
public:
    OrganisationRepository();
    static Organisation CreateOrganisation(OrganisationInput input);
    static Organisation ReadOrganisation(int id);
    static Organisation ReadOrganisation(std::string name);
    static Organisation ReadOrganisationByCode(std::string code);
    static std::vector<Organisation> ReadOrganisations(uint32_t userId);
    static void DeleteOrganisation(int id);
    static void AddUserToOrganisation(uint32_t userId, uint32_t orgId);
};