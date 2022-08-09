#pragma once

#include <tdme/tdme.h>

#include <tdme/engine/logics/Logic.h>
#include <tdme/engine/logics/MiniScriptLogic.h>

using std::string;
using std::vector;

using tdme::engine::logics::MiniScriptLogic;

using tdme::engine::logics::Logic;

void MiniScriptLogic::updateEngine() {
	miniScript->pushScriptState();
	miniScript->emit("updateEngine");
	miniScript->popScriptState();
}

void MiniScriptLogic::updateLogic() {
	miniScript->emit("updateLogic");
}

void MiniScriptLogic::onLogicAdded() {
	miniScript->pushScriptState();
	miniScript->emit("logicAdded");
	miniScript->popScriptState();
}

void MiniScriptLogic::onLogicsProcessed() {
	miniScript->pushScriptState();
	miniScript->emit("logicsProcessed");
	miniScript->popScriptState();
}

