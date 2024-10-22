#include<Box.h>

class ExampleLayer : public Box::Layer
{
public:
	ExampleLayer() :Layer("Example"){}

	void OnUpdate() override
	{
		BOX_INFO("ExampleLayer::Update");
	}

	void OnEvent(Box::Event& event) override
	{
		BOX_TRACE("{0}", event.ToString());
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