#pragma once

#ifdef BOX_PLATFORM_WINDOWS
	#ifdef BOX_BUILD_DLL
		#define BOX_API __declspec(dllexport)
	#else
		#define BOX_API __declspec(dllimport)
	#endif // BOX_BUILD_DLL

#else
	#error Box only support Windows!
#endif

#ifdef BOX_ENABLE_ASSERTS
	#define BOX_ASSERT(x, ...) { if(!(x)) { BOX_CLIENT_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak();} }
	#define	BOX_CORE_ASSERT(x, ...) { if(!(x)) {BOX_CORE_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); } }
#else
	#define BOX_ASSERT(x, ...)
	#define BOX_CORE_ASSERT(x, ...)
#endif

#define BIT(x) (1 << x)