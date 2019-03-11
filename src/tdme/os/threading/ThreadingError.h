/**
 * @version $Id: 9d8dfaef0d634c38ad446b419df31cc9f50a2c0a $
 */

#pragma once

#include <iostream>
#include <string>

using std::cout;
using std::endl;
using std::string;
using std::to_string;

#define PTHREAD_CHECK_ERROR(NAME, MSG, FUNCTION) if (result != 0) cout << (NAME + "(" + FUNCTION + "): " + MSG + "(" + to_string(result) + ")") << endl;
