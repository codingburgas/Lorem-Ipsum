#pragma once
#include <iostream>
#include <string>
#include "../models/userModels.hpp"
#include "../db.hpp"
#include <soci/session.h>

class UserRepository{
public:
    UserRepository();
    static User CreateUser(UserInput input);
    static User ReadUser(int id);
    static User ReadUser(std::string username);
    static void deleteUser(int id);
};