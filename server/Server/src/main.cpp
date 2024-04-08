#include <pistache/endpoint.h>

using namespace Pistache;

struct HelloHandler : public Http::Handler {
  HTTP_PROTOTYPE(HelloHandler)
  void onRequest(const Http::Request&, Http::ResponseWriter response) override {
    response.send(Http::Code::Ok, "Az sum bog");
  }
};

int main() {
  Http::listenAndServe<HelloHandler>(Pistache::Address("*:3000"));
}