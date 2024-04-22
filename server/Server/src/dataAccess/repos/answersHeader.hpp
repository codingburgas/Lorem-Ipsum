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
};