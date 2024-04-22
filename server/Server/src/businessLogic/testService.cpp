#include "testService.hpp"

Test TestService::RegisterTest(TestInput input, int id)
{
    Theme th = ThemeService::GetTheme(id);
    
    input.themeId = th.id;
    
    Test test = TestRepository::CreateTest(input);

    return test;
}

Test TestService::GetTest(int id)
{
    Test test = TestRepository::ReadTest(id);

    return test;
}

std::vector<Test> TestService::GetTests(int themeId)
{
    Theme th = ThemeService::GetTheme(themeId);
    std::vector<Test> test = TestRepository::ReadTests(th.id);

    return test;
}

Test TestService::RemoveTest(TestInput input)
{
    Test test = TestRepository::CreateTest(input);

    return test;
}