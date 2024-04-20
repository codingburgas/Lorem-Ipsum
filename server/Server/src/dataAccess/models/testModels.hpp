#pragma once
#include <iostream>
#include <string>

struct Test{
    int id;
    std::string title;
};

struct QuestionTest{
    int questionId;
    int testId;
};

struct Question{
    int id;
    std::string question;
    std::string answerA;
    std::string answerB;
    std::string answerC;
    std::string answerD;
    std::string correctAnswer;
};