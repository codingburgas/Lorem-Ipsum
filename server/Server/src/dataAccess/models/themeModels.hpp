#pragma once
#include <string>

struct Theme{
    int id;
    int courseId;
    std::string unitInfo;
    std::string title;
};

struct ThemeInput{
    int id;
    int courseId;
    std::string unitInfo;
    std::string title;

};

struct ThemeTest{
    int themeTestId;
    int testId;
};

struct ThemeCourse{
    int themeId;
    int courseId;
};
