#include "answersService.hpp"

Answers AnswersService::RegisterAnswers(AnswersInput input, int id, std::string token )
{
    User us = UserService::GetUser(token);
    Question qu = QuestionsService::GetQuestion(id);
    
    input.userId = us.id;
    input.questionId = qu.id;

    Answers an = AnswerRepository::CreateAnswer(input);

    return an;
}

Answers AnswersService::GetAnswer(int id)
{
    Answers an = AnswerRepository::ReadAnswer(id);

    return an;
}


Answers AnswersService::GetAnswerByQuestionId(int id, std::string token)
{

    User us = UserService::GetUser(token);
    Question qu = QuestionsService::GetQuestion(id);

    Answers an = AnswerRepository::ReadAnswerByQuestionId(qu.id, us.id);

    return an;
}


