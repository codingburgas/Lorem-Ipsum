#pragma once
#include <iostream>
#include <string>
#include "../models/userModels.hpp"
#include "../db.hpp"
#include <soci/session.h>

class UserRepository{
private:
    soci::session* sql;
public:
    UserRepository();
    User createUser(UserInput input);
    User readUser(int id);
    User readUser(std::string username);
    User updateUser(UserInput input);
    void deleteUser(int id);

};