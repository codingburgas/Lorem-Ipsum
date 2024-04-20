#include "courseService.hpp"


Course CourseService::RegisterCourse(CourseInput input, std::string token, int id)
{
    input.code = generateCode(6);
    User user = UserService::GetUser(token);
    Organisation org = OrganisationService::GetOrganisation(id);
    input.ownerId = user.id;
    input.organisationId = org.id;
    
    Course cor = CourseRepository::CreateCourse(input);

    return cor;
}

Course CourseService::RemoveCourse(CourseInput input, std::string token)
{
    Course cor = CourseRepository::CreateCourse(input);

    return cor;
}

std::vector<Course> CourseService::GetCourses(std::string token)
{
    User user = UserService::GetUser(token);
    std::vector<Course> orgs = CourseRepository::ReadCourses(user.id);

    return orgs;
}

Course CourseService::GetCourse(int id)
{
    Course cor = CourseRepository::ReadCourse(id);

    return cor;
}

void CourseService::JoinCourse(std::string code, std::string token)
{
    Course cor = CourseRepository::ReadCourseByCode(code);
    User user = UserService::GetUser(token);

    CourseRepository::AddUserToCourse(user.id, cor.id);
}