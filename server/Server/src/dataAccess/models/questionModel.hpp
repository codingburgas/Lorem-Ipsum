#pragma once
#include <iostream>
#include <string>
struct Question{
    int id;
    int testId;
    std::string question;
    std::string answerA;
    std::string answerB;
    std::string answerC;
    std::string answerD;
    std::string correctAnswer;
};

struct QuestionInput{
    int id;
    int testId;
    std::string question;
    std::string answerA;
    std::string answerB;
    std::string answerC;
    std::string answerD;
    std::string correctAnswer;
};