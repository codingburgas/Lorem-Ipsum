#include "authService.hpp"
#include <iomanip>
#include <sstream>
#include <jwt-cpp/jwt.h>

// std::string bytesToHexString(const std::vector<uint8_t>& bytes) 
// {
//     std::stringstream ss;
//     for (size_t i = 0; i < bytes.size(); ++i) {
//         ss << std::hex << std::setw(2) << std::setfill('0') << static_cast<int>(bytes[i]);
//     }
//     return ss.str();
// }

User UserService::RegisterUser(UserInput input)
{
    // const char* salt = "mysalt";
    // std::vector<uint8_t> hash;
    // int r = argon2d_hash_raw(2, 1, 1, input.password.c_str(), input.password.length(), salt, strlen(salt), hash.data(), HASHLEN);

    // input.password = bytesToHexString(hash);
    User user = UserRepository::CreateUser(input);

    return user;
}

std::string UserService::LoginUser(UserLoginInput input)
{
    User user = UserRepository::ReadUser(input.username);

    std::string password_hash = input.password;

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