#include <Box.h>

class Sandbox : public Box::Application 
{
public:
	Sandbox() 
	{

	}

	~Sandbox() 
	{
		
	}
};

Box::Application* Box::CreateApplication() 
{
	return new Sandbox();
}

/*
int main() 
{
	Sandbox* sandbox = new Sandbox();
	sandbox->Run();
	delete sandbox;
}

*/