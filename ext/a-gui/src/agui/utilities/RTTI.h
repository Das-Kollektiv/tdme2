#pragma once

#include <string>

#include <agui/agui.h>
#include <agui/utilities/fwd-agui.h>

using std::string;

/**
 * Run time type information utility class
 * @author Andreas Drewke
 */
class agui::utilities::RTTI {
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
