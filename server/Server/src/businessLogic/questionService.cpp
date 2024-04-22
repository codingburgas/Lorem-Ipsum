#include "questionService.hpp"

Question QuestionsService::RegisterQuestion(QuestionInput input, int id)
{
    Test test = TestService::GetTest(id);
    
    input.testId = test.id;
    
    Question qu = QuestionRepository::CreateQuestion(input);

    return qu;
}

Question QuestionsService::GetQuestion(int id)
{
    Question qu = QuestionRepository::ReadQuestion(id);

    return qu;
}

std::vector<Question> QuestionsService::GetQuestions(int testId)
{
    std::vector<Question> question = QuestionRepository::ReadQuestions(testId);

    return question;
}

// Question QuestionsService::RemoveQuestion(int id)
// {
//     Question qu = TestService::GetTest(id);
//     Question question = QuestionRepository::DeleteQuestion(qu.id);

//     return qu;
// }