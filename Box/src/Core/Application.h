#pragma once

#include "Core.h"

namespace Box 
{
	class BOX_API Application
	{
	public:
		Application();
		virtual ~Application();

		void Run();
	};

	// To be defined in CLIENT
	Application* CreateApplication();
}

