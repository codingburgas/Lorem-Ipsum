#pragma once
#include <iostream>
#include <string>

struct Test{
    int id;
    std::string title;
};

struct Theme{
    std::string unitInfo;
    std::string title;
    bool hasHomework;
};

struct ThemeTest{
    int themeTestId;
    int testId;
};

struct QuestionTest{
    int questionId;
    int testId;
};

struct Question{
    int id;
    std::string question;
    std::string answer;
    int dificulty;
};