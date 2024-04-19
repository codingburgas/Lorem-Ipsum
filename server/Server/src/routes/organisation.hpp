#pragma once
#include <pistache/endpoint.h>
#include <pistache/router.h>

class AuthenticationHandler {
public:
    void CreatOrganisation(const Pistache::Rest::Request& request, Pistache::Http::ResponseWriter response);
    void GetOrganisation(const Pistache::Rest::Request& request, Pistache::Http::ResponseWriter response);
    void JoinOrganisation(const Pistache::Rest::Request& request, Pistache::Http::ResponseWriter response);
};