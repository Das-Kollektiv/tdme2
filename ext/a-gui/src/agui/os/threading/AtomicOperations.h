#pragma once

#include <agui/os/threading/fwd-agui.h>

#include <agui/agui.h>

#if defined(_WIN32) && defined(_MSC_VER)
	#define NOMINMAX
	#include <windows.h>
#endif

/**
 * Atomic operations
 * @author Andreas Drewke
 */
class agui::os::threading::AtomicOperations {
public:

	/**
	 * Increment uint32 value and return its value
	 * @param value reference to value
	 * @param byValue value you like to add
	 * @returns incremented value
	 */
	inline static uint32_t increment(volatile uint32_t& value, uint32_t byValue = 1) {
		#if defined(_WIN32) && defined(_MSC_VER)
			return InterlockedAdd((volatile long*)&value, (long)byValue);
		#else
			return __sync_add_and_fetch(&value, byValue);
		#endif
	}

	/**
	 * Decrement uint32 value and return its value
	 * @param value reference to value
	 * @param byValue value you like to subtract
	 * @returns decremented value
	 */
	inline static uint32_t decrement(volatile uint32_t& value, uint32_t byValue = 1) {
		#if defined(_WIN32) && defined(_MSC_VER)
			return InterlockedAdd((volatile long*)&value, (long)-byValue);
		#else
			return __sync_sub_and_fetch(&value, byValue);
		#endif
	}

};
