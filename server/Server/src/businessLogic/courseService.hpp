#pragma once
#include "../dataAccess/repos/courseHeader.hpp"
#include "authService.hpp"
#include "orgService.hpp"
#include <vector>

class CourseService{
public:
    static std::vector<Course> GetCoursesByOrg(int id);
    static Course RegisterCourse(CourseInput input, std::string token, int id);
    static Course RemoveCourse(CourseInput input, std::string token);
    static std::vector<Course> GetCourses(std::string token, int id);
    static Course GetCourse(int id);
    static void JoinCourse(std::string name, std::string token);
};