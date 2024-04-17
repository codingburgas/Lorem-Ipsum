#pragma once
#include <iostream>
#include <string>

struct User{
    int id;
    std::string name;
    std::string username;
    std::string email;
    std::string country;
    std::string password_hash;
};
struct UserInput{
    int id;
    std::string name;
    std::string username;
    std::string email;
    std::string country;
    std::string password;
};

struct UserLoginInput{
    std::string username;
    std::string password;
};

struct UserCours{
    int userId;
    int coursId;
};

struct UserBadge{
    int userId;
    int badgeId;
};