#pragma once
#include <string>
#include <iostream>

struct Badge{
    int id;
    std::string title;
    std::string color;
    std::string img;
};

struct Notification{
    int userId;
    std::string title;
    std::string info;
};