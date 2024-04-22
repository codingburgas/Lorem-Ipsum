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

void AnswersService::CreateScore(int id, std::string token)
{
    User us = UserService::GetUser(token);

    std::vector<Question> qu = QuestionsService::GetQuestions(id);

    float score = 0;

    for (int i = 0; i < qu.size(); i++)
    {
        Answers an = GetAnswerByQuestionId(qu[i].id, token);

        if (an.answer == qu[i].correctAnswer)
        {
            score++;
        }
    }

    score = (score / qu.size()) * 100;

    AnswerRepository::CreateScore(id, us.id, score);
}

std::string AnswersService::GetScore(int id, std::string token)
{
    User us = UserService::GetUser(token);

    std::string score = AnswerRepository::GetScoreByTest(id, us.id);

    return score;
}