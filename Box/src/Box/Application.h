#pragma once

#include "Core.h"
#include "Box/LayerStack.h"
#include "Box/Events/Event.h"
#include "Box/Events/ApplicationEvent.h"
#include "Window.h"

namespace Box {
	class BOX_API Application {

	public:
		Application();
		virtual ~Application();


		void Run();

		void OnEvent(Event& e);

		void PushLayer(Layer* layer);
		void PushOverlay(Layer* overlay);
	private:
		bool OnWindowClose(WindowCloseEvent& e);

		std::unique_ptr<Window> m_Window;
		bool m_Running = true;
		LayerStack m_LayerStack;
	};

	// Define in the client
	Application* CreateApplication();
}