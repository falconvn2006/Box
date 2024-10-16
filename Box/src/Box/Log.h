#pragma once

#include "Core.h"
#include "spdlog/spdlog.h"
#include "spdlog/fmt/ostr.h"

namespace Box {
	class BOX_API Log
	{
	public:
		static void Init();

		inline static std::shared_ptr<spdlog::logger>& GetCoreLogger() { return s_CoreLogger; }
		inline static std::shared_ptr<spdlog::logger>& GetClientLogger() { return s_ClientLogger; }

	private:
		static std::shared_ptr<spdlog::logger> s_CoreLogger;
		static std::shared_ptr<spdlog::logger> s_ClientLogger;

	};

}

// Box log macros
#define BOX_CORE_TRACE(...)		::Box::Log::GetCoreLogger()->trace(__VA_ARGS__)
#define BOX_CORE_INFO(...)		::Box::Log::GetCoreLogger()->info(__VA_ARGS__)
#define BOX_CORE_WARN(...)		::Box::Log::GetCoreLogger()->warn(__VA_ARGS__)
#define BOX_CORE_ERROR(...)		::Box::Log::GetCoreLogger()->error(__VA_ARGS__)
#define BOX_CORE_FATAL(...)		::Box::Log::GetCoreLogger()->fatal(__VA_ARGS__)

// Client log macros
#define BOX_TRACE(...)		::Box::Log::GetClientLogger()->trace(__VA_ARGS__)
#define BOX_INFO(...)		::Box::Log::GetClientLogger()->info(__VA_ARGS__)
#define BOX_WARN(...)		::Box::Log::GetClientLogger()->warn(__VA_ARGS__)
#define BOX_ERROR(...)		::Box::Log::GetClientLogger()->error(__VA_ARGS__)
#define BOX_FATAL(...)		::Box::Log::GetClientLogger()->fatal(__VA_ARGS__)