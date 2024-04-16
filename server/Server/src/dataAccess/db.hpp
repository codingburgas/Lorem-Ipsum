#pragma once
#include "shema.hpp"

class DatabaseConnection{
public:
    dmitigr::pgfe::Connection* conn = nullptr;

    DatabaseConnection();
};