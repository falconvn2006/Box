#pragma once

#include <memory>

#ifdef BOX_PLATFORM_WINDOWS
#if BOX_DYNAMIC_LINK
	#ifdef BOX_BUILD_DLL
		#define BOX_API __declspec(dllexport)
	#else
		#define BOX_API __declspec(dllimport)
	#endif // BOX_BUILD_DLL
#else
	#define BOX_API
#endif
#else
	#error Box only support windows
#endif

#ifdef BOX_DEBUG
	#define BOX_ENABLE_ASSERTS
#endif

#ifdef BOX_ENABLE_ASSERTS
	#define BOX_ASSERT(x, ...) { if(!(x)) { BOX_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); } }
	#define BOX_CORE_ASSERT(x, ...) { if(!(x)) { BOX_CORE_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak();  } }
#else
	#define BOX_ASSERT(x, ...)
	#define BOX_CORE_ASSERT(x, ...)
#endif

#define BIT(x) (1 << x)

#define BOX_BIND_EVENT_FN(fn) std::bind(&fn, this, std::placeholders::_1)

namespace Box
{
	template<typename T>
	using Scope = std::unique_ptr<T>;
	template<typename T, typename ... Args>
	constexpr Scope<T> CreateScope(Args&& ... args)
	{
		return std::make_unique<T>(std::forward<Args>(args)...);
	}

	template<typename T>
	using Ref = std::shared_ptr<T>;
	template<typename T, typename ... Args>
	constexpr Ref<T> CreateRef(Args&& ... args)
	{
		return std::make_shared<T>(std::forward<Args>(args)...);
	}
}