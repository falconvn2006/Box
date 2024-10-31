#include<Box.h>
#include "imgui/imgui.h"

class ExampleLayer : public Box::Layer
{
public:
	ExampleLayer() :Layer("Example"){}

	void OnUpdate() override
	{
		/*BOX_INFO("ExampleLayer::Update");*/
	}

	void OnImGuiRender() override
	{
		ImGui::Begin("Test");
		ImGui::Text("Hello World!");
		ImGui::End();
	}

	void OnEvent(Box::Event& event) override
	{
		/*BOX_TRACE("{0}", event.ToString());*/

		if (event.GetEventType() == Box::EventType::KeyPressed)
		{
			Box::KeyPressedEvent& e = (Box::KeyPressedEvent&)event;
			BOX_TRACE("{0}", (char)e.GetKeyCode());
		}
	}
};

class Sandbox : public Box::Application
{
public:
	Sandbox()
	{
		PushLayer(new ExampleLayer());
	}

	~Sandbox()
	{

	}
};

Box::Application* Box::CreateApplication()
{
	return new Sandbox();
}