#pragma once

#include "Core.h"
#include "Box/LayerStack.h"
#include "Box/Events/Event.h"
#include "Box/Events/ApplicationEvent.h"
#include "Window.h"

#include "Box/ImGui/ImGuiLayer.h"

// Temporary
#include "Box/Renderer/Shader.h"

namespace Box {
	class BOX_API Application {

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

		std::unique_ptr<Window> m_Window;
		ImGuiLayer* m_ImGuiLayer;
		bool m_Running = true;
		LayerStack m_LayerStack;

		unsigned int m_VertexArray, m_VertexBuffer, m_IndexBuffer;
		std::unique_ptr<Shader> m_Shader;
	private:
		static Application* s_Instance;
	};

	// Define in the client
	Application* CreateApplication();
}