#include "bph.h"
#include "Application.h"

#include "Events/ApplicationEvent.h"
#include "Log.h"

namespace Box 
{
	Application::Application()
	{

	}

	Application::~Application()
	{

	}

	void Application::Run() 
	{
		WindowResizeEvent e(1200, 720);
		BOX_CLIENT_TRACE(e);

		while (true);
	}
}
