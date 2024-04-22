#include "./dataAccess/db.hpp"
#include "dataAccess/shema.hpp"
#include "routes/authHandler.hpp"
#include "routes/orgHandler.hpp"
#include "routes/corHandler.hpp"
#include "routes/themeHandler.hpp"
#include "routes/testHandler.hpp"
#include "routes/quHandler.hpp"

#include <pistache/endpoint.h>
#include <pistache/router.h>

#include <iostream>

int main() {
  srand((unsigned)time(NULL) * getpid());
  std::cout << "Server is running" << std::endl;

  DatabaseConnection* db = new DatabaseConnection;
  db->DropDatabase();
  createShema(db->sql);

  Pistache::Address addr(Pistache::Ipv4::any(), Pistache::Port(std::getenv("PORT")));

  auto opts = Pistache::Http::Endpoint::options().threads(1);
  Pistache::Http::Endpoint server(addr);
  server.init(opts);

  Pistache::Rest::Router router;
  AuthHandler authHandler;
  Pistache::Rest::Routes::Post(router, "/register", Pistache::Rest::Routes::bind(&AuthHandler::RegisterUser, &authHandler));
  Pistache::Rest::Routes::Post(router, "/login", Pistache::Rest::Routes::bind(&AuthHandler::LoginUser, &authHandler));
  Pistache::Rest::Routes::Get(router, "/user", Pistache::Rest::Routes::bind(&AuthHandler::GetUser, &authHandler));

  OrganizationsHandler orgHandler;
  Pistache::Rest::Routes::Post(router, "/organizations/create", Pistache::Rest::Routes::bind(&OrganizationsHandler::CreateOrganisation, &orgHandler));
  Pistache::Rest::Routes::Get(router, "/organizations", Pistache::Rest::Routes::bind(&OrganizationsHandler::GetOrganisations, &orgHandler));
  Pistache::Rest::Routes::Get(router, "/organizations/:id", Pistache::Rest::Routes::bind(&OrganizationsHandler::GetOrganisation, &orgHandler));
  Pistache::Rest::Routes::Post(router, "/organizations/join", Pistache::Rest::Routes::bind(&OrganizationsHandler::JoinOrganisation, &orgHandler));

  CourseHandler corHandler;
  Pistache::Rest::Routes::Post(router, "/course/create", Pistache::Rest::Routes::bind(&CourseHandler::CreateCourse, &corHandler));
  Pistache::Rest::Routes::Get(router, "/courses", Pistache::Rest::Routes::bind(&CourseHandler::GetCourses, &corHandler));
  Pistache::Rest::Routes::Get(router, "/course/:id", Pistache::Rest::Routes::bind(&CourseHandler::GetCourse, &corHandler));
  Pistache::Rest::Routes::Post(router, "/course/join", Pistache::Rest::Routes::bind(&CourseHandler::JoinCourse, &corHandler));
  Pistache::Rest::Routes::Get(router, "/courses/:id", Pistache::Rest::Routes::bind(&CourseHandler::GetCourseByOrg, &corHandler));

  ThemeHandler thHandler;
  Pistache::Rest::Routes::Post(router, "/theme/create", Pistache::Rest::Routes::bind(&ThemeHandler::CreateTheme, &thHandler));
  Pistache::Rest::Routes::Get(router, "/themes/:id", Pistache::Rest::Routes::bind(&ThemeHandler::GetThemes, &thHandler));
  Pistache::Rest::Routes::Get(router, "/theme/:id", Pistache::Rest::Routes::bind(&ThemeHandler::GetTheme, &thHandler));

  TestHandler ttHandler;
  Pistache::Rest::Routes::Post(router, "/test/create", Pistache::Rest::Routes::bind(&TestHandler::CreatTest, &ttHandler));
  Pistache::Rest::Routes::Get(router, "/tests/:id", Pistache::Rest::Routes::bind(&TestHandler::GetTests, &ttHandler));
  Pistache::Rest::Routes::Get(router, "/test/:id", Pistache::Rest::Routes::bind(&TestHandler::GetTest , &ttHandler));
  
  QuestionHandler quHandler;
  Pistache::Rest::Routes::Post(router, "/question/create", Pistache::Rest::Routes::bind(&QuestionHandler::CreateQuestion, &quHandler));
  Pistache::Rest::Routes::Get(router, "/questions/:id", Pistache::Rest::Routes::bind(&QuestionHandler::GetQuestions, &quHandler));
  Pistache::Rest::Routes::Get(router, "/question/:id", Pistache::Rest::Routes::bind(&QuestionHandler::GetQuestion , &quHandler));
  


  server.setHandler(router.handler());
  server.serve();
  server.shutdown();
}