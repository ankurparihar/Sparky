
#include <memory>

#include "Core.h"
#include "spdlog/spdlog.h"
#include "spdlog/fmt/ostr.h"

namespace sparky {

	class Log
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

// Core log macros
#define SPARKY_CORE_TRACE(...)    ::sparky::Log::GetCoreLogger()->trace(__VA_ARGS__)
#define SPARKY_CORE_INFO(...)     ::sparky::Log::GetCoreLogger()->info(__VA_ARGS__)
#define SPARKY_CORE_WARN(...)     ::sparky::Log::GetCoreLogger()->warn(__VA_ARGS__)
#define SPARKY_CORE_ERROR(...)    ::sparky::Log::GetCoreLogger()->error(__VA_ARGS__)
// #define SP_CORE_FATAL(...)    ::sparky::Log::GetCoreLogger()->fatal(__VA_ARGS__)

// Client log macros
#define SPARKY_TRACE(...)	      ::sparky::Log::GetClientLogger()->trace(__VA_ARGS__)
#define SPARKY_INFO(...)	      ::sparky::Log::GetClientLogger()->info(__VA_ARGS__)
#define SPARKY_WARN(...)	      ::sparky::Log::GetClientLogger()->warn(__VA_ARGS__)
#define SPARKY_ERROR(...)	      ::sparky::Log::GetClientLogger()->error(__VA_ARGS__)
// #define SP__FATAL(...)	      ::sparky::Log::GetClientLogger()->fatal(__VA_ARGS__)