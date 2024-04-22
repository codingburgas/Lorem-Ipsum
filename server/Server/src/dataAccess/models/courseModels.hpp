#pragma once
#include <iostream>
#include <string>

struct Course{
    int id;
    int ownerId;
    int organisationId;
    std::string name;
    std::string code;
    std::string subject;
};
struct CourseInput{
    int id;
    int ownerId;
    int organisationId;
    std::string name;
    std::string code;
    std::string subject;
};

struct CourseScore{
    int id;
    int userId;
    int score;
    int courseId;
    int position;
};

struct CourseScoreInput{
    int id;
    int userId;
    int score;
    int courseId;
    int position;
};

