#pragma once

#ifdef BOX_PLATFORM_WINDOWS

extern Box::Application* Box::CreateApplication();

int main(int args, char** argv)
{
	printf("Welcome to Box Engine!\n");
	auto app = Box::CreateApplication();
	app->Run();
	delete app;
}
#endif // BOX_PLATFORM_WINDOWS

