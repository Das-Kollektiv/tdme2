#pragma once

#include <string>

#include <miniscript/miniscript.h>
#include <miniscript/miniscript/fwd-miniscript.h>
#include <miniscript/miniscript/Library.h>

using std::string;

using miniscript::miniscript::MiniScript;

using _Context = miniscript::miniscript::Context;
using _Library = miniscript::miniscript::Library;

/** 
 * Native script library
 * @author Andreas Drewke
 */
class miniscript::miniscript::NativeLibrary: public _Library
{

public:
	// forbid class copy
	FORBID_CLASS_COPY(NativeLibrary)

	/**
	 * Public constructor
	 * @param context context or nullptr
	 */
	NativeLibrary(_Context* context): _Library(context) {
	}

	/**
	 * Load script from library
	 * @param pathName path name
	 * @param fileName file name
	 * @param basePathName base path name
	 * @return MiniScript script from library
	 */
	virtual MiniScript* loadScript(const string& pathName, const string& fileName, const string& basePathName = string()) override;

};
