#pragma once
#include <iostream>
#include <string>
#include "../models/courseModels.hpp"
#include "../models/userModels.hpp"
#include "../models/organisationModels.hpp"
#include "../db.hpp"
#include <soci/session.h>



class CourseRepository{
public:
    CourseRepository();
    static Course CreateCourse(CourseInput input);
    static Course ReadCourse(int id);
    static Course ReadCourse(std::string name);
    static Course ReadCourseByCode(std::string code);
    static std::vector<Course> ReadCourses(uint32_t userId);
    static void DeleteCourse(int id);
    static void AddUserToCourse(uint32_t userId, uint32_t corId);
};