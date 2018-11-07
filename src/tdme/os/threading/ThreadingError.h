/**
 * @version $Id: 9d8dfaef0d634c38ad446b419df31cc9f50a2c0a $
 */

#pragma once

#include <string>

#include <tdme/utils/Console.h>

using std::string;
using std::to_string;

using tdme::utils::Console;

#define PTHREAD_CHECK_ERROR(NAME, MSG, FUNCTION) if (result != 0) Console::println(NAME + "(" + FUNCTION + "): " + MSG + "(" + to_string(result) + ")");
