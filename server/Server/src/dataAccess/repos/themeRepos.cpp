#include "themeHeader.hpp"

ThemeRepository::ThemeRepository() {};

Theme ThemeRepository::CreateTheme(ThemeInput input)
{
    *DatabaseConnection::sql << "SELECT * FROM themes WHERE title = :title", soci::use(input.title);

    if(DatabaseConnection::sql->got_data())
    {
        throw std::invalid_argument("Theme already exist");
    }
    
    Theme th;
    th.title = input.title;
    th.unitInfo = input.unitInfo;
    th.courseId = input.courseId;
    
    *DatabaseConnection::sql << "INSERT INTO themes(title, info, course_id) VALUES(:title, :info, :course_id)",
        soci::use(th.title),
        soci::use(th.unitInfo),
        soci::use(th.courseId);


    return th;
}

Theme ThemeRepository::ReadTheme(int id)
{
    Theme th;
    *DatabaseConnection::sql << "SELECT id, title, info, course_id FROM themes WHERE id = " << id, soci::into(th.id), soci::into(th.title), soci::into(th.unitInfo), soci::into(th.courseId);

    return th;
}

Theme ThemeRepository::ReadTheme(std::string title)
{
    Theme th;
    *DatabaseConnection::sql << "SELECT id, title, info, course_id FROM themes WHERE title = " << "\'" << title << "\'", soci::into(th.id), soci::into(th.title), soci::into(th.unitInfo), soci::into(th.courseId) ;

    return th;
}

std::vector<Theme> ThemeRepository::ReadThemes(uint32_t course_id)
{

    std::vector<Theme> themes;
    Theme th;
    soci::rowset<soci::row> rs = (DatabaseConnection::sql->prepare << "SELECT id, title, course_id, info FROM themes WHERE course_id =:courseId", soci::use(course_id));

    for (soci::rowset<soci::row>::const_iterator it = rs.begin(); it != rs.end(); ++it)
    {
        soci::row const &row = *it;
        th.id = row.get<int>(0);
        th.title = row.get<std::string>(1);
        th.courseId = row.get<int>(2);
        th.unitInfo = row.get<std::string>(3);
        themes.push_back(th);
    }

    return themes;
}

void ThemeRepository::DeleteTheme(int id){
    Theme th;
    *DatabaseConnection::sql << "DELETE FROM themes WHERE id=:id", soci::use(th.id);

}