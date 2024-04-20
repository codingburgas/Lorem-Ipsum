#pragma once
#include <pistache/endpoint.h>
#include <pistache/router.h>

class CourseHandler {
public:
    void CreateCourse(const Pistache::Rest::Request& request, Pistache::Http::ResponseWriter response);
    void GetCourses(const Pistache::Rest::Request& request, Pistache::Http::ResponseWriter response);
    void GetCourse(const Pistache::Rest::Request& request, Pistache::Http::ResponseWriter response);
    void JoinCourse(const Pistache::Rest::Request& request, Pistache::Http::ResponseWriter response);
};