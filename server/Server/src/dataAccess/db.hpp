#pragma once
#include <pgfe/pgfe.hpp>

namespace pgfe = dmitigr::pgfe;

class DatabaseConnection{
public:
     pgfe::Connection conn{pgfe::Connection_options{}
    .set(pgfe::Communication_mode::net)
    .set_hostname("localhost")
    .set_port(5432)
    .set_database("postgres")
    .set_username("postgres")
    .set_password("postgres")};


    DatabaseConnection(){
        conn.connect();
    };
    bool isConnected()const{
        return conn.is_connected();
    }
};