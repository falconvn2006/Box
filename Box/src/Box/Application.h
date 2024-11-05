#pragma once

#include "Core.h"
#include "Box/LayerStack.h"
#include "Box/Events/Event.h"
#include "Box/Events/ApplicationEvent.h"
#include "Window.h"

#include "Box/ImGui/ImGuiLayer.h"

// Temporary
#include "Box/Renderer/Shader.h"
#include "Box/Renderer/Buffer.h"
#include "Box/Renderer/VertexArray.h"

#include "Box/Renderer/OrthographicCamera.h"

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

		std::shared_ptr<Shader> m_Shader;
		std::shared_ptr<VertexArray> m_VertexArray;

		std::shared_ptr<Shader> m_BlueShader;
		std::shared_ptr<VertexArray> m_SquareVertexArray;

		OrthographicCamera m_Camera;
	private:
		static Application* s_Instance;
	};

	// Define in the client
	Application* CreateApplication();
}