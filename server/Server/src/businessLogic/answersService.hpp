#pragma once
#include "../dataAccess/repos/answersHeader.hpp"
#include "questionService.hpp"


class AnswersService{
public:
    static Answers RegisterAnswers(AnswersInput input, int id, std::string token);
    static Answers GetAnswer(int id);
    static Answers GetAnswerByQuestionId(int id, std::string token);
    static void CreateScore(int id, std::string token);
    static std::stirng GetScore(int id, std::string token);
};