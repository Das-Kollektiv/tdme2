
#pragma once

#include <string>

#include <tdme.h>
#include <tdme/os/threading/fwd-tdme.h>
#include <tdme/os/threading/Mutex.h>
#include <tdme/utils/fwd-tdme.h>

using std::string;

/** 
 * Console 
 * @author Andreas Drewke
 * @versio $Id$
 */
class tdme::utils::Console
{
public:
	/** 
	 * Print given string and trailing newline to console
	 * @param string
	 */
	static void println(const string& str);

	/** 
	 * Print given string
	 * @param string
	 */
	static void print(const string& str);

	/** 
	 * Print new line to console
	 * @param text
	 */
	static void println();

private:
	static Mutex mutex;
};
