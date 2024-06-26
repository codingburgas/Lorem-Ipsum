#pragma once
#include "../dataAccess/repos/themeHeader.hpp"
#include "courseService.hpp"


class ThemeService{
public:
    static Theme RegisterTheme(ThemeInput input, int id);
    static Theme RemoveTheme(ThemeInput input);
    static std::vector<Theme> GetThemes(int courseId);
    static Theme GetTheme(int id);
};