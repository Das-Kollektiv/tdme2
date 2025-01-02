#include <minitscript/minitscript/NativeLibrary.h>

#include <memory>
#include <string>

#include <minitscript/minitscript.h>
#include <minitscript/minitscript/MinitScript.h>
#include <minitscript/minitscript/Library.h>
#include <minitscript/utilities/Console.h>

{$library-includes}

using std::make_unique;
using std::string;
using std::unique_ptr;

using minitscript::minitscript::NativeLibrary;

using minitscript::minitscript::MinitScript;

using _Context = minitscript::minitscript::Context;
using _Library = minitscript::minitscript::Library;
using _Console = minitscript::utilities::Console;

MinitScript* NativeLibrary::loadScript(const string& pathName, const string& fileName, const string& basePathName) {
	_Console::printLine("NativeLibrary::loadScript(): " + pathName + "/" + fileName + (basePathName.empty() == false?" @ " + basePathName:""));
	//
	unique_ptr<MinitScript> script;
	//
	{$library-code}
	{
		_Console::printLine("NativeLibrary::loadScript(): " + pathName + "/" + fileName + (basePathName.empty() == false?" @ " + basePathName:"") + ": native script not found");
		return nullptr;
	}
	//
	script->setContext(context);
	script->setLibrary(this);
	script->parseScript((basePathName.empty() == false?basePathName + "/":"") + pathName, fileName, {$native-only});
	return script.release();
}

//
extern "C" _Library* createInstance()
{
	_Console::printLine("NativeLibrary::createInstance(): Creating script library instance!");
	return new NativeLibrary(nullptr);
}
