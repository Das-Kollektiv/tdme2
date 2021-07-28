#pragma once

#include <string>

#include <tdme/utilities/fwd-tdme.h>

using std::string;

/**
 * Run time type information utility class
 * @author Andreas Drewke
 */
class tdme::utilities::RTTI {
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
