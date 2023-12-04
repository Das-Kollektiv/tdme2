#include <miniscript/miniscript/Context.h>

#include <string>
#include <unordered_map>
#include <vector>

#include <miniscript/miniscript.h>
#include <miniscript/miniscript/MiniScript.h>
#include <miniscript/utilities/Console.h>

using std::string;
using std::unordered_map;
using std::vector;

using miniscript::miniscript::Context;

using miniscript::miniscript::MiniScript;
using miniscript::utilities::Console;

Context::Context() {
}

Context::~Context() {
	for (const auto& [scriptId, script]: scriptsById) delete script;
	scriptsById.clear();
}


void Context::addScript(const string& id, MiniScript* script) {
	if (scriptsById.find(id) != scriptsById.end()) {
		Console::println("An error occurred: a script with id " + id + " is already registered");
		return;
	}
	scriptsById[id] = script;
}

void Context::removeScript(const string& id) {
	auto scriptsIt = scriptsById.find(id);
	if (scriptsIt == scriptsById.end()) {
		Console::println("An error occurred: no script with id " + id + " is registered");
		return;
	}
	delete scriptsIt->second;
	scriptsById.erase(scriptsIt);
}
