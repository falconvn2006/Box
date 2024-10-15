#include "Application.h"

#include "Box/Events/ApplicationEvent.h"
#include "Box/Log.h"

namespace Box {

	Application::Application()
	{

	}

	Application::~Application()
	{

	}

	void Application::Run()
	{
		WindowResizeEvent e(1280, 720);
		BOX_TRACE(e.ToString());

		while (true);
	}
}