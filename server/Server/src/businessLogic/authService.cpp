#include "authService.hpp"

User UserService::registerUser(UserInput input)
{
    // UserRepository userRepo;


    // std::string email = input.email;
    // std::string isEmail = "SELECT email FROM User WHERE email = " + email;

    // std::string username = input.username;
    // std::string isUsername = "SELECT username FROM User WHERE username = " + username;

    // std::string password = input.password;
    // if (password.size() >= 8)
    // {

    //     uint8_t hash1[HASHLEN];

    //     uint8_t salt[SALTLEN];

    //     memset(salt, 0x00, SALTLEN);

    //     uint8_t *pwd = (uint8_t *)strdup(password.c_str());
    //     uint32_t pwdlen = password.size();

    //     uint32_t t_cost = 2;
    //     uint32_t m_cost = (1 << 16);
    //     uint32_t parallelism = 1;

    //     int rc = argon2i_hash_raw(t_cost, m_cost, parallelism, pwd, pwdlen, salt, SALTLEN, hash1, HASHLEN);
    //     if (ARGON2_OK != rc)
    //     {
    //         printf("Error: %s\n", argon2_error_message(rc));
    //         exit(1);
    //     }

    //     std::string hashedPassword;
    //     for (int i = 0; i < HASHLEN; i++)
    //     {
    //         char hex[3];
    //         printf(hex, sizeof(hex), "%02x", hash1[i]);
    //         hashedPassword += hex;
    //     }
    //     password = hashedPassword;
    // }
    // else
    // {
    //     throw std::invalid_argument("Password must be at least 8 characters");
    // }
    // if (isEmail)
    // {
    //     throw std::invalid_argument("Email is already taken");
    // }
    // else
    // {
    //     if (!email.find("@") && email.find("."))
    //     {
    //         throw std::invalid_argument("Invalid email");
    //     }

        
    // }
    // if (isUsername)
    // {
    //     throw std::invalid_argument("Uername is already taken");
    // }


    

    // create user
    // User newUser;

    // newUser.name = input.name;
    // newUser.username = input.username;
    // newUser.country = input.country;
    // newUser.email = input.email;
    // newUser.password = input.password;

    // // set the jwt token

    // return newUser;
}

// User UserService::loginUser()
// {

//     // check if the username or password is correct

//     // login

//     // give jwt token
// }