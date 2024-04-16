#pragma once
#include <iostream>
#include <string>
#include <pgfe/pgfe.hpp>
#include "../models/userModels.hpp"
#include "../db.hpp"

class UserRepository{
private:
    dmitigr::pgfe::Connection* conn;
public:
    UserRepository();
    User createUser(UserInput input);
    User readUser(int id);
    User readUser(std::string username);
    User updateUser(UserInput input);
    void deleteUser(int id);

};