#pragma once
#include <pistache/endpoint.h>
#include <pistache/router.h>

class AuthenticationHandler {
public:
    void RegisterUser(const Pistache::Rest::Request& request, Pistache::Http::ResponseWriter response);
    void GetUser(const Pistache::Rest::Request& request, Pistache::Http::ResponseWriter response);
    void LoginUser(const Pistache::Rest::Request& request, Pistache::Http::ResponseWriter response);
};