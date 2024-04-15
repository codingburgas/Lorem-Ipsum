#pragma once
#include <iostream>
#include <string>

struct Cours{
    int id;
    int ownerId;
    int organisationId;
    std::string name;
    std::string subject;
};
struct CourseScore{
    int id;
    int userId;
    int score;
    int courseId;
    int position;
};
