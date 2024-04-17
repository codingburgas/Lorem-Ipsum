#pragma once
#include <soci/soci.h>
#include <soci/postgresql/soci-postgresql.h>

class DatabaseConnection{
public:
    inline static soci::session* sql;

    DatabaseConnection();

    static void DropDatabase();
};