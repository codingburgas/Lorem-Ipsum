#include "Core.h"
#include "ApplicationLayer.h"

class Application : public Core::Application
{
public:
   Application()
   {
      PushLayer(std::shared_ptr<ApplicationLayer>(new ApplicationLayer));
   }
};

int main()
{
   Application* app = new Application;
   app->Init({1280, 720}, "Lorem Ipsum");
   app->Run();
}