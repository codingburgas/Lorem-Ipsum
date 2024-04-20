#pragma once
#include <pistache/endpoint.h>
#include <pistache/router.h>

class ThemeHandler {
public:
    void CreateTheme(const Pistache::Rest::Request& request, Pistache::Http::ResponseWriter response);
    void GetTheme(const Pistache::Rest::Request& request, Pistache::Http::ResponseWriter response);
    void GetThemes(const Pistache::Rest::Request& request, Pistache::Http::ResponseWriter response);
};