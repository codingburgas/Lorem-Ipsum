#pragma once
#include <iostream>
#include <string>

struct stats{
    int id;
    int coursId;
    std::string highest_student;
    std::string lowest_student;
    std::string course_score;
};

struct Scores{
    int testId;
    int userId;
    int score;
};
