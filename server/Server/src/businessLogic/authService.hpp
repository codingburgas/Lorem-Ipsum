#include "../dataAccess/repos/userHeader.hpp"
#include "argon2.h"
#include <cstring>
#include <cstdlib>

#define HASHLEN 32
#define SALTLEN 16
#define PWD "password"

class UserService{
public:
    User registerUser(UserInput input);
    // User loginUser();
};