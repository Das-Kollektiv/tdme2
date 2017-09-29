#include <tdme/utils/Time.h>

using std::chrono;

using tdme::utils::Time;

inline static int64_t Time::getCurrentMillis()
{
	return chrono::duration_cast<chrono::milliseconds>(chrono::high_resolution_clock::now() - chrono::high_resolution_clock::from_time_t(0)).count();
}
