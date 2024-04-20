#include "db.hpp"
#include <cstdlib>
#include <string>

DatabaseConnection::DatabaseConnection()
{
    sql = new soci::session(soci::postgresql, 
    "dbname=" + (std::string)std::getenv("POSTGRES_DB") 
    + " user=" + (std::string)std::getenv("POSTGRES_USER") 
    + " password=" + (std::string)std::getenv("POSTGRES_PASSWORD") 
    + " host=" + (std::string)std::getenv("POSTGRES_HOST")
    + " port=" + (std::string)std::getenv("POSTGRES_PORT"));
}

void DatabaseConnection::DropDatabase()
{
    *sql << R"(
        DROP SCHEMA public CASCADE;
        CREATE SCHEMA public;
    )";
}