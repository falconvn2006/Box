#pragma once

#include "Core.h"
#include "Box/LayerStack.h"
#include "Box/Events/Event.h"
#include "Box/Events/ApplicationEvent.h"

#include "Box/Core/Timestep.h"

#include "Window.h"

#include "Box/ImGui/ImGuiLayer.h"

namespace Box {
	class Application {

	public:
		Application();
		virtual ~Application();


		void Run();

		void OnEvent(Event& e);

		void PushLayer(Layer* layer);
		void PushOverlay(Layer* overlay);

		inline static Application& Get() { return *s_Instance; }
		inline Window& GetWindow() { return *m_Window; }
	private:
		bool OnWindowClose(WindowCloseEvent& e);
	
	private:
		std::unique_ptr<Window> m_Window;
		ImGuiLayer* m_ImGuiLayer;
		bool m_Running = true;
		LayerStack m_LayerStack;
		float m_LastFrameTime = 0.0f;

	private:
		static Application* s_Instance;
	};

	// Define in the client
	Application* CreateApplication();
}