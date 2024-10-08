#pragma once

#ifdef BOX_PLATFORM_WINDOWS

extern Box::Application* Box::CreateApplication();

int main(int argc, char** argv)
{
	printf("Hello World!");
	auto app = Box::CreateApplication();
	app->Run();
	delete app;
}

#endif