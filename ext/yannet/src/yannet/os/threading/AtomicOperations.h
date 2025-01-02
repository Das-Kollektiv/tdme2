#pragma once

#include <yannet/yannet.h>
#include <yannet/os/threading/fwd-yannet.h>

#if defined(_WIN32) && defined(_MSC_VER)
	#define NOMINMAX
	#include <windows.h>
#endif

/**
 * Atomic operations
 * @author Andreas Drewke
 */
class yannet::os::threading::AtomicOperations {
public:

	/**
	 * Increment uint32 value and return its value
	 * @param value reference to value
	 * @param byValue value you like to add
	 * @return incremented value
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
	 * @return decremented value
	 */
	inline static uint32_t decrement(volatile uint32_t& value, uint32_t byValue = 1) {
		#if defined(_WIN32) && defined(_MSC_VER)
			return InterlockedAdd((volatile long*)&value, (long)-byValue);
		#else
			return __sync_sub_and_fetch(&value, byValue);
		#endif
	}

};
