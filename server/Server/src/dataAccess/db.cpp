#include "db.hpp"

DatabaseConnection::DatabaseConnection(){
    dmitigr::pgfe::Connection_options options;
    options.set(dmitigr::pgfe::Communication_mode::net)
        .set_hostname("localhost")
        .set_port(5432)
        .set_database("postgres")
        .set_username("postgres")
        .set_password("postgres");

    conn = new dmitigr::pgfe::Connection(options);

    conn->connect();
};