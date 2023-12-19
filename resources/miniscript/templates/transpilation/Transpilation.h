#pragma once

#include <miniscript/miniscript.h>
#include <miniscript/miniscript/MiniScript.h>

#include <{$base-class-header}>

/**
 * MiniScript -> C++ transpilation of {$script}
 */
class {$class-name}: public {$base-class} {
public:
	// forbid class copy
	FORBID_CLASS_COPY({$class-name})

	/**
	 * Public constructor
	 */
	{$class-name}();

	/*__MINISCRIPT_TRANSPILEDMINISCRIPTCODE_DECLARATIONS_START__*/
	/*__MINISCRIPT_TRANSPILEDMINISCRIPTCODE_DECLARATIONS_END__*/

};
