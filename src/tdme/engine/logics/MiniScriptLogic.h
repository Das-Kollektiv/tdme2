#pragma once

#include <span>
#include <string>

#include <tdme/tdme.h>

#include <tdme/engine/logics/Logic.h>
#include <tdme/engine/logics/LogicMiniScript.h>
#include <tdme/engine/model/Model.h>
#include <tdme/engine/model/RotationOrder.h>
#include <tdme/engine/prototype/Prototype.h>
#include <tdme/engine/Engine.h>
#include <tdme/engine/Transform.h>
#include <tdme/engine/EntityHierarchy.h>
#include <tdme/engine/SceneConnector.h>
#include <tdme/tools/editor/misc/Tools.h>
#include <tdme/utilities/Console.h>
#include <tdme/utilities/MiniScript.h>

using std::span;
using std::string;

using tdme::engine::logics::LogicMiniScript;

using tdme::engine::logics::Logic;
using tdme::engine::model::Model;
using tdme::engine::model::RotationOrder;
using tdme::engine::prototype::Prototype;
using tdme::engine::Engine;
using tdme::engine::Transform;
using tdme::engine::EntityHierarchy;
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
	 * @param prototype prototype
	 * @param hierarchyId hierarchy id
	 * @param hierarchyParentId hierarchy parent id
	 */
	inline MiniScriptLogic(Context* context, const string& id, bool handlingHIDInput, LogicMiniScript* miniScript, Prototype* prototype, const string& hierarchyId = string(), const string& hierarchyParentId = string()):
		Logic(context, id, handlingHIDInput), miniScript(miniScript), hierarchyId(hierarchyId), hierarchyParentId(hierarchyParentId), prototype(prototype) {
		//
		miniScript->setContext(context);
		miniScript->setLogic(this);
		// execute initialize() function
		vector<MiniScript::ScriptVariable> argumentValues(0);
		MiniScript::ScriptVariable returnValue;
		span argumentValuesSpan(argumentValues);
		if (miniScript->call("initialize", argumentValuesSpan, returnValue) == false) {
			Console::println("MiniScriptLogic::onLogicsProcessed(): Failed to call initialize() function");
		}
	}

	/**
	 * @return Returns mini script
	 */
	inline LogicMiniScript* getMiniScript() {
		return miniScript;
	}

	/**
	 * @return hierarchy id
	 */
	inline const string& getHierarchyId() {
		return hierarchyId;
	}

	/**
	 * @return hierarchy parent id
	 */
	inline const string& getHierarchyParentId() {
		return hierarchyParentId;
	}

	// overridden methods
	inline void handleHIDEvents(vector<GUIMouseEvent>& mouseEvents, vector<GUIKeyboardEvent>& keyEvents) {
		miniScript->collectHIDEvents(mouseEvents, keyEvents);
	}

	inline void updateEngine() override {
		// add engine entities requested by MiniScript
		if (miniScript->enginePrototypesToAdd.empty() == false) {
			miniScript->prototypesToAddMutex.lock();
			for (auto& prototypeToAdd: miniScript->enginePrototypesToAdd) {
				EntityHierarchy* parentEntity = nullptr;
				if (prototypeToAdd.hierarchyId.empty() == false) {
					parentEntity = dynamic_cast<EntityHierarchy*>(context->getEngine()->getEntity(prototypeToAdd.hierarchyId));
				}
				auto transform = prototypeToAdd.transform;
				if (prototypeToAdd.attachNodeId.empty() == false && prototype->getModel() != nullptr) {
					Matrix4x4 attachNodeTransformMatrix;
					if (prototype->getModel()->computeTransformMatrix(
						prototypeToAdd.attachNodeId,
						prototype->getModel()->getImportTransformMatrix(),
						attachNodeTransformMatrix) == true) {
						//
						transform.fromMatrix(attachNodeTransformMatrix, RotationOrder::ZYX);
					}
				}
				auto entity =
					SceneConnector::createEntity(
						prototypeToAdd.prototype,
						prototypeToAdd.attachNodeId.empty() == false?prototypeToAdd.attachNodeId + "." + prototypeToAdd.id:prototypeToAdd.id,
						transform,
						1,
						parentEntity != nullptr
					);
				if (parentEntity == nullptr) {
					context->getEngine()->addEntity(entity);
				} else {
					parentEntity->addEntity(entity, prototypeToAdd.hierarchyParentId);
					parentEntity->update();
				}
			}
			miniScript->enginePrototypesToAdd.clear();
			miniScript->prototypesToAddMutex.unlock();
		}
		//
		if (engineInitialized == false) {
			// execute initializeEngine() function
			vector<MiniScript::ScriptVariable> argumentValues(0);
			MiniScript::ScriptVariable returnValue;
			span argumentValuesSpan(argumentValues);
			if (miniScript->call("initializeEngine", argumentValuesSpan, returnValue) == false) {
				Console::println("MiniScriptLogic::updateEngine(): Failed to call initializeEngine() function");
			}
			//
			engineInitialized = true;
		}
		// execute updateEngine() function
		vector<MiniScript::ScriptVariable> argumentValues(0);
		MiniScript::ScriptVariable returnValue;
		span argumentValuesSpan(argumentValues);
		if (miniScript->call("updateEngine", argumentValuesSpan, returnValue) == false) {
			Console::println("MiniScriptLogic::updateEngine(): Failed to call updateEngine() function");
		}
	}

	inline void updateLogic() override {
		// add physics entities requested by MiniScript and scripts
		if (miniScript->physicsPrototypesToAdd.empty() == false) {
			miniScript->prototypesToAddMutex.lock();
			//
			for (auto& prototypeToAdd: miniScript->physicsPrototypesToAdd) {
				// add to physics
				if (prototypeToAdd.prototype->getBoundingVolumeCount() > 0) {
					auto transform = prototypeToAdd.transform;
					if (prototypeToAdd.attachNodeId.empty() == false && prototype->getModel() != nullptr) {
						Matrix4x4 attachNodeTransformMatrix;
						if (prototype->getModel()->computeTransformMatrix(
							prototypeToAdd.attachNodeId,
							prototype->getModel()->getImportTransformMatrix(),
							attachNodeTransformMatrix) == true) {
							//
							transform.fromMatrix(attachNodeTransformMatrix, RotationOrder::ZYX);
						}
					}
					//
					if (prototypeToAdd.hierarchyId.empty() == false) {
						SceneConnector::createSubBody(
							context->getWorld(),
							prototypeToAdd.prototype,
							prototypeToAdd.attachNodeId.empty() == false?prototypeToAdd.attachNodeId + "." + prototypeToAdd.id:prototypeToAdd.id,
							transform,
							prototypeToAdd.hierarchyId,
							prototypeToAdd.hierarchyParentId
						);
					} else {
						SceneConnector::createBody(
							context->getWorld(),
							prototypeToAdd.prototype,
							prototypeToAdd.id,
							transform,
							Body::COLLISION_TYPEID_DYNAMIC
						);
					}
				}
				// add logic
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
							prototypeToAdd.id,
							prototype->isScriptHandlingHID(),
							logicMiniScript,
							prototypeToAdd.prototype,
							prototypeToAdd.hierarchyId,
							prototypeToAdd.hierarchyParentId
						)
					);
				}
			}
			//
			miniScript->physicsPrototypesToAdd.clear();
			//
			miniScript->prototypesToAddMutex.unlock();
		}
		//
		if (logicInitialized == false) {
			// execute initializeLogic() function
			vector<MiniScript::ScriptVariable> argumentValues(0);
			MiniScript::ScriptVariable returnValue;
			span argumentValuesSpan(argumentValues);
			if (miniScript->call("initializeLogic", argumentValuesSpan, returnValue) == false) {
				Console::println("MiniScriptLogic::updateLogic(): Failed to call initializeLogic() function");
			}
			//
			logicInitialized = true;
		}
		// execute on: nothing and other event polling and execution
		miniScript->execute();
		// execute updateLogic() function
		vector<MiniScript::ScriptVariable> argumentValues(0);
		MiniScript::ScriptVariable returnValue;
		span argumentValuesSpan(argumentValues);
		if (miniScript->call("updateLogic", argumentValuesSpan, returnValue) == false) {
			Console::println("MiniScriptLogic::updateLogic(): Failed to call updateLogic() function");
		}
	}

	inline void onLogicAdded() override {
		// execute onLogicAdded() function
		vector<MiniScript::ScriptVariable> argumentValues(0);
		MiniScript::ScriptVariable returnValue;
		span argumentValuesSpan(argumentValues);
		if (miniScript->call("onLogicAdded", argumentValuesSpan, returnValue) == false) {
			Console::println("MiniScriptLogic::onLogicAdded(): Failed to call onLogicAdded() function");
		}
	}

	inline void onLogicsProcessed() override {
		// execute onLogicsProcessed() function
		vector<MiniScript::ScriptVariable> argumentValues(0);
		MiniScript::ScriptVariable returnValue;
		span argumentValuesSpan(argumentValues);
		if (miniScript->call("onLogicsProcessed", argumentValuesSpan, returnValue) == false) {
			Console::println("MiniScriptLogic::onLogicsProcessed(): Failed to call onLogicsProcessed() function");
		}
	}

private:
	LogicMiniScript* miniScript { nullptr };
	Prototype* prototype { nullptr };
	bool engineInitialized { false };
	bool logicInitialized { false };
	string hierarchyId;
	string hierarchyParentId;
};
