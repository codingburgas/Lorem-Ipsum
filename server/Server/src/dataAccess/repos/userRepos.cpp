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

    *DatabaseConnection::sql << "SELECT id FROM users WHERE username = " << "\'" << input.username << "\'", soci::into(user.id);

    *DatabaseConnection::sql << "INSERT INTO organisations_users(organisation_id, user_id, role) VALUES(:organisationId, :userId, 'memeber')",
        soci::use(1),
        soci::use(user.id);

    *DatabaseConnection::sql << "INSERT INTO users_courses(user_id, course_id, user_role) VALUES(:user_id, :course_id, 'member')",
        soci::use(user.id),
        soci::use(1);

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


void UserRepository::deleteUser(int id){
    User user;
    *DatabaseConnection::sql << "DELETE FROM organisations WHERE id=:id", soci::use(user.id);


}
