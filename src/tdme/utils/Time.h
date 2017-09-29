#pragma once

#include <tdme/utils/fwd-tdme.h>

#include <chrono>

using std::chrono;

/**
 * Time-related utilities
 * @author mahula
 * @version $Id$
 */
class tdme::utils::Time final
{
public:

	/**
	 * Retrieve current time in milliseconds
	 * @return int64_t
	 */
	inline static int64_t getCurrentMillis();
}
