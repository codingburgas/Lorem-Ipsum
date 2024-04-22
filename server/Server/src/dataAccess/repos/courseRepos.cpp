#include "courseHeader.hpp"
#include "organisationHeader.hpp"

CourseRepository::CourseRepository() {};

std::vector<Course> CourseRepository::ReadCoursesByOrg(int id)
{
    std::vector<Course> courses;
    Course cor;
    soci::rowset<soci::row> rs = (DatabaseConnection::sql->prepare << "SELECT id, name, owner_id, organisation_id, subject, code FROM courses WHERE organisation_id = :id", soci::use(id));

    for (soci::rowset<soci::row>::const_iterator it = rs.begin(); it != rs.end(); ++it)
    {
        soci::row const &row = *it;
        cor.id = row.get<int>(0);
        cor.organisationId = row.get<int>(3);
        cor.name = row.get<std::string>(1);
        cor.ownerId = row.get<int>(2);
        cor.code = row.get<std::string>(5);
        cor.subject = row.get<std::string>(4);
        courses.push_back(cor);
    }

    return courses;
}

Course CourseRepository::CreateCourse(CourseInput input)
{   
    
    Course cor;
    cor.name = input.name;
    cor.subject = input.subject;
    cor.code = input.code;
    cor.ownerId = input.ownerId;
    cor.organisationId = input.organisationId;
    
    *DatabaseConnection::sql << "INSERT INTO courses(name, owner_id, organisation_id, code, subject) VALUES(:name, :owner_id, :organisation_id, :code, :subject)",
        soci::use(cor.name),
        soci::use(cor.ownerId),
        soci::use(cor.organisationId),
        soci::use(cor.code),
        soci::use(cor.subject);

    *DatabaseConnection::sql << "SELECT id FROM courses WHERE code = " << "\'" << cor.code << "\'", soci::into(cor.id);

    *DatabaseConnection::sql << "INSERT INTO organisations_courses(organisation_id, course_id) VALUES(:organisation_id, :course_id)",
        soci::use(cor.organisationId),
        soci::use(cor.id);

    *DatabaseConnection::sql << "INSERT INTO users_courses(user_id, course_id, user_role) VALUES(:user_id, :course_id, 'owner')",
        soci::use(cor.ownerId),
        soci::use(cor.id);
    
    return cor;
}

Course CourseRepository::ReadCourse(int id)
{
    Course cor;
    *DatabaseConnection::sql << "SELECT id, name, owner_id, organisation_id, subject, code FROM courses WHERE id = " << id, soci::into(cor.id), soci::into(cor.name), soci::into(cor.ownerId), soci::into(cor.organisationId), soci::into(cor.subject), soci::into(cor.code);

    return cor;
}

Course CourseRepository::ReadCourse(std::string name)
{
    Course cor;
    *DatabaseConnection::sql << "SELECT id, name, owner_id, organisation_id, subject, code FROM courses WHERE name = " << name, soci::into(cor.id), soci::into(cor.name), soci::into(cor.ownerId), soci::into(cor.organisationId), soci::into(cor.subject);

    return cor;
}
Course CourseRepository::ReadCourseByCode(std::string code)
{
    Course cor;
    *DatabaseConnection::sql << "SELECT id, name, owner_id, organisation_id, subject, code FROM courses WHERE code = " << "\'" << code << "\'", soci::into(cor.id), soci::into(cor.name), soci::into(cor.ownerId), soci::into(cor.code);

    return cor;
}


void CourseRepository::DeleteCourse(int id){
    Course cor;
    *DatabaseConnection::sql << "DELETE FROM courses WHERE id=:id", soci::use(cor.id);

}

std::vector<Course> CourseRepository::ReadCourses(uint32_t userId, uint32_t orgId)
{

    std::vector<Course> courses;
    Course cor;
    soci::rowset<soci::row> rs = (DatabaseConnection::sql->prepare << "SELECT o.id, o.name, o.subject, o.owner_id, o.organisation_id, o.code FROM courses o JOIN users_courses ou ON o.id = ou.course_id WHERE ou.user_id = :userId AND o.organisation_id = :organisationId", soci::use(userId), soci::use(orgId));

    for (soci::rowset<soci::row>::const_iterator it = rs.begin(); it != rs.end(); ++it)
    {
        soci::row const &row = *it;
        cor.id = row.get<int>(0);
        cor.organisationId = row.get<int>(3);
        cor.name = row.get<std::string>(1);
        cor.ownerId = row.get<int>(3);
        cor.code = row.get<std::string>(5);
        cor.subject = row.get<std::string>(2);
        courses.push_back(cor);
    }

    return courses;
}

void CourseRepository::AddUserToCourse(uint32_t userId, uint32_t corId)
{
    *DatabaseConnection::sql << "INSERT INTO users_courses(course_id, user_id, user_role) VALUES(:course_id, :user_id, 'member')",
        soci::use(corId),
        soci::use(userId);
}
