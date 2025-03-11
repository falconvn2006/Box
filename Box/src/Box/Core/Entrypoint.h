#pragma once

#ifdef BOX_PLATFORM_WINDOWS

extern Box::Application* Box::CreateApplication();

int main(int argc, char** argv)
{
	Box::Log::Init();

	BOX_CORE_WARN("Core engine intialized");
	BOX_INFO("Hello World!");

	auto app = Box::CreateApplication();
	app->Run();
	delete app;
}

#endif