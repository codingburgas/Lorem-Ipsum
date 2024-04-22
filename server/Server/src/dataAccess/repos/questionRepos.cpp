#include "questionsHeader.hpp"

QuestionRepository::QuestionRepository() {};

Question QuestionRepository::CreateQuestion(QuestionInput input)
{
    *DatabaseConnection::sql << "SELECT * FROM questions WHERE question = :question", soci::use(input.question);

    if(DatabaseConnection::sql->got_data())
    {
        throw std::invalid_argument("Question already exists");
    }
    
    Question qu;
    qu.testId = input.testId;
    qu.question = input.question;
    qu.answerA = input.answerA;
    qu.answerB = input.answerB;
    qu.answerC = input.answerC;
    qu.answerD = input.answerD;
    qu.correctAnswer = input.correctAnswer;
    
    *DatabaseConnection::sql << "INSERT INTO questions(test_id, question, correct_answer, answer_a, answer_b, answer_c,answer_d) VALUES(:test_id, :question, :correct_answer, :answer_a, :answer_b, :answer_c, :answer_d)",
        soci::use(qu.testId),
        soci::use(qu.question),
        soci::use(qu.correctAnswer),
        soci::use(qu.answerA),
        soci::use(qu.answerB),
        soci::use(qu.answerC),
        soci::use(qu.answerD);



    return qu;
}

Question QuestionRepository::ReadQuestion(int id)
{
    Question qu;
    *DatabaseConnection::sql << "SELECT id, test_id, question, correct_answer, answer_a, answer_b, answer_c, answer_d FROM questions WHERE id = " << id, soci::into(qu.id), soci::into(qu.testId), soci::into(qu.question), soci::into(qu.correctAnswer), soci::into(qu.answerA), soci::into(qu.answerB), soci::into(qu.answerC), soci::into(qu.answerD) ;

    return qu;
}



std::vector<Question> QuestionRepository::ReadQuestions(uint32_t testId)
{

    std::vector<Question> questions;
    soci::rowset<soci::row> rs = (DatabaseConnection::sql->prepare << "SELECT id, test_id, question, correct_answer, answer_a, answer_b, answer_c,answer_d FROM questions WHERE test_id = :testId", soci::use(testId));

    for (soci::rowset<soci::row>::const_iterator it = rs.begin(); it != rs.end(); ++it)
    {
        Question qu;
        soci::row const &row = *it;
        qu.id = row.get<int>(0);
        qu.testId = row.get<int>(1);
        qu.question = row.get<std::string>(2);
        qu.correctAnswer = row.get<std::string>(3);
        qu.answerA = row.get<std::string>(4);
        qu.answerB = row.get<std::string>(5);
        qu.answerC = row.get<std::string>(6);
        qu.answerD = row.get<std::string>(7);
        questions.push_back(qu);
    }

    return questions;
}

void QuestionRepository::DeleteQuestion(int id){
    Question qu;
    *DatabaseConnection::sql << "DELETE FROM questions WHERE id=:id", soci::use(qu.id);

}