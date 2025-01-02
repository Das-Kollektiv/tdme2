#include <minitscript/minitscript/Context.h>

#include <algorithm>
#include <string>
#include <unordered_map>
#include <vector>

#include <minitscript/minitscript.h>
#include <minitscript/minitscript/MinitScript.h>
#include <minitscript/utilities/Console.h>

using std::find;
using std::string;
using std::unordered_map;
using std::vector;

using minitscript::minitscript::Context;

using minitscript::minitscript::MinitScript;
using minitscript::utilities::Console;

Context::Context() {
}

Context::~Context() {
	for (const auto& [scriptId, script]: scriptsById) delete script;
	scriptsById.clear();
}

void Context::addScript(const string& id, MinitScript* script) {
	// do we already have a script registered with this id?
	if (scriptsById.find(id) != scriptsById.end()) {
		// yep
		Console::printLine("An error occurred: a script with id " + id + " is already registered");
		return;
	}
	// no, add it
	scriptsById[id] = script;
}

void Context::removeScript(const string& id) {
	// get script
	auto scriptsIt = scriptsById.find(id);
	if (scriptsIt == scriptsById.end()) {
		Console::printLine("An error occurred: no script with id " + id + " is registered");
		return;
	}
	auto script = scriptsIt->second;
	// do we have this script in use currently
	if (find(scriptCallStack.begin(), scriptCallStack.end(), script) != scriptCallStack.end()) {
		// yes
		Console::printLine("An error occurred: script with id " + id + " is currently in use");
		return;
	}
	// its safe to remove it
	delete script;
	scriptsById.erase(scriptsIt);
}
