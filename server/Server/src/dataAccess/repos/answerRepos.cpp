#include "answersHeader.hpp"
#include "testHeader.hpp"
#include "questionsHeader.hpp"

AnswerRepository::AnswerRepository() {};

Answers AnswerRepository::CreateAnswer(AnswersInput input)
{
    Answers an;
    an.userId = input.userId;
    an.questionId = input.questionId;
    an.answer = input.answer;
    
    *DatabaseConnection::sql << "INSERT INTO answers(question_id, answer, user_id) VALUES(:question_id, :answer, :user_id)",
        soci::use(an.questionId),
        soci::use(an.answer),
        soci::use(an.userId);

    return an;
}

Answers AnswerRepository::ReadAnswer(int id)
{
    Answers an;
    *DatabaseConnection::sql << "SELECT id, question_id, answer, user_id FROM answers WHERE id = " << id, soci::into(an.id), soci::into(an.questionId), soci::into(an.answer), soci::into(an.userId);

    return an;
}
Answers AnswerRepository::ReadAnswerByQuestionId(int questionId, int userId)
{
    Answers an;
    *DatabaseConnection::sql << "SELECT id, user_id, question_id, answer FROM answers WHERE user_id = " << userId << " AND question_id = " << questionId, soci::into(an.id), soci::into(an.userId), soci::into(an.questionId), soci::into(an.answer);

    return an;
}

void AnswerRepository::CreateScore(int testId, int userId, int score)
{
    *DatabaseConnection::sql << "INSERT INTO scores(test_id, user_id, score) VALUES(:test_id, :user_id, :score)",
        soci::use(testId),
        soci::use(userId),
        soci::use(score);
}

std::string AnswerRepository::GetScoreByTest(int id, int userId)
{
    std::string score;
    *DatabaseConnection::sql << "SELECT score FROM scores WHERE test_id = " << id << " AND user_id = " << userId, soci::into(score);

    return score;
}
