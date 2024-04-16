#include "db.hpp"

DatabaseConnection::DatabaseConnection()
{
    sql = new soci::session(soci::postgresql, "dbname=postgres user=postgres password=postgres host=postgres port=5432");
}