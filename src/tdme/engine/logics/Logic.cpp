#include <tdme/engine/logics/Logic.h>

#include <tdme/tdme.h>
#include <tdme/utilities/Console.h>

using tdme::engine::logics::Logic;

using tdme::utilities::Console;

Logic::Logic(Context* context, const string& id, bool handlingHIDInput) {
	this->context = context;
	this->id = id;
	this->handlingHIDInput = handlingHIDInput;
}

Logic::~Logic() {
}

void Logic::handleHIDEvents(vector<GUIMouseEvent>& mouseEvents, vector<GUIKeyboardEvent>& keyEvents) {
	// no op
}

void Logic::onLogicAdded() {
	// no op
}

void Logic::onLogicsProcessed() {
	// no op
}

void Logic::logState(int indent) {
	for (auto i = 0; i < indent; i++) Console::print("\t");
	Console::printLine(id + ": no state reported");
}
