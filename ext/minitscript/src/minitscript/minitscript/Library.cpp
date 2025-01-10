#include <minitscript/minitscript/Library.h>

#include <memory>
#include <string>

#include <minitscript/minitscript.h>
#include <minitscript/minitscript/MinitScript.h>
#include <minitscript/utilities/Console.h>

using std::make_unique;
using std::string;

using minitscript::minitscript::Library;

using minitscript::minitscript::Context;
using minitscript::minitscript::MinitScript;
using minitscript::utilities::Console;

Library::Library(Context* context) {
	this->context = context;
}

Library::~Library() {
}

MinitScript* Library::loadScript(const string& pathName, const string& fileName, const string& basePathName) {
	Console::printLine("Library::loadScript(): " + pathName + "/" + fileName + (basePathName.empty() == false?"@" + basePathName:""));
	auto script = make_unique<MinitScript>();
	script->setContext(context);
	script->setLibrary(this);
	script->parseScript((basePathName.empty() == false?basePathName + "/":"") + pathName, fileName);
	return script.release();
}
