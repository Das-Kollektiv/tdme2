/**
 * @version $Id: 63ea6991ff15d9217ab7fb9a4d9c79f20387bf95 $
 */

#pragma once

/**
 * JsonBox
 *
 * What is JSON?
 * [JSON](http://json.org/) (JavaScript Object Notation) is a lightweight data-interchange format.
 *
 * project_description What is Json Box?
 * Json Box is a C++ library used to read and write JSON with ease and speed.
 *
 * Things it does:
 * * Follows the standards established on [http://json.org/](http://json.org/)
 * * Read and write JSON in UTF-8
 * * Uses the STL streams for input and output
 * * Generated JSON can be indented and pretty or compact and hard-to-read
 * * Does not crash when the JSON input contains errors, it simply tries to interpret as much as it can
 *
 * Things it does not do:
 * * Read JSON in UTF-16 or UTF-32
 * * Keep the order of the members in objects (the standard doesn't require keeping the order)
 * * Write useful error messages when the JSON input contains errors
 *
 * The library wasn't designed with multi-threading in mind.
 * @see JsonBox
 */

#include "JsonException.h"
#include "Value.h"
#include "Array.h"
#include "Object.h"
