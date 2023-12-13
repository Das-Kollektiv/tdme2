#include <tdme/engine/logics/LogicMiniScript.h>

#include <memory>
#include <span>
#include <string>
#include <utility>
#include <vector>

#include <tdme/tdme.h>
#include <tdme/audio/Audio.h>
#include <tdme/engine/fileio/prototypes/PrototypeReader.h>
#include <tdme/engine/logics/Context.h>
#include <tdme/engine/logics/Logic.h>
#include <tdme/engine/logics/MiniScriptLogic.h>
#include <tdme/engine/Color4.h>
#include <tdme/engine/physics/Body.h>
#include <tdme/engine/primitives/BoundingBox.h>
#include <tdme/engine/scene/Scene.h>
#include <tdme/engine/Camera.h>
#include <tdme/engine/Engine.h>
#include <tdme/engine/EntityHierarchy.h>
#include <tdme/engine/Object.h>
#include <tdme/engine/ParticleSystem.h>
#include <tdme/engine/SceneConnector.h>
#include <tdme/engine/Timing.h>
#include <tdme/gui/events/GUIKeyboardEvent.h>
#include <tdme/gui/events/GUIMouseEvent.h>
#include <tdme/math/Matrix4x4.h>
#include <tdme/math/Vector2.h>
#include <tdme/math/Vector3.h>
#include <tdme/math/Vector4.h>
#include <tdme/os/filesystem/FileSystem.h>
#include <tdme/os/filesystem/FileSystemInterface.h>
#include <tdme/os/threading/Mutex.h>
#include <tdme/tools/editor/misc/Tools.h>
#include <tdme/tools/editor/Editor.h>
#include <tdme/utilities/Character.h>
#include <tdme/utilities/Console.h>
#include <tdme/utilities/Exception.h>
#include <tdme/utilities/EngineMiniScript.h>
#include <tdme/utilities/UTF8CharacterIterator.h>

using std::move;
using std::span;
using std::string;
using std::to_string;
using std::unique_ptr;
using std::vector;

using tdme::engine::logics::LogicMiniScript;

using tdme::audio::Audio;
using tdme::engine::fileio::prototypes::PrototypeReader;
using tdme::engine::logics::Context;
using tdme::engine::logics::Logic;
using tdme::engine::logics::MiniScriptLogic;
using tdme::engine::Color4;
using tdme::engine::physics::Body;
using tdme::engine::primitives::BoundingBox;
using tdme::engine::scene::Scene;
using tdme::engine::Camera;
using tdme::engine::Engine;
using tdme::engine::EntityHierarchy;
using tdme::engine::Object;
using tdme::engine::ParticleSystem;
using tdme::engine::SceneConnector;
using tdme::engine::Timing;
using tdme::gui::events::GUIKeyboardEvent;
using tdme::gui::events::GUIMouseEvent;
using tdme::math::Matrix4x4;
using tdme::math::Vector2;
using tdme::math::Vector3;
using tdme::math::Vector4;
using tdme::os::filesystem::FileSystem;
using tdme::os::filesystem::FileSystemInterface;
using tdme::os::threading::Mutex;
using tdme::tools::editor::misc::Tools;
using tdme::tools::editor::Editor;
using tdme::utilities::Character;
using tdme::utilities::Console;
using tdme::utilities::Exception;
using tdme::utilities::EngineMiniScript;
using tdme::utilities::UTF8CharacterIterator;

const vector<string> LogicMiniScript::CONTEXTFUNCTIONS_ENGINE = { "initializeEngine", "updateEngine" };
const vector<string> LogicMiniScript::CONTEXTFUNCTIONS_LOGIC = { "initializeLogic", "updateLogic", "onLogicAdded", "onLogicsProcessed" };
const vector<string> LogicMiniScript::CONTEXTFUNCTIONS_ENGINELOGIC = {
	// engine
	"initializeEngine", "updateEngine",
	// logic
	"initializeLogic", "updateLogic", "onLogicAdded", "onLogicsProcessed"
};

LogicMiniScript::LogicMiniScript(): EngineMiniScript(), prototypesToAddMutex("prototypetoadd-mutex") {
}

LogicMiniScript::~LogicMiniScript() {
}

const string LogicMiniScript::getBaseClass() {
	return "tdme::engine::logics::LogicMiniScript";
}

const vector<string> LogicMiniScript::getTranspilationUnits() {
	auto transpilationUnits = EngineMiniScript::getTranspilationUnits();
	transpilationUnits.push_back("src/tdme/engine/logics/LogicMiniScript.cpp");
	return transpilationUnits;
}

inline Entity* LogicMiniScript::getEntity(const string& entityId, const string& childEntityId) {
	auto entity = context->getEngine()->getEntity(entityId);
	if (entity == nullptr) return entity;
	if (childEntityId.empty() == false) {
		if (entity->getEntityType() == Entity::ENTITYTYPE_ENTITYHIERARCHY) {
			auto entityHierarchy = static_cast<EntityHierarchy*>(entity);
			return entityHierarchy->getEntity(childEntityId);
		} else {
			Console::println("LogicMiniScript::getEntity(): no entity hierarchy: can not resolve child entity by given id: " + childEntityId);
			return nullptr;
		}
	} else {
		return entity;
	}
}

void LogicMiniScript::registerStateMachineStates() {
	EngineMiniScript::registerStateMachineStates();
}

void LogicMiniScript::registerMethods() {
	EngineMiniScript::registerMethods();
	{
		//
		class MethodApplicationRunsInEditor: public Method {
		private:
			LogicMiniScript* miniScript { nullptr };
		public:
			MethodApplicationRunsInEditor(LogicMiniScript* miniScript):
				Method({}, VariableType::TYPE_BOOLEAN),
				miniScript(miniScript) {}
			const string getMethodName() override {
				return "application.runsInEditor";
			}
			void executeMethod(span<Variable>& argumentValues, Variable& returnValue, const Statement& statement) override {
				miniScript->setValue(returnValue, miniScript->logic->isRunningInEditor());
			}
			const vector<string>& getContextFunctions() {
				return CONTEXTFUNCTIONS_ALL;
			}
		};
		registerMethod(new MethodApplicationRunsInEditor(this));
	}
	{
		//
		class MethodApplicationIsFullScreen: public Method {
		private:
			LogicMiniScript* miniScript { nullptr };
		public:
			MethodApplicationIsFullScreen(LogicMiniScript* miniScript):
				Method({}, VariableType::TYPE_BOOLEAN),
				miniScript(miniScript) {}
			const string getMethodName() override {
				return "application.isFullScreen";
			}
			void executeMethod(span<Variable>& argumentValues, Variable& returnValue, const Statement& statement) override {
				miniScript->setValue(returnValue, Editor::getInstance() != nullptr?Editor::getInstance()->isFullScreen():false);
			}
			const vector<string>& getContextFunctions() {
				return CONTEXTFUNCTIONS_ALL;
			}
		};
		registerMethod(new MethodApplicationIsFullScreen(this));
	}
	{
		//
		class MethodLogicGetId: public Method {
		private:
			LogicMiniScript* miniScript { nullptr };
		public:
			MethodLogicGetId(LogicMiniScript* miniScript):
				Method({}, VariableType::TYPE_STRING),
				miniScript(miniScript) {}
			const string getMethodName() override {
				return "logic.getId";
			}
			void executeMethod(span<Variable>& argumentValues, Variable& returnValue, const Statement& statement) override {
				miniScript->setValue(returnValue, miniScript->logic->getId());
			}
			const vector<string>& getContextFunctions() {
				return CONTEXTFUNCTIONS_ENGINELOGIC;
			}
		};
		registerMethod(new MethodLogicGetId(this));
	}
	{
		//
		class MethodLogicGetHierarchyId: public Method {
		private:
			LogicMiniScript* miniScript { nullptr };
		public:
			MethodLogicGetHierarchyId(LogicMiniScript* miniScript):
				Method({}, VariableType::TYPE_STRING),
				miniScript(miniScript) {}
			const string getMethodName() override {
				return "logic.getHierarchyId";
			}
			void executeMethod(span<Variable>& argumentValues, Variable& returnValue, const Statement& statement) override {
				miniScript->setValue(returnValue, miniScript->logic->getHierarchyId());
			}
			const vector<string>& getContextFunctions() {
				return CONTEXTFUNCTIONS_ENGINELOGIC;
			}
		};
		registerMethod(new MethodLogicGetHierarchyId(this));
	}
	{
		//
		class MethodLogicGetHierarchyParentId: public Method {
		private:
			LogicMiniScript* miniScript { nullptr };
		public:
			MethodLogicGetHierarchyParentId(LogicMiniScript* miniScript):
				Method({}, VariableType::TYPE_STRING),
				miniScript(miniScript) {}
			const string getMethodName() override {
				return "logic.getHierarchyParentId";
			}
			void executeMethod(span<Variable>& argumentValues, Variable& returnValue, const Statement& statement) override {
				miniScript->setValue(returnValue, miniScript->logic->getHierarchyParentId());
			}
			const vector<string>& getContextFunctions() {
				return CONTEXTFUNCTIONS_ENGINELOGIC;
			}
		};
		registerMethod(new MethodLogicGetHierarchyParentId(this));
	}
	{
		//
		class MethodLogicGetLogicIds: public Method {
		private:
			LogicMiniScript* miniScript { nullptr };
		public:
			MethodLogicGetLogicIds(LogicMiniScript* miniScript):
				Method({}, VariableType::TYPE_ARRAY),
				miniScript(miniScript) {}
			const string getMethodName() override {
				return "logic.getLogicIds";
			}
			void executeMethod(span<Variable>& argumentValues, Variable& returnValue, const Statement& statement) override {
				const auto& contextLogics = miniScript->logic->getContext()->getLogics();
				returnValue.setType(EngineMiniScript::TYPE_ARRAY);
				for (auto contextLogic: contextLogics) {
					returnValue.pushArrayEntry(EngineMiniScript::Variable(contextLogic->getId()));
				}
			}
			const vector<string>& getContextFunctions() {
				return CONTEXTFUNCTIONS_LOGIC;
			}
		};
		registerMethod(new MethodLogicGetLogicIds(this));
	}
	{
		//
		class MethodAudioGetListenerPosition: public Method {
		private:
			LogicMiniScript* miniScript { nullptr };
		public:
			MethodAudioGetListenerPosition(LogicMiniScript* miniScript):
				Method(
					{},
					TYPE_VECTOR3
				),
				miniScript(miniScript) {}
			const string getMethodName() override {
				return "audio.getListenerPosition";
			}
			void executeMethod(span<Variable>& argumentValues, Variable& returnValue, const Statement& statement) override {
				miniScript->setValue(returnValue, miniScript->logic->getContext()->getAudio()->getListenerPosition());
			}
			const vector<string>& getContextFunctions() {
				return CONTEXTFUNCTIONS_ENGINE;
			}
		};
		registerMethod(new MethodAudioGetListenerPosition(this));
	}
	{
		//
		class MethodAudioSetListenerPosition: public Method {
		private:
			LogicMiniScript* miniScript { nullptr };
		public:
			MethodAudioSetListenerPosition(LogicMiniScript* miniScript):
				Method(
					{
						{ .type = TYPE_VECTOR3, .name = "position", .optional = false, .reference = false, .nullable = false }
					},
					VariableType::TYPE_NULL
				),
				miniScript(miniScript) {}
			const string getMethodName() override {
				return "audio.setListenerPosition";
			}
			void executeMethod(span<Variable>& argumentValues, Variable& returnValue, const Statement& statement) override {
				Vector3 position;
				if (miniScript->getVector3Value(argumentValues, 0, position) == true) {
					miniScript->logic->getContext()->getAudio()->setListenerPosition(position);
				} else {
					Console::println(getMethodName() + "(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation(getMethodName()));
					miniScript->startErrorScript();
				}
			}
			const vector<string>& getContextFunctions() {
				return CONTEXTFUNCTIONS_ENGINE;
			}
		};
		registerMethod(new MethodAudioSetListenerPosition(this));
	}
	{
		//
		class MethodAudioGetListenerOrientationUp: public Method {
		private:
			LogicMiniScript* miniScript { nullptr };
		public:
			MethodAudioGetListenerOrientationUp(LogicMiniScript* miniScript):
				Method(
					{},
					TYPE_VECTOR3
				),
				miniScript(miniScript) {}
			const string getMethodName() override {
				return "audio.getListenerOrientationUp";
			}
			void executeMethod(span<Variable>& argumentValues, Variable& returnValue, const Statement& statement) override {
				miniScript->setValue(returnValue, miniScript->logic->getContext()->getAudio()->getListenerOrientationUp());
			}
			const vector<string>& getContextFunctions() {
				return CONTEXTFUNCTIONS_ENGINE;
			}
		};
		registerMethod(new MethodAudioGetListenerOrientationUp(this));
	}
	{
		//
		class MethodAudioSetListenerOrientationUp: public Method {
		private:
			LogicMiniScript* miniScript { nullptr };
		public:
			MethodAudioSetListenerOrientationUp(LogicMiniScript* miniScript):
				Method(
					{
						{ .type = TYPE_VECTOR3, .name = "orientation", .optional = false, .reference = false, .nullable = false }
					},
					VariableType::TYPE_NULL
				),
				miniScript(miniScript) {}
			const string getMethodName() override {
				return "audio.setListenerOrientationUp";
			}
			void executeMethod(span<Variable>& argumentValues, Variable& returnValue, const Statement& statement) override {
				Vector3 orientation;
				if (miniScript->getVector3Value(argumentValues, 0, orientation) == true) {
					miniScript->logic->getContext()->getAudio()->setListenerOrientationUp(orientation);
				} else {
					Console::println(getMethodName() + "(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation(getMethodName()));
					miniScript->startErrorScript();
				}
			}
			const vector<string>& getContextFunctions() {
				return CONTEXTFUNCTIONS_ENGINE;
			}
		};
		registerMethod(new MethodAudioSetListenerOrientationUp(this));
	}
	{
		//
		class MethodAudioGetListenerOrientationAt: public Method {
		private:
			LogicMiniScript* miniScript { nullptr };
		public:
			MethodAudioGetListenerOrientationAt(LogicMiniScript* miniScript):
				Method(
					{},
					TYPE_VECTOR3
				),
				miniScript(miniScript) {}
			const string getMethodName() override {
				return "audio.getListenerOrientationAt";
			}
			void executeMethod(span<Variable>& argumentValues, Variable& returnValue, const Statement& statement) override {
				miniScript->setValue(returnValue, miniScript->logic->getContext()->getAudio()->getListenerOrientationAt());
			}
			const vector<string>& getContextFunctions() {
				return CONTEXTFUNCTIONS_ENGINE;
			}
		};
		registerMethod(new MethodAudioGetListenerOrientationAt(this));
	}
	{
		//
		class MethodAudioSetListenerOrientationAt: public Method {
		private:
			LogicMiniScript* miniScript { nullptr };
		public:
			MethodAudioSetListenerOrientationAt(LogicMiniScript* miniScript):
				Method(
					{
						{ .type = TYPE_VECTOR3, .name = "orientation", .optional = false, .reference = false, .nullable = false }
					},
					VariableType::TYPE_NULL
				),
				miniScript(miniScript) {}
			const string getMethodName() override {
				return "audio.setListenerOrientationAt";
			}
			void executeMethod(span<Variable>& argumentValues, Variable& returnValue, const Statement& statement) override {
				Vector3 orientation;
				if (miniScript->getVector3Value(argumentValues, 0, orientation) == true) {
					miniScript->logic->getContext()->getAudio()->setListenerOrientationAt(orientation);
				} else {
					Console::println(getMethodName() + "(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation(getMethodName()));
					miniScript->startErrorScript();
				}
			}
			const vector<string>& getContextFunctions() {
				return CONTEXTFUNCTIONS_ENGINE;
			}
		};
		registerMethod(new MethodAudioSetListenerOrientationAt(this));
	}
	{
		//
		class MethodAudioPlaySound: public Method {
		private:
			LogicMiniScript* miniScript { nullptr };
		public:
			MethodAudioPlaySound(LogicMiniScript* miniScript):
				Method(
					{
						{ .type = VariableType::TYPE_STRING, .name = "id", .optional = false, .reference = false, .nullable = false },
						{ .type = VariableType::TYPE_INTEGER, .name = "delay", .optional = true, .reference = false, .nullable = false },
						{ .type = VariableType::TYPE_INTEGER, .name = "gain", .optional = true, .reference = false, .nullable = false },
						{ .type = VariableType::TYPE_INTEGER, .name = "pitch", .optional = true, .reference = false, .nullable = false },
						{ .type = VariableType::TYPE_INTEGER, .name = "ignoreIfPlaying", .optional = true, .reference = false, .nullable = false }
					},
					VariableType::TYPE_NULL
				),
				miniScript(miniScript) {}
			const string getMethodName() override {
				return "audio.play";
			}
			void executeMethod(span<Variable>& argumentValues, Variable& returnValue, const Statement& statement) override {
				string id;
				int64_t delay = 0;
				auto gain = 1.0f;
				auto pitch = 1.0f;
				auto ignoreIfPlaying = false;
				if (miniScript->getStringValue(argumentValues, 0, id) == true &&
					miniScript->getIntegerValue(argumentValues, 1, delay, true) == true &&
					miniScript->getFloatValue(argumentValues, 2, gain, true) == true &&
					miniScript->getFloatValue(argumentValues, 3, pitch, true) == true &&
					miniScript->getBooleanValue(argumentValues, 4, ignoreIfPlaying, true) == true) {
					miniScript->logic->playSound(miniScript->logic->getId() + "." + id, delay, gain, pitch, ignoreIfPlaying);
				} else {
					Console::println(getMethodName() + "(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation(getMethodName()));
					miniScript->startErrorScript();
				}
			}
			const vector<string>& getContextFunctions() {
				return CONTEXTFUNCTIONS_ENGINE;
			}
		};
		registerMethod(new MethodAudioPlaySound(this));
	}
	{
		//
		class MethodAudioPlaySoundAtPosition: public Method {
		private:
			LogicMiniScript* miniScript { nullptr };
		public:
			MethodAudioPlaySoundAtPosition(LogicMiniScript* miniScript):
				Method(
					{
						{ .type = VariableType::TYPE_STRING, .name = "id", .optional = false, .reference = false, .nullable = false },
						{ .type = TYPE_VECTOR3, .name = "position", .optional = false, .reference = false, .nullable = false },
						{ .type = VariableType::TYPE_INTEGER, .name = "delay", .optional = true, .reference = false, .nullable = false },
						{ .type = VariableType::TYPE_INTEGER, .name = "gain", .optional = true, .reference = false, .nullable = false },
						{ .type = VariableType::TYPE_INTEGER, .name = "pitch", .optional = true, .reference = false, .nullable = false },
						{ .type = VariableType::TYPE_INTEGER, .name = "ignoreIfPlaying", .optional = true, .reference = false, .nullable = false }
					},
					VariableType::TYPE_NULL
				),
				miniScript(miniScript) {}
			const string getMethodName() override {
				return "audio.playAtPosition";
			}
			void executeMethod(span<Variable>& argumentValues, Variable& returnValue, const Statement& statement) override {
				string id;
				Vector3 position;
				int64_t delay = 0;
				auto gain = 1.0f;
				auto pitch = 1.0f;
				auto ignoreIfPlaying = false;
				if (miniScript->getStringValue(argumentValues, 0, id) == true &&
					miniScript->getVector3Value(argumentValues, 1, position) == true &&
					miniScript->getIntegerValue(argumentValues, 2, delay, true) == true &&
					miniScript->getFloatValue(argumentValues, 3, gain, true) == true &&
					miniScript->getFloatValue(argumentValues, 4, pitch, true) == true &&
					miniScript->getBooleanValue(argumentValues, 5, ignoreIfPlaying, true) == true) {
					miniScript->logic->playSound(miniScript->logic->getId() + "." + id, position, delay, gain, pitch, ignoreIfPlaying);
				} else {
					Console::println(getMethodName() + "(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation(getMethodName()));
					miniScript->startErrorScript();
				}
			}
			const vector<string>& getContextFunctions() {
				return CONTEXTFUNCTIONS_ENGINE;
			}
		};
		registerMethod(new MethodAudioPlaySoundAtPosition(this));
	}
	{
		//
		class MethodLogicSignalSend: public Method {
		private:
			LogicMiniScript* miniScript { nullptr };
		public:
			MethodLogicSignalSend(LogicMiniScript* miniScript):
				Method({
					{ .type = VariableType::TYPE_STRING, .name = "logicId", .optional = false, .reference = false, .nullable = false },
					{ .type = VariableType::TYPE_STRING, .name = "signal", .optional = false, .reference = false, .nullable = false }
				}),
				miniScript(miniScript) {}
			const string getMethodName() override {
				return "logic.signal.send";
			}
			void executeMethod(span<Variable>& argumentValues, Variable& returnValue, const Statement& statement) override {
				string logicId;
				string signal;
				if (miniScript->getStringValue(argumentValues, 0, logicId) == true &&
					miniScript->getStringValue(argumentValues, 1, signal) == true) {
					auto logic = static_cast<Logic*>(miniScript->context->getLogic(logicId));
					if (logic == nullptr) {
						Console::println(getMethodName() + "(): " + miniScript->getStatementInformation(statement) + ": no logic with given id: " + logicId);
						miniScript->startErrorScript();
					} else {
						vector<Variable> arguments(argumentValues.size() - 2);
						for (auto i = 2; i < argumentValues.size(); i++) arguments.push_back(argumentValues[i]);
						logic->addSignal(signal, arguments);
					}
				} else {
					Console::println(getMethodName() + "(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation(getMethodName()));
					miniScript->startErrorScript();
				}
			}
			bool isVariadic() const override {
				return true;
			}
			const vector<string>& getContextFunctions() {
				return CONTEXTFUNCTIONS_LOGIC;
			}
		};
		registerMethod(new MethodLogicSignalSend(this));
	}
	{
		//
		class MethodLogicHas: public Method {
		private:
			LogicMiniScript* miniScript { nullptr };
		public:
			MethodLogicHas(LogicMiniScript* miniScript):
				Method(
					{
						{ .type = VariableType::TYPE_STRING, .name = "logicId", .optional = false, .reference = false, .nullable = false },
						{ .type = VariableType::TYPE_STRING, .name = "callable", .optional = false, .reference = false, .nullable = false }
					},
					VariableType::TYPE_BOOLEAN
				),
				miniScript(miniScript) {}
			const string getMethodName() override {
				return "logic.has";
			}
			void executeMethod(span<Variable>& argumentValues, Variable& returnValue, const Statement& statement) override {
				string logicId;
				string callable;
				if (EngineMiniScript::getStringValue(argumentValues, 0, logicId) == false ||
					EngineMiniScript::getStringValue(argumentValues, 1, callable) == false) {
					Console::println(getMethodName() + "(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation(getMethodName()));
					miniScript->startErrorScript();
				} else {
					auto logic = dynamic_cast<MiniScriptLogic*>(miniScript->context->getLogic(logicId));
					if (logic == nullptr || logic->getMiniScript() == nullptr) {
						miniScript->setValue(returnValue, false);
					} else {
						auto logicMiniScript = logic->getMiniScript();
						auto scriptIdx = logicMiniScript->getFunctionScriptIdx(callable);
						if (scriptIdx == SCRIPTIDX_NONE || logicMiniScript->getScripts()[scriptIdx].callableFunction == false) {
							miniScript->setValue(returnValue, false);
						} else {
							miniScript->setValue(returnValue, true);
						}
					}
				}
			}
		};
		registerMethod(new MethodLogicHas(this));
	}
	{
		//
		class MethodLogicCall: public Method {
		private:
			LogicMiniScript* miniScript { nullptr };
		public:
			MethodLogicCall(LogicMiniScript* miniScript):
				Method(
					{
						{ .type = VariableType::TYPE_STRING, .name = "logicId", .optional = false, .reference = false, .nullable = false },
						{ .type = VariableType::TYPE_STRING, .name = "callable", .optional = false, .reference = false, .nullable = false }
					},
					VariableType::TYPE_PSEUDO_MIXED
				),
				miniScript(miniScript) {}
			const string getMethodName() override {
				return "logic.call";
			}
			void executeMethod(span<Variable>& argumentValues, Variable& returnValue, const Statement& statement) override {
				string logicId;
				string callable;
				if (EngineMiniScript::getStringValue(argumentValues, 0, logicId) == false ||
					EngineMiniScript::getStringValue(argumentValues, 1, callable) == false) {
					Console::println(getMethodName() + "(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation(getMethodName()));
					miniScript->startErrorScript();
				} else {
					auto logic = dynamic_cast<MiniScriptLogic*>(miniScript->context->getLogic(logicId));
					if (logic == nullptr || logic->getMiniScript() == nullptr) {
						Console::println(getMethodName() + "(): " + miniScript->getStatementInformation(statement) + ": no mini script logic with given id: " + logicId);
						miniScript->startErrorScript();
					} else {
						auto logicMiniScript = logic->getMiniScript();
						auto scriptIdx = logicMiniScript->getFunctionScriptIdx(callable);
						if (scriptIdx == SCRIPTIDX_NONE || logicMiniScript->getScripts()[scriptIdx].callableFunction == false) {
							Console::println(getMethodName() + "(): " + miniScript->getStatementInformation(statement) + ": callable not found: " + callable);
							miniScript->startErrorScript();
						} else {
							#if defined (__APPLE__)
								// MACOSX currently does not support initializing span using begin and end iterators,
								vector<Variable> callArgumentValues(argumentValues.size() - 2);
								for (auto i = 2; i < argumentValues.size(); i++) callArgumentValues[i - 2] = move(argumentValues[i]);
								// call
								span callArgumentValuesSpan(callArgumentValues);
								logicMiniScript->call(scriptIdx, callArgumentValuesSpan, returnValue);
								// move back arguments
								for (auto i = 2; i < argumentValues.size(); i++) argumentValues[i] = move(callArgumentValues[i - 2]);
							#else
								span callArgumentValuesSpan(argumentValues.begin() + 2, argumentValues.end());
								logicMiniScript->call(scriptIdx, callArgumentValuesSpan, returnValue);
							#endif
						}
					}
				}
			}
			bool isVariadic() const override {
				return true;
			}
		};
		registerMethod(new MethodLogicCall(this));
	}
	{
		//
		class MethodLogicSignalHas: public Method {
		private:
			LogicMiniScript* miniScript { nullptr };
		public:
			MethodLogicSignalHas(LogicMiniScript* miniScript):
				Method({}, VariableType::TYPE_BOOLEAN),
				miniScript(miniScript) {}
			const string getMethodName() override {
				return "logic.signal.has";
			}
			void executeMethod(span<Variable>& argumentValues, Variable& returnValue, const Statement& statement) override {
				miniScript->setValue(returnValue, miniScript->logic->hasSignal());
			}
			const vector<string>& getContextFunctions() {
				return CONTEXTFUNCTIONS_ALL;
			}
		};
		registerMethod(new MethodLogicSignalHas(this));
	}
	{
		//
		class MethodLogicSignalGetName: public Method {
		private:
			LogicMiniScript* miniScript { nullptr };
		public:
			MethodLogicSignalGetName(LogicMiniScript* miniScript):
				Method({}, VariableType::TYPE_STRING),
				miniScript(miniScript) {}
			const string getMethodName() override {
				return "logic.signal.getName";
			}
			void executeMethod(span<Variable>& argumentValues, Variable& returnValue, const Statement& statement) override {
				miniScript->setValue(returnValue, miniScript->logic->getSignalName());
			}
			const vector<string>& getContextFunctions() {
				return CONTEXTFUNCTIONS_ALL;
			}
		};
		registerMethod(new MethodLogicSignalGetName(this));
	}
	{
		//
		class MethodLogicSignalGetArgument: public Method {
		private:
			LogicMiniScript* miniScript { nullptr };
		public:
			MethodLogicSignalGetArgument(LogicMiniScript* miniScript):
				Method(
					{
						{ .type = VariableType::TYPE_INTEGER, .name = "argumentIndex", .optional = false, .reference = false, .nullable = false }
					},
					VariableType::TYPE_PSEUDO_MIXED
				),
				miniScript(miniScript) {}
			const string getMethodName() override {
				return "logic.signal.getArgument";
			}
			void executeMethod(span<Variable>& argumentValues, Variable& returnValue, const Statement& statement) override {
				int64_t argumentIndex;
				if (miniScript->getIntegerValue(argumentValues, 0, argumentIndex) == true) {
					returnValue = miniScript->logic->getSignalArgument(argumentIndex);
				} else {
					Console::println(getMethodName() + "(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation(getMethodName()));
					miniScript->startErrorScript();
				}
			}
			const vector<string>& getContextFunctions() {
				return CONTEXTFUNCTIONS_ALL;
			}
		};
		registerMethod(new MethodLogicSignalGetArgument(this));
	}
	{
		//
		class MethodLogicSignalNext: public Method {
		private:
			LogicMiniScript* miniScript { nullptr };
		public:
			MethodLogicSignalNext(LogicMiniScript* miniScript):
				Method(),
				miniScript(miniScript) {}
			const string getMethodName() override {
				return "logic.signal.next";
			}
			void executeMethod(span<Variable>& argumentValues, Variable& returnValue, const Statement& statement) override {
				miniScript->logic->removeSignal();
			}
			const vector<string>& getContextFunctions() {
				return CONTEXTFUNCTIONS_ALL;
			}
		};
		registerMethod(new MethodLogicSignalNext(this));
	}
	// keyboard input
	{
		//
		class MethodInputKeyboardKEYCODE_LEFT: public Method {
		private:
			LogicMiniScript* miniScript { nullptr };
		public:
			MethodInputKeyboardKEYCODE_LEFT(LogicMiniScript* miniScript):
				Method({}, VariableType::TYPE_INTEGER),
				miniScript(miniScript) {}
			const string getMethodName() override {
				return "input.keyboard.KEYCODE_LEFT";
			}
			void executeMethod(span<Variable>& argumentValues, Variable& returnValue, const Statement& statement) override {
				returnValue = static_cast<int64_t>(GUIKeyboardEvent::KEYCODE_LEFT);
			}
			const vector<string>& getContextFunctions() {
				return CONTEXTFUNCTIONS_ALL;
			}
		};
		registerMethod(new MethodInputKeyboardKEYCODE_LEFT(this));
	}
	{
		//
		class MethodInputKeyboardKEYCODE_RIGHT: public Method {
		private:
			LogicMiniScript* miniScript { nullptr };
		public:
			MethodInputKeyboardKEYCODE_RIGHT(LogicMiniScript* miniScript):
				Method({}, VariableType::TYPE_INTEGER),
				miniScript(miniScript) {}
			const string getMethodName() override {
				return "input.keyboard.KEYCODE_RIGHT";
			}
			void executeMethod(span<Variable>& argumentValues, Variable& returnValue, const Statement& statement) override {
				returnValue = static_cast<int64_t>(GUIKeyboardEvent::KEYCODE_RIGHT);
			}
			const vector<string>& getContextFunctions() {
				return CONTEXTFUNCTIONS_ALL;
			}
		};
		registerMethod(new MethodInputKeyboardKEYCODE_RIGHT(this));
	}
	{
		//
		class MethodInputKeyboardKEYCODE_UP: public Method {
		private:
			LogicMiniScript* miniScript { nullptr };
		public:
			MethodInputKeyboardKEYCODE_UP(LogicMiniScript* miniScript):
				Method({}, VariableType::TYPE_INTEGER),
				miniScript(miniScript) {}
			const string getMethodName() override {
				return "input.keyboard.KEYCODE_UP";
			}
			void executeMethod(span<Variable>& argumentValues, Variable& returnValue, const Statement& statement) override {
				returnValue = static_cast<int64_t>(GUIKeyboardEvent::KEYCODE_UP);
			}
			const vector<string>& getContextFunctions() {
				return CONTEXTFUNCTIONS_ALL;
			}
		};
		registerMethod(new MethodInputKeyboardKEYCODE_UP(this));
	}
	{
		//
		class MethodInputKeyboardKEYCODE_DOWN: public Method {
		private:
			LogicMiniScript* miniScript { nullptr };
		public:
			MethodInputKeyboardKEYCODE_DOWN(LogicMiniScript* miniScript):
				Method({}, VariableType::TYPE_INTEGER),
				miniScript(miniScript) {}
			const string getMethodName() override {
				return "input.keyboard.KEYCODE_DOWN";
			}
			void executeMethod(span<Variable>& argumentValues, Variable& returnValue, const Statement& statement) override {
				returnValue = static_cast<int64_t>(GUIKeyboardEvent::KEYCODE_DOWN);
			}
			const vector<string>& getContextFunctions() {
				return CONTEXTFUNCTIONS_ALL;
			}
		};
		registerMethod(new MethodInputKeyboardKEYCODE_DOWN(this));
	}
	{
		//
		class MethodInputKeyboardKEYCODE_POS1: public Method {
		private:
			LogicMiniScript* miniScript { nullptr };
		public:
			MethodInputKeyboardKEYCODE_POS1(LogicMiniScript* miniScript):
				Method({}, VariableType::TYPE_INTEGER),
				miniScript(miniScript) {}
			const string getMethodName() override {
				return "input.keyboard.KEYCODE_POS1";
			}
			void executeMethod(span<Variable>& argumentValues, Variable& returnValue, const Statement& statement) override {
				returnValue = static_cast<int64_t>(GUIKeyboardEvent::KEYCODE_POS1);
			}
			const vector<string>& getContextFunctions() {
				return CONTEXTFUNCTIONS_ALL;
			}
		};
		registerMethod(new MethodInputKeyboardKEYCODE_POS1(this));
	}
	{
		//
		class MethodInputKeyboardKEYCODE_END: public Method {
		private:
			LogicMiniScript* miniScript { nullptr };
		public:
			MethodInputKeyboardKEYCODE_END(LogicMiniScript* miniScript):
				Method({}, VariableType::TYPE_INTEGER),
				miniScript(miniScript) {}
			const string getMethodName() override {
				return "input.keyboard.KEYCODE_END";
			}
			void executeMethod(span<Variable>& argumentValues, Variable& returnValue, const Statement& statement) override {
				returnValue = static_cast<int64_t>(GUIKeyboardEvent::KEYCODE_END);
			}
			const vector<string>& getContextFunctions() {
				return CONTEXTFUNCTIONS_ALL;
			}
		};
		registerMethod(new MethodInputKeyboardKEYCODE_END(this));
	}
	{
		//
		class MethodInputKeyboardKEYCODE_PAGEUP: public Method {
		private:
			LogicMiniScript* miniScript { nullptr };
		public:
			MethodInputKeyboardKEYCODE_PAGEUP(LogicMiniScript* miniScript):
				Method({}, VariableType::TYPE_INTEGER),
				miniScript(miniScript) {}
			const string getMethodName() override {
				return "input.keyboard.KEYCODE_PAGEUP";
			}
			void executeMethod(span<Variable>& argumentValues, Variable& returnValue, const Statement& statement) override {
				returnValue = static_cast<int64_t>(GUIKeyboardEvent::KEYCODE_PAGE_UP);
			}
			const vector<string>& getContextFunctions() {
				return CONTEXTFUNCTIONS_ALL;
			}
		};
		registerMethod(new MethodInputKeyboardKEYCODE_PAGEUP(this));
	}
	{
		//
		class MethodInputKeyboardKEYCODE_PAGEDOWN: public Method {
		private:
			LogicMiniScript* miniScript { nullptr };
		public:
			MethodInputKeyboardKEYCODE_PAGEDOWN(LogicMiniScript* miniScript):
				Method({}, VariableType::TYPE_INTEGER),
				miniScript(miniScript) {}
			const string getMethodName() override {
				return "input.keyboard.KEYCODE_PAGEDOWN";
			}
			void executeMethod(span<Variable>& argumentValues, Variable& returnValue, const Statement& statement) override {
				returnValue = static_cast<int64_t>(GUIKeyboardEvent::KEYCODE_PAGE_DOWN);
			}
			const vector<string>& getContextFunctions() {
				return CONTEXTFUNCTIONS_ALL;
			}
		};
		registerMethod(new MethodInputKeyboardKEYCODE_PAGEDOWN(this));
	}
	{
		//
		class MethodInputKeyboardKEYCODE_BACKSPACE: public Method {
		private:
			LogicMiniScript* miniScript { nullptr };
		public:
			MethodInputKeyboardKEYCODE_BACKSPACE(LogicMiniScript* miniScript):
				Method({}, VariableType::TYPE_INTEGER),
				miniScript(miniScript) {}
			const string getMethodName() override {
				return "input.keyboard.KEYCODE_BACKSPACE";
			}
			void executeMethod(span<Variable>& argumentValues, Variable& returnValue, const Statement& statement) override {
				returnValue = static_cast<int64_t>(GUIKeyboardEvent::KEYCODE_BACKSPACE);
			}
			const vector<string>& getContextFunctions() {
				return CONTEXTFUNCTIONS_ALL;
			}
		};
		registerMethod(new MethodInputKeyboardKEYCODE_BACKSPACE(this));
	}
	{
		//
		class MethodInputKeyboardKEYCODE_DELETE: public Method {
		private:
			LogicMiniScript* miniScript { nullptr };
		public:
			MethodInputKeyboardKEYCODE_DELETE(LogicMiniScript* miniScript):
				Method({}, VariableType::TYPE_INTEGER),
				miniScript(miniScript) {}
			const string getMethodName() override {
				return "input.keyboard.KEYCODE_DELETE";
			}
			void executeMethod(span<Variable>& argumentValues, Variable& returnValue, const Statement& statement) override {
				returnValue = static_cast<int64_t>(GUIKeyboardEvent::KEYCODE_DELETE);
			}
			const vector<string>& getContextFunctions() {
				return CONTEXTFUNCTIONS_ALL;
			}
		};
		registerMethod(new MethodInputKeyboardKEYCODE_DELETE(this));
	}
	{
		//
		class MethodInputKeyboardKEYCODE_SPACE: public Method {
		private:
			LogicMiniScript* miniScript { nullptr };
		public:
			MethodInputKeyboardKEYCODE_SPACE(LogicMiniScript* miniScript):
				Method({}, VariableType::TYPE_INTEGER),
				miniScript(miniScript) {}
			const string getMethodName() override {
				return "input.keyboard.KEYCODE_SPACE";
			}
			void executeMethod(span<Variable>& argumentValues, Variable& returnValue, const Statement& statement) override {
				returnValue = static_cast<int64_t>(GUIKeyboardEvent::KEYCODE_SPACE);
			}
			const vector<string>& getContextFunctions() {
				return CONTEXTFUNCTIONS_ALL;
			}
		};
		registerMethod(new MethodInputKeyboardKEYCODE_SPACE(this));
	}
	{
		//
		class MethodInputKeyboardKEYCODE_RETURN: public Method {
		private:
			LogicMiniScript* miniScript { nullptr };
		public:
			MethodInputKeyboardKEYCODE_RETURN(LogicMiniScript* miniScript):
				Method({}, VariableType::TYPE_INTEGER),
				miniScript(miniScript) {}
			const string getMethodName() override {
				return "input.keyboard.KEYCODE_RETURN";
			}
			void executeMethod(span<Variable>& argumentValues, Variable& returnValue, const Statement& statement) override {
				returnValue = static_cast<int64_t>(GUIKeyboardEvent::KEYCODE_RETURN);
			}
			const vector<string>& getContextFunctions() {
				return CONTEXTFUNCTIONS_ALL;
			}
		};
		registerMethod(new MethodInputKeyboardKEYCODE_RETURN(this));
	}
	{
		//
		class MethodInputKeyboardKEYCODE_ESCAPE: public Method {
		private:
			LogicMiniScript* miniScript { nullptr };
		public:
			MethodInputKeyboardKEYCODE_ESCAPE(LogicMiniScript* miniScript):
				Method({}, VariableType::TYPE_INTEGER),
				miniScript(miniScript) {}
			const string getMethodName() override {
				return "input.keyboard.KEYCODE_ESCAPE";
			}
			void executeMethod(span<Variable>& argumentValues, Variable& returnValue, const Statement& statement) override {
				returnValue = static_cast<int64_t>(GUIKeyboardEvent::KEYCODE_ESCAPE);
			}
			const vector<string>& getContextFunctions() {
				return CONTEXTFUNCTIONS_ALL;
			}
		};
		registerMethod(new MethodInputKeyboardKEYCODE_ESCAPE(this));
	}
	{
		//
		class MethodInputKeyboardKEYCODE_F1: public Method {
		private:
			LogicMiniScript* miniScript { nullptr };
		public:
			MethodInputKeyboardKEYCODE_F1(LogicMiniScript* miniScript):
				Method({}, VariableType::TYPE_INTEGER),
				miniScript(miniScript) {}
			const string getMethodName() override {
				return "input.keyboard.KEYCODE_F1";
			}
			void executeMethod(span<Variable>& argumentValues, Variable& returnValue, const Statement& statement) override {
				returnValue = static_cast<int64_t>(GUIKeyboardEvent::KEYCODE_F1);
			}
			const vector<string>& getContextFunctions() {
				return CONTEXTFUNCTIONS_ALL;
			}
		};
		registerMethod(new MethodInputKeyboardKEYCODE_F1(this));
	}
	{
		//
		class MethodInputKeyboardKEYCODE_F2: public Method {
		private:
			LogicMiniScript* miniScript { nullptr };
		public:
			MethodInputKeyboardKEYCODE_F2(LogicMiniScript* miniScript):
				Method({}, VariableType::TYPE_INTEGER),
				miniScript(miniScript) {}
			const string getMethodName() override {
				return "input.keyboard.KEYCODE_F2";
			}
			void executeMethod(span<Variable>& argumentValues, Variable& returnValue, const Statement& statement) override {
				returnValue = static_cast<int64_t>(GUIKeyboardEvent::KEYCODE_F2);
			}
			const vector<string>& getContextFunctions() {
				return CONTEXTFUNCTIONS_ALL;
			}
		};
		registerMethod(new MethodInputKeyboardKEYCODE_F2(this));
	}
	{
		//
		class MethodInputKeyboardKEYCODE_F3: public Method {
		private:
			LogicMiniScript* miniScript { nullptr };
		public:
			MethodInputKeyboardKEYCODE_F3(LogicMiniScript* miniScript):
				Method({}, VariableType::TYPE_INTEGER),
				miniScript(miniScript) {}
			const string getMethodName() override {
				return "input.keyboard.KEYCODE_F3";
			}
			void executeMethod(span<Variable>& argumentValues, Variable& returnValue, const Statement& statement) override {
				returnValue = static_cast<int64_t>(GUIKeyboardEvent::KEYCODE_F3);
			}
			const vector<string>& getContextFunctions() {
				return CONTEXTFUNCTIONS_ALL;
			}
		};
		registerMethod(new MethodInputKeyboardKEYCODE_F3(this));
	}
	{
		//
		class MethodInputKeyboardKEYCODE_F4: public Method {
		private:
			LogicMiniScript* miniScript { nullptr };
		public:
			MethodInputKeyboardKEYCODE_F4(LogicMiniScript* miniScript):
				Method({}, VariableType::TYPE_INTEGER),
				miniScript(miniScript) {}
			const string getMethodName() override {
				return "input.keyboard.KEYCODE_F4";
			}
			void executeMethod(span<Variable>& argumentValues, Variable& returnValue, const Statement& statement) override {
				returnValue = static_cast<int64_t>(GUIKeyboardEvent::KEYCODE_F4);
			}
			const vector<string>& getContextFunctions() {
				return CONTEXTFUNCTIONS_ALL;
			}
		};
		registerMethod(new MethodInputKeyboardKEYCODE_F4(this));
	}
	{
		//
		class MethodInputKeyboardKEYCODE_F5: public Method {
		private:
			LogicMiniScript* miniScript { nullptr };
		public:
			MethodInputKeyboardKEYCODE_F5(LogicMiniScript* miniScript):
				Method({}, VariableType::TYPE_INTEGER),
				miniScript(miniScript) {}
			const string getMethodName() override {
				return "input.keyboard.KEYCODE_F5";
			}
			void executeMethod(span<Variable>& argumentValues, Variable& returnValue, const Statement& statement) override {
				returnValue = static_cast<int64_t>(GUIKeyboardEvent::KEYCODE_F5);
			}
			const vector<string>& getContextFunctions() {
				return CONTEXTFUNCTIONS_ALL;
			}
		};
		registerMethod(new MethodInputKeyboardKEYCODE_F5(this));
	}
	{
		//
		class MethodInputKeyboardKEYCODE_F6: public Method {
		private:
			LogicMiniScript* miniScript { nullptr };
		public:
			MethodInputKeyboardKEYCODE_F6(LogicMiniScript* miniScript):
				Method({}, VariableType::TYPE_INTEGER),
				miniScript(miniScript) {}
			const string getMethodName() override {
				return "input.keyboard.KEYCODE_F6";
			}
			void executeMethod(span<Variable>& argumentValues, Variable& returnValue, const Statement& statement) override {
				returnValue = static_cast<int64_t>(GUIKeyboardEvent::KEYCODE_F6);
			}
			const vector<string>& getContextFunctions() {
				return CONTEXTFUNCTIONS_ALL;
			}
		};
		registerMethod(new MethodInputKeyboardKEYCODE_F6(this));
	}
	{
		//
		class MethodInputKeyboardKEYCODE_F7: public Method {
		private:
			LogicMiniScript* miniScript { nullptr };
		public:
			MethodInputKeyboardKEYCODE_F7(LogicMiniScript* miniScript):
				Method({}, VariableType::TYPE_INTEGER),
				miniScript(miniScript) {}
			const string getMethodName() override {
				return "input.keyboard.KEYCODE_F7";
			}
			void executeMethod(span<Variable>& argumentValues, Variable& returnValue, const Statement& statement) override {
				returnValue = static_cast<int64_t>(GUIKeyboardEvent::KEYCODE_F7);
			}
			const vector<string>& getContextFunctions() {
				return CONTEXTFUNCTIONS_ALL;
			}
		};
		registerMethod(new MethodInputKeyboardKEYCODE_F7(this));
	}
	{
		//
		class MethodInputKeyboardKEYCODE_F8: public Method {
		private:
			LogicMiniScript* miniScript { nullptr };
		public:
			MethodInputKeyboardKEYCODE_F8(LogicMiniScript* miniScript):
				Method({}, VariableType::TYPE_INTEGER),
				miniScript(miniScript) {}
			const string getMethodName() override {
				return "input.keyboard.KEYCODE_F8";
			}
			void executeMethod(span<Variable>& argumentValues, Variable& returnValue, const Statement& statement) override {
				returnValue = static_cast<int64_t>(GUIKeyboardEvent::KEYCODE_F8);
			}
			const vector<string>& getContextFunctions() {
				return CONTEXTFUNCTIONS_ALL;
			}
		};
		registerMethod(new MethodInputKeyboardKEYCODE_F8(this));
	}
	{
		//
		class MethodInputKeyboardKEYCODE_F9: public Method {
		private:
			LogicMiniScript* miniScript { nullptr };
		public:
			MethodInputKeyboardKEYCODE_F9(LogicMiniScript* miniScript):
				Method({}, VariableType::TYPE_INTEGER),
				miniScript(miniScript) {}
			const string getMethodName() override {
				return "input.keyboard.KEYCODE_F9";
			}
			void executeMethod(span<Variable>& argumentValues, Variable& returnValue, const Statement& statement) override {
				returnValue = static_cast<int64_t>(GUIKeyboardEvent::KEYCODE_F9);
			}
			const vector<string>& getContextFunctions() {
				return CONTEXTFUNCTIONS_ALL;
			}
		};
		registerMethod(new MethodInputKeyboardKEYCODE_F9(this));
	}
	{
		//
		class MethodInputKeyboardKEYCODE_F10: public Method {
		private:
			LogicMiniScript* miniScript { nullptr };
		public:
			MethodInputKeyboardKEYCODE_F10(LogicMiniScript* miniScript):
				Method({}, VariableType::TYPE_INTEGER),
				miniScript(miniScript) {}
			const string getMethodName() override {
				return "input.keyboard.KEYCODE_F10";
			}
			void executeMethod(span<Variable>& argumentValues, Variable& returnValue, const Statement& statement) override {
				returnValue = static_cast<int64_t>(GUIKeyboardEvent::KEYCODE_F10);
			}
			const vector<string>& getContextFunctions() {
				return CONTEXTFUNCTIONS_ALL;
			}
		};
		registerMethod(new MethodInputKeyboardKEYCODE_F10(this));
	}
	{
		//
		class MethodInputKeyboardKEYCODE_F11: public Method {
		private:
			LogicMiniScript* miniScript { nullptr };
		public:
			MethodInputKeyboardKEYCODE_F11(LogicMiniScript* miniScript):
				Method({}, VariableType::TYPE_INTEGER),
				miniScript(miniScript) {}
			const string getMethodName() override {
				return "input.keyboard.KEYCODE_F11";
			}
			void executeMethod(span<Variable>& argumentValues, Variable& returnValue, const Statement& statement) override {
				returnValue = static_cast<int64_t>(GUIKeyboardEvent::KEYCODE_F11);
			}
			const vector<string>& getContextFunctions() {
				return CONTEXTFUNCTIONS_ALL;
			}
		};
		registerMethod(new MethodInputKeyboardKEYCODE_F11(this));
	}
	{
		//
		class MethodInputKeyboardKEYCODE_F12: public Method {
		private:
			LogicMiniScript* miniScript { nullptr };
		public:
			MethodInputKeyboardKEYCODE_F12(LogicMiniScript* miniScript):
				Method({}, VariableType::TYPE_INTEGER),
				miniScript(miniScript) {}
			const string getMethodName() override {
				return "input.keyboard.KEYCODE_F12";
			}
			void executeMethod(span<Variable>& argumentValues, Variable& returnValue, const Statement& statement) override {
				returnValue = static_cast<int64_t>(GUIKeyboardEvent::KEYCODE_F12);
			}
			const vector<string>& getContextFunctions() {
				return CONTEXTFUNCTIONS_ALL;
			}
		};
		registerMethod(new MethodInputKeyboardKEYCODE_F12(this));
	}
	{
		//
		class MethodInputKeyboardIsKeyDown: public Method {
		private:
			LogicMiniScript* miniScript { nullptr };
		public:
			MethodInputKeyboardIsKeyDown(LogicMiniScript* miniScript):
				Method(
					{
						{ .type = VariableType::TYPE_INTEGER, .name = "keyCode", .optional = false, .reference = false, .nullable = false }
					},
					VariableType::TYPE_BOOLEAN
				),
				miniScript(miniScript) {}
			const string getMethodName() override {
				return "input.keyboard.isKeyDown";
			}
			void executeMethod(span<Variable>& argumentValues, Variable& returnValue, const Statement& statement) override {
				int64_t keyCode;
				if (miniScript->getIntegerValue(argumentValues, 0, keyCode) == true) {
					returnValue = miniScript->keyboardKeys.find(keyCode) != miniScript->keyboardKeys.end();
				} else {
					Console::println(getMethodName() + "(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation(getMethodName()));
					miniScript->startErrorScript();
				}
			}
			const vector<string>& getContextFunctions() {
				return CONTEXTFUNCTIONS_ALL;
			}
		};
		registerMethod(new MethodInputKeyboardIsKeyDown(this));
	}
	{
		//
		class MethodInputKeyboardIsCharDown: public Method {
		private:
			LogicMiniScript* miniScript { nullptr };
		public:
			MethodInputKeyboardIsCharDown(LogicMiniScript* miniScript):
				Method(
					{
						{ .type = VariableType::TYPE_STRING, .name = "charAsString", .optional = false, .reference = false, .nullable = false }
					},
					VariableType::TYPE_BOOLEAN
				),
				miniScript(miniScript) {}
			const string getMethodName() override {
				return "input.keyboard.isCharDown";
			}
			void executeMethod(span<Variable>& argumentValues, Variable& returnValue, const Statement& statement) override {
				string charAsString;
				if (miniScript->getStringValue(argumentValues, 0, charAsString) == true) {
					UTF8CharacterIterator u8It(charAsString);
					auto keyChar = u8It.hasNext() == true?u8It.next():-1;
					returnValue = miniScript->keyboardChars.find(keyChar) != miniScript->keyboardChars.end();
				} else {
					Console::println(getMethodName() + "(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation(getMethodName()));
					miniScript->startErrorScript();
				}
			}
			const vector<string>& getContextFunctions() {
				return CONTEXTFUNCTIONS_ALL;
			}
		};
		registerMethod(new MethodInputKeyboardIsCharDown(this));
	}
	{
		//
		class MethodInputKeyboardGetTypedString: public Method {
		private:
			LogicMiniScript* miniScript { nullptr };
		public:
			MethodInputKeyboardGetTypedString(LogicMiniScript* miniScript):
				Method({}, VariableType::TYPE_STRING),
				miniScript(miniScript) {}
			const string getMethodName() override {
				return "input.keyboard.getTypedString";
			}
			void executeMethod(span<Variable>& argumentValues, Variable& returnValue, const Statement& statement) override {
				returnValue = miniScript->keyboardTypedChars;
			}
			const vector<string>& getContextFunctions() {
				return CONTEXTFUNCTIONS_ALL;
			}
		};
		registerMethod(new MethodInputKeyboardGetTypedString(this));
	}
	{
		//
		class MethodInputKeyboardIsControlDown: public Method {
		private:
			LogicMiniScript* miniScript { nullptr };
		public:
			MethodInputKeyboardIsControlDown(LogicMiniScript* miniScript):
				Method({}, VariableType::TYPE_BOOLEAN),
				miniScript(miniScript) {}
			const string getMethodName() override {
				return "input.keyboard.isControlDown";
			}
			void executeMethod(span<Variable>& argumentValues, Variable& returnValue, const Statement& statement) override {
				returnValue = miniScript->keyboardControlDown == true;
			}
			const vector<string>& getContextFunctions() {
				return CONTEXTFUNCTIONS_ALL;
			}
		};
		registerMethod(new MethodInputKeyboardIsControlDown(this));
	}
	{
		//
		class MethodInputKeyboardIsMetaDown: public Method {
		private:
			LogicMiniScript* miniScript { nullptr };
		public:
			MethodInputKeyboardIsMetaDown(LogicMiniScript* miniScript):
				Method({}, VariableType::TYPE_BOOLEAN),
				miniScript(miniScript) {}
			const string getMethodName() override {
				return "input.keyboard.isMetaDown";
			}
			void executeMethod(span<Variable>& argumentValues, Variable& returnValue, const Statement& statement) override {
				returnValue = miniScript->keyboardControlDown == true;
			}
			const vector<string>& getContextFunctions() {
				return CONTEXTFUNCTIONS_ALL;
			}
		};
		registerMethod(new MethodInputKeyboardIsMetaDown(this));
	}
	{
		//
		class MethodInputKeyboardIsAltDown: public Method {
		private:
			LogicMiniScript* miniScript { nullptr };
		public:
			MethodInputKeyboardIsAltDown(LogicMiniScript* miniScript):
				Method({}, VariableType::TYPE_BOOLEAN),
				miniScript(miniScript) {}
			const string getMethodName() override {
				return "input.keyboard.isAltDown";
			}
			void executeMethod(span<Variable>& argumentValues, Variable& returnValue, const Statement& statement) override {
				returnValue = miniScript->keyboardAltDown == true;
			}
			const vector<string>& getContextFunctions() {
				return CONTEXTFUNCTIONS_ALL;
			}
		};
		registerMethod(new MethodInputKeyboardIsAltDown(this));
	}
	{
		//
		class MethodInputKeyboardIsShiftDown: public Method {
		private:
			LogicMiniScript* miniScript { nullptr };
		public:
			MethodInputKeyboardIsShiftDown(LogicMiniScript* miniScript):
				Method({}, VariableType::TYPE_BOOLEAN),
				miniScript(miniScript) {}
			const string getMethodName() override {
				return "input.keyboard.isShiftDown";
			}
			void executeMethod(span<Variable>& argumentValues, Variable& returnValue, const Statement& statement) override {
				returnValue = miniScript->keyboardShiftDown == true;
			}
			const vector<string>& getContextFunctions() {
				return CONTEXTFUNCTIONS_ALL;
			}
		};
		registerMethod(new MethodInputKeyboardIsShiftDown(this));
	}
	// mouse input
	{
		//
		class MethodInputMouseBUTTON_LEFT: public Method {
		private:
			LogicMiniScript* miniScript { nullptr };
		public:
			MethodInputMouseBUTTON_LEFT(LogicMiniScript* miniScript):
				Method({}, VariableType::TYPE_INTEGER),
				miniScript(miniScript) {}
			const string getMethodName() override {
				return "input.mouse.BUTTON_LEFT";
			}
			void executeMethod(span<Variable>& argumentValues, Variable& returnValue, const Statement& statement) override {
				returnValue = static_cast<int64_t>(GUIMouseEvent::MOUSEEVENT_BUTTON_LEFT - 1);
			}
			const vector<string>& getContextFunctions() {
				return CONTEXTFUNCTIONS_ALL;
			}
		};
		registerMethod(new MethodInputMouseBUTTON_LEFT(this));
	}
	{
		//
		class MethodInputMouseBUTTON_MIDDLE: public Method {
		private:
			LogicMiniScript* miniScript { nullptr };
		public:
			MethodInputMouseBUTTON_MIDDLE(LogicMiniScript* miniScript):
				Method({}, VariableType::TYPE_INTEGER),
				miniScript(miniScript) {}
			const string getMethodName() override {
				return "input.mouse.BUTTON_MIDDLE";
			}
			void executeMethod(span<Variable>& argumentValues, Variable& returnValue, const Statement& statement) override {
				returnValue = static_cast<int64_t>(GUIMouseEvent::MOUSEEVENT_BUTTON_MIDDLE - 1);
			}
			const vector<string>& getContextFunctions() {
				return CONTEXTFUNCTIONS_ALL;
			}
		};
		registerMethod(new MethodInputMouseBUTTON_MIDDLE(this));
	}
	{
		//
		class MethodInputMouseBUTTON_RIGHT: public Method {
		private:
			LogicMiniScript* miniScript { nullptr };
		public:
			MethodInputMouseBUTTON_RIGHT(LogicMiniScript* miniScript):
				Method({}, VariableType::TYPE_INTEGER),
				miniScript(miniScript) {}
			const string getMethodName() override {
				return "input.mouse.BUTTON_RIGHT";
			}
			void executeMethod(span<Variable>& argumentValues, Variable& returnValue, const Statement& statement) override {
				returnValue = static_cast<int64_t>(GUIMouseEvent::MOUSEEVENT_BUTTON_RIGHT - 1);
			}
			const vector<string>& getContextFunctions() {
				return CONTEXTFUNCTIONS_ALL;
			}
		};
		registerMethod(new MethodInputMouseBUTTON_RIGHT(this));
	}
	{
		//
		class MethodInputMouseIsButtonDown: public Method {
		private:
			LogicMiniScript* miniScript { nullptr };
		public:
			MethodInputMouseIsButtonDown(LogicMiniScript* miniScript):
				Method(
					{
						{ .type = VariableType::TYPE_INTEGER, .name = "button", .optional = false, .reference = false, .nullable = false }
					},
					VariableType::TYPE_BOOLEAN),
				miniScript(miniScript) {}
			const string getMethodName() override {
				return "input.mouse.isButtonDown";
			}
			void executeMethod(span<Variable>& argumentValues, Variable& returnValue, const Statement& statement) override {
				int64_t button;
				if (miniScript->getIntegerValue(argumentValues, 0, button) == true) {
					returnValue = button >= 0 && button <= 3?miniScript->mouseDown[button]:false;
				} else {
					Console::println(getMethodName() + "(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation(getMethodName()));
					miniScript->startErrorScript();
				}
			}
			const vector<string>& getContextFunctions() {
				return CONTEXTFUNCTIONS_ALL;
			}
		};
		registerMethod(new MethodInputMouseIsButtonDown(this));
	}
	{
		//
		class MethodInputMouseIsButtonUp: public Method {
		private:
			LogicMiniScript* miniScript { nullptr };
		public:
			MethodInputMouseIsButtonUp(LogicMiniScript* miniScript):
				Method(
					{
						{ .type = VariableType::TYPE_INTEGER, .name = "button", .optional = false, .reference = false, .nullable = false }
					},
					VariableType::TYPE_BOOLEAN),
				miniScript(miniScript) {}
			const string getMethodName() override {
				return "input.mouse.isButtonUp";
			}
			void executeMethod(span<Variable>& argumentValues, Variable& returnValue, const Statement& statement) override {
				int64_t button;
				if (miniScript->getIntegerValue(argumentValues, 0, button) == true) {
					returnValue = button >= 0 && button <= 3?miniScript->mouseUp[button]:false;
				} else {
					Console::println(getMethodName() + "(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation(getMethodName()));
					miniScript->startErrorScript();
				}
			}
			const vector<string>& getContextFunctions() {
				return CONTEXTFUNCTIONS_ALL;
			}
		};
		registerMethod(new MethodInputMouseIsButtonUp(this));
	}
	{
		//
		class MethodInputMouseIsDragging: public Method {
		private:
			LogicMiniScript* miniScript { nullptr };
		public:
			MethodInputMouseIsDragging(LogicMiniScript* miniScript):
				Method(
					{
						{ .type = VariableType::TYPE_INTEGER, .name = "button", .optional = false, .reference = false, .nullable = false }
					},
					VariableType::TYPE_BOOLEAN),
				miniScript(miniScript) {}
			const string getMethodName() override {
				return "input.mouse.isDragging";
			}
			void executeMethod(span<Variable>& argumentValues, Variable& returnValue, const Statement& statement) override {
				int64_t button;
				if (miniScript->getIntegerValue(argumentValues, 0, button) == true) {
					returnValue = button >= 0 && button <= 3?miniScript->mouseDragging[button]:false;
				} else {
					Console::println(getMethodName() + "(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation(getMethodName()));
					miniScript->startErrorScript();
				}
			}
			const vector<string>& getContextFunctions() {
				return CONTEXTFUNCTIONS_ALL;
			}
		};
		registerMethod(new MethodInputMouseIsDragging(this));
	}
	{
		//
		class MethodInputMouseHasMoved: public Method {
		private:
			LogicMiniScript* miniScript { nullptr };
		public:
			MethodInputMouseHasMoved(LogicMiniScript* miniScript):
				Method({}, VariableType::TYPE_BOOLEAN),
				miniScript(miniScript) {}
			const string getMethodName() override {
				return "input.mouse.hasMoved";
			}
			void executeMethod(span<Variable>& argumentValues, Variable& returnValue, const Statement& statement) override {
				returnValue = miniScript->mouseMoved;
			}
			const vector<string>& getContextFunctions() {
				return CONTEXTFUNCTIONS_ALL;
			}
		};
		registerMethod(new MethodInputMouseHasMoved(this));
	}
	{
		//
		class MethodInputMouseGetX: public Method {
		private:
			LogicMiniScript* miniScript { nullptr };
		public:
			MethodInputMouseGetX(LogicMiniScript* miniScript):
				Method({}, VariableType::TYPE_INTEGER),
				miniScript(miniScript) {}
			const string getMethodName() override {
				return "input.mouse.getX";
			}
			void executeMethod(span<Variable>& argumentValues, Variable& returnValue, const Statement& statement) override {
				returnValue = static_cast<int64_t>(miniScript->mouseX);
			}
			const vector<string>& getContextFunctions() {
				return CONTEXTFUNCTIONS_ALL;
			}
		};
		registerMethod(new MethodInputMouseGetX(this));
	}
	{
		//
		class MethodInputMouseGetXUnscaled: public Method {
		private:
			LogicMiniScript* miniScript { nullptr };
		public:
			MethodInputMouseGetXUnscaled(LogicMiniScript* miniScript):
				Method({}, VariableType::TYPE_INTEGER),
				miniScript(miniScript) {}
			const string getMethodName() override {
				return "input.mouse.getXUnscaled";
			}
			void executeMethod(span<Variable>& argumentValues, Variable& returnValue, const Statement& statement) override {
				returnValue = static_cast<int64_t>(miniScript->mouseXUnscaled);
			}
			const vector<string>& getContextFunctions() {
				return CONTEXTFUNCTIONS_ALL;
			}
		};
		registerMethod(new MethodInputMouseGetXUnscaled(this));
	}
	{
		//
		class MethodInputMouseGetY: public Method {
		private:
			LogicMiniScript* miniScript { nullptr };
		public:
			MethodInputMouseGetY(LogicMiniScript* miniScript):
				Method({}, VariableType::TYPE_INTEGER),
				miniScript(miniScript) {}
			const string getMethodName() override {
				return "input.mouse.getY";
			}
			void executeMethod(span<Variable>& argumentValues, Variable& returnValue, const Statement& statement) override {
				returnValue = static_cast<int64_t>(miniScript->mouseY);
			}
			const vector<string>& getContextFunctions() {
				return CONTEXTFUNCTIONS_ALL;
			}
		};
		registerMethod(new MethodInputMouseGetY(this));
	}
	{
		//
		class MethodInputMouseGetYUnscaled: public Method {
		private:
			LogicMiniScript* miniScript { nullptr };
		public:
			MethodInputMouseGetYUnscaled(LogicMiniScript* miniScript):
				Method({}, VariableType::TYPE_INTEGER),
				miniScript(miniScript) {}
			const string getMethodName() override {
				return "input.mouse.getYUnscaled";
			}
			void executeMethod(span<Variable>& argumentValues, Variable& returnValue, const Statement& statement) override {
				returnValue = static_cast<int64_t>(miniScript->mouseYUnscaled);
			}
			const vector<string>& getContextFunctions() {
				return CONTEXTFUNCTIONS_ALL;
			}
		};
		registerMethod(new MethodInputMouseGetYUnscaled(this));
	}
	{
		//
		class MethodInputMouseGetWheelX: public Method {
		private:
			LogicMiniScript* miniScript { nullptr };
		public:
			MethodInputMouseGetWheelX(LogicMiniScript* miniScript):
				Method({}, VariableType::TYPE_FLOAT),
				miniScript(miniScript) {}
			const string getMethodName() override {
				return "input.mouse.getWheelX";
			}
			void executeMethod(span<Variable>& argumentValues, Variable& returnValue, const Statement& statement) override {
				returnValue = miniScript->mouseWheelX;
			}
			const vector<string>& getContextFunctions() {
				return CONTEXTFUNCTIONS_ALL;
			}
		};
		registerMethod(new MethodInputMouseGetWheelX(this));
	}
	{
		//
		class MethodInputMouseGetWheelY: public Method {
		private:
			LogicMiniScript* miniScript { nullptr };
		public:
			MethodInputMouseGetWheelY(LogicMiniScript* miniScript):
				Method({}, VariableType::TYPE_FLOAT),
				miniScript(miniScript) {}
			const string getMethodName() override {
				return "input.mouse.getWheelY";
			}
			void executeMethod(span<Variable>& argumentValues, Variable& returnValue, const Statement& statement) override {
				returnValue = miniScript->mouseWheelY;
			}
			const vector<string>& getContextFunctions() {
				return CONTEXTFUNCTIONS_ALL;
			}
		};
		registerMethod(new MethodInputMouseGetWheelY(this));
	}
	{
		//
		class MethodInputMouseGetWheelZ: public Method {
		private:
			LogicMiniScript* miniScript { nullptr };
		public:
			MethodInputMouseGetWheelZ(LogicMiniScript* miniScript):
				Method({}, VariableType::TYPE_FLOAT),
				miniScript(miniScript) {}
			const string getMethodName() override {
				return "input.mouse.getWheelZ";
			}
			void executeMethod(span<Variable>& argumentValues, Variable& returnValue, const Statement& statement) override {
				returnValue = miniScript->mouseWheelZ;
			}
			const vector<string>& getContextFunctions() {
				return CONTEXTFUNCTIONS_ALL;
			}
		};
		registerMethod(new MethodInputMouseGetWheelZ(this));
	}
	// camera
	{
		//
		class MethodCameraGetLookFrom: public Method {
		private:
			LogicMiniScript* miniScript { nullptr };
		public:
			MethodCameraGetLookFrom(LogicMiniScript* miniScript):
				Method({}, TYPE_VECTOR3),
				miniScript(miniScript) {}
			const string getMethodName() override {
				return "engine.camera.getLookFrom";
			}
			void executeMethod(span<Variable>& argumentValues, Variable& returnValue, const Statement& statement) override {
				miniScript->setValue(returnValue, miniScript->context->getEngine()->getCamera()->getLookFrom());
			}
			const vector<string>& getContextFunctions() {
				return CONTEXTFUNCTIONS_ENGINE;
			}
		};
		registerMethod(new MethodCameraGetLookFrom(this));
	}
	{
		//
		class MethodCameraSetLookFrom: public Method {
		private:
			LogicMiniScript* miniScript { nullptr };
		public:
			MethodCameraSetLookFrom(LogicMiniScript* miniScript):
				Method(
					{
						{ .type = TYPE_VECTOR3, .name = "lookFrom", .optional = false, .reference = false, .nullable = false }
					},
					VariableType::TYPE_NULL
				),
				miniScript(miniScript) {}
			const string getMethodName() override {
				return "engine.camera.setLookFrom";
			}
			void executeMethod(span<Variable>& argumentValues, Variable& returnValue, const Statement& statement) override {
				Vector3 lookFrom;
				if (miniScript->getVector3Value(argumentValues, 0, lookFrom) == true) {
					miniScript->context->getEngine()->getCamera()->setLookFrom(lookFrom);
				} else {
					Console::println(getMethodName() + "(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation(getMethodName()));
					miniScript->startErrorScript();
				}
			}
			const vector<string>& getContextFunctions() {
				return CONTEXTFUNCTIONS_ENGINE;
			}
		};
		registerMethod(new MethodCameraSetLookFrom(this));
	}
	{
		//
		class MethodCameraGetLookAt: public Method {
		private:
			LogicMiniScript* miniScript { nullptr };
		public:
			MethodCameraGetLookAt(LogicMiniScript* miniScript):
				Method({}, TYPE_VECTOR3),
				miniScript(miniScript) {}
			const string getMethodName() override {
				return "engine.camera.getLookAt";
			}
			void executeMethod(span<Variable>& argumentValues, Variable& returnValue, const Statement& statement) override {
				miniScript->setValue(returnValue, miniScript->context->getEngine()->getCamera()->getLookAt());
			}
			const vector<string>& getContextFunctions() {
				return CONTEXTFUNCTIONS_ENGINE;
			}
		};
		registerMethod(new MethodCameraGetLookAt(this));
	}
	{
		//
		class MethodCameraSetLookAt: public Method {
		private:
			LogicMiniScript* miniScript { nullptr };
		public:
			MethodCameraSetLookAt(LogicMiniScript* miniScript):
				Method(
					{
						{ .type = TYPE_VECTOR3, .name = "lookAt", .optional = false, .reference = false, .nullable = false }
					},
					VariableType::TYPE_NULL
				),
				miniScript(miniScript) {}
			const string getMethodName() override {
				return "engine.camera.setLookAt";
			}
			void executeMethod(span<Variable>& argumentValues, Variable& returnValue, const Statement& statement) override {
				Vector3 lookAt;
				if (miniScript->getVector3Value(argumentValues, 0, lookAt) == true) {
					miniScript->context->getEngine()->getCamera()->setLookAt(lookAt);
				} else {
					Console::println(getMethodName() + "(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation(getMethodName()));
					miniScript->startErrorScript();
				}
			}
			const vector<string>& getContextFunctions() {
				return CONTEXTFUNCTIONS_ENGINE;
			}
		};
		registerMethod(new MethodCameraSetLookAt(this));
	}
	{
		//
		class MethodCameraGetUpVector: public Method {
		private:
			LogicMiniScript* miniScript { nullptr };
		public:
			MethodCameraGetUpVector(LogicMiniScript* miniScript):
				Method({}, TYPE_VECTOR3),
				miniScript(miniScript) {}
			const string getMethodName() override {
				return "engine.camera.getUpVector";
			}
			void executeMethod(span<Variable>& argumentValues, Variable& returnValue, const Statement& statement) override {
				miniScript->setValue(returnValue, miniScript->context->getEngine()->getCamera()->getUpVector());
			}
			const vector<string>& getContextFunctions() {
				return CONTEXTFUNCTIONS_ENGINE;
			}
		};
		registerMethod(new MethodCameraGetUpVector(this));
	}
	{
		//
		class MethodCameraSetUpVector: public Method {
		private:
			LogicMiniScript* miniScript { nullptr };
		public:
			MethodCameraSetUpVector(LogicMiniScript* miniScript):
				Method(
					{
						{ .type = TYPE_VECTOR3, .name = "upVector", .optional = false, .reference = false, .nullable = false }
					},
					VariableType::TYPE_NULL
				),
				miniScript(miniScript) {}
			const string getMethodName() override {
				return "engine.camera.setUpVector";
			}
			void executeMethod(span<Variable>& argumentValues, Variable& returnValue, const Statement& statement) override {
				Vector3 upVector;
				if (miniScript->getVector3Value(argumentValues, 0, upVector) == true) {
					miniScript->context->getEngine()->getCamera()->setUpVector(upVector);
				} else {
					Console::println(getMethodName() + "(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation(getMethodName()));
					miniScript->startErrorScript();
				}
			}
			const vector<string>& getContextFunctions() {
				return CONTEXTFUNCTIONS_ENGINE;
			}
		};
		registerMethod(new MethodCameraSetUpVector(this));
	}
	{
		//
		class MethodCameraComputeUpVector: public Method {
		private:
			LogicMiniScript* miniScript { nullptr };
		public:
			MethodCameraComputeUpVector(LogicMiniScript* miniScript):
				Method(
					{
						{ .type = TYPE_VECTOR3, .name = "lookFrom", .optional = false, .reference = false, .nullable = false },
						{ .type = TYPE_VECTOR3, .name = "lookAt", .optional = false, .reference = false, .nullable = false }
					},
					TYPE_VECTOR3
				),
				miniScript(miniScript) {}
			const string getMethodName() override {
				return "engine.camera.computeUpVector";
			}
			void executeMethod(span<Variable>& argumentValues, Variable& returnValue, const Statement& statement) override {
				Vector3 lookFrom;
				Vector3 lookAt;
				if (miniScript->getVector3Value(argumentValues, 0, lookFrom) == true &&
					miniScript->getVector3Value(argumentValues, 1, lookAt) == true) {
					miniScript->setValue(returnValue, Camera::computeUpVector(lookFrom, lookAt));
				} else {
					Console::println(getMethodName() + "(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation(getMethodName()));
					miniScript->startErrorScript();
				}
			}
			const vector<string>& getContextFunctions() {
				return CONTEXTFUNCTIONS_ENGINE;
			}
		};
		registerMethod(new MethodCameraComputeUpVector(this));
	}
	{
		//
		class MethodCameraGetFovX: public Method {
		private:
			LogicMiniScript* miniScript { nullptr };
		public:
			MethodCameraGetFovX(LogicMiniScript* miniScript):
				Method({}, VariableType::TYPE_FLOAT),
				miniScript(miniScript) {}
			const string getMethodName() override {
				return "engine.camera.getFovX";
			}
			void executeMethod(span<Variable>& argumentValues, Variable& returnValue, const Statement& statement) override {
				returnValue = miniScript->context->getEngine()->getCamera()->getFovX();
			}
			const vector<string>& getContextFunctions() {
				return CONTEXTFUNCTIONS_ENGINE;
			}
		};
		registerMethod(new MethodCameraGetFovX(this));
	}
	{
		//
		class MethodCameraSetFovX: public Method {
		private:
			LogicMiniScript* miniScript { nullptr };
		public:
			MethodCameraSetFovX(LogicMiniScript* miniScript):
				Method(
					{
						{ .type = VariableType::TYPE_FLOAT, .name = "fovX", .optional = false, .reference = false, .nullable = false }
					},
					VariableType::TYPE_NULL
				),
				miniScript(miniScript) {}
			const string getMethodName() override {
				return "engine.camera.setFovX";
			}
			void executeMethod(span<Variable>& argumentValues, Variable& returnValue, const Statement& statement) override {
				float fovX;
				if (miniScript->getFloatValue(argumentValues, 0, fovX) == true) {
					miniScript->context->getEngine()->getCamera()->setFovX(fovX);
				} else {
					Console::println(getMethodName() + "(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation(getMethodName()));
					miniScript->startErrorScript();
				}
			}
			const vector<string>& getContextFunctions() {
				return CONTEXTFUNCTIONS_ENGINE;
			}
		};
		registerMethod(new MethodCameraSetFovX(this));
	}
	// timing
	{
		//
		class MethodTimingGetDeltaTime: public Method {
		private:
			LogicMiniScript* miniScript { nullptr };
		public:
			MethodTimingGetDeltaTime(LogicMiniScript* miniScript):
				Method({}, VariableType::TYPE_INTEGER),
				miniScript(miniScript) {}
			const string getMethodName() override {
				return "engine.timing.getDeltaTime";
			}
			void executeMethod(span<Variable>& argumentValues, Variable& returnValue, const Statement& statement) override {
				returnValue = miniScript->context->getEngine()->getTiming()->getDeltaTime();
			}
			const vector<string>& getContextFunctions() {
				return CONTEXTFUNCTIONS_ENGINE;
			}
		};
		registerMethod(new MethodTimingGetDeltaTime(this));
	}
	{
		//
		class MethodTimingGetDeltaTimeSeconds: public Method {
		private:
			LogicMiniScript* miniScript { nullptr };
		public:
			MethodTimingGetDeltaTimeSeconds(LogicMiniScript* miniScript):
				Method({}, VariableType::TYPE_FLOAT),
				miniScript(miniScript) {}
			const string getMethodName() override {
				return "engine.timing.getDeltaTimeSeconds";
			}
			void executeMethod(span<Variable>& argumentValues, Variable& returnValue, const Statement& statement) override {
				returnValue = miniScript->context->getEngine()->getTiming()->getDeltaTimeSeconds();
			}
			const vector<string>& getContextFunctions() {
				return CONTEXTFUNCTIONS_ENGINE;
			}
		};
		registerMethod(new MethodTimingGetDeltaTimeSeconds(this));
	}
	{
		//
		class MethodTimingGetAvarageFPS: public Method {
		private:
			LogicMiniScript* miniScript { nullptr };
		public:
			MethodTimingGetAvarageFPS(LogicMiniScript* miniScript):
				Method({}, VariableType::TYPE_FLOAT),
				miniScript(miniScript) {}
			const string getMethodName() override {
				return "engine.timing.getAvarageFPS";
			}
			void executeMethod(span<Variable>& argumentValues, Variable& returnValue, const Statement& statement) override {
				returnValue = miniScript->context->getEngine()->getTiming()->getAvarageFPS();
			}
			const vector<string>& getContextFunctions() {
				return CONTEXTFUNCTIONS_ENGINE;
			}
		};
		registerMethod(new MethodTimingGetAvarageFPS(this));
	}
	// engine
	{
		//
		class MethodEngineGetAnimationComputationReduction1Distance: public Method {
		private:
			LogicMiniScript* miniScript { nullptr };
		public:
			MethodEngineGetAnimationComputationReduction1Distance(LogicMiniScript* miniScript):
				Method({}, VariableType::TYPE_FLOAT),
				miniScript(miniScript) {}
			const string getMethodName() override {
				return "engine.getAnimationComputationReduction1Distance";
			}
			void executeMethod(span<Variable>& argumentValues, Variable& returnValue, const Statement& statement) override {
				miniScript->setValue(returnValue, Engine::getAnimationComputationReduction1Distance());
			}
			const vector<string>& getContextFunctions() {
				return CONTEXTFUNCTIONS_ENGINE;
			}
		};
		registerMethod(new MethodEngineGetAnimationComputationReduction1Distance(this));
	}
	{
		//
		class MethodEngineSetAnimationComputationReduction1Distance: public Method {
		private:
			LogicMiniScript* miniScript { nullptr };
		public:
			MethodEngineSetAnimationComputationReduction1Distance(LogicMiniScript* miniScript):
				Method(
					{
						{ .type = VariableType::TYPE_FLOAT, .name = "animationComputationReduction1Distance", .optional = false, .reference = false, .nullable = false }
					},
					VariableType::TYPE_NULL
				),
				miniScript(miniScript) {}
			const string getMethodName() override {
				return "engine.setAnimationComputationReduction1Distance";
			}
			void executeMethod(span<Variable>& argumentValues, Variable& returnValue, const Statement& statement) override {
				float animationComputationReduction1Distance;
				if (miniScript->getFloatValue(argumentValues, 0, animationComputationReduction1Distance) == true) {
					Engine::setAnimationComputationReduction1Distance(animationComputationReduction1Distance);
				} else {
					Console::println(getMethodName() + "(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation(getMethodName()));
					miniScript->startErrorScript();
				}

			}
			const vector<string>& getContextFunctions() {
				return CONTEXTFUNCTIONS_ENGINE;
			}
		};
		registerMethod(new MethodEngineSetAnimationComputationReduction1Distance(this));
	}
	{
		//
		class MethodEngineGetAnimationComputationReduction2Distance: public Method {
		private:
			LogicMiniScript* miniScript { nullptr };
		public:
			MethodEngineGetAnimationComputationReduction2Distance(LogicMiniScript* miniScript):
				Method({}, VariableType::TYPE_FLOAT),
				miniScript(miniScript) {}
			const string getMethodName() override {
				return "engine.getAnimationComputationReduction2Distance";
			}
			void executeMethod(span<Variable>& argumentValues, Variable& returnValue, const Statement& statement) override {
				miniScript->setValue(returnValue, Engine::getAnimationComputationReduction2Distance());
			}
			const vector<string>& getContextFunctions() {
				return CONTEXTFUNCTIONS_ENGINE;
			}
		};
		registerMethod(new MethodEngineGetAnimationComputationReduction2Distance(this));
	}
	{
		//
		class MethodEngineSetAnimationComputationReduction2Distance: public Method {
		private:
			LogicMiniScript* miniScript { nullptr };
		public:
			MethodEngineSetAnimationComputationReduction2Distance(LogicMiniScript* miniScript):
				Method(
					{
						{ .type = VariableType::TYPE_FLOAT, .name = "animationComputationReduction2Distance", .optional = false, .reference = false, .nullable = false }
					},
					VariableType::TYPE_NULL
				),
				miniScript(miniScript) {}
			const string getMethodName() override {
				return "engine.setAnimationComputationReduction2Distance";
			}
			void executeMethod(span<Variable>& argumentValues, Variable& returnValue, const Statement& statement) override {
				float animationComputationReduction2Distance;
				if (miniScript->getFloatValue(argumentValues, 0, animationComputationReduction2Distance) == true) {
					Engine::setAnimationComputationReduction2Distance(animationComputationReduction2Distance);
				} else {
					Console::println(getMethodName() + "(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation(getMethodName()));
					miniScript->startErrorScript();
				}

			}
			const vector<string>& getContextFunctions() {
				return CONTEXTFUNCTIONS_ENGINE;
			}
		};
		registerMethod(new MethodEngineSetAnimationComputationReduction2Distance(this));
	}
	{
		//
		class MethodEngineGetWidth: public Method {
		private:
			LogicMiniScript* miniScript { nullptr };
		public:
			MethodEngineGetWidth(LogicMiniScript* miniScript):
				Method({}, VariableType::TYPE_INTEGER),
				miniScript(miniScript) {}
			const string getMethodName() override {
				return "engine.getWidth";
			}
			void executeMethod(span<Variable>& argumentValues, Variable& returnValue, const Statement& statement) override {
				returnValue = static_cast<int64_t>(miniScript->context->getEngine()->getWidth());
			}
			const vector<string>& getContextFunctions() {
				return CONTEXTFUNCTIONS_ENGINE;
			}
		};
		registerMethod(new MethodEngineGetWidth(this));
	}
	{
		//
		class MethodEngineGetHeight: public Method {
		private:
			LogicMiniScript* miniScript { nullptr };
		public:
			MethodEngineGetHeight(LogicMiniScript* miniScript):
				Method({}, VariableType::TYPE_INTEGER),
				miniScript(miniScript) {}
			const string getMethodName() override {
				return "engine.getHeight";
			}
			void executeMethod(span<Variable>& argumentValues, Variable& returnValue, const Statement& statement) override {
				returnValue = static_cast<int64_t>(miniScript->context->getEngine()->getHeight());
			}
			const vector<string>& getContextFunctions() {
				return CONTEXTFUNCTIONS_ENGINE;
			}
		};
		registerMethod(new MethodEngineGetHeight(this));
	}
	{
		//
		class MethodEngineDumpEntities: public Method {
		private:
			LogicMiniScript* miniScript { nullptr };
		public:
			MethodEngineDumpEntities(LogicMiniScript* miniScript):
				Method({}, VariableType::TYPE_NULL),
				miniScript(miniScript) {}
			const string getMethodName() override {
				return "engine.dumpEntities";
			}
			void executeMethod(span<Variable>& argumentValues, Variable& returnValue, const Statement& statement) override {
				miniScript->context->getEngine()->dumpEntities();
			}
			const vector<string>& getContextFunctions() {
				return CONTEXTFUNCTIONS_ENGINE;
			}
		};
		registerMethod(new MethodEngineDumpEntities(this));
	}
	{
		//
		class MethodEngineDumpShaders: public Method {
		private:
			LogicMiniScript* miniScript { nullptr };
		public:
			MethodEngineDumpShaders(LogicMiniScript* miniScript):
				Method({}, VariableType::TYPE_NULL),
				miniScript(miniScript) {}
			const string getMethodName() override {
				return "engine.dumpShaders";
			}
			void executeMethod(span<Variable>& argumentValues, Variable& returnValue, const Statement& statement) override {
				miniScript->context->getEngine()->dumpShaders();
			}
			const vector<string>& getContextFunctions() {
				return CONTEXTFUNCTIONS_ENGINE;
			}
		};
		registerMethod(new MethodEngineDumpShaders(this));
	}
	{
		//
		class MethodEngineGetEntityIdByMousePosition: public Method {
		private:
			LogicMiniScript* miniScript { nullptr };
		public:
			MethodEngineGetEntityIdByMousePosition(LogicMiniScript* miniScript):
				Method(
					{
						{ .type = VariableType::TYPE_INTEGER, .name = "mouseX", .optional = false, .reference = false, .nullable = false },
						{ .type = VariableType::TYPE_INTEGER, .name = "mouseY", .optional = false, .reference = false, .nullable = false }
					},
					VariableType::TYPE_STRING
				),
				miniScript(miniScript) {}
			const string getMethodName() override {
				return "engine.getEntityIdByMousePosition";
			}
			void executeMethod(span<Variable>& argumentValues, Variable& returnValue, const Statement& statement) override {
				int64_t mouseX;
				int64_t mouseY;
				if (miniScript->getIntegerValue(argumentValues, 0, mouseX) == true &&
					miniScript->getIntegerValue(argumentValues, 1, mouseY) == true) {
					auto entity = miniScript->context->getEngine()->getEntityByMousePosition(mouseX, mouseY);
					if (entity != nullptr) returnValue = entity->getId();
				} else {
					Console::println(getMethodName() + "(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation(getMethodName()));
					miniScript->startErrorScript();
				}
			}
			const vector<string>& getContextFunctions() {
				return CONTEXTFUNCTIONS_ENGINE;
			}
		};
		registerMethod(new MethodEngineGetEntityIdByMousePosition(this));
	}
	{
		//
		class MethodEngineComputeWorldCoordinateByMousePosition: public Method {
		private:
			LogicMiniScript* miniScript { nullptr };
		public:
			MethodEngineComputeWorldCoordinateByMousePosition(LogicMiniScript* miniScript):
				Method(
					{
						{ .type = VariableType::TYPE_INTEGER, .name = "mouseX", .optional = false, .reference = false, .nullable = false },
						{ .type = VariableType::TYPE_INTEGER, .name = "mouseY", .optional = false, .reference = false, .nullable = false }
					},
					TYPE_VECTOR3
				),
				miniScript(miniScript) {}
			const string getMethodName() override {
				return "engine.computeWorldCoordinateByMousePosition";
			}
			void executeMethod(span<Variable>& argumentValues, Variable& returnValue, const Statement& statement) override {
				int64_t mouseX;
				int64_t mouseY;
				if (miniScript->getIntegerValue(argumentValues, 0, mouseX) == true &&
					miniScript->getIntegerValue(argumentValues, 1, mouseY) == true) {
					miniScript->setValue(returnValue, miniScript->context->getEngine()->computeWorldCoordinateByMousePosition(mouseX, mouseY));
				} else {
					Console::println(getMethodName() + "(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation(getMethodName()));
					miniScript->startErrorScript();
				}
			}
			const vector<string>& getContextFunctions() {
				return CONTEXTFUNCTIONS_ENGINE;
			}
		};
		registerMethod(new MethodEngineComputeWorldCoordinateByMousePosition(this));
	}
	{
		//
		class MethodEngineComputeScreenCoordinateByWorldCoordinate: public Method {
		private:
			LogicMiniScript* miniScript { nullptr };
		public:
			MethodEngineComputeScreenCoordinateByWorldCoordinate(LogicMiniScript* miniScript):
				Method(
					{
						{ .type = TYPE_VECTOR3, .name = "worldCoodinate", .optional = false, .reference = false, .nullable = false },
						{ .type = TYPE_VECTOR2, .name = "screenCoordinate", .optional = false, .reference = true, .nullable = false }
					},
					VariableType::TYPE_BOOLEAN
				),
				miniScript(miniScript) {}
			const string getMethodName() override {
				return "engine.computeScreenCoordinateByWorldCoordinate";
			}
			void executeMethod(span<Variable>& argumentValues, Variable& returnValue, const Statement& statement) override {
				Vector3 worldCoodinate;
				if (argumentValues.size() == 2 &&
					miniScript->getVector3Value(argumentValues, 0, worldCoodinate) == true) {
					Vector2 screenCoordinate;
					if (miniScript->context->getEngine()->computeScreenCoordinateByWorldCoordinate(worldCoodinate, screenCoordinate) == true) {
						miniScript->setValue(argumentValues[1], screenCoordinate);
						returnValue = true;
					} else {
						returnValue = false;
					}
				} else {
					Console::println(getMethodName() + "(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation(getMethodName()));
					miniScript->startErrorScript();
				}
			}
			const vector<string>& getContextFunctions() {
				return CONTEXTFUNCTIONS_ENGINE;
			}
		};
		registerMethod(new MethodEngineComputeScreenCoordinateByWorldCoordinate(this));
	}
	{
		//
		class MethodEntityGetTransform: public Method {
		private:
			LogicMiniScript* miniScript { nullptr };
		public:
			MethodEntityGetTransform(LogicMiniScript* miniScript):
				Method(
					{
						{ .type = VariableType::TYPE_STRING, .name = "entityId", .optional = false, .reference = false, .nullable = false },
						{ .type = VariableType::TYPE_STRING, .name = "childEntityId", .optional = true, .reference = false, .nullable = false }
					},
					TYPE_TRANSFORM
				),
				miniScript(miniScript) {}
			const string getMethodName() override {
				return "engine.entity.getTransform";
			}
			void executeMethod(span<Variable>& argumentValues, Variable& returnValue, const Statement& statement) override {
				string entityId;
				string childEntityId;
				if (miniScript->getStringValue(argumentValues, 0, entityId) == true &&
					miniScript->getStringValue(argumentValues, 1, childEntityId, true) == true) {
					auto entity = miniScript->getEntity(entityId, childEntityId);
					if (entity != nullptr) {
						miniScript->setValue(returnValue, entity->getTransform());
					} else {
						Console::println(getMethodName() + "(): " + miniScript->getStatementInformation(statement) + ": entity not found: " + (childEntityId.empty() == true?entityId:childEntityId + "@" + entityId));
					}
				} else {
					Console::println(getMethodName() + "(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation(getMethodName()));
					miniScript->startErrorScript();
				}
			}
			const vector<string>& getContextFunctions() {
				return CONTEXTFUNCTIONS_ENGINE;
			}
		};
		registerMethod(new MethodEntityGetTransform(this));
	}
	{
		//
		class MethodEntitySetTransform: public Method {
		private:
			LogicMiniScript* miniScript { nullptr };
		public:
			MethodEntitySetTransform(LogicMiniScript* miniScript):
				Method(
					{
						{ .type = VariableType::TYPE_STRING, .name = "entityId", .optional = false, .reference = false, .nullable = false },
						{ .type = TYPE_TRANSFORM, .name = "transform", .optional = false, .reference = false, .nullable = false },
						{ .type = VariableType::TYPE_STRING, .name = "childEntityId", .optional = true, .reference = false, .nullable = false }
					},
					VariableType::TYPE_NULL
				),
				miniScript(miniScript) {}
			const string getMethodName() override {
				return "engine.entity.setTransform";
			}
			void executeMethod(span<Variable>& argumentValues, Variable& returnValue, const Statement& statement) override {
				string entityId;
				Transform transform;
				string childEntityId;
				if (miniScript->getStringValue(argumentValues, 0, entityId) == true &&
					miniScript->getTransformValue(argumentValues, 1, transform) == true &&
					miniScript->getStringValue(argumentValues, 2, childEntityId, true) == true) {
					auto entity = miniScript->getEntity(entityId, childEntityId);
					if (entity != nullptr) {
						entity->setTransform(transform);
					} else {
						Console::println(getMethodName() + "(): " + miniScript->getStatementInformation(statement) + ": entity not found: " + (childEntityId.empty() == true?entityId:childEntityId + "@" + entityId));
					}
				} else {
					Console::println(getMethodName() + "(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation(getMethodName()));
					miniScript->startErrorScript();
				}
			}
			const vector<string>& getContextFunctions() {
				return CONTEXTFUNCTIONS_ENGINE;
			}
		};
		registerMethod(new MethodEntitySetTransform(this));
	}
	{
		//
		class MethodEntityIsEnabled: public Method {
		private:
			LogicMiniScript* miniScript { nullptr };
		public:
			MethodEntityIsEnabled(LogicMiniScript* miniScript):
				Method(
					{
						{ .type = VariableType::TYPE_STRING, .name = "entityId", .optional = false, .reference = false, .nullable = false },
						{ .type = VariableType::TYPE_STRING, .name = "childEntityId", .optional = true, .reference = false, .nullable = false }
					},
					VariableType::TYPE_BOOLEAN
				),
				miniScript(miniScript) {}
			const string getMethodName() override {
				return "engine.entity.isEnabled";
			}
			void executeMethod(span<Variable>& argumentValues, Variable& returnValue, const Statement& statement) override {
				string entityId;
				string childEntityId;
				if (miniScript->getStringValue(argumentValues, 0, entityId) == true &&
					miniScript->getStringValue(argumentValues, 1, childEntityId, true) == true) {
					auto entity = miniScript->getEntity(entityId, childEntityId);
					if (entity != nullptr) {
						returnValue = entity->isEnabled();
					} else {
						Console::println(getMethodName() + "(): " + miniScript->getStatementInformation(statement) + ": entity not found: " + (childEntityId.empty() == true?entityId:childEntityId + "@" + entityId));
					}
				} else {
					Console::println(getMethodName() + "(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation(getMethodName()));
					miniScript->startErrorScript();
				}
			}
			const vector<string>& getContextFunctions() {
				return CONTEXTFUNCTIONS_ENGINE;
			}
		};
		registerMethod(new MethodEntityIsEnabled(this));
	}
	{
		//
		class MethodEntitySetEnabled: public Method {
		private:
			LogicMiniScript* miniScript { nullptr };
		public:
			MethodEntitySetEnabled(LogicMiniScript* miniScript):
				Method(
					{
						{ .type = VariableType::TYPE_STRING, .name = "entityId", .optional = false, .reference = false, .nullable = false },
						{ .type = VariableType::TYPE_BOOLEAN, .name = "enabled", .optional = false, .reference = false, .nullable = false },
						{ .type = VariableType::TYPE_STRING, .name = "childEntityId", .optional = true, .reference = false, .nullable = false }
					},
					VariableType::TYPE_NULL
				),
				miniScript(miniScript) {}
			const string getMethodName() override {
				return "engine.entity.setEnabled";
			}
			void executeMethod(span<Variable>& argumentValues, Variable& returnValue, const Statement& statement) override {
				string entityId;
				bool enabled;
				string childEntityId;
				if (miniScript->getStringValue(argumentValues, 0, entityId) == true &&
					miniScript->getBooleanValue(argumentValues, 1, enabled) == true &&
					miniScript->getStringValue(argumentValues, 2, childEntityId, true) == true) {
					auto entity = miniScript->getEntity(entityId, childEntityId);
					if (entity != nullptr) {
						entity->setEnabled(enabled);
					} else {
						Console::println(getMethodName() + "(): " + miniScript->getStatementInformation(statement) + ": entity not found: " + (childEntityId.empty() == true?entityId:childEntityId + "@" + entityId));
					}
				} else {
					Console::println(getMethodName() + "(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation(getMethodName()));
					miniScript->startErrorScript();
				}
			}
			const vector<string>& getContextFunctions() {
				return CONTEXTFUNCTIONS_ENGINE;
			}
		};
		registerMethod(new MethodEntitySetEnabled(this));
	}
	{
		//
		class MethodEntityIsPickable: public Method {
		private:
			LogicMiniScript* miniScript { nullptr };
		public:
			MethodEntityIsPickable(LogicMiniScript* miniScript):
				Method(
					{
						{ .type = VariableType::TYPE_STRING, .name = "entityId", .optional = false, .reference = false, .nullable = false },
						{ .type = VariableType::TYPE_STRING, .name = "childEntityId", .optional = true, .reference = false, .nullable = false }
					},
					VariableType::TYPE_BOOLEAN
				),
				miniScript(miniScript) {}
			const string getMethodName() override {
				return "engine.entity.isPickable";
			}
			void executeMethod(span<Variable>& argumentValues, Variable& returnValue, const Statement& statement) override {
				string entityId;
				string childEntityId;
				if (miniScript->getStringValue(argumentValues, 0, entityId) == true &&
					miniScript->getStringValue(argumentValues, 1, childEntityId, true) == true) {
					auto entity = miniScript->getEntity(entityId, childEntityId);
					if (entity != nullptr) {
						returnValue = entity->isPickable();
					} else {
						Console::println(getMethodName() + "(): " + miniScript->getStatementInformation(statement) + ": entity not found: " + (childEntityId.empty() == true?entityId:childEntityId + "@" + entityId));
					}
				} else {
					Console::println(getMethodName() + "(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation(getMethodName()));
					miniScript->startErrorScript();
				}
			}
			const vector<string>& getContextFunctions() {
				return CONTEXTFUNCTIONS_ENGINE;
			}
		};
		registerMethod(new MethodEntityIsPickable(this));
	}
	{
		//
		class MethodEntitySetPickable: public Method {
		private:
			LogicMiniScript* miniScript { nullptr };
		public:
			MethodEntitySetPickable(LogicMiniScript* miniScript):
				Method(
					{
						{ .type = VariableType::TYPE_STRING, .name = "entityId", .optional = false, .reference = false, .nullable = false },
						{ .type = VariableType::TYPE_BOOLEAN, .name = "pickable", .optional = false, .reference = false, .nullable = false },
						{ .type = VariableType::TYPE_STRING, .name = "childEntityId", .optional = true, .reference = false, .nullable = false }
					},
					VariableType::TYPE_NULL
				),
				miniScript(miniScript) {}
			const string getMethodName() override {
				return "engine.entity.setPickable";
			}
			void executeMethod(span<Variable>& argumentValues, Variable& returnValue, const Statement& statement) override {
				string entityId;
				bool pickable;
				string childEntityId;
				if (miniScript->getStringValue(argumentValues, 0, entityId) == true &&
					miniScript->getBooleanValue(argumentValues, 1, pickable) == true &&
					miniScript->getStringValue(argumentValues, 2, childEntityId, true) == true) {
					auto entity = miniScript->getEntity(entityId, childEntityId);
					if (entity != nullptr) {
						entity->setPickable(pickable);
					} else {
						Console::println(getMethodName() + "(): " + miniScript->getStatementInformation(statement) + ": entity not found: " + (childEntityId.empty() == true?entityId:childEntityId + "@" + entityId));
					}
				} else {
					Console::println(getMethodName() + "(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation(getMethodName()));
					miniScript->startErrorScript();
				}
			}
			const vector<string>& getContextFunctions() {
				return CONTEXTFUNCTIONS_ENGINE;
			}
		};
		registerMethod(new MethodEntitySetPickable(this));
	}
	{
		//
		class MethodEntityGetEffectColorMul: public Method {
		private:
			LogicMiniScript* miniScript { nullptr };
		public:
			MethodEntityGetEffectColorMul(LogicMiniScript* miniScript):
				Method(
					{
						{ .type = VariableType::TYPE_STRING, .name = "entityId", .optional = false, .reference = false, .nullable = false },
						{ .type = VariableType::TYPE_STRING, .name = "childEntityId", .optional = true, .reference = false, .nullable = false }
					},
					TYPE_VECTOR4
				),
				miniScript(miniScript) {}
			const string getMethodName() override {
				return "engine.entity.getEffectColorMul";
			}
			void executeMethod(span<Variable>& argumentValues, Variable& returnValue, const Statement& statement) override {
				string entityId;
				string childEntityId;
				if (miniScript->getStringValue(argumentValues, 0, entityId) == true &&
					miniScript->getStringValue(argumentValues, 1, childEntityId, true) == true) {
					auto entity = miniScript->getEntity(entityId, childEntityId);
					if (entity != nullptr) {
						auto effectColorMul = entity->getEffectColorMul();
						miniScript->setValue(returnValue, Vector4(effectColorMul.getRed(), effectColorMul.getGreen(), effectColorMul.getBlue(), effectColorMul.getAlpha()));
					} else {
						Console::println(getMethodName() + "(): " + miniScript->getStatementInformation(statement) + ": entity not found: " + (childEntityId.empty() == true?entityId:childEntityId + "@" + entityId));
					}
				} else {
					Console::println(getMethodName() + "(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation(getMethodName()));
					miniScript->startErrorScript();
				}
			}
			const vector<string>& getContextFunctions() {
				return CONTEXTFUNCTIONS_ENGINE;
			}
		};
		registerMethod(new MethodEntityGetEffectColorMul(this));
	}
	{
		//
		class MethodEntitySetEffectColorMul: public Method {
		private:
			LogicMiniScript* miniScript { nullptr };
		public:
			MethodEntitySetEffectColorMul(LogicMiniScript* miniScript):
				Method(
					{
						{ .type = VariableType::TYPE_STRING, .name = "entityId", .optional = false, .reference = false, .nullable = false },
						{ .type = TYPE_VECTOR4, .name = "effectColorMul", .optional = false, .reference = false, .nullable = false },
						{ .type = VariableType::TYPE_STRING, .name = "childEntityId", .optional = true, .reference = false, .nullable = false }
					},
					VariableType::TYPE_NULL
				),
				miniScript(miniScript) {}
			const string getMethodName() override {
				return "engine.entity.setEffectColorMul";
			}
			void executeMethod(span<Variable>& argumentValues, Variable& returnValue, const Statement& statement) override {
				string entityId;
				Vector4 effectColorMul;
				string childEntityId;
				if (miniScript->getStringValue(argumentValues, 0, entityId) == true &&
					miniScript->getVector4Value(argumentValues, 1, effectColorMul) == true &&
					miniScript->getStringValue(argumentValues, 2, childEntityId, true) == true) {
					auto entity = miniScript->getEntity(entityId, childEntityId);
					if (entity != nullptr) {
						entity->setEffectColorMul(Color4(effectColorMul.getX(), effectColorMul.getY(), effectColorMul.getZ(), effectColorMul.getW()));
					} else {
						Console::println(getMethodName() + "(): " + miniScript->getStatementInformation(statement) + ": entity not found: " + (childEntityId.empty() == true?entityId:childEntityId + "@" + entityId));
					}
				} else {
					Console::println(getMethodName() + "(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation(getMethodName()));
					miniScript->startErrorScript();
				}
			}
			const vector<string>& getContextFunctions() {
				return CONTEXTFUNCTIONS_ENGINE;
			}
		};
		registerMethod(new MethodEntitySetEffectColorMul(this));
	}
	{
		//
		class MethodEntityGetEffectColorAdd: public Method {
		private:
			LogicMiniScript* miniScript { nullptr };
		public:
			MethodEntityGetEffectColorAdd(LogicMiniScript* miniScript):
				Method(
					{
						{ .type = VariableType::TYPE_STRING, .name = "entityId", .optional = false, .reference = false, .nullable = false },
						{ .type = VariableType::TYPE_STRING, .name = "childEntityId", .optional = true, .reference = false, .nullable = false }
					},
					TYPE_VECTOR4
				),
				miniScript(miniScript) {}
			const string getMethodName() override {
				return "engine.entity.getEffectColorAdd";
			}
			void executeMethod(span<Variable>& argumentValues, Variable& returnValue, const Statement& statement) override {
				string entityId;
				string childEntityId;
				if (miniScript->getStringValue(argumentValues, 0, entityId) == true &&
					miniScript->getStringValue(argumentValues, 1, childEntityId, true) == true) {
					auto entity = miniScript->getEntity(entityId, childEntityId);
					if (entity != nullptr) {
						auto effectColorAdd = entity->getEffectColorAdd();
						miniScript->setValue(returnValue, Vector4(effectColorAdd.getRed(), effectColorAdd.getGreen(), effectColorAdd.getBlue(), effectColorAdd.getAlpha()));
					} else {
						Console::println(getMethodName() + "(): " + miniScript->getStatementInformation(statement) + ": entity not found: " + (childEntityId.empty() == true?entityId:childEntityId + "@" + entityId));
					}
				} else {
					Console::println(getMethodName() + "(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation(getMethodName()));
					miniScript->startErrorScript();
				}
			}
			const vector<string>& getContextFunctions() {
				return CONTEXTFUNCTIONS_ENGINE;
			}
		};
		registerMethod(new MethodEntityGetEffectColorAdd(this));
	}
	{
		//
		class MethodEntitySetEffectColorAdd: public Method {
		private:
			LogicMiniScript* miniScript { nullptr };
		public:
			MethodEntitySetEffectColorAdd(LogicMiniScript* miniScript):
				Method(
					{
						{ .type = VariableType::TYPE_STRING, .name = "entityId", .optional = false, .reference = false, .nullable = false },
						{ .type = TYPE_VECTOR4, .name = "effectColorAdd", .optional = false, .reference = false, .nullable = false },
						{ .type = VariableType::TYPE_STRING, .name = "childEntityId", .optional = true, .reference = false, .nullable = false }
					},
					VariableType::TYPE_NULL
				),
				miniScript(miniScript) {}
			const string getMethodName() override {
				return "engine.entity.setEffectColorAdd";
			}
			void executeMethod(span<Variable>& argumentValues, Variable& returnValue, const Statement& statement) override {
				string entityId;
				Vector4 effectColorAdd;
				string childEntityId;
				if (miniScript->getStringValue(argumentValues, 0, entityId) == true &&
					miniScript->getVector4Value(argumentValues, 1, effectColorAdd) == true &&
					miniScript->getStringValue(argumentValues, 2, childEntityId, true) == true) {
					auto entity = miniScript->getEntity(entityId, childEntityId);
					if (entity != nullptr) {
						entity->setEffectColorAdd(Color4(effectColorAdd.getX(), effectColorAdd.getY(), effectColorAdd.getZ(), effectColorAdd.getW()));
					} else {
						Console::println(getMethodName() + "(): " + miniScript->getStatementInformation(statement) + ": entity not found: " + (childEntityId.empty() == true?entityId:childEntityId + "@" + entityId));
					}
				} else {
					Console::println(getMethodName() + "(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation(getMethodName()));
					miniScript->startErrorScript();
				}
			}
			const vector<string>& getContextFunctions() {
				return CONTEXTFUNCTIONS_ENGINE;
			}
		};
		registerMethod(new MethodEntitySetEffectColorAdd(this));
	}
	{
		//
		class MethodEntityGetAnimation: public Method {
		private:
			LogicMiniScript* miniScript { nullptr };
		public:
			MethodEntityGetAnimation(LogicMiniScript* miniScript):
				Method(
					{
						{ .type = VariableType::TYPE_STRING, .name = "entityId", .optional = false, .reference = false, .nullable = false },
						{ .type = VariableType::TYPE_STRING, .name = "childEntityId", .optional = true, .reference = false, .nullable = false }
					},
					VariableType::TYPE_STRING
				),
				miniScript(miniScript) {}
			const string getMethodName() override {
				return "engine.entity.getAnimation";
			}
			void executeMethod(span<Variable>& argumentValues, Variable& returnValue, const Statement& statement) override {
				string entityId;
				string childEntityId;
				if (miniScript->getStringValue(argumentValues, 0, entityId) == true &&
					miniScript->getStringValue(argumentValues, 1, childEntityId, true) == true) {
					auto object = dynamic_cast<Object*>(miniScript->getEntity(entityId, childEntityId));
					if (object != nullptr) {
						miniScript->setValue(returnValue, object->getAnimation());
					} else {
						Console::println(getMethodName() + "(): " + miniScript->getStatementInformation(statement) + ": object entity not found: " + (childEntityId.empty() == true?entityId:childEntityId + "@" + entityId));
					}
				} else {
					Console::println(getMethodName() + "(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation(getMethodName()));
					miniScript->startErrorScript();
				}
			}
			const vector<string>& getContextFunctions() {
				return CONTEXTFUNCTIONS_ENGINE;
			}
		};
		registerMethod(new MethodEntityGetAnimation(this));
	}
	{
		//
		class MethodEntitySetAnimation: public Method {
		private:
			LogicMiniScript* miniScript { nullptr };
		public:
			MethodEntitySetAnimation(LogicMiniScript* miniScript):
				Method(
					{
						{ .type = VariableType::TYPE_STRING, .name = "entityId", .optional = false, .reference = false, .nullable = false },
						{ .type = VariableType::TYPE_STRING, .name = "animation", .optional = false, .reference = false, .nullable = false },
						{ .type = VariableType::TYPE_FLOAT, .name = "speed", .optional = true, .reference = false, .nullable = false },
						{ .type = VariableType::TYPE_STRING, .name = "childEntityId", .optional = true, .reference = false, .nullable = false },
					},
					VariableType::TYPE_NULL
				),
				miniScript(miniScript) {}
			const string getMethodName() override {
				return "engine.entity.setAnimation";
			}
			void executeMethod(span<Variable>& argumentValues, Variable& returnValue, const Statement& statement) override {
				string entityId;
				string animation;
				float speed = 1.0f;
				string childEntityId;
				if (miniScript->getStringValue(argumentValues, 0, entityId) == true &&
					miniScript->getStringValue(argumentValues, 1, animation) == true &&
					miniScript->getFloatValue(argumentValues, 2, speed, true) == true &&
					miniScript->getStringValue(argumentValues, 3, childEntityId, true) == true) {
					auto object = dynamic_cast<Object*>(miniScript->getEntity(entityId, childEntityId));
					if (object != nullptr) {
						object->setAnimation(animation, speed);
					} else {
						Console::println(getMethodName() + "(): " + miniScript->getStatementInformation(statement) + ": object entity not found: " + (childEntityId.empty() == true?entityId:childEntityId + "@" + entityId));
					}
				} else {
					Console::println(getMethodName() + "(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation(getMethodName()));
					miniScript->startErrorScript();
				}
			}
			const vector<string>& getContextFunctions() {
				return CONTEXTFUNCTIONS_ENGINE;
			}
		};
		registerMethod(new MethodEntitySetAnimation(this));
	}
	{
		//
		class MethodEntitySetAnimationSpeed: public Method {
		private:
			LogicMiniScript* miniScript { nullptr };
		public:
			MethodEntitySetAnimationSpeed(LogicMiniScript* miniScript):
				Method(
					{
						{ .type = VariableType::TYPE_STRING, .name = "entityId", .optional = false, .reference = false, .nullable = false },
						{ .type = VariableType::TYPE_FLOAT, .name = "speed", .optional = false, .reference = false, .nullable = false },
						{ .type = VariableType::TYPE_STRING, .name = "childEntityId", .optional = true, .reference = false, .nullable = false },
					},
					VariableType::TYPE_NULL
				),
				miniScript(miniScript) {}
			const string getMethodName() override {
				return "engine.entity.setAnimationSpeed";
			}
			void executeMethod(span<Variable>& argumentValues, Variable& returnValue, const Statement& statement) override {
				string entityId;
				float speed;
				string childEntityId;
				if (miniScript->getStringValue(argumentValues, 0, entityId) == true &&
					miniScript->getFloatValue(argumentValues, 1, speed) == true &&
					miniScript->getStringValue(argumentValues, 2, childEntityId, true) == true) {
					auto object = dynamic_cast<Object*>(miniScript->getEntity(entityId, childEntityId));
					if (object != nullptr) {
						object->setAnimationSpeed(speed);
					} else {
						Console::println(getMethodName() + "(): " + miniScript->getStatementInformation(statement) + ": object entity not found: " + (childEntityId.empty() == true?entityId:childEntityId + "@" + entityId));
					}
				} else {
					Console::println(getMethodName() + "(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation(getMethodName()));
					miniScript->startErrorScript();
				}
			}
			const vector<string>& getContextFunctions() {
				return CONTEXTFUNCTIONS_ENGINE;
			}
		};
		registerMethod(new MethodEntitySetAnimationSpeed(this));
	}
	{
		//
		class MethodEntityGetAnimationTime: public Method {
		private:
			LogicMiniScript* miniScript { nullptr };
		public:
			MethodEntityGetAnimationTime(LogicMiniScript* miniScript):
				Method(
					{
						{ .type = VariableType::TYPE_STRING, .name = "entityId", .optional = false, .reference = false, .nullable = false },
						{ .type = VariableType::TYPE_STRING, .name = "childEntityId", .optional = true, .reference = false, .nullable = false },
					},
					VariableType::TYPE_FLOAT
				),
				miniScript(miniScript) {}
			const string getMethodName() override {
				return "engine.entity.getAnimationTime";
			}
			void executeMethod(span<Variable>& argumentValues, Variable& returnValue, const Statement& statement) override {
				string entityId;
				string childEntityId;
				if (miniScript->getStringValue(argumentValues, 0, entityId) == true &&
					miniScript->getStringValue(argumentValues, 1, childEntityId, true) == true) {
					auto object = dynamic_cast<Object*>(miniScript->getEntity(entityId, childEntityId));
					if (object != nullptr) {
						miniScript->setValue(returnValue, object->getAnimationTime());
					} else {
						Console::println(getMethodName() + "(): " + miniScript->getStatementInformation(statement) + ": object entity not found: " + (childEntityId.empty() == true?entityId:childEntityId + "@" + entityId));
					}
				} else {
					Console::println(getMethodName() + "(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation(getMethodName()));
					miniScript->startErrorScript();
				}
			}
			const vector<string>& getContextFunctions() {
				return CONTEXTFUNCTIONS_ENGINE;
			}
		};
		registerMethod(new MethodEntityGetAnimationTime(this));
	}
	{
		//
		class MethodEntityHasOverlayAnimation: public Method {
		private:
			LogicMiniScript* miniScript { nullptr };
		public:
			MethodEntityHasOverlayAnimation(LogicMiniScript* miniScript):
				Method(
					{
						{ .type = VariableType::TYPE_STRING, .name = "entityId", .optional = false, .reference = false, .nullable = false },
						{ .type = VariableType::TYPE_STRING, .name = "animation", .optional = false, .reference = false, .nullable = false },
						{ .type = VariableType::TYPE_STRING, .name = "childEntityId", .optional = true, .reference = false, .nullable = false },
					},
					VariableType::TYPE_BOOLEAN
				),
				miniScript(miniScript) {}
			const string getMethodName() override {
				return "engine.entity.hasOverlayAnimation";
			}
			void executeMethod(span<Variable>& argumentValues, Variable& returnValue, const Statement& statement) override {
				string entityId;
				string animation;
				string childEntityId;
				if (miniScript->getStringValue(argumentValues, 0, entityId) == true &&
					miniScript->getStringValue(argumentValues, 1, animation) == true &&
					miniScript->getStringValue(argumentValues, 2, childEntityId, true) == true) {
					auto object = dynamic_cast<Object*>(miniScript->getEntity(entityId, childEntityId));
					if (object != nullptr) {
						returnValue = object->hasOverlayAnimation(animation);
					} else {
						Console::println(getMethodName() + "(): " + miniScript->getStatementInformation(statement) + ": object entity not found: " + (childEntityId.empty() == true?entityId:childEntityId + "@" + entityId));
					}
				} else {
					Console::println(getMethodName() + "(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation(getMethodName()));
					miniScript->startErrorScript();
				}
			}
			const vector<string>& getContextFunctions() {
				return CONTEXTFUNCTIONS_ENGINE;
			}
		};
		registerMethod(new MethodEntityHasOverlayAnimation(this));
	}
	{
		//
		class MethodEntityAddOverlayAnimation: public Method {
		private:
			LogicMiniScript* miniScript { nullptr };
		public:
			MethodEntityAddOverlayAnimation(LogicMiniScript* miniScript):
				Method(
					{
						{ .type = VariableType::TYPE_STRING, .name = "entityId", .optional = false, .reference = false, .nullable = false },
						{ .type = VariableType::TYPE_STRING, .name = "animation", .optional = false, .reference = false, .nullable = false },
						{ .type = VariableType::TYPE_STRING, .name = "childEntityId", .optional = true, .reference = false, .nullable = false },
					},
					VariableType::TYPE_NULL
				),
				miniScript(miniScript) {}
			const string getMethodName() override {
				return "engine.entity.addOverlayAnimation";
			}
			void executeMethod(span<Variable>& argumentValues, Variable& returnValue, const Statement& statement) override {
				string entityId;
				string animation;
				string childEntityId;
				if (miniScript->getStringValue(argumentValues, 0, entityId) == true &&
					miniScript->getStringValue(argumentValues, 1, animation) == true &&
					miniScript->getStringValue(argumentValues, 2, childEntityId, true) == true) {
					auto object = dynamic_cast<Object*>(miniScript->getEntity(entityId, childEntityId));
					if (object != nullptr) {
						object->addOverlayAnimation(animation);
					} else {
						Console::println(getMethodName() + "(): " + miniScript->getStatementInformation(statement) + ": object entity not found: " + (childEntityId.empty() == true?entityId:childEntityId + "@" + entityId));
					}
				} else {
					Console::println(getMethodName() + "(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation(getMethodName()));
					miniScript->startErrorScript();
				}
			}
			const vector<string>& getContextFunctions() {
				return CONTEXTFUNCTIONS_ENGINE;
			}
		};
		registerMethod(new MethodEntityAddOverlayAnimation(this));
	}
	{
		//
		class MethodEntityRemoveOverlayAnimation: public Method {
		private:
			LogicMiniScript* miniScript { nullptr };
		public:
			MethodEntityRemoveOverlayAnimation(LogicMiniScript* miniScript):
				Method(
					{
						{ .type = VariableType::TYPE_STRING, .name = "entityId", .optional = false, .reference = false, .nullable = false },
						{ .type = VariableType::TYPE_STRING, .name = "animation", .optional = false, .reference = false, .nullable = false },
						{ .type = VariableType::TYPE_STRING, .name = "childEntityId", .optional = true, .reference = false, .nullable = false },
					},
					VariableType::TYPE_NULL
				),
				miniScript(miniScript) {}
			const string getMethodName() override {
				return "engine.entity.removeOverlayAnimation";
			}
			void executeMethod(span<Variable>& argumentValues, Variable& returnValue, const Statement& statement) override {
				string entityId;
				string animation;
				string childEntityId;
				if (miniScript->getStringValue(argumentValues, 0, entityId) == true &&
					miniScript->getStringValue(argumentValues, 1, animation) == true &&
					miniScript->getStringValue(argumentValues, 2, childEntityId, true) == true) {
					auto object = dynamic_cast<Object*>(miniScript->getEntity(entityId, childEntityId));
					if (object != nullptr) {
						object->removeOverlayAnimation(animation);
					} else {
						Console::println(getMethodName() + "(): " + miniScript->getStatementInformation(statement) + ": object entity not found: " + (childEntityId.empty() == true?entityId:childEntityId + "@" + entityId));
					}
				} else {
					Console::println(getMethodName() + "(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation(getMethodName()));
					miniScript->startErrorScript();
				}
			}
			const vector<string>& getContextFunctions() {
				return CONTEXTFUNCTIONS_ENGINE;
			}
		};
		registerMethod(new MethodEntityRemoveOverlayAnimation(this));
	}
	{
		//
		class MethodEntityRemoveFinishedOverlayAnimations: public Method {
		private:
			LogicMiniScript* miniScript { nullptr };
		public:
			MethodEntityRemoveFinishedOverlayAnimations(LogicMiniScript* miniScript):
				Method(
					{
						{ .type = VariableType::TYPE_STRING, .name = "entityId", .optional = false, .reference = false, .nullable = false },
						{ .type = VariableType::TYPE_STRING, .name = "childEntityId", .optional = true, .reference = false, .nullable = false },
					},
					VariableType::TYPE_NULL
				),
				miniScript(miniScript) {}
			const string getMethodName() override {
				return "engine.entity.removeFinishedOverlayAnimations";
			}
			void executeMethod(span<Variable>& argumentValues, Variable& returnValue, const Statement& statement) override {
				string entityId;
				string childEntityId;
				if (miniScript->getStringValue(argumentValues, 0, entityId) == true &&
					miniScript->getStringValue(argumentValues, 1, childEntityId, true) == true) {
					auto object = dynamic_cast<Object*>(miniScript->getEntity(entityId, childEntityId));
					if (object != nullptr) {
						object->removeFinishedOverlayAnimations();
					} else {
						Console::println(getMethodName() + "(): " + miniScript->getStatementInformation(statement) + ": object entity not found: " + (childEntityId.empty() == true?entityId:childEntityId + "@" + entityId));
					}
				} else {
					Console::println(getMethodName() + "(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation(getMethodName()));
					miniScript->startErrorScript();
				}
			}
			const vector<string>& getContextFunctions() {
				return CONTEXTFUNCTIONS_ENGINE;
			}
		};
		registerMethod(new MethodEntityRemoveFinishedOverlayAnimations(this));
	}
	{
		//
		class MethodEntityRemoveOverlayAnimations: public Method {
		private:
			LogicMiniScript* miniScript { nullptr };
		public:
			MethodEntityRemoveOverlayAnimations(LogicMiniScript* miniScript):
				Method(
					{
						{ .type = VariableType::TYPE_STRING, .name = "entityId", .optional = false, .reference = false, .nullable = false },
						{ .type = VariableType::TYPE_STRING, .name = "childEntityId", .optional = true, .reference = false, .nullable = false },
					},
					VariableType::TYPE_NULL
				),
				miniScript(miniScript) {}
			const string getMethodName() override {
				return "engine.entity.removeOverlayAnimations";
			}
			void executeMethod(span<Variable>& argumentValues, Variable& returnValue, const Statement& statement) override {
				string entityId;
				string childEntityId;
				if (miniScript->getStringValue(argumentValues, 0, entityId) == true &&
					miniScript->getStringValue(argumentValues, 1, childEntityId, true) == true) {
					auto object = dynamic_cast<Object*>(miniScript->getEntity(entityId, childEntityId));
					if (object != nullptr) {
						object->removeOverlayAnimations();
					} else {
						Console::println(getMethodName() + "(): " + miniScript->getStatementInformation(statement) + ": object entity not found: " + (childEntityId.empty() == true?entityId:childEntityId + "@" + entityId));
					}
				} else {
					Console::println(getMethodName() + "(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation(getMethodName()));
					miniScript->startErrorScript();
				}
			}
			const vector<string>& getContextFunctions() {
				return CONTEXTFUNCTIONS_ENGINE;
			}
		};
		registerMethod(new MethodEntityRemoveOverlayAnimations(this));
	}
	{
		//
		class MethodEntityGetOverlayAnimationTime: public Method {
		private:
			LogicMiniScript* miniScript { nullptr };
		public:
			MethodEntityGetOverlayAnimationTime(LogicMiniScript* miniScript):
				Method(
					{
						{ .type = VariableType::TYPE_STRING, .name = "entityId", .optional = false, .reference = false, .nullable = false },
						{ .type = VariableType::TYPE_STRING, .name = "animation", .optional = false, .reference = false, .nullable = false },
						{ .type = VariableType::TYPE_STRING, .name = "childEntityId", .optional = true, .reference = false, .nullable = false },
					},
					VariableType::TYPE_FLOAT
				),
				miniScript(miniScript) {}
			const string getMethodName() override {
				return "engine.entity.getOverlayAnimationTime";
			}
			void executeMethod(span<Variable>& argumentValues, Variable& returnValue, const Statement& statement) override {
				string entityId;
				string animation;
				string childEntityId;
				if (miniScript->getStringValue(argumentValues, 0, entityId) == true &&
					miniScript->getStringValue(argumentValues, 1, animation) == true &&
					miniScript->getStringValue(argumentValues, 2, childEntityId, true) == true) {
					auto object = dynamic_cast<Object*>(miniScript->getEntity(entityId, childEntityId));
					if (object != nullptr) {
						miniScript->setValue(returnValue, object->getOverlayAnimationTime(animation));
					} else {
						Console::println(getMethodName() + "(): " + miniScript->getStatementInformation(statement) + ": object entity not found: " + (childEntityId.empty() == true?entityId:childEntityId + "@" + entityId));
					}
				} else {
					Console::println(getMethodName() + "(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation(getMethodName()));
					miniScript->startErrorScript();
				}
			}
			const vector<string>& getContextFunctions() {
				return CONTEXTFUNCTIONS_ENGINE;
			}
		};
		registerMethod(new MethodEntityGetOverlayAnimationTime(this));
	}
	{
		//
		class MethodEntityGetNodeTransformMatrix: public Method {
		private:
			LogicMiniScript* miniScript { nullptr };
		public:
			MethodEntityGetNodeTransformMatrix(LogicMiniScript* miniScript):
				Method(
					{
						{ .type = VariableType::TYPE_STRING, .name = "entityId", .optional = false, .reference = false, .nullable = false },
						{ .type = VariableType::TYPE_STRING, .name = "nodeId", .optional = false, .reference = false, .nullable = false },
						{ .type = VariableType::TYPE_STRING, .name = "childEntityId", .optional = true, .reference = false, .nullable = false },
					},
					TYPE_MATRIX4x4
				),
				miniScript(miniScript) {}
			const string getMethodName() override {
				return "engine.entity.getNodeTransformMatrix";
			}
			void executeMethod(span<Variable>& argumentValues, Variable& returnValue, const Statement& statement) override {
				string entityId;
				string nodeId;
				string childEntityId;
				if (miniScript->getStringValue(argumentValues, 0, entityId) == true &&
					miniScript->getStringValue(argumentValues, 1, nodeId) == true &&
					miniScript->getStringValue(argumentValues, 2, childEntityId, true) == true) {
					auto object = dynamic_cast<Object*>(miniScript->getEntity(entityId, childEntityId));
					if (object != nullptr) {
						miniScript->setValue(returnValue, object->getNodeTransformMatrix(nodeId));
					} else {
						Console::println(getMethodName() + "(): " + miniScript->getStatementInformation(statement) + ": object entity not found: " + (childEntityId.empty() == true?entityId:childEntityId + "@" + entityId));
					}
				} else {
					Console::println(getMethodName() + "(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation(getMethodName()));
					miniScript->startErrorScript();
				}
			}
			const vector<string>& getContextFunctions() {
				return CONTEXTFUNCTIONS_ENGINE;
			}
		};
		registerMethod(new MethodEntityGetNodeTransformMatrix(this));
	}
	{
		//
		class MethodEntityGetNodeTransform: public Method {
		private:
			LogicMiniScript* miniScript { nullptr };
		public:
			MethodEntityGetNodeTransform(LogicMiniScript* miniScript):
				Method(
					{
						{ .type = VariableType::TYPE_STRING, .name = "entityId", .optional = false, .reference = false, .nullable = false },
						{ .type = VariableType::TYPE_STRING, .name = "nodeId", .optional = false, .reference = false, .nullable = false },
						{ .type = VariableType::TYPE_STRING, .name = "childEntityId", .optional = true, .reference = false, .nullable = false },
					},
					TYPE_TRANSFORM
				),
				miniScript(miniScript) {}
			const string getMethodName() override {
				return "engine.entity.getNodeTransform";
			}
			void executeMethod(span<Variable>& argumentValues, Variable& returnValue, const Statement& statement) override {
				string entityId;
				string nodeId;
				string childEntityId;
				if (miniScript->getStringValue(argumentValues, 0, entityId) == true &&
					miniScript->getStringValue(argumentValues, 1, nodeId) == true &&
					miniScript->getStringValue(argumentValues, 2, childEntityId, true) == true) {
					auto object = dynamic_cast<Object*>(miniScript->getEntity(entityId, childEntityId));
					if (object != nullptr) {
						Transform transform;
						transform.fromMatrix(object->getNodeTransformMatrix(nodeId), RotationOrder::ZYX);
						miniScript->setValue(returnValue, transform);
					} else {
						Console::println(getMethodName() + "(): " + miniScript->getStatementInformation(statement) + ": object entity not found: " + (childEntityId.empty() == true?entityId:childEntityId + "@" + entityId));
					}
				} else {
					Console::println(getMethodName() + "(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation(getMethodName()));
					miniScript->startErrorScript();
				}
			}
			const vector<string>& getContextFunctions() {
				return CONTEXTFUNCTIONS_ENGINE;
			}
		};
		registerMethod(new MethodEntityGetNodeTransform(this));
	}
	{
		//
		class MethodEntitySetNodeTransformMatrix: public Method {
		private:
			LogicMiniScript* miniScript { nullptr };
		public:
			MethodEntitySetNodeTransformMatrix(LogicMiniScript* miniScript):
				Method(
					{
						{ .type = VariableType::TYPE_STRING, .name = "entityId", .optional = false, .reference = false, .nullable = false },
						{ .type = VariableType::TYPE_STRING, .name = "nodeId", .optional = false, .reference = false, .nullable = false },
						{ .type = TYPE_MATRIX4x4, .name = "matrix", .optional = false, .reference = false, .nullable = false },
						{ .type = VariableType::TYPE_STRING, .name = "childEntityId", .optional = true, .reference = false, .nullable = false },
					},
					VariableType::TYPE_NULL
				),
				miniScript(miniScript) {}
			const string getMethodName() override {
				return "engine.entity.setNodeTransformMatrix";
			}
			void executeMethod(span<Variable>& argumentValues, Variable& returnValue, const Statement& statement) override {
				string entityId;
				string nodeId;
				Matrix4x4 matrix;
				string childEntityId;
				if (miniScript->getStringValue(argumentValues, 0, entityId) == true &&
					miniScript->getStringValue(argumentValues, 1, nodeId) == true &&
					miniScript->getMatrix4x4Value(argumentValues, 2, matrix) == true &&
					miniScript->getStringValue(argumentValues, 3, childEntityId, true) == true) {
					auto object = dynamic_cast<Object*>(miniScript->getEntity(entityId, childEntityId));
					if (object != nullptr) {
						object->setNodeTransformMatrix(nodeId, matrix);
					} else {
						Console::println(getMethodName() + "(): " + miniScript->getStatementInformation(statement) + ": object entity not found: " + (childEntityId.empty() == true?entityId:childEntityId + "@" + entityId));
					}
				} else {
					Console::println(getMethodName() + "(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation(getMethodName()));
					miniScript->startErrorScript();
				}
			}
			const vector<string>& getContextFunctions() {
				return CONTEXTFUNCTIONS_ENGINE;
			}
		};
		registerMethod(new MethodEntitySetNodeTransformMatrix(this));
	}
	{
		//
		class MethodEntitySetNodeTransform: public Method {
		private:
			LogicMiniScript* miniScript { nullptr };
		public:
			MethodEntitySetNodeTransform(LogicMiniScript* miniScript):
				Method(
					{
						{ .type = VariableType::TYPE_STRING, .name = "entityId", .optional = false, .reference = false, .nullable = false },
						{ .type = VariableType::TYPE_STRING, .name = "nodeId", .optional = false, .reference = false, .nullable = false },
						{ .type = TYPE_TRANSFORM, .name = "transform", .optional = false, .reference = false, .nullable = false },
						{ .type = VariableType::TYPE_STRING, .name = "childEntityId", .optional = true, .reference = false, .nullable = false },
					},
					VariableType::TYPE_NULL
				),
				miniScript(miniScript) {}
			const string getMethodName() override {
				return "engine.entity.setNodeTransform";
			}
			void executeMethod(span<Variable>& argumentValues, Variable& returnValue, const Statement& statement) override {
				string entityId;
				string nodeId;
				Transform transform;
				string childEntityId;
				if (miniScript->getStringValue(argumentValues, 0, entityId) == true &&
					miniScript->getStringValue(argumentValues, 1, nodeId) == true &&
					miniScript->getTransformValue(argumentValues, 2, transform) == true &&
					miniScript->getStringValue(argumentValues, 3, childEntityId, true) == true) {
					auto object = dynamic_cast<Object*>(miniScript->getEntity(entityId, childEntityId));
					if (object != nullptr) {
						object->setNodeTransformMatrix(nodeId, transform.getTransformMatrix());
					} else {
						Console::println(getMethodName() + "(): " + miniScript->getStatementInformation(statement) + ": object entity not found: " + (childEntityId.empty() == true?entityId:childEntityId + "@" + entityId));
					}
				} else {
					Console::println(getMethodName() + "(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation(getMethodName()));
					miniScript->startErrorScript();
				}
			}
			const vector<string>& getContextFunctions() {
				return CONTEXTFUNCTIONS_ENGINE;
			}
		};
		registerMethod(new MethodEntitySetNodeTransform(this));
	}
	{
		//
		class MethodEntityUnsetNodeTransformMatrix: public Method {
		private:
			LogicMiniScript* miniScript { nullptr };
		public:
			MethodEntityUnsetNodeTransformMatrix(LogicMiniScript* miniScript):
				Method(
					{
						{ .type = VariableType::TYPE_STRING, .name = "entityId", .optional = false, .reference = false, .nullable = false },
						{ .type = VariableType::TYPE_STRING, .name = "nodeId", .optional = false, .reference = false, .nullable = false },
						{ .type = VariableType::TYPE_STRING, .name = "childEntityId", .optional = true, .reference = false, .nullable = false },
					},
					VariableType::TYPE_NULL
				),
				miniScript(miniScript) {}
			const string getMethodName() override {
				return "engine.entity.unsetNodeTransformMatrix";
			}
			void executeMethod(span<Variable>& argumentValues, Variable& returnValue, const Statement& statement) override {
				string entityId;
				string nodeId;
				string childEntityId;
				if (miniScript->getStringValue(argumentValues, 0, entityId) == true &&
					miniScript->getStringValue(argumentValues, 1, nodeId) == true &&
					miniScript->getStringValue(argumentValues, 2, childEntityId, true) == true) {
					auto object = dynamic_cast<Object*>(miniScript->getEntity(entityId, childEntityId));
					if (object != nullptr) {
						object->unsetNodeTransformMatrix(nodeId);
					} else {
						Console::println(getMethodName() + "(): " + miniScript->getStatementInformation(statement) + ": object entity not found: " + (childEntityId.empty() == true?entityId:childEntityId + "@" + entityId));
					}
				} else {
					Console::println(getMethodName() + "(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation(getMethodName()));
					miniScript->startErrorScript();
				}
			}
			const vector<string>& getContextFunctions() {
				return CONTEXTFUNCTIONS_ENGINE;
			}
		};
		registerMethod(new MethodEntityUnsetNodeTransformMatrix(this));
	}
	{
		//
		class MethodEntityUnsetNodeTransform: public Method {
		private:
			LogicMiniScript* miniScript { nullptr };
		public:
			MethodEntityUnsetNodeTransform(LogicMiniScript* miniScript):
				Method(
					{
						{ .type = VariableType::TYPE_STRING, .name = "entityId", .optional = false, .reference = false, .nullable = false },
						{ .type = VariableType::TYPE_STRING, .name = "nodeId", .optional = false, .reference = false, .nullable = false },
						{ .type = VariableType::TYPE_STRING, .name = "childEntityId", .optional = true, .reference = false, .nullable = false },
					},
					VariableType::TYPE_NULL
				),
				miniScript(miniScript) {}
			const string getMethodName() override {
				return "engine.entity.unsetNodeTransform";
			}
			void executeMethod(span<Variable>& argumentValues, Variable& returnValue, const Statement& statement) override {
				string entityId;
				string nodeId;
				string childEntityId;
				if (miniScript->getStringValue(argumentValues, 0, entityId) == true &&
					miniScript->getStringValue(argumentValues, 1, nodeId) == true &&
					miniScript->getStringValue(argumentValues, 2, childEntityId, true) == true) {
					auto object = dynamic_cast<Object*>(miniScript->getEntity(entityId, childEntityId));
					if (object != nullptr) {
						object->unsetNodeTransformMatrix(nodeId);
					} else {
						Console::println(getMethodName() + "(): " + miniScript->getStatementInformation(statement) + ": object entity not found: " + (childEntityId.empty() == true?entityId:childEntityId + "@" + entityId));
					}
				} else {
					Console::println(getMethodName() + "(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation(getMethodName()));
					miniScript->startErrorScript();
				}
			}
			const vector<string>& getContextFunctions() {
				return CONTEXTFUNCTIONS_ENGINE;
			}
		};
		registerMethod(new MethodEntityUnsetNodeTransform(this));
	}
	{
		//
		class MethodEntityEmitParticles: public Method {
		private:
			LogicMiniScript* miniScript { nullptr };
		public:
			MethodEntityEmitParticles(LogicMiniScript* miniScript):
				Method(
					{
						{ .type = VariableType::TYPE_STRING, .name = "entityId", .optional = false, .reference = false, .nullable = false },
						{ .type = VariableType::TYPE_STRING, .name = "childEntityId", .optional = true, .reference = false, .nullable = false },
					},
					VariableType::TYPE_INTEGER
				),
				miniScript(miniScript) {}
			const string getMethodName() override {
				return "engine.entity.emitParticles";
			}
			void executeMethod(span<Variable>& argumentValues, Variable& returnValue, const Statement& statement) override {
				string entityId;
				string childEntityId;
				if (miniScript->getStringValue(argumentValues, 0, entityId) == true &&
					miniScript->getStringValue(argumentValues, 1, childEntityId, true) == true) {
					auto entity = dynamic_cast<ParticleSystem*>(miniScript->getEntity(entityId, childEntityId));
					if (entity != nullptr) {
						returnValue = static_cast<int64_t>(entity->emitParticles());
					} else {
						Console::println(getMethodName() + "(): " + miniScript->getStatementInformation(statement) + ": particle system entity not found: " + (childEntityId.empty() == true?entityId:childEntityId + "@" + entityId));
					}
				} else {
					Console::println(getMethodName() + "(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation(getMethodName()));
					miniScript->startErrorScript();
				}
			}
			const vector<string>& getContextFunctions() {
				return CONTEXTFUNCTIONS_ENGINE;
			}
		};
		registerMethod(new MethodEntityEmitParticles(this));
	}
	// physics
	{
		//
		class MethodBodyTYPE_STATIC: public Method {
		private:
			LogicMiniScript* miniScript { nullptr };
		public:
			MethodBodyTYPE_STATIC(LogicMiniScript* miniScript):
				Method({}, VariableType::TYPE_INTEGER),
				miniScript(miniScript) {}
			const string getMethodName() override {
				return "world.body.TYPE_STATIC";
			}
			void executeMethod(span<Variable>& argumentValues, Variable& returnValue, const Statement& statement) override {
				returnValue = static_cast<int64_t>(Body::BODYTYPE_STATIC);
			}
			const vector<string>& getContextFunctions() {
				return CONTEXTFUNCTIONS_LOGIC;
			}
		};
		registerMethod(new MethodBodyTYPE_STATIC(this));
	}
	{
		//
		class MethodBodyTYPE_DYNAMIC: public Method {
		private:
			LogicMiniScript* miniScript { nullptr };
		public:
			MethodBodyTYPE_DYNAMIC(LogicMiniScript* miniScript):
				Method({}, VariableType::TYPE_INTEGER),
				miniScript(miniScript) {}
			const string getMethodName() override {
				return "world.body.TYPE_DYNAMIC";
			}
			void executeMethod(span<Variable>& argumentValues, Variable& returnValue, const Statement& statement) override {
				returnValue = static_cast<int64_t>(Body::BODYTYPE_DYNAMIC);
			}
			const vector<string>& getContextFunctions() {
				return CONTEXTFUNCTIONS_LOGIC;
			}
		};
		registerMethod(new MethodBodyTYPE_DYNAMIC(this));
	}
	{
		//
		class MethodBodyTYPE_COLLISIONSTATIC: public Method {
		private:
			LogicMiniScript* miniScript { nullptr };
		public:
			MethodBodyTYPE_COLLISIONSTATIC(LogicMiniScript* miniScript):
				Method({}, VariableType::TYPE_INTEGER),
				miniScript(miniScript) {}
			const string getMethodName() override {
				return "world.body.TYPE_COLLISION_STATIC";
			}
			void executeMethod(span<Variable>& argumentValues, Variable& returnValue, const Statement& statement) override {
				returnValue = static_cast<int64_t>(Body::BODYTYPE_COLLISION_STATIC);
			}
			const vector<string>& getContextFunctions() {
				return CONTEXTFUNCTIONS_LOGIC;
			}
		};
		registerMethod(new MethodBodyTYPE_COLLISIONSTATIC(this));
	}
	{
		//
		class MethodBodyTYPE_COLLISIONDYNAMIC: public Method {
		private:
			LogicMiniScript* miniScript { nullptr };
		public:
			MethodBodyTYPE_COLLISIONDYNAMIC(LogicMiniScript* miniScript):
				Method({}, VariableType::TYPE_INTEGER),
				miniScript(miniScript) {}
			const string getMethodName() override {
				return "world.body.TYPE_COLLISION_DYNAMIC";
			}
			void executeMethod(span<Variable>& argumentValues, Variable& returnValue, const Statement& statement) override {
				returnValue = static_cast<int64_t>(Body::BODYTYPE_COLLISION_DYNAMIC);
			}
			const vector<string>& getContextFunctions() {
				return CONTEXTFUNCTIONS_LOGIC;
			}
		};
		registerMethod(new MethodBodyTYPE_COLLISIONDYNAMIC(this));
	}
	{
		//
		class MethodBodyCOLLISION_TYPEID_STATIC: public Method {
		private:
			LogicMiniScript* miniScript { nullptr };
		public:
			MethodBodyCOLLISION_TYPEID_STATIC(LogicMiniScript* miniScript):
				Method({}, VariableType::TYPE_INTEGER),
				miniScript(miniScript) {}
			const string getMethodName() override {
				return "world.body.COLLISION_TYPEID_STATIC";
			}
			void executeMethod(span<Variable>& argumentValues, Variable& returnValue, const Statement& statement) override {
				returnValue = static_cast<int64_t>(Body::COLLISION_TYPEID_STATIC);
			}
			const vector<string>& getContextFunctions() {
				return CONTEXTFUNCTIONS_LOGIC;
			}
		};
		registerMethod(new MethodBodyCOLLISION_TYPEID_STATIC(this));
	}
	{
		//
		class MethodBodyCOLLISION_TYPEID_DYNAMIC: public Method {
		private:
			LogicMiniScript* miniScript { nullptr };
		public:
			MethodBodyCOLLISION_TYPEID_DYNAMIC(LogicMiniScript* miniScript):
				Method({}, VariableType::TYPE_INTEGER),
				miniScript(miniScript) {}
			const string getMethodName() override {
				return "world.body.COLLISION_TYPEID_DYNAMIC";
			}
			void executeMethod(span<Variable>& argumentValues, Variable& returnValue, const Statement& statement) override {
				returnValue = static_cast<int64_t>(Body::COLLISION_TYPEID_DYNAMIC);
			}
			const vector<string>& getContextFunctions() {
				return CONTEXTFUNCTIONS_LOGIC;
			}
		};
		registerMethod(new MethodBodyCOLLISION_TYPEID_DYNAMIC(this));
	}
	{
		//
		class MethodBodyCOLLISION_TYPEID_3: public Method {
		private:
			LogicMiniScript* miniScript { nullptr };
		public:
			MethodBodyCOLLISION_TYPEID_3(LogicMiniScript* miniScript):
				Method({}, VariableType::TYPE_INTEGER),
				miniScript(miniScript) {}
			const string getMethodName() override {
				return "world.body.COLLISION_TYPEID_3";
			}
			void executeMethod(span<Variable>& argumentValues, Variable& returnValue, const Statement& statement) override {
				returnValue = static_cast<int64_t>(Body::COLLISION_TYPEID_3);
			}
			const vector<string>& getContextFunctions() {
				return CONTEXTFUNCTIONS_LOGIC;
			}
		};
		registerMethod(new MethodBodyCOLLISION_TYPEID_3(this));
	}
	{
		//
		class MethodBodyCOLLISION_TYPEID_4: public Method {
		private:
			LogicMiniScript* miniScript { nullptr };
		public:
			MethodBodyCOLLISION_TYPEID_4(LogicMiniScript* miniScript):
				Method({}, VariableType::TYPE_INTEGER),
				miniScript(miniScript) {}
			const string getMethodName() override {
				return "world.body.COLLISION_TYPEID_4";
			}
			void executeMethod(span<Variable>& argumentValues, Variable& returnValue, const Statement& statement) override {
				returnValue = static_cast<int64_t>(Body::COLLISION_TYPEID_4);
			}
			const vector<string>& getContextFunctions() {
				return CONTEXTFUNCTIONS_LOGIC;
			}
		};
		registerMethod(new MethodBodyCOLLISION_TYPEID_4(this));
	}
	{
		//
		class MethodBodyCOLLISION_TYPEID_5: public Method {
		private:
			LogicMiniScript* miniScript { nullptr };
		public:
			MethodBodyCOLLISION_TYPEID_5(LogicMiniScript* miniScript):
				Method({}, VariableType::TYPE_INTEGER),
				miniScript(miniScript) {}
			const string getMethodName() override {
				return "world.body.COLLISION_TYPEID_5";
			}
			void executeMethod(span<Variable>& argumentValues, Variable& returnValue, const Statement& statement) override {
				returnValue = static_cast<int64_t>(Body::COLLISION_TYPEID_5);
			}
			const vector<string>& getContextFunctions() {
				return CONTEXTFUNCTIONS_LOGIC;
			}
		};
		registerMethod(new MethodBodyCOLLISION_TYPEID_5(this));
	}
	{
		//
		class MethodBodyCOLLISION_TYPEID_6: public Method {
		private:
			LogicMiniScript* miniScript { nullptr };
		public:
			MethodBodyCOLLISION_TYPEID_6(LogicMiniScript* miniScript):
				Method({}, VariableType::TYPE_INTEGER),
				miniScript(miniScript) {}
			const string getMethodName() override {
				return "world.body.COLLISION_TYPEID_6";
			}
			void executeMethod(span<Variable>& argumentValues, Variable& returnValue, const Statement& statement) override {
				returnValue = static_cast<int64_t>(Body::COLLISION_TYPEID_6);
			}
			const vector<string>& getContextFunctions() {
				return CONTEXTFUNCTIONS_LOGIC;
			}
		};
		registerMethod(new MethodBodyCOLLISION_TYPEID_6(this));
	}
	{
		//
		class MethodBodyCOLLISION_TYPEID_7: public Method {
		private:
			LogicMiniScript* miniScript { nullptr };
		public:
			MethodBodyCOLLISION_TYPEID_7(LogicMiniScript* miniScript):
				Method({}, VariableType::TYPE_INTEGER),
				miniScript(miniScript) {}
			const string getMethodName() override {
				return "world.body.COLLISION_TYPEID_7";
			}
			void executeMethod(span<Variable>& argumentValues, Variable& returnValue, const Statement& statement) override {
				returnValue = static_cast<int64_t>(Body::COLLISION_TYPEID_7);
			}
			const vector<string>& getContextFunctions() {
				return CONTEXTFUNCTIONS_LOGIC;
			}
		};
		registerMethod(new MethodBodyCOLLISION_TYPEID_7(this));
	}
	{
		//
		class MethodBodyCOLLISION_TYPEID_8: public Method {
		private:
			LogicMiniScript* miniScript { nullptr };
		public:
			MethodBodyCOLLISION_TYPEID_8(LogicMiniScript* miniScript):
				Method({}, VariableType::TYPE_INTEGER),
				miniScript(miniScript) {}
			const string getMethodName() override {
				return "world.body.COLLISION_TYPEID_8";
			}
			void executeMethod(span<Variable>& argumentValues, Variable& returnValue, const Statement& statement) override {
				returnValue = static_cast<int64_t>(Body::COLLISION_TYPEID_8);
			}
			const vector<string>& getContextFunctions() {
				return CONTEXTFUNCTIONS_LOGIC;
			}
		};
		registerMethod(new MethodBodyCOLLISION_TYPEID_8(this));
	}
	{
		//
		class MethodBodyCOLLISION_TYPEID_9: public Method {
		private:
			LogicMiniScript* miniScript { nullptr };
		public:
			MethodBodyCOLLISION_TYPEID_9(LogicMiniScript* miniScript):
				Method({}, VariableType::TYPE_INTEGER),
				miniScript(miniScript) {}
			const string getMethodName() override {
				return "world.body.COLLISION_TYPEID_9";
			}
			void executeMethod(span<Variable>& argumentValues, Variable& returnValue, const Statement& statement) override {
				returnValue = static_cast<int64_t>(Body::COLLISION_TYPEID_9);
			}
			const vector<string>& getContextFunctions() {
				return CONTEXTFUNCTIONS_LOGIC;
			}
		};
		registerMethod(new MethodBodyCOLLISION_TYPEID_9(this));
	}
	{
		//
		class MethodBodyCOLLISION_TYPEID_10: public Method {
		private:
			LogicMiniScript* miniScript { nullptr };
		public:
			MethodBodyCOLLISION_TYPEID_10(LogicMiniScript* miniScript):
				Method({}, VariableType::TYPE_INTEGER),
				miniScript(miniScript) {}
			const string getMethodName() override {
				return "world.body.COLLISION_TYPEID_10";
			}
			void executeMethod(span<Variable>& argumentValues, Variable& returnValue, const Statement& statement) override {
				returnValue = static_cast<int64_t>(Body::COLLISION_TYPEID_10);
			}
			const vector<string>& getContextFunctions() {
				return CONTEXTFUNCTIONS_LOGIC;
			}
		};
		registerMethod(new MethodBodyCOLLISION_TYPEID_10(this));
	}
	{
		//
		class MethodBodyCOLLISION_TYPEID_11: public Method {
		private:
			LogicMiniScript* miniScript { nullptr };
		public:
			MethodBodyCOLLISION_TYPEID_11(LogicMiniScript* miniScript):
				Method({}, VariableType::TYPE_INTEGER),
				miniScript(miniScript) {}
			const string getMethodName() override {
				return "world.body.COLLISION_TYPEID_11";
			}
			void executeMethod(span<Variable>& argumentValues, Variable& returnValue, const Statement& statement) override {
				returnValue = static_cast<int64_t>(Body::COLLISION_TYPEID_11);
			}
			const vector<string>& getContextFunctions() {
				return CONTEXTFUNCTIONS_LOGIC;
			}
		};
		registerMethod(new MethodBodyCOLLISION_TYPEID_11(this));
	}
	{
		//
		class MethodBodyCOLLISION_TYPEID_12: public Method {
		private:
			LogicMiniScript* miniScript { nullptr };
		public:
			MethodBodyCOLLISION_TYPEID_12(LogicMiniScript* miniScript):
				Method({}, VariableType::TYPE_INTEGER),
				miniScript(miniScript) {}
			const string getMethodName() override {
				return "world.body.COLLISION_TYPEID_12";
			}
			void executeMethod(span<Variable>& argumentValues, Variable& returnValue, const Statement& statement) override {
				returnValue = static_cast<int64_t>(Body::COLLISION_TYPEID_12);
			}
			const vector<string>& getContextFunctions() {
				return CONTEXTFUNCTIONS_LOGIC;
			}
		};
		registerMethod(new MethodBodyCOLLISION_TYPEID_12(this));
	}
	{
		//
		class MethodBodyCOLLISION_TYPEID_13: public Method {
		private:
			LogicMiniScript* miniScript { nullptr };
		public:
			MethodBodyCOLLISION_TYPEID_13(LogicMiniScript* miniScript):
				Method({}, VariableType::TYPE_INTEGER),
				miniScript(miniScript) {}
			const string getMethodName() override {
				return "world.body.COLLISION_TYPEID_13";
			}
			void executeMethod(span<Variable>& argumentValues, Variable& returnValue, const Statement& statement) override {
				returnValue = static_cast<int64_t>(Body::COLLISION_TYPEID_13);
			}
			const vector<string>& getContextFunctions() {
				return CONTEXTFUNCTIONS_LOGIC;
			}
		};
		registerMethod(new MethodBodyCOLLISION_TYPEID_13(this));
	}
	{
		//
		class MethodBodyCOLLISION_TYPEID_14: public Method {
		private:
			LogicMiniScript* miniScript { nullptr };
		public:
			MethodBodyCOLLISION_TYPEID_14(LogicMiniScript* miniScript):
				Method({}, VariableType::TYPE_INTEGER),
				miniScript(miniScript) {}
			const string getMethodName() override {
				return "world.body.COLLISION_TYPEID_14";
			}
			void executeMethod(span<Variable>& argumentValues, Variable& returnValue, const Statement& statement) override {
				returnValue = static_cast<int64_t>(Body::COLLISION_TYPEID_14);
			}
			const vector<string>& getContextFunctions() {
				return CONTEXTFUNCTIONS_LOGIC;
			}
		};
		registerMethod(new MethodBodyCOLLISION_TYPEID_14(this));
	}
	{
		//
		class MethodBodyCOLLISION_TYPEID_15: public Method {
		private:
			LogicMiniScript* miniScript { nullptr };
		public:
			MethodBodyCOLLISION_TYPEID_15(LogicMiniScript* miniScript):
				Method({}, VariableType::TYPE_INTEGER),
				miniScript(miniScript) {}
			const string getMethodName() override {
				return "world.body.COLLISION_TYPEID_15";
			}
			void executeMethod(span<Variable>& argumentValues, Variable& returnValue, const Statement& statement) override {
				returnValue = static_cast<int64_t>(Body::COLLISION_TYPEID_15);
			}
			const vector<string>& getContextFunctions() {
				return CONTEXTFUNCTIONS_LOGIC;
			}
		};
		registerMethod(new MethodBodyCOLLISION_TYPEID_15(this));
	}
	{
		//
		class MethodBodyCOLLISION_TYPEID_16: public Method {
		private:
			LogicMiniScript* miniScript { nullptr };
		public:
			MethodBodyCOLLISION_TYPEID_16(LogicMiniScript* miniScript):
				Method({}, VariableType::TYPE_INTEGER),
				miniScript(miniScript) {}
			const string getMethodName() override {
				return "world.body.COLLISION_TYPEID_16";
			}
			void executeMethod(span<Variable>& argumentValues, Variable& returnValue, const Statement& statement) override {
				returnValue = static_cast<int64_t>(Body::COLLISION_TYPEID_16);
			}
			const vector<string>& getContextFunctions() {
				return CONTEXTFUNCTIONS_LOGIC;
			}
		};
		registerMethod(new MethodBodyCOLLISION_TYPEID_16(this));
	}
	{
		//
		class MethodBodyCOLLISION_TYPEID_ALL: public Method {
		private:
			LogicMiniScript* miniScript { nullptr };
		public:
			MethodBodyCOLLISION_TYPEID_ALL(LogicMiniScript* miniScript):
				Method({}, VariableType::TYPE_INTEGER),
				miniScript(miniScript) {}
			const string getMethodName() override {
				return "world.body.COLLISION_TYPEID_ALL";
			}
			void executeMethod(span<Variable>& argumentValues, Variable& returnValue, const Statement& statement) override {
				returnValue = static_cast<int64_t>(Body::COLLISION_TYPEID_ALL);
			}
			const vector<string>& getContextFunctions() {
				return CONTEXTFUNCTIONS_LOGIC;
			}
		};
		registerMethod(new MethodBodyCOLLISION_TYPEID_ALL(this));
	}
	{
		//
		class MethodBodyIsEnabled: public Method {
		private:
			LogicMiniScript* miniScript { nullptr };
		public:
			MethodBodyIsEnabled(LogicMiniScript* miniScript):
				Method(
					{
						{ .type = VariableType::TYPE_STRING, .name = "bodyId", .optional = false, .reference = false, .nullable = false }
					},
					VariableType::TYPE_BOOLEAN
				),
				miniScript(miniScript) {}
			const string getMethodName() override {
				return "world.body.isEnabled";
			}
			void executeMethod(span<Variable>& argumentValues, Variable& returnValue, const Statement& statement) override {
				string bodyId;
				if (miniScript->getStringValue(argumentValues, 0, bodyId) == true) {
					auto body = miniScript->context->getWorld()->getBody(bodyId);
					if (body != nullptr) {
						returnValue = body->isEnabled();
					} else {
						Console::println(getMethodName() + "(): " + miniScript->getStatementInformation(statement) + ": body not found: " + bodyId);
					}
				} else {
					Console::println(getMethodName() + "(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation(getMethodName()));
					miniScript->startErrorScript();
				}
			}
			const vector<string>& getContextFunctions() {
				return CONTEXTFUNCTIONS_LOGIC;
			}
		};
		registerMethod(new MethodBodyIsEnabled(this));
	}
	{
		//
		class MethodBodySetEnabled: public Method {
		private:
			LogicMiniScript* miniScript { nullptr };
		public:
			MethodBodySetEnabled(LogicMiniScript* miniScript):
				Method(
					{
						{ .type = VariableType::TYPE_STRING, .name = "bodyId", .optional = false, .reference = false, .nullable = false },
						{ .type = VariableType::TYPE_BOOLEAN, .name = "enabled", .optional = false, .reference = false, .nullable = false }
					},
					VariableType::TYPE_NULL
				),
				miniScript(miniScript) {}
			const string getMethodName() override {
				return "world.body.setEnabled";
			}
			void executeMethod(span<Variable>& argumentValues, Variable& returnValue, const Statement& statement) override {
				string bodyId;
				bool enabled;
				if (miniScript->getStringValue(argumentValues, 0, bodyId) == true &&
					miniScript->getBooleanValue(argumentValues, 1, enabled) == true) {
					auto body = miniScript->context->getWorld()->getBody(bodyId);
					if (body != nullptr) {
						body->setEnabled(enabled);
					} else {
						Console::println(getMethodName() + "(): " + miniScript->getStatementInformation(statement) + ": body not found: " + bodyId);
					}
				} else {
					Console::println(getMethodName() + "(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation(getMethodName()));
					miniScript->startErrorScript();
				}
			}
			const vector<string>& getContextFunctions() {
				return CONTEXTFUNCTIONS_LOGIC;
			}
		};
		registerMethod(new MethodBodySetEnabled(this));
	}
	{
		//
		class MethodBodyGetType: public Method {
		private:
			LogicMiniScript* miniScript { nullptr };
		public:
			MethodBodyGetType(LogicMiniScript* miniScript):
				Method(
					{
						{ .type = VariableType::TYPE_STRING, .name = "bodyId", .optional = false, .reference = false, .nullable = false }
					},
					VariableType::TYPE_INTEGER
				),
				miniScript(miniScript) {}
			const string getMethodName() override {
				return "world.body.getType";
			}
			void executeMethod(span<Variable>& argumentValues, Variable& returnValue, const Statement& statement) override {
				string bodyId;
				if (miniScript->getStringValue(argumentValues, 0, bodyId) == true) {
					auto body = miniScript->context->getWorld()->getBody(bodyId);
					if (body != nullptr) {
						returnValue = static_cast<int64_t>(body->getType());
					} else {
						Console::println(getMethodName() + "(): " + miniScript->getStatementInformation(statement) + ": body not found: " + bodyId);
					}
				} else {
					Console::println(getMethodName() + "(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation(getMethodName()));
					miniScript->startErrorScript();
				}
			}
			const vector<string>& getContextFunctions() {
				return CONTEXTFUNCTIONS_LOGIC;
			}
		};
		registerMethod(new MethodBodyGetType(this));
	}
	{
		//
		class MethodBodyGetCollisionTypeId: public Method {
		private:
			LogicMiniScript* miniScript { nullptr };
		public:
			MethodBodyGetCollisionTypeId(LogicMiniScript* miniScript):
				Method(
					{
						{ .type = VariableType::TYPE_STRING, .name = "bodyId", .optional = false, .reference = false, .nullable = false }
					},
					VariableType::TYPE_INTEGER
				),
				miniScript(miniScript) {}
			const string getMethodName() override {
				return "world.body.getCollisionTypeId";
			}
			void executeMethod(span<Variable>& argumentValues, Variable& returnValue, const Statement& statement) override {
				string bodyId;
				if (miniScript->getStringValue(argumentValues, 0, bodyId) == true) {
					auto body = miniScript->context->getWorld()->getBody(bodyId);
					if (body != nullptr) {
						returnValue = static_cast<int64_t>(body->getCollisionTypeId());
					} else {
						Console::println(getMethodName() + "(): " + miniScript->getStatementInformation(statement) + ": body not found: " + bodyId);
					}
				} else {
					Console::println(getMethodName() + "(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation(getMethodName()));
					miniScript->startErrorScript();
				}
			}
			const vector<string>& getContextFunctions() {
				return CONTEXTFUNCTIONS_LOGIC;
			}
		};
		registerMethod(new MethodBodyGetCollisionTypeId(this));
	}
	{
		//
		class MethodBodySetCollisionTypeId: public Method {
		private:
			LogicMiniScript* miniScript { nullptr };
		public:
			MethodBodySetCollisionTypeId(LogicMiniScript* miniScript):
				Method(
					{
						{ .type = VariableType::TYPE_STRING, .name = "bodyId", .optional = false, .reference = false, .nullable = false },
						{ .type = VariableType::TYPE_INTEGER, .name = "collisionTypeId", .optional = false, .reference = false, .nullable = false }
					},
					VariableType::TYPE_NULL
				),
				miniScript(miniScript) {}
			const string getMethodName() override {
				return "world.body.setCollisionTypeId";
			}
			void executeMethod(span<Variable>& argumentValues, Variable& returnValue, const Statement& statement) override {
				string bodyId;
				int64_t collisionTypeId;
				if (miniScript->getStringValue(argumentValues, 0, bodyId) == true &&
					miniScript->getIntegerValue(argumentValues, 1, collisionTypeId) == true) {
					auto body = miniScript->context->getWorld()->getBody(bodyId);
					if (body != nullptr) {
						body->setCollisionTypeId(collisionTypeId);
					} else {
						Console::println(getMethodName() + "(): " + miniScript->getStatementInformation(statement) + ": body not found: " + bodyId);
					}
				} else {
					Console::println(getMethodName() + "(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation(getMethodName()));
					miniScript->startErrorScript();
				}
			}
			const vector<string>& getContextFunctions() {
				return CONTEXTFUNCTIONS_LOGIC;
			}
		};
		registerMethod(new MethodBodySetCollisionTypeId(this));
	}
	{
		//
		class MethodBodyGetCollisionTypeIds: public Method {
		private:
			LogicMiniScript* miniScript { nullptr };
		public:
			MethodBodyGetCollisionTypeIds(LogicMiniScript* miniScript):
				Method(
					{
						{ .type = VariableType::TYPE_STRING, .name = "bodyId", .optional = false, .reference = false, .nullable = false }
					},
					VariableType::TYPE_INTEGER
				),
				miniScript(miniScript) {}
			const string getMethodName() override {
				return "world.body.getCollisionTypeIds";
			}
			void executeMethod(span<Variable>& argumentValues, Variable& returnValue, const Statement& statement) override {
				string bodyId;
				if (miniScript->getStringValue(argumentValues, 0, bodyId) == true) {
					auto body = miniScript->context->getWorld()->getBody(bodyId);
					if (body != nullptr) {
						returnValue = static_cast<int64_t>(body->getCollisionTypeIds());
					} else {
						Console::println(getMethodName() + "(): " + miniScript->getStatementInformation(statement) + ": body not found: " + bodyId);
					}
				} else {
					Console::println(getMethodName() + "(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation(getMethodName()));
					miniScript->startErrorScript();
				}
			}
			const vector<string>& getContextFunctions() {
				return CONTEXTFUNCTIONS_LOGIC;
			}
		};
		registerMethod(new MethodBodyGetCollisionTypeIds(this));
	}
	{
		//
		class MethodBodySetCollisionTypeIds: public Method {
		private:
			LogicMiniScript* miniScript { nullptr };
		public:
			MethodBodySetCollisionTypeIds(LogicMiniScript* miniScript):
				Method(
					{
						{ .type = VariableType::TYPE_STRING, .name = "bodyId", .optional = false, .reference = false, .nullable = false },
						{ .type = VariableType::TYPE_INTEGER, .name = "collisionTypeIds", .optional = false, .reference = false, .nullable = false }
					},
					VariableType::TYPE_NULL
				),
				miniScript(miniScript) {}
			const string getMethodName() override {
				return "world.body.setCollisionTypeIds";
			}
			void executeMethod(span<Variable>& argumentValues, Variable& returnValue, const Statement& statement) override {
				string bodyId;
				int64_t collisionTypeIds;
				if (miniScript->getStringValue(argumentValues, 0, bodyId) == true &&
					miniScript->getIntegerValue(argumentValues, 1, collisionTypeIds) == true) {
					auto body = miniScript->context->getWorld()->getBody(bodyId);
					if (body != nullptr) {
						body->setCollisionTypeIds(collisionTypeIds);
					} else {
						Console::println(getMethodName() + "(): " + miniScript->getStatementInformation(statement) + ": body not found: " + bodyId);
					}
				} else {
					Console::println(getMethodName() + "(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation(getMethodName()));
					miniScript->startErrorScript();
				}
			}
			const vector<string>& getContextFunctions() {
				return CONTEXTFUNCTIONS_LOGIC;
			}
		};
		registerMethod(new MethodBodySetCollisionTypeIds(this));
	}
	{
		//
		class MethodBodyGetLinearDamping: public Method {
		private:
			LogicMiniScript* miniScript { nullptr };
		public:
			MethodBodyGetLinearDamping(LogicMiniScript* miniScript):
				Method(
					{
						{ .type = VariableType::TYPE_STRING, .name = "bodyId", .optional = false, .reference = false, .nullable = false }
					},
					VariableType::TYPE_FLOAT
				),
				miniScript(miniScript) {}
			const string getMethodName() override {
				return "world.body.getLinearDamping";
			}
			void executeMethod(span<Variable>& argumentValues, Variable& returnValue, const Statement& statement) override {
				string bodyId;
				if (miniScript->getStringValue(argumentValues, 0, bodyId) == true) {
					auto body = miniScript->context->getWorld()->getBody(bodyId);
					if (body != nullptr) {
						returnValue = body->getLinearDamping();
					} else {
						Console::println(getMethodName() + "(): " + miniScript->getStatementInformation(statement) + ": body not found: " + bodyId);
					}
				} else {
					Console::println(getMethodName() + "(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation(getMethodName()));
					miniScript->startErrorScript();
				}
			}
			const vector<string>& getContextFunctions() {
				return CONTEXTFUNCTIONS_LOGIC;
			}
		};
		registerMethod(new MethodBodyGetLinearDamping(this));
	}
	{
		//
		class MethodBodySetLinearDamping: public Method {
		private:
			LogicMiniScript* miniScript { nullptr };
		public:
			MethodBodySetLinearDamping(LogicMiniScript* miniScript):
				Method(
					{
						{ .type = VariableType::TYPE_STRING, .name = "bodyId", .optional = false, .reference = false, .nullable = false },
						{ .type = VariableType::TYPE_FLOAT, .name = "linearDamping", .optional = false, .reference = false, .nullable = false }
					},
					VariableType::TYPE_NULL
				),
				miniScript(miniScript) {}
			const string getMethodName() override {
				return "world.body.setLinearDamping";
			}
			void executeMethod(span<Variable>& argumentValues, Variable& returnValue, const Statement& statement) override {
				string bodyId;
				float linearDamping;
				if (miniScript->getStringValue(argumentValues, 0, bodyId) == true &&
					miniScript->getFloatValue(argumentValues, 1, linearDamping) == true) {
					auto body = miniScript->context->getWorld()->getBody(bodyId);
					if (body != nullptr) {
						body->setLinearDamping(linearDamping);
					} else {
						Console::println(getMethodName() + "(): " + miniScript->getStatementInformation(statement) + ": body not found: " + bodyId);
					}
				} else {
					Console::println(getMethodName() + "(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation(getMethodName()));
					miniScript->startErrorScript();
				}
			}
			const vector<string>& getContextFunctions() {
				return CONTEXTFUNCTIONS_LOGIC;
			}
		};
		registerMethod(new MethodBodySetLinearDamping(this));
	}
	{
		//
		class MethodBodyGetAngularDamping: public Method {
		private:
			LogicMiniScript* miniScript { nullptr };
		public:
			MethodBodyGetAngularDamping(LogicMiniScript* miniScript):
				Method(
					{
						{ .type = VariableType::TYPE_STRING, .name = "bodyId", .optional = false, .reference = false, .nullable = false }
					},
					VariableType::TYPE_FLOAT
				),
				miniScript(miniScript) {}
			const string getMethodName() override {
				return "world.body.getAngularDamping";
			}
			void executeMethod(span<Variable>& argumentValues, Variable& returnValue, const Statement& statement) override {
				string bodyId;
				if (miniScript->getStringValue(argumentValues, 0, bodyId) == true) {
					auto body = miniScript->context->getWorld()->getBody(bodyId);
					if (body != nullptr) {
						returnValue = body->getAngularDamping();
					} else {
						Console::println(getMethodName() + "(): " + miniScript->getStatementInformation(statement) + ": body not found: " + bodyId);
					}
				} else {
					Console::println(getMethodName() + "(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation(getMethodName()));
					miniScript->startErrorScript();
				}
			}
			const vector<string>& getContextFunctions() {
				return CONTEXTFUNCTIONS_LOGIC;
			}
		};
		registerMethod(new MethodBodyGetAngularDamping(this));
	}
	{
		//
		class MethodBodySetAngularDamping: public Method {
		private:
			LogicMiniScript* miniScript { nullptr };
		public:
			MethodBodySetAngularDamping(LogicMiniScript* miniScript):
				Method(
					{
						{ .type = VariableType::TYPE_STRING, .name = "bodyId", .optional = false, .reference = false, .nullable = false },
						{ .type = VariableType::TYPE_FLOAT, .name = "angularDamping", .optional = false, .reference = false, .nullable = false }
					},
					VariableType::TYPE_NULL
				),
				miniScript(miniScript) {}
			const string getMethodName() override {
				return "world.body.setAngularDamping";
			}
			void executeMethod(span<Variable>& argumentValues, Variable& returnValue, const Statement& statement) override {
				string bodyId;
				float angularDamping;
				if (miniScript->getStringValue(argumentValues, 0, bodyId) == true &&
					miniScript->getFloatValue(argumentValues, 1, angularDamping) == true) {
					auto body = miniScript->context->getWorld()->getBody(bodyId);
					if (body != nullptr) {
						body->setAngularDamping(angularDamping);
					} else {
						Console::println(getMethodName() + "(): " + miniScript->getStatementInformation(statement) + ": body not found: " + bodyId);
					}
				} else {
					Console::println(getMethodName() + "(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation(getMethodName()));
					miniScript->startErrorScript();
				}
			}
			const vector<string>& getContextFunctions() {
				return CONTEXTFUNCTIONS_LOGIC;
			}
		};
		registerMethod(new MethodBodySetAngularDamping(this));
	}
	{
		//
		class MethodBodyGetLinearVelocity: public Method {
		private:
			LogicMiniScript* miniScript { nullptr };
		public:
			MethodBodyGetLinearVelocity(LogicMiniScript* miniScript):
				Method(
					{
						{ .type = VariableType::TYPE_STRING, .name = "bodyId", .optional = false, .reference = false, .nullable = false }
					},
					TYPE_VECTOR3
				),
				miniScript(miniScript) {}
			const string getMethodName() override {
				return "world.body.getLinearVelocity";
			}
			void executeMethod(span<Variable>& argumentValues, Variable& returnValue, const Statement& statement) override {
				string bodyId;
				if (miniScript->getStringValue(argumentValues, 0, bodyId) == true) {
					auto body = miniScript->context->getWorld()->getBody(bodyId);
					if (body != nullptr) {
						miniScript->setValue(returnValue, body->getLinearVelocity());
					} else {
						Console::println(getMethodName() + "(): " + miniScript->getStatementInformation(statement) + ": body not found: " + bodyId);
					}
				} else {
					Console::println(getMethodName() + "(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation(getMethodName()));
					miniScript->startErrorScript();
				}
			}
			const vector<string>& getContextFunctions() {
				return CONTEXTFUNCTIONS_LOGIC;
			}
		};
		registerMethod(new MethodBodyGetLinearVelocity(this));
	}
	{
		//
		class MethodBodySetLinearVelocity: public Method {
		private:
			LogicMiniScript* miniScript { nullptr };
		public:
			MethodBodySetLinearVelocity(LogicMiniScript* miniScript):
				Method(
					{
						{ .type = VariableType::TYPE_STRING, .name = "bodyId", .optional = false, .reference = false, .nullable = false },
						{ .type = TYPE_VECTOR3, .name = "linearVelocity", .optional = false, .reference = false, .nullable = false }
					},
					VariableType::TYPE_NULL
				),
				miniScript(miniScript) {}
			const string getMethodName() override {
				return "world.body.setLinearVelocity";
			}
			void executeMethod(span<Variable>& argumentValues, Variable& returnValue, const Statement& statement) override {
				string bodyId;
				Vector3 linearVelocity;
				if (miniScript->getStringValue(argumentValues, 0, bodyId) == true &&
					miniScript->getVector3Value(argumentValues, 1, linearVelocity) == true) {
					auto body = miniScript->context->getWorld()->getBody(bodyId);
					if (body != nullptr) {
						body->setLinearVelocity(linearVelocity);
					} else {
						Console::println(getMethodName() + "(): " + miniScript->getStatementInformation(statement) + ": body not found: " + bodyId);
					}
				} else {
					Console::println(getMethodName() + "(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation(getMethodName()));
					miniScript->startErrorScript();
				}
			}
			const vector<string>& getContextFunctions() {
				return CONTEXTFUNCTIONS_LOGIC;
			}
		};
		registerMethod(new MethodBodySetLinearVelocity(this));
	}
	{
		//
		class MethodBodyGetAngularVelocity: public Method {
		private:
			LogicMiniScript* miniScript { nullptr };
		public:
			MethodBodyGetAngularVelocity(LogicMiniScript* miniScript):
				Method(
					{
						{ .type = VariableType::TYPE_STRING, .name = "bodyId", .optional = false, .reference = false, .nullable = false }
					},
					TYPE_VECTOR3
				),
				miniScript(miniScript) {}
			const string getMethodName() override {
				return "world.body.getAngularVelocity";
			}
			void executeMethod(span<Variable>& argumentValues, Variable& returnValue, const Statement& statement) override {
				string bodyId;
				if (miniScript->getStringValue(argumentValues, 0, bodyId) == true) {
					auto body = miniScript->context->getWorld()->getBody(bodyId);
					if (body != nullptr) {
						miniScript->setValue(returnValue, body->getAngularVelocity());
					} else {
						Console::println(getMethodName() + "(): " + miniScript->getStatementInformation(statement) + ": body not found: " + bodyId);
					}
				} else {
					Console::println(getMethodName() + "(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation(getMethodName()));
					miniScript->startErrorScript();
				}
			}
			const vector<string>& getContextFunctions() {
				return CONTEXTFUNCTIONS_LOGIC;
			}
		};
		registerMethod(new MethodBodyGetAngularVelocity(this));
	}
	{
		//
		class MethodBodySetAngularVelocity: public Method {
		private:
			LogicMiniScript* miniScript { nullptr };
		public:
			MethodBodySetAngularVelocity(LogicMiniScript* miniScript):
				Method(
					{
						{ .type = VariableType::TYPE_STRING, .name = "bodyId", .optional = false, .reference = false, .nullable = false },
						{ .type = TYPE_VECTOR3, .name = "angularVelocity", .optional = false, .reference = false, .nullable = false }
					},
					VariableType::TYPE_NULL
				),
				miniScript(miniScript) {}
			const string getMethodName() override {
				return "world.body.setAngularVelocity";
			}
			void executeMethod(span<Variable>& argumentValues, Variable& returnValue, const Statement& statement) override {
				string bodyId;
				Vector3 angularVelocity;
				if (miniScript->getStringValue(argumentValues, 0, bodyId) == true &&
					miniScript->getVector3Value(argumentValues, 1, angularVelocity) == true) {
					auto body = miniScript->context->getWorld()->getBody(bodyId);
					if (body != nullptr) {
						body->setAngularVelocity(angularVelocity);
					} else {
						Console::println(getMethodName() + "(): " + miniScript->getStatementInformation(statement) + ": body not found: " + bodyId);
					}
				} else {
					Console::println(getMethodName() + "(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation(getMethodName()));
					miniScript->startErrorScript();
				}
			}
			const vector<string>& getContextFunctions() {
				return CONTEXTFUNCTIONS_LOGIC;
			}
		};
		registerMethod(new MethodBodySetAngularVelocity(this));
	}
	{
		//
		class MethodBodyAddForce: public Method {
		private:
			LogicMiniScript* miniScript { nullptr };
		public:
			MethodBodyAddForce(LogicMiniScript* miniScript):
				Method(
					{
						{ .type = VariableType::TYPE_STRING, .name = "bodyId", .optional = false, .reference = false, .nullable = false },
						{ .type = TYPE_VECTOR3, .name = "force", .optional = false, .reference = false, .nullable = false },
						{ .type = TYPE_VECTOR3, .name = "origin", .optional = true, .reference = false, .nullable = false }
					},
					VariableType::TYPE_NULL
				),
				miniScript(miniScript) {}
			const string getMethodName() override {
				return "world.body.addForce";
			}
			void executeMethod(span<Variable>& argumentValues, Variable& returnValue, const Statement& statement) override {
				string bodyId;
				Vector3 force;
				Vector3 forceOrigin;
				if (miniScript->getStringValue(argumentValues, 0, bodyId) == true &&
					miniScript->getVector3Value(argumentValues, 1, force) == true &&
					miniScript->getVector3Value(argumentValues, 2, forceOrigin, true) == true) {
					auto body = miniScript->context->getWorld()->getBody(bodyId);
					if (body != nullptr) {
						if (argumentValues.size() == 2) {
							body->addForce(force);
						} else
						if (argumentValues.size() == 3) {
							body->addForce(forceOrigin, force);
						} else {
							Console::println(getMethodName() + "(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation(getMethodName()));
							miniScript->startErrorScript();
						}
					} else {
						Console::println(getMethodName() + "(): " + miniScript->getStatementInformation(statement) + ": body not found: " + bodyId);
					}
				} else {
					Console::println(getMethodName() + "(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation(getMethodName()));
					miniScript->startErrorScript();
				}
			}
			const vector<string>& getContextFunctions() {
				return CONTEXTFUNCTIONS_LOGIC;
			}
		};
		registerMethod(new MethodBodyAddForce(this));
	}
	{
		//
		class MethodBodyAddTorque: public Method {
		private:
			LogicMiniScript* miniScript { nullptr };
		public:
			MethodBodyAddTorque(LogicMiniScript* miniScript):
				Method(
					{
						{ .type = VariableType::TYPE_STRING, .name = "bodyId", .optional = false, .reference = false, .nullable = false },
						{ .type = TYPE_VECTOR3, .name = "torque", .optional = false, .reference = false, .nullable = false }
					},
					VariableType::TYPE_NULL
				),
				miniScript(miniScript) {}
			const string getMethodName() override {
				return "world.body.addTorque";
			}
			void executeMethod(span<Variable>& argumentValues, Variable& returnValue, const Statement& statement) override {
				string bodyId;
				Vector3 torque;
				if (miniScript->getStringValue(argumentValues, 0, bodyId) == true &&
					miniScript->getVector3Value(argumentValues, 1, torque) == true) {
					auto body = miniScript->context->getWorld()->getBody(bodyId);
					if (body != nullptr) {
						body->addTorque(torque);
					} else {
						Console::println(getMethodName() + "(): " + miniScript->getStatementInformation(statement) + ": body not found: " + bodyId);
					}
				} else {
					Console::println(getMethodName() + "(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation(getMethodName()));
					miniScript->startErrorScript();
				}
			}
			const vector<string>& getContextFunctions() {
				return CONTEXTFUNCTIONS_LOGIC;
			}
		};
		registerMethod(new MethodBodyAddTorque(this));
	}
	{
		//
		class MethodBodyGetTransform: public Method {
		private:
			LogicMiniScript* miniScript { nullptr };
		public:
			MethodBodyGetTransform(LogicMiniScript* miniScript):
				Method(
					{
						{ .type = VariableType::TYPE_STRING, .name = "bodyId", .optional = false, .reference = false, .nullable = false }
					},
					TYPE_TRANSFORM
				),
				miniScript(miniScript) {}
			const string getMethodName() override {
				return "world.body.getTransform";
			}
			void executeMethod(span<Variable>& argumentValues, Variable& returnValue, const Statement& statement) override {
				string bodyId;
				if (miniScript->getStringValue(argumentValues, 0, bodyId) == true) {
					auto body = miniScript->context->getWorld()->getBody(bodyId);
					if (body != nullptr) {
						// get transform and make sure its a euler transform
						auto transform = body->getTransform();
						auto euler = transform.getTransformMatrix().computeEulerAngles();
						while (transform.getRotationCount() > 3) transform.removeRotation(transform.getRotationCount() - 1);
						while (transform.getRotationCount() < 3) transform.addRotation(Vector3(), 0.0f);
						transform.setRotationAxis(0, Vector3(0.0f, 0.0f, 1.0f));
						transform.setRotationAxis(1, Vector3(0.0f, 1.0f, 0.0f));
						transform.setRotationAxis(2, Vector3(1.0f, 0.0f, 0.0f));
						transform.setRotationAngle(0, euler.getZ());
						transform.setRotationAngle(1, euler.getY());
						transform.setRotationAngle(2, euler.getX());
						transform.update();
						miniScript->setValue(returnValue, transform);
					} else {
						Console::println(getMethodName() + "(): " + miniScript->getStatementInformation(statement) + ": body not found: " + bodyId);
					}
				} else {
					Console::println(getMethodName() + "(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation(getMethodName()));
					miniScript->startErrorScript();
				}
			}
			const vector<string>& getContextFunctions() {
				return CONTEXTFUNCTIONS_LOGIC;
			}
		};
		registerMethod(new MethodBodyGetTransform(this));
	}
	{
		//
		class MethodBodySetTransform: public Method {
		private:
			LogicMiniScript* miniScript { nullptr };
		public:
			MethodBodySetTransform(LogicMiniScript* miniScript):
				Method(
					{
						{ .type = VariableType::TYPE_STRING, .name = "bodyId", .optional = false, .reference = false, .nullable = false },
						{ .type = TYPE_TRANSFORM, .name = "transform", .optional = false, .reference = false, .nullable = false }
					},
					VariableType::TYPE_NULL
				),
				miniScript(miniScript) {}
			const string getMethodName() override {
				return "world.body.setTransform";
			}
			void executeMethod(span<Variable>& argumentValues, Variable& returnValue, const Statement& statement) override {
				string bodyId;
				Transform transform;
				if (miniScript->getStringValue(argumentValues, 0, bodyId) == true &&
					miniScript->getTransformValue(argumentValues, 1, transform) == true) {
					auto body = miniScript->context->getWorld()->getBody(bodyId);
					if (body != nullptr) {
						body->setTransform(transform);
					} else {
						Console::println(getMethodName() + "(): " + miniScript->getStatementInformation(statement) + ": body not found: " + bodyId);
					}
				} else {
					Console::println(getMethodName() + "(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation(getMethodName()));
					miniScript->startErrorScript();
				}
			}
			const vector<string>& getContextFunctions() {
				return CONTEXTFUNCTIONS_LOGIC;
			}
		};
		registerMethod(new MethodBodySetTransform(this));
	}
	{
		//
		class MethodWorldDetermineHeight: public Method {
		private:
			LogicMiniScript* miniScript { nullptr };
		public:
			MethodWorldDetermineHeight(LogicMiniScript* miniScript):
				Method(
					{
						{ .type = VariableType::TYPE_INTEGER, .name = "collisionTypeIds", .optional = false, .reference = false, .nullable = false },
						{ .type = VariableType::TYPE_FLOAT, .name = "stepUpMax", .optional = false, .reference = false, .nullable = false },
						{ .type = TYPE_VECTOR3, .name = "point", .optional = false, .reference = false, .nullable = false },
						{ .type = TYPE_VECTOR3, .name = "heightPoint", .optional = false, .reference = true, .nullable = false },
						{ .type = VariableType::TYPE_STRING, .name = "bodyId", .optional = true, .reference = true, .nullable = false },
						{ .type = VariableType::TYPE_FLOAT, .name = "minHeight", .optional = true, .reference = false, .nullable = false },
						{ .type = VariableType::TYPE_FLOAT, .name = "maxHeight", .optional = true, .reference = false, .nullable = false }
					},
					VariableType::TYPE_BOOLEAN
				),
				miniScript(miniScript) {}
			const string getMethodName() override {
				return "world.determineHeight";
			}
			void executeMethod(span<Variable>& argumentValues, Variable& returnValue, const Statement& statement) override {
				int64_t collisionTypeIds;
				float stepUpMax;
				Vector3 point;
				Vector3 heightPoint;
				float minHeight = -10000.0f;
				float maxHeight = 10000.0f;
				if (miniScript->getIntegerValue(argumentValues, 0, collisionTypeIds) == true &&
					miniScript->getFloatValue(argumentValues, 1, stepUpMax) == true &&
					miniScript->getVector3Value(argumentValues, 2, point) == true &&
					miniScript->getVector3Value(argumentValues, 3, heightPoint) == true &&
					miniScript->getFloatValue(argumentValues, 5, minHeight, true) == true &&
					miniScript->getFloatValue(argumentValues, 6, maxHeight, true) == true) {
					auto body = miniScript->context->getWorld()->determineHeight(collisionTypeIds, stepUpMax, point, heightPoint, minHeight, maxHeight);
					if (body != nullptr) {
						miniScript->setValue(argumentValues[3], heightPoint);
						if (argumentValues.size() >= 5) argumentValues[4].setValue(body->getId());
						returnValue = true;
					} else {
						returnValue = false;
					}
				} else {
					Console::println(getMethodName() + "(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation(getMethodName()));
					miniScript->startErrorScript();
				}
			}
			const vector<string>& getContextFunctions() {
				return CONTEXTFUNCTIONS_LOGIC;
			}
		};
		registerMethod(new MethodWorldDetermineHeight(this));
	}
	{
		//
		class MethodWorldDoRayCasting: public Method {
		private:
			LogicMiniScript* miniScript { nullptr };
		public:
			MethodWorldDoRayCasting(LogicMiniScript* miniScript):
				Method(
					{
						{ .type = VariableType::TYPE_INTEGER, .name = "collisionTypeIds", .optional = false, .reference = false, .nullable = false },
						{ .type = TYPE_VECTOR3, .name = "start", .optional = false, .reference = false, .nullable = false },
						{ .type = TYPE_VECTOR3, .name = "end", .optional = false, .reference = false, .nullable = false },
						{ .type = TYPE_VECTOR3, .name = "hitPoint", .optional = false, .reference = true, .nullable = false },
						{ .type = VariableType::TYPE_STRING, .name = "bodyId", .optional = true, .reference = true, .nullable = false },
						{ .type = VariableType::TYPE_STRING, .name = "actorId", .optional = true, .reference = false, .nullable = false },
					},
					VariableType::TYPE_BOOLEAN
				),
				miniScript(miniScript) {}
			const string getMethodName() override {
				return "world.doRayCasting";
			}
			void executeMethod(span<Variable>& argumentValues, Variable& returnValue, const Statement& statement) override {
				int64_t collisionTypeIds;
				Vector3 start;
				Vector3 end;
				Vector3 hitPoint;
				string actorId;
				if (miniScript->getIntegerValue(argumentValues, 0, collisionTypeIds) == true &&
					miniScript->getVector3Value(argumentValues, 1, start) == true &&
					miniScript->getVector3Value(argumentValues, 2, end) == true &&
					miniScript->getStringValue(argumentValues, 5, actorId, true) == true) {
					auto body = miniScript->context->getWorld()->doRayCasting(collisionTypeIds, start, end, hitPoint, actorId);
					if (body != nullptr) {
						miniScript->setValue(argumentValues[3], hitPoint);
						if (argumentValues.size() >= 5) argumentValues[4].setValue(body->getId());
						miniScript->setValue(returnValue, true);
					} else {
						miniScript->setValue(returnValue, false);
					}
				} else {
					Console::println(getMethodName() + "(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation(getMethodName()));
					miniScript->startErrorScript();
				}
			}
			const vector<string>& getContextFunctions() {
				return CONTEXTFUNCTIONS_LOGIC;
			}
		};
		registerMethod(new MethodWorldDoRayCasting(this));
	}
	{
		//
		class MethodWorldDoCollide: public Method {
		private:
			LogicMiniScript* miniScript { nullptr };
		public:
			MethodWorldDoCollide(LogicMiniScript* miniScript):
				Method(
					{
						{ .type = VariableType::TYPE_STRING, .name = "bodyId1", .optional = false, .reference = false, .nullable = false },
						{ .type = VariableType::TYPE_STRING, .name = "bodyId2", .optional = false, .reference = false, .nullable = false }
					},
					VariableType::TYPE_BOOLEAN
				),
				miniScript(miniScript) {}
			const string getMethodName() override {
				return "world.doCollide";
			}
			void executeMethod(span<Variable>& argumentValues, Variable& returnValue, const Statement& statement) override {
				string bodyId1;
				string bodyId2;
				if (miniScript->getStringValue(argumentValues, 0, bodyId1) == true &&
					miniScript->getStringValue(argumentValues, 1, bodyId2) == true) {
					auto body1 = miniScript->context->getWorld()->getBody(bodyId1);
					auto body2 = miniScript->context->getWorld()->getBody(bodyId2);
					if (body1 == nullptr) {
						Console::println(getMethodName() + "(): " + miniScript->getStatementInformation(statement) + ": body1 not found: " + bodyId1);
					} else
					if (body2 == nullptr) {
						Console::println(getMethodName() + "(): " + miniScript->getStatementInformation(statement) + ": body2 not found: " + bodyId2);
					} else {
						returnValue = miniScript->context->getWorld()->doCollide(body1, body2);
					}
				} else {
					Console::println(getMethodName() + "(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation(getMethodName()));
					miniScript->startErrorScript();
				}
			}
			const vector<string>& getContextFunctions() {
				return CONTEXTFUNCTIONS_LOGIC;
			}
		};
		registerMethod(new MethodWorldDoCollide(this));
	}
	{
		//
		class MethodWorldDoesCollideWith: public Method {
		private:
			LogicMiniScript* miniScript { nullptr };
		public:
			MethodWorldDoesCollideWith(LogicMiniScript* miniScript):
				Method(
					{
						{ .type = VariableType::TYPE_INTEGER, .name = "collisionTypeIds", .optional = false, .reference = false, .nullable = false },
						{ .type = VariableType::TYPE_STRING, .name = "bodyId", .optional = false, .reference = false, .nullable = false }
					},
					VariableType::TYPE_ARRAY
				),
				miniScript(miniScript) {}
			const string getMethodName() override {
				return "world.doesCollideWith";
			}
			void executeMethod(span<Variable>& argumentValues, Variable& returnValue, const Statement& statement) override {
				int64_t collisionTypeIds;
				string bodyId;
				if (miniScript->getIntegerValue(argumentValues, 0, collisionTypeIds) == true &&
					miniScript->getStringValue(argumentValues, 1, bodyId) == true) {
					auto body = miniScript->context->getWorld()->getBody(bodyId);
					if (body == nullptr) {
						Console::println(getMethodName() + "(): " + miniScript->getStatementInformation(statement) + ": body not found: " + bodyId);
					} else {
						vector<Body*> collisionBodies;
						miniScript->context->getWorld()->doesCollideWith(collisionTypeIds, body, collisionBodies);
						returnValue.setType(EngineMiniScript::TYPE_ARRAY);
						for (auto collisionBody: collisionBodies) {
							returnValue.pushArrayEntry(collisionBody->getId());
						}
					}
				} else {
					Console::println(getMethodName() + "(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation(getMethodName()));
					miniScript->startErrorScript();
				}
			}
			const vector<string>& getContextFunctions() {
				return CONTEXTFUNCTIONS_LOGIC;
			}
		};
		registerMethod(new MethodWorldDoesCollideWith(this));
	}
	// path finding
	{
		//
		class MethodPathFindingSTATE_IDLE: public Method {
		private:
			LogicMiniScript* miniScript { nullptr };
		public:
			MethodPathFindingSTATE_IDLE(LogicMiniScript* miniScript):
				Method({}, VariableType::TYPE_INTEGER),
				miniScript(miniScript) {}
			const string getMethodName() override {
				return "pathfinding.STATE_IDLE";
			}
			void executeMethod(span<Variable>& argumentValues, Variable& returnValue, const Statement& statement) override {
				returnValue = static_cast<int64_t>(Context::PathFindingThread::STATE_IDLE);
			}
			const vector<string>& getContextFunctions() {
				return CONTEXTFUNCTIONS_LOGIC;
			}
		};
		registerMethod(new MethodPathFindingSTATE_IDLE(this));
	}
	{
		//
		class MethodPathFindingSTATE_TRYLOCK_FAILED: public Method {
		private:
			LogicMiniScript* miniScript { nullptr };
		public:
			MethodPathFindingSTATE_TRYLOCK_FAILED(LogicMiniScript* miniScript):
				Method({}, VariableType::TYPE_INTEGER),
				miniScript(miniScript) {}
			const string getMethodName() override {
				return "pathfinding.STATE_TRYLOCK_FAILED";
			}
			void executeMethod(span<Variable>& argumentValues, Variable& returnValue, const Statement& statement) override {
				returnValue = static_cast<int64_t>(Context::PathFindingThread::STATE_TRYLOCK_FAILED);
			}
			const vector<string>& getContextFunctions() {
				return CONTEXTFUNCTIONS_LOGIC;
			}
		};
		registerMethod(new MethodPathFindingSTATE_TRYLOCK_FAILED(this));
	}
	{
		//
		class MethodPathFindingSTATE_PATHFINDING_OTHER: public Method {
		private:
			LogicMiniScript* miniScript { nullptr };
		public:
			MethodPathFindingSTATE_PATHFINDING_OTHER(LogicMiniScript* miniScript):
				Method({}, VariableType::TYPE_INTEGER),
				miniScript(miniScript) {}
			const string getMethodName() override {
				return "pathfinding.STATE_PATHFINDING_OTHER";
			}
			void executeMethod(span<Variable>& argumentValues, Variable& returnValue, const Statement& statement) override {
				returnValue = static_cast<int64_t>(Context::PathFindingThread::STATE_PATHFINDING_OTHER);
			}
			const vector<string>& getContextFunctions() {
				return CONTEXTFUNCTIONS_LOGIC;
			}
		};
		registerMethod(new MethodPathFindingSTATE_PATHFINDING_OTHER(this));
	}
	{
		//
		class MethodPathFindingSTATE_PATHFINDING: public Method {
		private:
			LogicMiniScript* miniScript { nullptr };
		public:
			MethodPathFindingSTATE_PATHFINDING(LogicMiniScript* miniScript):
				Method({}, VariableType::TYPE_INTEGER),
				miniScript(miniScript) {}
			const string getMethodName() override {
				return "pathfinding.STATE_PATHFINDING";
			}
			void executeMethod(span<Variable>& argumentValues, Variable& returnValue, const Statement& statement) override {
				returnValue = static_cast<int64_t>(Context::PathFindingThread::STATE_PATHFINDING);
			}
			const vector<string>& getContextFunctions() {
				return CONTEXTFUNCTIONS_LOGIC;
			}
		};
		registerMethod(new MethodPathFindingSTATE_PATHFINDING(this));
	}
	{
		//
		class MethodPathFindingSTATE_PATHFINDING_FAILED: public Method {
		private:
			LogicMiniScript* miniScript { nullptr };
		public:
			MethodPathFindingSTATE_PATHFINDING_FAILED(LogicMiniScript* miniScript):
				Method({}, VariableType::TYPE_INTEGER),
				miniScript(miniScript) {}
			const string getMethodName() override {
				return "pathfinding.STATE_PATHFINDING_FAILED";
			}
			void executeMethod(span<Variable>& argumentValues, Variable& returnValue, const Statement& statement) override {
				returnValue = static_cast<int64_t>(Context::PathFindingThread::STATE_PATHFINDING_FAILED);
			}
			const vector<string>& getContextFunctions() {
				return CONTEXTFUNCTIONS_LOGIC;
			}
		};
		registerMethod(new MethodPathFindingSTATE_PATHFINDING_FAILED(this));
	}
	{
		//
		class MethodPathFindingSTATE_PATHFINDING_SUCCESS: public Method {
		private:
			LogicMiniScript* miniScript { nullptr };
		public:
			MethodPathFindingSTATE_PATHFINDING_SUCCESS(LogicMiniScript* miniScript):
				Method({}, VariableType::TYPE_INTEGER),
				miniScript(miniScript) {}
			const string getMethodName() override {
				return "pathfinding.STATE_PATHFINDING_SUCCESS";
			}
			void executeMethod(span<Variable>& argumentValues, Variable& returnValue, const Statement& statement) override {
				returnValue = static_cast<int64_t>(Context::PathFindingThread::STATE_PATHFINDING_SUCCESS);
			}
			const vector<string>& getContextFunctions() {
				return CONTEXTFUNCTIONS_LOGIC;
			}
		};
		registerMethod(new MethodPathFindingSTATE_PATHFINDING_SUCCESS(this));
	}
	{
		//
		class MethodPathFindingFindPath: public Method {
		private:
			LogicMiniScript* miniScript { nullptr };
		public:
			MethodPathFindingFindPath(LogicMiniScript* miniScript):
				Method(
					{
						{ .type = VariableType::TYPE_STRING, .name = "logicId", .optional = false, .reference = false, .nullable = false },
						{ .type = TYPE_VECTOR3, .name = "startPosition", .optional = false, .reference = false, .nullable = false },
						{ .type = TYPE_VECTOR3, .name = "endPosition", .optional = false, .reference = false, .nullable = false },
						{ .type = VariableType::TYPE_ARRAY, .name = "path", .optional = false, .reference = true, .nullable = false },
					},
					VariableType::TYPE_INTEGER
				),
				miniScript(miniScript) {}
			const string getMethodName() override {
				return "pathfinding.findPath";
			}
			void executeMethod(span<Variable>& argumentValues, Variable& returnValue, const Statement& statement) override {
				string logicId;
				Vector3 startPosition;
				Vector3 endPosition;
				if (argumentValues.size() == 4 &&
					miniScript->getStringValue(argumentValues, 0, logicId) == true &&
					miniScript->getVector3Value(argumentValues, 1, startPosition) == true &&
					miniScript->getVector3Value(argumentValues, 2, endPosition) == true) {
					argumentValues[3].setType(EngineMiniScript::TYPE_ARRAY);
					vector<Vector3> path;
					auto pathFindingState = miniScript->context->getPathFinding()->findPath(logicId, logicId, startPosition, endPosition, path);
					returnValue = static_cast<int64_t>(pathFindingState);
					for (const auto& position: path) {
						MiniScript::Variable positionVariable;
						miniScript->setValue(positionVariable, position);
						argumentValues[3].pushArrayEntry(positionVariable);
					};
				} else {
					Console::println(getMethodName() + "(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation(getMethodName()));
					miniScript->startErrorScript();
				}
			}
			const vector<string>& getContextFunctions() {
				return CONTEXTFUNCTIONS_LOGIC;
			}
		};
		registerMethod(new MethodPathFindingFindPath(this));
	}
	// scene
	{
		//
		class MethodSceneGetWidth: public Method {
		private:
			LogicMiniScript* miniScript { nullptr };
		public:
			MethodSceneGetWidth(LogicMiniScript* miniScript):
				Method({}, VariableType::TYPE_FLOAT),
				miniScript(miniScript) {}
			const string getMethodName() override {
				return "scene.getWidth";
			}
			void executeMethod(span<Variable>& argumentValues, Variable& returnValue, const Statement& statement) override {
				miniScript->setValue(returnValue, miniScript->context->getScene()->getBoundingBox()->getDimensions().getX());
			}
			const vector<string>& getContextFunctions() {
				return CONTEXTFUNCTIONS_ALL;
			}
		};
		registerMethod(new MethodSceneGetWidth(this));
	}
	{
		//
		class MethodSceneGetHeight: public Method {
		private:
			LogicMiniScript* miniScript { nullptr };
		public:
			MethodSceneGetHeight(LogicMiniScript* miniScript):
				Method({}, VariableType::TYPE_FLOAT),
				miniScript(miniScript) {}
			const string getMethodName() override {
				return "scene.getHeight";
			}
			void executeMethod(span<Variable>& argumentValues, Variable& returnValue, const Statement& statement) override {
				returnValue = miniScript->context->getScene()->getBoundingBox()->getDimensions().getY();
			}
			const vector<string>& getContextFunctions() {
				return CONTEXTFUNCTIONS_ALL;
			}
		};
		registerMethod(new MethodSceneGetHeight(this));
	}
	{
		//
		class MethodSceneGetDepth: public Method {
		private:
			LogicMiniScript* miniScript { nullptr };
		public:
			MethodSceneGetDepth(LogicMiniScript* miniScript):
				Method({}, VariableType::TYPE_FLOAT),
				miniScript(miniScript) {}
			const string getMethodName() override {
				return "scene.getDepth";
			}
			void executeMethod(span<Variable>& argumentValues, Variable& returnValue, const Statement& statement) override {
				returnValue = miniScript->context->getScene()->getBoundingBox()->getDimensions().getZ();
			}
			const vector<string>& getContextFunctions() {
				return CONTEXTFUNCTIONS_ALL;
			}
		};
		registerMethod(new MethodSceneGetDepth(this));
	}
	// sceneconnector
	{
		//
		class MethodSceneConnectorSpawnPrototype: public Method {
		private:
			LogicMiniScript* miniScript { nullptr };
		public:
			MethodSceneConnectorSpawnPrototype(LogicMiniScript* miniScript):
				Method(
					{
						{ .type = VariableType::TYPE_STRING, .name = "pathName", .optional = false, .reference = false, .nullable = false },
						{ .type = VariableType::TYPE_STRING, .name = "fileName", .optional = false, .reference = false, .nullable = false },
						{ .type = VariableType::TYPE_STRING, .name = "id", .optional = false, .reference = false, .nullable = false },
						{ .type = TYPE_TRANSFORM, .name = "transform", .optional = false, .reference = false, .nullable = false },
						{ .type = VariableType::TYPE_STRING, .name = "hierarchyId", .optional = true, .reference = false, .nullable = false },
						{ .type = VariableType::TYPE_STRING, .name = "hierarchyParentId", .optional = true, .reference = false, .nullable = false },
					},
					VariableType::TYPE_NULL
				),
				miniScript(miniScript) {}
			const string getMethodName() override {
				return "sceneconnector.spawnPrototype";
			}
			void executeMethod(span<Variable>& argumentValues, Variable& returnValue, const Statement& statement) override {
				string pathName;
				string fileName;
				string id;
				Transform transform;
				string hierarchyId;
				string hierarchyParentId;
				if (miniScript->getStringValue(argumentValues, 0, pathName) == true &&
					miniScript->getStringValue(argumentValues, 1, fileName) == true &&
					miniScript->getStringValue(argumentValues, 2, id) == true &&
					miniScript->getTransformValue(argumentValues, 3, transform) == true &&
					miniScript->getStringValue(argumentValues, 4, hierarchyId, true) == true &&
					miniScript->getStringValue(argumentValues, 5, hierarchyParentId, true) == true) {
					miniScript->prototypesToAddMutex.lock();
					try {
						auto _pathName = pathName;
						if (miniScript->context->getApplicationRootPathName().empty() == false) {
							_pathName = FileSystem::getInstance()->getCanonicalURI(miniScript->context->getApplicationRootPathName(), pathName);
						}
						Prototype* prototype = nullptr;
						auto canonicalPath = FileSystem::getInstance()->getCanonicalURI(_pathName, fileName);
						auto prototypeIt = miniScript->prototypes.find(canonicalPath);
						if (prototypeIt != miniScript->prototypes.end()) {
							prototypeIt->second.counter++;
							prototype = prototypeIt->second.prototype.get();
						} else {
							prototype = PrototypeReader::read(_pathName, fileName);
							miniScript->prototypes[canonicalPath] = {
								.counter = 1,
								.prototype = unique_ptr<Prototype>(prototype)
							};
						}
						miniScript->enginePrototypesToAdd.emplace_back(
							PrototypeToAdd::TYPE_SPAWN,
							prototype,
							id,
							string(),
							transform,
							hierarchyId,
							hierarchyParentId
						);
						miniScript->physicsPrototypesToAdd.emplace_back(
							PrototypeToAdd::TYPE_SPAWN,
							prototype,
							id,
							string(),
							transform,
							hierarchyId,
							hierarchyParentId
						);
					} catch (Exception& exception) {
						miniScript->prototypesToAddMutex.unlock();
						Console::println("MethodSceneConnectorSpawnPrototype::executeMethod(): An error occurred: " + string(exception.what()));
						miniScript->startErrorScript();
					}
					miniScript->prototypesToAddMutex.unlock();
				} else {
					Console::println(getMethodName() + "(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation(getMethodName()));
					miniScript->startErrorScript();
				}
			}
			const vector<string>& getContextFunctions() {
				return CONTEXTFUNCTIONS_LOGIC;
			}
		};
		registerMethod(new MethodSceneConnectorSpawnPrototype(this));
	}
	{
		//
		class MethodSceneConnectorAttachPrototype: public Method {
		private:
			LogicMiniScript* miniScript { nullptr };
		public:
			MethodSceneConnectorAttachPrototype(LogicMiniScript* miniScript):
				Method(
					{
						{ .type = VariableType::TYPE_STRING, .name = "pathName", .optional = false, .reference = false, .nullable = false },
						{ .type = VariableType::TYPE_STRING, .name = "fileName", .optional = false, .reference = false, .nullable = false },
						{ .type = VariableType::TYPE_STRING, .name = "id", .optional = false, .reference = false, .nullable = false },
						{ .type = VariableType::TYPE_STRING, .name = "attachNodeId", .optional = false, .reference = false, .nullable = false },
						{ .type = TYPE_TRANSFORM, .name = "transform", .optional = false, .reference = false, .nullable = false },
						{ .type = VariableType::TYPE_STRING, .name = "parentId", .optional = true, .reference = false, .nullable = false },
					},
					VariableType::TYPE_NULL
				),
				miniScript(miniScript) {}
			const string getMethodName() override {
				return "sceneconnector.attachPrototype";
			}
			void executeMethod(span<Variable>& argumentValues, Variable& returnValue, const Statement& statement) override {
				string pathName;
				string fileName;
				string id;
				string attachNodeId;
				Transform transform;
				string hierarchyParentId;
				if (miniScript->getStringValue(argumentValues, 0, pathName) == true &&
					miniScript->getStringValue(argumentValues, 1, fileName) == true &&
					miniScript->getStringValue(argumentValues, 2, id) == true &&
					miniScript->getStringValue(argumentValues, 3, attachNodeId) == true &&
					miniScript->getTransformValue(argumentValues, 4, transform) == true &&
					miniScript->getStringValue(argumentValues, 5, hierarchyParentId, true) == true) {
					miniScript->prototypesToAddMutex.lock();
					try {
						auto _pathName = pathName;
						if (miniScript->context->getApplicationRootPathName().empty() == false) {
							_pathName = FileSystem::getInstance()->getCanonicalURI(miniScript->context->getApplicationRootPathName(), pathName);
						}
						Prototype* prototype = nullptr;
						auto canonicalPath = FileSystem::getInstance()->getCanonicalURI(_pathName, fileName);
						auto prototypeIt = miniScript->prototypes.find(canonicalPath);
						if (prototypeIt != miniScript->prototypes.end()) {
							prototypeIt->second.counter++;
							prototype = prototypeIt->second.prototype.get();
						} else {
							prototype = PrototypeReader::read(_pathName, fileName);
							miniScript->prototypes[canonicalPath] = {
								.counter = 1,
								.prototype = unique_ptr<Prototype>(prototype)
							};
						}
						miniScript->enginePrototypesToAdd.emplace_back(
							PrototypeToAdd::TYPE_ATTACH,
							prototype,
							id,
							attachNodeId,
							transform,
							miniScript->logic->getId(),
							hierarchyParentId
						);
						miniScript->physicsPrototypesToAdd.emplace_back(
							PrototypeToAdd::TYPE_ATTACH,
							prototype,
							id,
							attachNodeId,
							transform,
							miniScript->logic->getId(),
							hierarchyParentId
						);
					} catch (Exception& exception) {
						miniScript->prototypesToAddMutex.unlock();
						Console::println("MethodSceneConnectorAttachPrototype::executeMethod(): An error occurred: " + string(exception.what()));
						miniScript->startErrorScript();
					}
					miniScript->prototypesToAddMutex.unlock();
				} else {
					Console::println(getMethodName() + "(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation(getMethodName()));
					miniScript->startErrorScript();
				}
			}
			const vector<string>& getContextFunctions() {
				return CONTEXTFUNCTIONS_LOGIC;
			}
		};
		registerMethod(new MethodSceneConnectorAttachPrototype(this));
	}
}

void LogicMiniScript::registerVariables() {
}

void LogicMiniScript::collectHIDEvents(vector<GUIMouseEvent>& mouseEvents, vector<GUIKeyboardEvent>& keyEvents) {
	// keyboard events
	keyboardTypedChars.clear();
	keyboardControlDown = false;
	keyboardMetaDown = false;
	keyboardAltDown = false;
	keyboardShiftDown = false;
	for (const auto& event: keyEvents) {
		// processed already?
		if (event.isProcessed() == true) continue;
		// key pressed
		if (event.getType() == GUIKeyboardEvent::KEYBOARDEVENT_KEY_PRESSED) {
			keyboardChars.insert(event.getKeyChar());
			keyboardKeys.insert(event.getKeyCode());
		} else
		// key released
		if (event.getType() == GUIKeyboardEvent::KEYBOARDEVENT_KEY_RELEASED) {
			keyboardChars.erase(event.getKeyChar());
			keyboardKeys.erase(event.getKeyCode());
		} else
		// key typed
		if (event.getType() == GUIKeyboardEvent::KEYBOARDEVENT_KEY_TYPED) {
			Character::appendToString(keyboardTypedChars, event.getKeyChar());
		}
		// extra keys
		if (event.isControlDown() == true) keyboardControlDown = true;
		if (event.isMetaDown() == true) keyboardMetaDown = true;
		if (event.isAltDown() == true) keyboardAltDown = true;
		if (event.isShiftDown() == true) keyboardShiftDown = true;
	}

	// mouse
	mouseDown.fill(false);
	mouseUp.fill(false);
	mouseDragging.fill(false);
	mouseMoved = false;
	mouseWheelX = 0.0f;
	mouseWheelY = 0.0f;
	mouseWheelZ = 0.0f;
	for (const auto& event: mouseEvents) {
		// mouse move
		if (event.isProcessed() == false && event.getType() == GUIMouseEvent::MOUSEEVENT_MOVED) {
			mouseMoved = true;
		} else
		// on press and drag
		//	store button and mouse dragging properties
		if (event.isProcessed() == false && event.getType() == GUIMouseEvent::MOUSEEVENT_PRESSED) {
			if (event.getButton() != GUIMouseEvent::MOUSEEVENT_BUTTON_NONE) {
				mouseDown[event.getButton() - 1] = true;
			}
		} else
		if (event.isProcessed() == false && event.getType() == GUIMouseEvent::MOUSEEVENT_DRAGGED) {
			if (event.getButton() != GUIMouseEvent::MOUSEEVENT_BUTTON_NONE) {
				mouseDragging[event.getButton() - 1] = true;
			}
		} else
		// on release
		//	store release
		if (event.getType() == GUIMouseEvent::MOUSEEVENT_RELEASED) {
			if (event.getButton() != GUIMouseEvent::MOUSEEVENT_BUTTON_NONE) {
				mouseUp[event.getButton() - 1] = true;
			}
		} else
		// wheel
		if (event.isProcessed() == false && event.getType() == GUIMouseEvent::MOUSEEVENT_WHEEL_MOVED) {
			mouseWheelX+= event.getWheelX();
			mouseWheelY+= event.getWheelY();
			mouseWheelZ+= event.getWheelZ();
		}
		// always store mouse position
		mouseX = event.getX();
		mouseXUnscaled = event.getXUnscaled();
		mouseY = event.getY();
		mouseYUnscaled = event.getYUnscaled();
		// extra keys
		if (event.isControlDown() == true) keyboardControlDown = true;
		if (event.isMetaDown() == true) keyboardMetaDown = true;
		if (event.isAltDown() == true) keyboardAltDown = true;
		if (event.isShiftDown() == true) keyboardShiftDown = true;
	}
}
