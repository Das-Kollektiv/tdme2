#pragma once

#include <string>

#include <miniscript/miniscript.h>
#include <miniscript/miniscript/fwd-miniscript.h>

using std::string;

using miniscript::miniscript::MiniScript;
using _Context = miniscript::miniscript::Context;

/** 
 * Script library
 * @author Andreas Drewke
 */
class miniscript::miniscript::Library
{
private:
	_Context* context { nullptr };

public:
	// forbid class copy
	FORBID_CLASS_COPY(Library)

	/**
	 * Public constructor
	 * @param context context or nullptr
	 */
	Library(_Context* context);

	/**
	 * @return context
	 */
	inline _Context* getContext() {
		return context;
	}

	/**
	 * Set context
	 * @param context context
	 */
	inline void setContext(_Context* context) {
		this->context = context;
	}

	/**
	 * Destructor
	 */
	virtual ~Library();

	/**
	 * Load script from library
	 * @param pathName path name
	 * @param fileName file name
	 * @return MiniScript script from library
	 */
	virtual MiniScript* loadScript(const string& pathName, const string& fileName);

};
