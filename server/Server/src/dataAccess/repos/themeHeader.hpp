#pragma once
#include <iostream>
#include <string>
#include "../models/organisationModels.hpp"
#include "../models/userModels.hpp"
#include "../models/themeModels.hpp"

#include "../db.hpp"
#include <soci/session.h>

class ThemeRepository{
public:
    ThemeRepository();
    static Theme CreateTheme(ThemeInput input);
    static Theme ReadTheme(int id);
    static Theme ReadTheme(std::string title);
    static std::vector<Theme> ReadThemes(uint32_t userId);
    static void DeleteTheme(int id);
};