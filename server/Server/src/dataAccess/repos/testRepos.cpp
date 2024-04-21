#include "testHeader.hpp"
#include "courseHeader.hpp"



TestRepository::TestRepository() {};

Test TestRepository::CreateTest(TestInput input)
{   
    
    Test test;
    test.title = input.title;
    test.themeId = input.themeId;

    
    *DatabaseConnection::sql << "INSERT INTO tests(title, theme_id) VALUES(:title, :theme_id)",
        soci::use(test.title),
        soci::use(test.themeId);


    

    
    return test;
}

Test TestRepository::ReadTest(int id)
{
    Test test;
    *DatabaseConnection::sql << "SELECT id, title, theme_id FROM tests WHERE id = " << id, soci::into(test.id), soci::into(test.title), soci::into(test.themeId);

    return test;
}

Test TestRepository::ReadTest(std::string title)
{
    Test test;
    *DatabaseConnection::sql << "SELECT id, title, theme_id FROM tests WHERE title = " << title, soci::into(test.id), soci::into(test.title), soci::into(test.themeId);

    return test;
}



void TestRepository::DeleteTest(int id){
    Test test;
    *DatabaseConnection::sql << "DELETE FROM tests WHERE id=:id", soci::use(test.id);

}

std::vector<Test> TestRepository::ReadTests(uint32_t themeId)
{

    std::vector<Test> tests;
    Test ts;
    soci::rowset<soci::row> rs = (DatabaseConnection::sql->prepare << "SELECT id, title, theme_id FROM tests WHERE theme_id =:theme_id", soci::use(themeId));

    for (soci::rowset<soci::row>::const_iterator it = rs.begin(); it != rs.end(); ++it)
    {
        soci::row const &row = *it;
        ts.id = row.get<int>(0);
        ts.title = row.get<std::string>(1);
        ts.themeId = row.get<int>(2);
        tests.push_back(ts);
    }

    return tests;
}

