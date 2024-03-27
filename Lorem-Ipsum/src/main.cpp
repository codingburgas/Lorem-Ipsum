#include "Core.h"

#include <imgui.h>

class Layer : public Core::Layer
{
   void OnAttach() override
   {
      
   }

   void OnUpdate() override
   {
      
   }

   void OnImGuiRender() override
   {
      ImGui::Begin("Main");

      ImGui::Text("Hello from Vankata");

      ImGui::End();
   }
};

class Application : public Core::Application
{
public:
   Application()
   {
      PushLayer(std::shared_ptr<Layer>(new Layer));
   }

   ~Application()
   {
      
   }
};

int main()
{
   Application* app = new Application;
   app->Init({1280, 720}, "Sandbox");
   app->Run();
}