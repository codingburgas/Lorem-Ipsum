#include "authService.hpp"
#include <iomanip>
#include <sstream>
#include <jwt-cpp/jwt.h>
#include <string>


std::string hashingPassword(std::string password, std::string username){
    const size_t hash_length = 32;
    const size_t time_cost = 3;
    const size_t memory_cost = 65536;
    const size_t threads = 4;

    unsigned char hash[hash_length];

    int ret = argon2_hash(time_cost, memory_cost, threads, password.c_str(), password.size(),
                          username.c_str(), username.size(), hash, hash_length, nullptr, 0, Argon2_d, ARGON2_VERSION_NUMBER);
    
    std::string hashedPassword = "";
    for (size_t i = 0; i < hash_length; ++i) 
    {
        hashedPassword += std::to_string(hash[i]);
    }

    return hashedPassword;
}

User UserService::RegisterUser(UserInput input)
{
    std::string toHashedPassord = input.password;
    std::string lowerCasePass;

    for(auto i : input.username)
        lowerCasePass += std::tolower(i);
    input.username = lowerCasePass;

    input.password = hashingPassword(toHashedPassord, input.username);
    User user = UserRepository::CreateUser(input);

    return user;
}

std::string UserService::LoginUser(UserLoginInput input)
{
    std::string lowerCasePass;
    
    for(auto i : input.username)
        lowerCasePass += std::tolower(i);

    input.username = lowerCasePass;

    User user = UserRepository::ReadUser(input.username);

    std::string password_hash = hashingPassword(input.password, input.username);

    if(user.password_hash != password_hash)
    {
        throw std::invalid_argument("Invalid password");
    }

    auto token = jwt::create()
        .set_type("JWS")
        .set_issuer(user.username)
        .sign(jwt::algorithm::hs256{"secret"});

    return token;
}

bool UserService::ValidateToken(std::string token)
{
    try
    {
        jwt::decoded_jwt decoded = jwt::decode(token);
        return true;
    }
    catch(const std::exception& e)
    {
        return false;
    }
}

User UserService::GetUser(std::string token)
{
    jwt::decoded_jwt decoded = jwt::decode(token);

    std::string username;
    for (auto& el : decoded.get_payload_json())
    {
        if(el.first == "iss")
        {
            username = el.second.get<std::string>();
        }
    }

    User user = UserRepository::ReadUser(username);

    return user;
}