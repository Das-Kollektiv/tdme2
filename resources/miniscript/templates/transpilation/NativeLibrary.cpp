#include <miniscript/miniscript/NativeLibrary.h>

#include <memory>
#include <string>

#include <miniscript/miniscript.h>
#include <miniscript/miniscript/MiniScript.h>
#include <miniscript/miniscript/Library.h>
#include <miniscript/utilities/Console.h>

{$library-includes}

using std::make_unique;
using std::string;
using std::unique_ptr;

using miniscript::miniscript::NativeLibrary;

using miniscript::miniscript::MiniScript;

using _Context = miniscript::miniscript::Context;
using _Library = miniscript::miniscript::Library;
using _Console = miniscript::utilities::Console;

MiniScript* NativeLibrary::loadScript(const string& pathName, const string& fileName, const string& basePathName) {
	_Console::println("NativeLibrary::loadScript(): " + pathName + "/" + fileName + (basePathName.empty() == false?"@" + basePathName:""));
	unique_ptr<MiniScript> script;
	//
	{$library-code}
	//
	script->setContext(context);
	script->setLibrary(this);
	script->parseScript((basePathName.empty() == false?basePathName + "/":"") + pathName, fileName);
	return script.release();
}

//
extern "C" _Library* createInstance()
{
	_Console::println("NativeLibrary::createInstance(): Creating library instance!");
	return new NativeLibrary(nullptr);
}
