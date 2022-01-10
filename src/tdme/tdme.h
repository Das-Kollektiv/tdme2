#pragma once

#include <climits>
#include <cstdint>

#if defined(TDME2_DLL_EXPORT)
	#define STATIC_DLL_IMPEXT __declspec(dllexport)
#elif defined(TDME2_DLL_IMPORT)
	#define STATIC_DLL_IMPEXT __declspec(dllimport)
#else
	#define STATIC_DLL_IMPEXT
#endif

#if INTPTR_MAX == INT64_MAX
	#define CPU_64BIT
#elif INTPTR_MAX == INT32_MAX
	#define CPU_32BIT
#else
	#error "Unknown register width or missing size macros"
#endif
