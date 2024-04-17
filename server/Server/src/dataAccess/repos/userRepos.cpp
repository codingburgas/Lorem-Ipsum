#include "userHeader.hpp"

UserRepository::UserRepository() {};

User UserRepository::CreateUser(UserInput input)
{
    *DatabaseConnection::sql << "SELECT * FROM users WHERE username = :username", soci::use(input.username);

    if(DatabaseConnection::sql->got_data())
    {
        throw std::invalid_argument("Username already exists");
    }

    User user;
    user.name = input.name;
    user.username = input.username;
    user.email = input.email;
    user.country = input.country;

    *DatabaseConnection::sql << "INSERT INTO users(name, username, email, country, password_hash) VALUES(:name, :username, :email, :country, :password_hash)",
        soci::use(input.name), soci::use(input.username), soci::use(input.email), soci::use(input.country), soci::use(input.password);

    return user;
}

User UserRepository::ReadUser(int id)
{
    User user;
    *DatabaseConnection::sql << "SELECT id, name, username, email, country, password_hash FROM users WHERE id = " << id, soci::into(user.id), soci::into(user.name), soci::into(user.username), soci::into(user.email), soci::into(user.country), soci::into(user.password_hash);

    return user;
}

User UserRepository::ReadUser(std::string username)
{
    User user;
    *DatabaseConnection::sql << "SELECT id, name, username, email, country, password_hash FROM users WHERE username = \'" << username << "\'", soci::into(user.id), soci::into(user.name), soci::into(user.username), soci::into(user.email), soci::into(user.country), soci::into(user.password_hash);

    return user;
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
