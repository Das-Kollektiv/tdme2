#include <miniscript/miniscript/Library.h>

#include <memory>
#include <string>

#include <miniscript/miniscript.h>
#include <miniscript/miniscript/MiniScript.h>
#include <miniscript/utilities/Console.h>

{$library-includes}

using std::make_unique;
using std::string;
using std::unique_ptr;

using miniscript::miniscript::Library;

using miniscript::miniscript::Context;
using miniscript::miniscript::MiniScript;
using miniscript::utilities::Console;

Library::Library(Context* context) {
	this->context = context;
}

Library::~Library() {
}

MiniScript* Library::loadScript(const string& pathName, const string& fileName) {
	Console::println("NativeLibrary::loadScript(): " + pathName + "/" + fileName);
	unique_ptr<MiniScript> script;
	//
	{$library-code}
	//
	script->setContext(context);
	script->setLibrary(this);
	script->parseScript(pathName, fileName);
	return script.release();
}

//
extern "C" Library* createInstance()
{
	Console::println("Library::createInstance(): Creating library instance!");
	return new Library(nullptr);
}
