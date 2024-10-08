#pragma once

#include "Core.h"

namespace Box {
	class BOX_API Application {

	public:
		Application();
		virtual ~Application();


		void Run();

	};

	// Define in the client
	Application* CreateApplication();
}