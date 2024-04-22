#pragma once
#include <pistache/endpoint.h>
#include <pistache/router.h>

class TestHandler {
public:
    void CreatTest(const Pistache::Rest::Request& request, Pistache::Http::ResponseWriter response);
    void GetTest(const Pistache::Rest::Request& request, Pistache::Http::ResponseWriter response);
    void GetTests(const Pistache::Rest::Request& request, Pistache::Http::ResponseWriter response);
};