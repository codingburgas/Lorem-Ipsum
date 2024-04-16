#include "userHeader.hpp"

// UserRepository::UserRepository():conn(DatabaseConnection().conn){};

User UserRepository::createUser(UserInput input){
    // User out;
    // conn->execute(
    //     [&](auto && row){
    //         out.id = to<int>(row["id"]);
    //         out.name = to<std::string>(row["name"]);
    //         out.username = to<std::string>(row["username"]);
    //         out.email = to<std::string>(row["email"]);
    //         out.country = to<std::string>(row["country"]);
    //         out.password = to<std::string>(row["password"]);
    //     },
    //     "INSERT INTO User (id, firstName, username, email, country, password) VALUES ($1::integer, $2::string, $3::string, $4::string, $5::string, $6::string) RETURNING id, name, username, email, country, password",
    //     input.id, input.name, input.username, input.email, input.country, input.password
        
    // );
    // return out;
}

User UserRepository::readUser(int id){
    // User user;
    // conn->execute(
    //     [&](auto && row){
    //         user.id = to<int>(row["id"]);
    //         user.name = to<std::string>(row["name"]);
    //         user.username = to<std::string>(row["username"]);
    //         user.email = to<std::string>(row["email"]);
    //         user.country = to<std::string>(row["country"]);
    //         user.password = to<std::string>(row["password"]);
    //     },
    //     "SELECT * FROM User WHERE id = $1::integer",
    //     id
        
    // );
    // return user;
}
User UserRepository::updateUser(UserInput input){
    // User out;
    // conn->execute(
    //     [&](auto && row){
    //         out.username = to<std::string>(row["username"]);
    //         out.email = to<std::string>(row["email"]);
    //         out.country = to<std::string>(row["country"]);
    //         out.password = to<std::string>(row["password"]);
    //     },
    //     "UPDATE User SET username=$1::string, email=$2::string, country=$3::string, password=4$::string WHERE id=$5::int",
    //     input.username, input.email, input.country, input.password
    // );
    // return out;
}
void UserRepository::deleteUser(int id){
    // conn->execute("DELETE FROM User WHERE id=$1::integer",id);
}
