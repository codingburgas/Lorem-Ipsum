#include "pch.h"
#include "Application.h"

#include "imgui_impl_raylib.h"

namespace Core {
	Application::Application()
	{
		assert(!s_Instance, "Application already exists");

		s_Instance = this;
	}

	void Application::Init(glm::vec2 size, std::string title)
	{
		m_Window.reset(Window::CreateWindow(size.x, size.y, title));
		m_Window->Init();

#ifndef IMGUI_DISABLED
		ImGui::CreateContext();
		
		ImGuiIO& io = ImGui::GetIO(); (void)io;
		io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
		io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;

		ImGui::StyleColorsDark();

		ImGui_ImplRaylib_Init();
#endif
	}

	void Application::Run()
	{
		for(auto layer : m_LayerStack)
		{ 
			layer->OnAttach();
		}

		while (m_IsRunning)
		{
			if(m_Window->IsWindowOpen())
			{
				m_IsRunning = false;
			}
			
#ifdef IMGUI_DISABLED
			BeginDrawing();
#endif
			
			for(auto layer : m_LayerStack)
			{ 
				layer->OnUpdate();
			}

			for(auto layer : m_LayerStack)
			{ 
				layer->OnUIRender();
			}
			
#ifdef IMGUI_DISABLED
			EndDrawing();
#endif

#ifndef IMGUI_DISABLED
			ImGui_ImplRaylib_ProcessEvents();

			ImGui_ImplRaylib_NewFrame();
			ImGui::NewFrame();

			ImGui::DockSpaceOverViewport(ImGui::GetMainViewport());

			for(auto layer : m_LayerStack)
			{ 
				layer->OnImGuiRender();
			}
#endif

#ifndef IMGUI_DISABLED
			ImGui::Render();

			BeginDrawing();
			ImGui_ImplRaylib_RenderDrawData(ImGui::GetDrawData());
			EndDrawing();
#endif
		}

		for(auto layer : m_LayerStack)
		{ 
			layer->OnDetach();
		}
		
#ifndef IMGUI_DISABLED
		ImGui_ImplRaylib_Shutdown();
		ImGui::DestroyContext();
#endif
	}
}
