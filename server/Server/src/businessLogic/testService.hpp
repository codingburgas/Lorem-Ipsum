#pragma once
#include "../dataAccess/repos/testHeader.hpp"
#include "themeService.hpp"


class TestService{
public:
    static Test RegisterTest(TestInput input, int id);
    static Test RemoveTest(TestInput input);
    static std::vector<Test> GetTests(int themeId);
    static Test GetTest(int id);
};