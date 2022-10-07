#pragma once

#include <span>
#include <string>

#include <tdme/tdme.h>

#include <tdme/engine/logics/fwd-tdme.h>
#include <tdme/engine/logics/Logic.h>
#include <tdme/engine/logics/LogicMiniScript.h>
#include <tdme/engine/prototype/Prototype.h>
#include <tdme/engine/Engine.h>
#include <tdme/engine/SceneConnector.h>
#include <tdme/tools/editor/misc/Tools.h>
#include <tdme/utilities/Console.h>
#include <tdme/utilities/MiniScript.h>

using std::span;
using std::string;

using tdme::engine::logics::LogicMiniScript;

using tdme::engine::logics::Logic;
using tdme::engine::prototype::Prototype;
using tdme::engine::Engine;
using tdme::engine::SceneConnector;
using tdme::tools::editor::misc::Tools;
using tdme::utilities::Console;
using tdme::utilities::MiniScript;

/**
 * Mini script logic
 * @author Andreas Drewke
 */
class tdme::engine::logics::MiniScriptLogic: public Logic {
public:

	/**
	 * Public constructor
	 * @param context context
	 * @param id id
	 * @param handlingHIDInput handling hid input
	 * @param miniScript logic mini script
	 */
	inline MiniScriptLogic(Context* context, const string& id, bool handlingHIDInput, LogicMiniScript* miniScript): Logic(context, id, handlingHIDInput), miniScript(miniScript) {
		miniScript->setContext(context);
		miniScript->setLogic(this);
	}

	// overridden methods
	inline void handleHIDEvents(vector<GUIMouseEvent>& mouseEvents, vector<GUIKeyboardEvent>& keyEvents) {
		miniScript->collectHIDEvents(mouseEvents, keyEvents);
	}

	inline void updateEngine() override {
		// add engine entities requested by MiniScript
		if (miniScript->enginePrototypesToAdd.empty() == false) {
			miniScript->prototypesToAddMutex.lock();
			for (auto& prototypeToAddIt: miniScript->enginePrototypesToAdd) {
				auto& prototypeToAdd = prototypeToAddIt.second;
				context->getEngine()->addEntity(
					SceneConnector::createEntity(
						prototypeToAdd.prototype,
						prototypeToAdd.id,
						prototypeToAdd.transform
					)
				);
			}
			miniScript->enginePrototypesToAdd.clear();
			miniScript->prototypesToAddMutex.unlock();
		}
		//
		vector<MiniScript::ScriptVariable> argumentValues(0);
		MiniScript::ScriptVariable returnValue;
		span argumentValuesSpan(argumentValues);
		if (miniScript->call("updateEngine", argumentValuesSpan, returnValue) == false) {
			Console::println("MiniScriptLogic::updateEngine()(): Failed to call updateEngine() function");
		}
	}

	inline void updateLogic() override {
		// add physics entities requested by MiniScript and scripts
		if (miniScript->physicsPrototypesToAdd.empty() == false) {
			miniScript->prototypesToAddMutex.lock();
			for (auto& prototypeToAddIt: miniScript->physicsPrototypesToAdd) {
				auto& prototypeToAdd = prototypeToAddIt.second;
				SceneConnector::createBody(
					context->getWorld(),
					prototypeToAdd.prototype,
					prototypeToAdd.id,
					prototypeToAdd.transform,
					Body::COLLISION_TYPEID_DYNAMIC
				);
				if (prototypeToAdd.prototype->hasScript() == true) {
					auto prototype = prototypeToAdd.prototype;
					auto logicMiniScript = new LogicMiniScript();
					logicMiniScript->loadScript(
						Tools::getPathName(prototype->getScript()),
						Tools::getFileName(prototype->getScript())
					);
					miniScript->context->addLogic(
						new MiniScriptLogic(
							miniScript->context,
							id,
							prototype->isScriptHandlingHID(),
							logicMiniScript
						)
					);
				}
			}
			miniScript->physicsPrototypesToAdd.clear();
			miniScript->prototypesToAddMutex.unlock();
		}
		//
		vector<MiniScript::ScriptVariable> argumentValues(0);
		MiniScript::ScriptVariable returnValue;
		span argumentValuesSpan(argumentValues);
		if (miniScript->call("updateLogic", argumentValuesSpan, returnValue) == false) {
			Console::println("MiniScriptLogic::updateLogic()(): Failed to call updateLogic() function");
		}
	}

	inline void onLogicAdded() override {
		vector<MiniScript::ScriptVariable> argumentValues(0);
		MiniScript::ScriptVariable returnValue;
		span argumentValuesSpan(argumentValues);
		if (miniScript->call("onLogicAdded", argumentValuesSpan, returnValue) == false) {
			Console::println("MiniScriptLogic::onLogicAdded()(): Failed to call onLogicAdded() function");
		}
	}

	inline void onLogicsProcessed() override {
		vector<MiniScript::ScriptVariable> argumentValues(0);
		MiniScript::ScriptVariable returnValue;
		span argumentValuesSpan(argumentValues);
		if (miniScript->call("onLogicsProcessed", argumentValuesSpan, returnValue) == false) {
			Console::println("MiniScriptLogic::onLogicsProcessed()(): Failed to call onLogicsProcessed() function");
		}
	}

private:
	LogicMiniScript* miniScript { nullptr };
};
