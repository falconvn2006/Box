#pragma once

#ifdef BOX_PLATFORM_WINDOWS
	#ifdef BOX_BUILD_DLL
		#define BOX_API __declspec(dllexport)
	#else
		#define BOX_API __declspec(dllimport)
	#endif // BOX_BUILD_DLL
#else
	#error Box only support windows
#endif

#define BIT(x) (1 << x)