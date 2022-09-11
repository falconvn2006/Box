#pragma once

#ifdef BOX_PLATFORM_WINDOWS

extern Box::Application* Box::CreateApplication();

int main(int args, char** argv)
{
	Box::Log::Init();
	BOX_CORE_WARN("Log Initialized!");
	std::string msg = "World";
	BOX_CLIENT_INFO("Hello {0}!", msg);

	//printf("Welcome to Box Engine!\n");
	auto app = Box::CreateApplication();
	app->Run();
	delete app;
}
#endif // BOX_PLATFORM_WINDOWS

