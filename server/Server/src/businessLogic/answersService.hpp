#pragma once
#include "../dataAccess/repos/answersHeader.hpp"
#include "questionService.hpp"
#include <string>

class AnswersService{
public:
    static Answers RegisterAnswers(AnswersInput input, int id, std::string token);
    static Answers GetAnswer(int id);
    static Answers GetAnswerByQuestionId(int id, std::string token);
    static void CreateScore(int id, std::string token);
    static std::string GetScore(int id, std::string token);
};