#include <miniscript/miniscript/Library.h>

#include <memory>
#include <string>

#include <miniscript/miniscript.h>
#include <miniscript/miniscript/MiniScript.h>
#include <miniscript/utilities/Console.h>

using std::make_unique;
using std::string;

using _Context = miniscript::miniscript::Context;
using _Library = miniscript::miniscript::Library;
using _Console = miniscript::utilities::Console;

_Library::Library(_Context* context) {
	this->context = context;
}

_Library::~Library() {
}

MiniScript* _Library::loadScript(const string& pathName, const string& fileName, const string& basePathName) {
	_Console::printLine("Library::loadScript(): " + pathName + "/" + fileName + (basePathName.empty() == false?"@" + basePathName:""));
	auto script = make_unique<MiniScript>();
	script->setContext(context);
	script->setLibrary(this);
	script->parseScript((basePathName.empty() == false?basePathName + "/":"") + pathName, fileName);
	return script.release();
}
