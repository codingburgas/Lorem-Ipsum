#include "./dataAccess/db.hpp"
#include "dataAccess/shema.hpp"
#include "routes/authentication.hpp"

#include <pistache/endpoint.h>
#include <pistache/router.h>

#include <iostream>

int main() {
  std::cout << "Server is running" << std::endl;

  DatabaseConnection* db = new DatabaseConnection;
  db->DropDatabase();
  createShema(db->sql);

  Pistache::Address addr(Pistache::Ipv4::any(), Pistache::Port(3000));

  auto opts = Pistache::Http::Endpoint::options().threads(1);
  Pistache::Http::Endpoint server(addr);
  server.init(opts);

  Pistache::Rest::Router authRouter;
  AuthenticationHandler authHandler;
  Pistache::Rest::Routes::Post(authRouter, "/register", Pistache::Rest::Routes::bind(&AuthenticationHandler::RegisterUser, &authHandler));
  Pistache::Rest::Routes::Post(authRouter, "/login", Pistache::Rest::Routes::bind(&AuthenticationHandler::LoginUser, &authHandler));
  Pistache::Rest::Routes::Get(authRouter, "/user", Pistache::Rest::Routes::bind(&AuthenticationHandler::GetUser, &authHandler));

  server.setHandler(authRouter.handler());
  server.serve();
  server.shutdown();
}