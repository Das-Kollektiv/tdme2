#pragma once

#include <agui/agui.h>
#include <agui/utilities/fwd-agui.h>

#include <chrono>
#include <ctime>
#include <string>

using std::chrono::duration_cast;
using std::chrono::high_resolution_clock;
using std::chrono::milliseconds;
using std::string;

/**
 * Time utility class
 * @author mahula
 */
class agui::utilities::Time
{
public:

	/**
	 * Retrieve current time in milliseconds
	 * @returns int64_t
	 */
	inline static int64_t getCurrentMillis() {
		return high_resolution_clock::now().time_since_epoch() / milliseconds(1);
	}

	/**
	 * Get date/time as string
	 * @param format format, see strftime
	 * @returns date/time as string
	 */
	inline static string getAsString(const string& format = "%Y-%m-%d %H:%M:%S") {
		// see: https://stackoverflow.com/questions/34963738/c11-get-current-date-and-time-as-string
		std::time_t now = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
		char timeString[256] = {0};
		std::strftime(timeString, sizeof(timeString), format.c_str(), std::localtime(&now));
		return string(timeString);
	}
};
