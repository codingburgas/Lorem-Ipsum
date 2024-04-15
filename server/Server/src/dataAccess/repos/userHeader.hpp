#pragma once
#include <iostream>
#include <string>
#include <pgfe/pgfe.hpp>
#include "../models/userModels.hpp"
#include "../db.hpp"

using pgfe::to;


class UserRepository{
private:
    pgfe::Connection conn;
public:
    UserRepository();
    User createUser(UserInput input);
    User readUser(int id);
    User updateUser(UserInput input);
    void deleteUser(int id);

};