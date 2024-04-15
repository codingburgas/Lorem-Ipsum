#pragma once
#include <iostream>
#include <string>

struct Organisation{
    int id;
    std::string name;
    int ownerId;
};

struct bridgeOrganisationUser{
    int userId;
    int organisationId;
};

struct bridgeOrganisationCourse{
    int courseId;
    int organisationId;
};