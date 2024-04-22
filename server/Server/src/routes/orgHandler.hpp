#pragma once
#include <pistache/endpoint.h>
#include <pistache/router.h>

class OrganizationsHandler {
public:
    void CreateOrganisation(const Pistache::Rest::Request& request, Pistache::Http::ResponseWriter response);
    void GetOrganisations(const Pistache::Rest::Request& request, Pistache::Http::ResponseWriter response);
    void GetOrganisation(const Pistache::Rest::Request& request, Pistache::Http::ResponseWriter response);
    void JoinOrganisation(const Pistache::Rest::Request& request, Pistache::Http::ResponseWriter response);
};