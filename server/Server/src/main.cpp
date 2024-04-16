#include <pistache/endpoint.h>
#include "rapidjson/document.h"
#include "rapidjson/writer.h"
#include "rapidjson/stringbuffer.h"
#include "./dataAccess/db.hpp"
// #include <pgfe/pgfe.hpp>

using namespace Pistache;


struct HelloHandler : public Http::Handler {
  HTTP_PROTOTYPE(HelloHandler)
  void onRequest(const Http::Request&, Http::ResponseWriter response) override {
    const char* json = "{\"name\": \"Ivan\"}";

    // rapidjson::Document d;
    // d.Parse(json);

    // rapidjson::Value& s = d["name"];
    // s.SetString("Ivan Stoychev");

    // rapidjson::StringBuffer buffer;
    // rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
    // d.Accept(writer);

    response.send(Http::Code::Ok, json);
  }
};

int main() {
  Http::listenAndServe<HelloHandler>(Pistache::Address("*:3000"));
  DatabaseConnection* db = new DatabaseConnection;
  createShema(db->conn);
}