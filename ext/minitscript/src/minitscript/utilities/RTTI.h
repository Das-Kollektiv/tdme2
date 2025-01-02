#pragma once

#include <string>

#include <minitscript/minitscript.h>
#include <minitscript/utilities/fwd-minitscript.h>

using std::string;

/**
 * Run time type information utility class
 * @author Andreas Drewke
 */
class minitscript::utilities::RTTI {
public:
	/**
	 * @brief Demangle c++ symbol names
	 * @return demangled name
	 */
	static const string demangle(const string& name);

	/**
	 * @brief Returns the current backtrace as string
	 * @return backtrace as string
	 */
	static const string backtrace();
};
