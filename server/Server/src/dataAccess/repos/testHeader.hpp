#pragma once
#include <iostream>
#include <string>
#include "../models/organisationModels.hpp"
#include "../models/userModels.hpp"
#include "../models/themeModels.hpp"
#include "../models/testModels.hpp"

#include "../db.hpp"
#include <soci/session.h>



class TestRepository{
public:
    TestRepository();
    static Test CreateTest(ThemeInput input);
    static Test RedTest(int id);
    static Test ReadTest(std::string title);
    static std::vector<Test> ReadTests(uint32_t userId);
    static void DeleteTest(int id);
};