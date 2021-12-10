#pragma once

#include <cstdint>
#include <climits>

#if INTPTR_MAX == INT64_MAX
	#define CPU_64BIT
#elif INTPTR_MAX == INT32_MAX
	#define CPU_32BIT
#else
	#error "Unknown register width or missing size macros"
#endif
