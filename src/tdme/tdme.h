#pragma once

#include <climits>
#include <cstdint>

#if defined(_MSC_VER)
	// TODO: 128 bit primitive ordinal datatype or some workaround
	#define CPU_32BIT
#else
	#if INTPTR_MAX == INT64_MAX
		#define CPU_64BIT
	#elif INTPTR_MAX == INT32_MAX
		#define CPU_32BIT
	#else
		#error "Unknown register width or missing size macros"
	#endif
#endif
