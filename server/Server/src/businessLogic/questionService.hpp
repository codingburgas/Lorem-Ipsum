#pragma once
#include "../dataAccess/repos/questionsHeader.hpp"
#include "testService.hpp"


class QuestionsService{
public:
    static Question RegisterQuestion(QuestionInput input, int id);
    //static void RemoveQuestion(int id);
    static std::vector<Question> GetQuestions(int testId);
    static Question GetQuestion(int id);
};