#pragma once
#include <iostream>
#include <string>
#include "../models/organisationModels.hpp"
#include "../models/userModels.hpp"
#include "../models/themeModels.hpp"
#include "../models/testModels.hpp"
#include "../models/questionModel.hpp"

#include "../db.hpp"
#include <soci/session.h>



class QuestionRepository{
public:
    QuestionRepository();
    static Question CreateQuestion(QuestionInput input);
    static Question ReadQuestion(int id);
    static std::vector<Question> ReadQuestions(uint32_t testId);
    static void DeleteQuestion(int id);
};