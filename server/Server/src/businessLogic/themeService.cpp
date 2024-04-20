#include "themeService.hpp"

Theme ThemeService::RegisterTheme(ThemeInput input, int id)
{
    Course cor = CourseService::GetCourse(id);
    
    input.courseId = cor.id;
    
    Theme th = ThemeRepository::CreateTheme(input);

    return th;
}

Theme ThemeService::GetTheme(int id)
{
    Theme th = ThemeRepository::ReadTheme(id);

    return th;
}

std::vector<Theme> ThemeService::GetThemes(std::string token)
{
    User user = UserService::GetUser(token);
    std::vector<Theme> th = ThemeRepository::ReadThemes(user.id);

    return th;
}

Theme ThemeService::RemoveTheme(ThemeInput input)
{
    Theme th = ThemeRepository::CreateTheme(input);

    return th;
}