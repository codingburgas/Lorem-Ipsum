#pragma once
#include "../models/answersModels.hpp"
#include "../models/courseModels.hpp"
#include "../models/userModels.hpp"
#include "../models/organisationModels.hpp"
#include "../db.hpp"
#include <soci/session.h>


class AnswerRepository{
public:
    AnswerRepository();
    static Answers CreateAnswer(AnswersInput input);
    static Answers ReadAnswer(int id);
    static Answers ReadAnswerByQuestionId(int questionId, int userId);
    static void CreateScore(int testId, int userId, int score);
    static std::string GetScoreByTest(int id, int userId);
};