#include "../dataAccess/repos/userHeader.hpp"
#include "argon2.h"
#include <cstring>
#include <cstdlib>

#define HASHLEN 32
#define SALTLEN 16

class UserService{
public:
    static User RegisterUser(UserInput input);
    static std::string LoginUser(UserLoginInput input);
    static bool ValidateToken(std::string token);
    static User GetUser(std::string token);
};