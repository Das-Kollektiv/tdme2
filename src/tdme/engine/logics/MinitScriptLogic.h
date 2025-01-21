#pragma once

#include <memory>
#include <span>
#include <string>
#include <unordered_map>

#include <minitscript/minitscript.h>
#include <minitscript/minitscript/Library.h>
#include <minitscript/minitscript/MinitScript.h>


#include <tdme/tdme.h>
#include <tdme/engine/logics/Logic.h>
#include <tdme/engine/logics/LogicMinitScript.h>
#include <tdme/engine/model/Model.h>
#include <tdme/engine/model/RotationOrder.h>
#include <tdme/engine/prototype/Prototype.h>
#include <tdme/engine/tools/FileSystemTools.h>
#include <tdme/engine/Engine.h>
#include <tdme/engine/EntityHierarchy.h>
#include <tdme/engine/SceneConnector.h>
#include <tdme/engine/Transform.h>
#include <tdme/minitscript/EngineMinitScript.h>
#include <tdme/utilities/Console.h>

using std::make_unique;
using std::span;
using std::string;
using std::unique_ptr;
using std::unordered_map;

using minitscript::minitscript::Library;
using minitscript::minitscript::MinitScript;

using tdme::engine::logics::LogicMinitScript;

using tdme::engine::logics::Logic;
using tdme::engine::model::Model;
using tdme::engine::model::RotationOrder;
using tdme::engine::prototype::Prototype;
using tdme::engine::tools::FileSystemTools;
using tdme::engine::Engine;
using tdme::engine::EntityHierarchy;
using tdme::engine::SceneConnector;
using tdme::engine::Transform;
using tdme::minitscript::EngineMinitScript;
using tdme::utilities::Console;

/**
 * Mini script logic
 * @author Andreas Drewke
 */
class tdme::engine::logics::MinitScriptLogic: public Logic {
public:
	// forbid class copy
	FORBID_CLASS_COPY(MinitScriptLogic)

	/**
	 * Public constructor
	 * @param context context
	 * @param id id
	 * @param handlingHIDInput handling hid input
	 * @param miniScript logic mini script
	 * @param prototype prototype
	 * @param runsInEditor runs in editor
	 * @param hierarchyId hierarchy id
	 * @param hierarchyParentId hierarchy parent id
	 */
	inline MinitScriptLogic(Context* context, const string& id, bool handlingHIDInput, LogicMinitScript* miniScript, Prototype* prototype, bool runsInEditor, const string& hierarchyId = string(), const string& hierarchyParentId = string()):
		Logic(context, id, handlingHIDInput), miniScript(unique_ptr<LogicMinitScript>(miniScript)), runsInEditor(runsInEditor), hierarchyId(hierarchyId), hierarchyParentId(hierarchyParentId) {
		//
		enginePrototypes[id] = prototype;
		logicPrototypes[id] = prototype;
		//
		miniScript->setContext(context);
		miniScript->setLogic(this);
	}

	/**
	 * @returns is running in editor
	 */
	inline bool isRunningInEditor() {
		return runsInEditor;
	}

	/**
	 * @returns Returns mini script
	 */
	inline LogicMinitScript* getMinitScript() {
		return miniScript.get();
	}

	/**
	 * @returns hierarchy id
	 */
	inline const string& getHierarchyId() {
		return hierarchyId;
	}

	/**
	 * @returns hierarchy parent id
	 */
	inline const string& getHierarchyParentId() {
		return hierarchyParentId;
	}

	// overridden methods
	inline void handleHIDEvents(vector<GUIMouseEvent>& mouseEvents, vector<GUIKeyboardEvent>& keyEvents) {
		miniScript->collectHIDEvents(mouseEvents, keyEvents);
	}

	inline void updateEngine() override {
		// add engine entities requested by EngineMinitScript
		if (miniScript->enginePrototypesToAdd.empty() == false) {
			miniScript->prototypesToAddMutex.lock();
			for (const auto& prototypeToAdd: miniScript->enginePrototypesToAdd) {
				//
				Console::printLine("MinitScriptLogic::updateEngine(): adding prototype: id: " + prototypeToAdd.id + ", hierarchyId: " + prototypeToAdd.hierarchyId + ", hierarchy parent id: " + prototypeToAdd.hierarchyParentId);
				//
				EntityHierarchy* parentEntity = nullptr;
				if (prototypeToAdd.hierarchyId.empty() == false) {
					parentEntity = dynamic_cast<EntityHierarchy*>(context->getEngine()->getEntity(prototypeToAdd.hierarchyId));
				}
				auto transform = prototypeToAdd.transform;
				if (prototypeToAdd.type == LogicMinitScript::PrototypeToAdd::TYPE_ATTACH &&
					prototypeToAdd.attachNodeId.empty() == false) {
					auto prototypeIt = enginePrototypes.find(prototypeToAdd.hierarchyParentId);
					auto prototype = prototypeIt == enginePrototypes.end()?nullptr:prototypeIt->second;
					Matrix4x4 attachNodeTransformMatrix;
					if (prototype != nullptr &&
						prototype->getModel() != nullptr &&
						prototype->getModel()->computeTransformMatrix(
							prototypeToAdd.attachNodeId,
							prototype->getModel()->getImportTransformMatrix(),
							attachNodeTransformMatrix
						) == true) {
						//
						Transform attachNodeTransform;
						attachNodeTransform.fromMatrix(attachNodeTransformMatrix, RotationOrder::ZYX);
						transform = attachNodeTransform * transform;
					} else {
						Console::printLine("MinitScriptLogic::updateEngine(): " + getId() + ": " + prototypeToAdd.attachNodeId + "@" + getId() + " not found");
					}
					/*
					// TODO: we need to create structure of attachNodeId ... ROOT
					//	but our bots do not have a structure until now
					auto node = prototype->getModel()->getNodeById(prototypeToAdd.attachNodeId);
					while (node != nullptr) {
						node = node->getParentNode();
					}
					*/
				}
				//
				auto id = prototypeToAdd.attachNodeId.empty() == false?prototypeToAdd.attachNodeId + "." + prototypeToAdd.id:prototypeToAdd.id;
				//
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
				//
				if (prototypeToAdd.type == LogicMinitScript::PrototypeToAdd::TYPE_ATTACH) enginePrototypes[id] = prototypeToAdd.prototype;
				//
				SceneConnector::addSounds(context->getAudio(), prototypeToAdd.prototype, id);
			}
			miniScript->enginePrototypesToAdd.clear();
			miniScript->prototypesToAddMutex.unlock();
		}
		//
		if (engineInitialized == false) {
			// load sounds
			auto prototypeIt = enginePrototypes.find(id);
			if (prototypeIt != enginePrototypes.end()) {
				SceneConnector::addSounds(context->getAudio(), prototypeIt->second, id);
			}
			// execute initializeEngine() function
			vector<EngineMinitScript::Variable> arguments(0);
			EngineMinitScript::Variable returnValue;
			span argumentsSpan(arguments);
			if (miniScript->call("initializeEngine", argumentsSpan, returnValue) == false) {
				// Console::printLine("MinitScriptLogic::updateEngine(): Failed to call initializeEngine() function");
			}
			//
			engineInitialized = true;
		}
		// execute updateEngine() function
		vector<EngineMinitScript::Variable> arguments(0);
		EngineMinitScript::Variable returnValue;
		span argumentsSpan(arguments);
		if (miniScript->call("updateEngine", argumentsSpan, returnValue) == false) {
			// Console::printLine("MinitScriptLogic::updateEngine(): Failed to call updateEngine() function");
		}
	}

	inline void updateLogic() override {
		// add physics entities requested by EngineMinitScript and scripts
		if (miniScript->physicsPrototypesToAdd.empty() == false) {
			miniScript->prototypesToAddMutex.lock();
			//
			for (const auto& prototypeToAdd: miniScript->physicsPrototypesToAdd) {
				//
				Console::printLine("MinitScriptLogic::updateLogic(): adding prototype: id: " + prototypeToAdd.id + ", hierarchyId: " + prototypeToAdd.hierarchyId + ", hierarchy parent id: " + prototypeToAdd.hierarchyParentId);
				//
				// add to physics
				auto transform = prototypeToAdd.transform;
				if (prototypeToAdd.type == LogicMinitScript::PrototypeToAdd::TYPE_ATTACH &&
					prototypeToAdd.attachNodeId.empty() == false) {
					auto prototypeIt = logicPrototypes.find(prototypeToAdd.hierarchyParentId);
					auto prototype = prototypeIt == logicPrototypes.end()?nullptr:prototypeIt->second;
					Matrix4x4 attachNodeTransformMatrix;
					if (prototype != nullptr &&
						prototype->getModel() != nullptr &&
						prototype->getModel()->computeTransformMatrix(
							prototypeToAdd.attachNodeId,
							prototype->getModel()->getImportTransformMatrix(),
							attachNodeTransformMatrix
						) == true) {
						//
						Transform attachNodeTransform;
						attachNodeTransform.fromMatrix(attachNodeTransformMatrix, RotationOrder::ZYX);
						transform = attachNodeTransform * transform;
					} else {
						Console::printLine("MinitScriptLogic::updateLogic(): " + getId() + ": " + prototypeToAdd.attachNodeId + "@" + getId() + " not found");
					}
					/*
					// TODO: we need to create structure of attachNodeId ... ROOT
					//	but our bots do not have a structure until now
					auto node = prototype->getModel()->getNodeById(prototypeToAdd.attachNodeId);
					while (node != nullptr) {
						node = node->getParentNode();
					}
					*/
				}
				//
				auto id = prototypeToAdd.attachNodeId.empty() == false?prototypeToAdd.attachNodeId + "." + prototypeToAdd.id:prototypeToAdd.id;
				//
				if (prototypeToAdd.hierarchyId.empty() == false) {
					SceneConnector::createSubBody(
						context->getWorld(),
						prototypeToAdd.prototype,
						id,
						transform,
						prototypeToAdd.hierarchyId,
						prototypeToAdd.hierarchyParentId
					);
				} else {
					SceneConnector::createBody(
						context->getWorld(),
						prototypeToAdd.prototype,
						id,
						transform,
						Body::COLLISION_TYPEID_DYNAMIC
					);
				}
				//
				if (prototypeToAdd.type == LogicMinitScript::PrototypeToAdd::TYPE_ATTACH) logicPrototypes[id] = prototypeToAdd.prototype;

				// add logic
				if (prototypeToAdd.prototype->hasScript() == true) {
					auto prototype = prototypeToAdd.prototype;
					//
					unique_ptr<LogicMinitScript> logicMinitScript;
					// try to load from native library
					if (miniScript->getLibrary() != nullptr) {
						//
						auto scriptURI = context->getRelativeURI(prototype->getScript());
						// load from library as generic MinitScript
						auto libraryMinitScript = unique_ptr<MinitScript>(
							miniScript->getLibrary()->loadScript(
								FileSystemTools::getPathName(scriptURI),
								FileSystemTools::getFileName(scriptURI),
								context->getApplicationRootPathName()
							)
						);
						// no native script found?
						if (libraryMinitScript == nullptr) {
							// no op
						} else
						// no LogicMinitScript
						if (dynamic_cast<LogicMinitScript*>(libraryMinitScript.get()) == nullptr) {
							Console::printLine("MinitScriptLogic::updateLogic(): Native library: Native script not of type LogicMinitScript: " + prototype->getScript());
						} else {
							// cast to LogicMinitScript
							logicMinitScript = unique_ptr<LogicMinitScript>(dynamic_cast<LogicMinitScript*>(libraryMinitScript.release()));
						}
					}
					// have script?
					if (logicMinitScript == nullptr) {
						// nope, just parse script into LogicMinitScript
						logicMinitScript = make_unique<LogicMinitScript>();
						logicMinitScript->parseScript(
							FileSystemTools::getPathName(prototype->getScript()),
							FileSystemTools::getFileName(prototype->getScript())
						);
					}
					// add logic if valid
					if (logicMinitScript->isValid() == false) {
						Console::printLine("MinitScriptLogic::updateLogic(): Script not valid. Not using it: " + prototype->getScript());
					} else {
						miniScript->context->addLogic(
							make_unique<MinitScriptLogic>(
								miniScript->context,
								prototypeToAdd.id,
								prototype->isScriptHandlingHID(),
								logicMinitScript.release(),
								prototypeToAdd.prototype,
								runsInEditor,
								prototypeToAdd.hierarchyId,
								prototypeToAdd.hierarchyParentId
							).release()
						);
					}
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
			vector<EngineMinitScript::Variable> arguments(0);
			EngineMinitScript::Variable returnValue;
			span argumentsSpan(arguments);
			if (miniScript->call("initializeLogic", argumentsSpan, returnValue) == false) {
				// Console::printLine("MinitScriptLogic::updateLogic(): Failed to call initializeLogic() function");
			}
			//
			logicInitialized = true;
		}
		// execute on: nothing and other event polling and execution
		miniScript->execute();
		// execute updateLogic() function
		vector<EngineMinitScript::Variable> arguments(0);
		EngineMinitScript::Variable returnValue;
		span argumentsSpan(arguments);
		if (miniScript->call("updateLogic", argumentsSpan, returnValue) == false) {
			// Console::printLine("MinitScriptLogic::updateLogic(): Failed to call updateLogic() function");
		}
	}

	inline void onLogicAdded() override {
		// execute onLogicAdded() function
		vector<EngineMinitScript::Variable> arguments(0);
		EngineMinitScript::Variable returnValue;
		span argumentsSpan(arguments);
		if (miniScript->call("onLogicAdded", argumentsSpan, returnValue) == false) {
			// Console::printLine("MinitScriptLogic::onLogicAdded(): Failed to call onLogicAdded() function");
		}
	}

	inline void onLogicsProcessed() override {
		// execute onLogicsProcessed() function
		vector<EngineMinitScript::Variable> arguments(0);
		EngineMinitScript::Variable returnValue;
		span argumentsSpan(arguments);
		if (miniScript->call("onLogicsProcessed", argumentsSpan, returnValue) == false) {
			// Console::printLine("MinitScriptLogic::onLogicsProcessed(): Failed to call onLogicsProcessed() function");
		}
	}

private:
	unique_ptr<LogicMinitScript> miniScript;
	unordered_map<string, Prototype*> enginePrototypes;
	unordered_map<string, Prototype*> logicPrototypes;
	bool runsInEditor;
	string hierarchyId;
	string hierarchyParentId;
	bool engineInitialized { false };
	bool logicInitialized { false };
};
