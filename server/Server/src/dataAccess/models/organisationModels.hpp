#pragma once
#include <iostream>
#include <string>

struct Organisation{
    int id;
    std::string name;
    std::string code;
    int ownerId;
};

struct OrganisationInput{
    int id;
    std::string name;
    std::string code;
    int ownerId;
};

struct bridgeOrganisationUser{
    int userId;
    int organisationId;
    std::string role;
};

struct bridgeOrganisationCourse{
    int courseId;
    int organisationId;
};