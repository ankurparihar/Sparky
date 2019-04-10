#pragma once

#ifdef SPARKY_ENABLE_ASSERTS
#define SPARKY_ASSERT(x, ...) { if(!(x)) { SPARKY_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); } }
#define SPARKY_CORE_ASSERT(x, ...) { if(!(x)) { SPARKY_CORE_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); } }
#else
#define SPARKY_ASSERT(x, ...)
#define SPARKY_CORE_ASSERT(x, ...)
#endif

#define BIT(x) (1 << x)