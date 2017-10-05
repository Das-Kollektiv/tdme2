#pragma once

#include <tdme/utils/fwd-tdme.h>

#include <chrono>

using std::chrono::duration_cast;
using std::chrono::high_resolution_clock;
using std::chrono::milliseconds;

/**
 * Time-related utilities
 * @author mahula
 * @version $Id$
 */
class tdme::utils::Time
{
public:

	/**
	 * Retrieve current time in milliseconds
	 * @return int64_t
	 */
	inline static int64_t getCurrentMillis() {
		return high_resolution_clock::now().time_since_epoch() / milliseconds(1);
	}
};
