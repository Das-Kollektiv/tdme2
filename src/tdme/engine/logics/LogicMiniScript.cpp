#include <tdme/engine/logics/LogicMiniScript.h>

#include <span>
#include <string>
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
#include <tdme/tools/editor/TDMEEditor.h>
#include <tdme/utilities/Character.h>
#include <tdme/utilities/Console.h>
#include <tdme/utilities/Exception.h>
#include <tdme/utilities/MiniScript.h>
#include <tdme/utilities/UTF8CharacterIterator.h>

using std::span;
using std::string;
using std::to_string;
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
using tdme::tools::editor::TDMEEditor;
using tdme::utilities::Character;
using tdme::utilities::Console;
using tdme::utilities::Exception;
using tdme::utilities::MiniScript;
using tdme::utilities::UTF8CharacterIterator;

LogicMiniScript::LogicMiniScript(): MiniScript(), prototypesToAddMutex("prototypetoadd-mutex") {
}

LogicMiniScript::~LogicMiniScript() {
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
	MiniScript::registerStateMachineStates();
}

void LogicMiniScript::registerMethods() {
	MiniScript::registerMethods();
	{
		//
		class ScriptMethodApplicationRunsInEditor: public ScriptMethod {
		private:
			LogicMiniScript* miniScript { nullptr };
		public:
			ScriptMethodApplicationRunsInEditor(LogicMiniScript* miniScript):
				ScriptMethod({}, ScriptVariableType::TYPE_BOOLEAN),
				miniScript(miniScript) {}
			const string getMethodName() override {
				return "application.runsInEditor";
			}
			void executeMethod(span<ScriptVariable>& argumentValues, ScriptVariable& returnValue, const ScriptStatement& statement) override {
				returnValue.setValue(miniScript->logic->isRunningInEditor());
			}
			const vector<string>& getContextFunctions() {
				return CONTEXTFUNCTIONS_ALL;
			}
		};
		registerMethod(new ScriptMethodApplicationRunsInEditor(this));
	}
	{
		//
		class ScriptMethodApplicationIsFullScreen: public ScriptMethod {
		private:
			LogicMiniScript* miniScript { nullptr };
		public:
			ScriptMethodApplicationIsFullScreen(LogicMiniScript* miniScript):
				ScriptMethod({}, ScriptVariableType::TYPE_BOOLEAN),
				miniScript(miniScript) {}
			const string getMethodName() override {
				return "application.isFullScreen";
			}
			void executeMethod(span<ScriptVariable>& argumentValues, ScriptVariable& returnValue, const ScriptStatement& statement) override {
				returnValue.setValue(TDMEEditor::getInstance() != nullptr?TDMEEditor::getInstance()->isFullScreen():false);
			}
			const vector<string>& getContextFunctions() {
				return CONTEXTFUNCTIONS_ALL;
			}
		};
		registerMethod(new ScriptMethodApplicationIsFullScreen(this));
	}
	{
		//
		class ScriptMethodLogicGetId: public ScriptMethod {
		private:
			LogicMiniScript* miniScript { nullptr };
		public:
			ScriptMethodLogicGetId(LogicMiniScript* miniScript):
				ScriptMethod({}, ScriptVariableType::TYPE_STRING),
				miniScript(miniScript) {}
			const string getMethodName() override {
				return "logic.getId";
			}
			void executeMethod(span<ScriptVariable>& argumentValues, ScriptVariable& returnValue, const ScriptStatement& statement) override {
				returnValue.setValue(miniScript->logic->getId());
			}
			const vector<string>& getContextFunctions() {
				return CONTEXTFUNCTIONS_ENGINELOGIC;
			}
		};
		registerMethod(new ScriptMethodLogicGetId(this));
	}
	{
		//
		class ScriptMethodLogicGetHierarchyId: public ScriptMethod {
		private:
			LogicMiniScript* miniScript { nullptr };
		public:
			ScriptMethodLogicGetHierarchyId(LogicMiniScript* miniScript):
				ScriptMethod({}, ScriptVariableType::TYPE_STRING),
				miniScript(miniScript) {}
			const string getMethodName() override {
				return "logic.getHierarchyId";
			}
			void executeMethod(span<ScriptVariable>& argumentValues, ScriptVariable& returnValue, const ScriptStatement& statement) override {
				returnValue.setValue(miniScript->logic->getHierarchyId());
			}
			const vector<string>& getContextFunctions() {
				return CONTEXTFUNCTIONS_ENGINELOGIC;
			}
		};
		registerMethod(new ScriptMethodLogicGetHierarchyId(this));
	}
	{
		//
		class ScriptMethodLogicGetHierarchyParentId: public ScriptMethod {
		private:
			LogicMiniScript* miniScript { nullptr };
		public:
			ScriptMethodLogicGetHierarchyParentId(LogicMiniScript* miniScript):
				ScriptMethod({}, ScriptVariableType::TYPE_STRING),
				miniScript(miniScript) {}
			const string getMethodName() override {
				return "logic.getHierarchyParentId";
			}
			void executeMethod(span<ScriptVariable>& argumentValues, ScriptVariable& returnValue, const ScriptStatement& statement) override {
				returnValue.setValue(miniScript->logic->getHierarchyParentId());
			}
			const vector<string>& getContextFunctions() {
				return CONTEXTFUNCTIONS_ENGINELOGIC;
			}
		};
		registerMethod(new ScriptMethodLogicGetHierarchyParentId(this));
	}
	{
		//
		class ScriptMethodLogicGetLogicIds: public ScriptMethod {
		private:
			LogicMiniScript* miniScript { nullptr };
		public:
			ScriptMethodLogicGetLogicIds(LogicMiniScript* miniScript):
				ScriptMethod({}, ScriptVariableType::TYPE_ARRAY),
				miniScript(miniScript) {}
			const string getMethodName() override {
				return "logic.getLogicIds";
			}
			void executeMethod(span<ScriptVariable>& argumentValues, ScriptVariable& returnValue, const ScriptStatement& statement) override {
				auto contextLogics = miniScript->logic->getContext()->getLogics();
				returnValue.setType(MiniScript::TYPE_ARRAY);
				for (auto contextLogic: contextLogics) {
					returnValue.pushArrayValue(MiniScript::ScriptVariable(contextLogic->getId()));
				}
			}
			const vector<string>& getContextFunctions() {
				return CONTEXTFUNCTIONS_LOGIC;
			}
		};
		registerMethod(new ScriptMethodLogicGetLogicIds(this));
	}
	{
		//
		class ScriptMethodAudioGetListenerPosition: public ScriptMethod {
		private:
			LogicMiniScript* miniScript { nullptr };
		public:
			ScriptMethodAudioGetListenerPosition(LogicMiniScript* miniScript):
				ScriptMethod(
					{},
					ScriptVariableType::TYPE_VECTOR3
				),
				miniScript(miniScript) {}
			const string getMethodName() override {
				return "audio.getListenerPosition";
			}
			void executeMethod(span<ScriptVariable>& argumentValues, ScriptVariable& returnValue, const ScriptStatement& statement) override {
				returnValue.setValue(miniScript->logic->getContext()->getAudio()->getListenerPosition());
			}
			const vector<string>& getContextFunctions() {
				return CONTEXTFUNCTIONS_ENGINE;
			}
		};
		registerMethod(new ScriptMethodAudioGetListenerPosition(this));
	}
	{
		//
		class ScriptMethodAudioSetListenerPosition: public ScriptMethod {
		private:
			LogicMiniScript* miniScript { nullptr };
		public:
			ScriptMethodAudioSetListenerPosition(LogicMiniScript* miniScript):
				ScriptMethod(
					{
						{ .type = ScriptVariableType::TYPE_VECTOR3, .name = "position", .optional = false, .assignBack = false }
					},
					ScriptVariableType::TYPE_NULL
				),
				miniScript(miniScript) {}
			const string getMethodName() override {
				return "audio.setListenerPosition";
			}
			void executeMethod(span<ScriptVariable>& argumentValues, ScriptVariable& returnValue, const ScriptStatement& statement) override {
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
		registerMethod(new ScriptMethodAudioSetListenerPosition(this));
	}
	{
		//
		class ScriptMethodAudioGetListenerOrientationAt: public ScriptMethod {
		private:
			LogicMiniScript* miniScript { nullptr };
		public:
			ScriptMethodAudioGetListenerOrientationAt(LogicMiniScript* miniScript):
				ScriptMethod(
					{},
					ScriptVariableType::TYPE_VECTOR3
				),
				miniScript(miniScript) {}
			const string getMethodName() override {
				return "audio.getListenerOrientationAt";
			}
			void executeMethod(span<ScriptVariable>& argumentValues, ScriptVariable& returnValue, const ScriptStatement& statement) override {
				returnValue.setValue(miniScript->logic->getContext()->getAudio()->getListenerOrientationAt());
			}
			const vector<string>& getContextFunctions() {
				return CONTEXTFUNCTIONS_ENGINE;
			}
		};
		registerMethod(new ScriptMethodAudioGetListenerOrientationAt(this));
	}
	{
		//
		class ScriptMethodAudioSetListenerOrientationAt: public ScriptMethod {
		private:
			LogicMiniScript* miniScript { nullptr };
		public:
			ScriptMethodAudioSetListenerOrientationAt(LogicMiniScript* miniScript):
				ScriptMethod(
					{
						{ .type = ScriptVariableType::TYPE_VECTOR3, .name = "position", .optional = false, .assignBack = false }
					},
					ScriptVariableType::TYPE_NULL
				),
				miniScript(miniScript) {}
			const string getMethodName() override {
				return "audio.setListenerOrientationAt";
			}
			void executeMethod(span<ScriptVariable>& argumentValues, ScriptVariable& returnValue, const ScriptStatement& statement) override {
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
		registerMethod(new ScriptMethodAudioSetListenerOrientationAt(this));
	}
	{
		//
		class ScriptMethodAudioPlaySound: public ScriptMethod {
		private:
			LogicMiniScript* miniScript { nullptr };
		public:
			ScriptMethodAudioPlaySound(LogicMiniScript* miniScript):
				ScriptMethod(
					{
						{ .type = ScriptVariableType::TYPE_STRING, .name = "id", .optional = false, .assignBack = false },
						{ .type = ScriptVariableType::TYPE_INTEGER, .name = "delay", .optional = true, .assignBack = false },
						{ .type = ScriptVariableType::TYPE_INTEGER, .name = "gain", .optional = true, .assignBack = false },
						{ .type = ScriptVariableType::TYPE_INTEGER, .name = "pitch", .optional = true, .assignBack = false },
						{ .type = ScriptVariableType::TYPE_INTEGER, .name = "ignoreIfPlaying", .optional = true, .assignBack = false }
					},
					ScriptVariableType::TYPE_STRING
				),
				miniScript(miniScript) {}
			const string getMethodName() override {
				return "audio.play";
			}
			void executeMethod(span<ScriptVariable>& argumentValues, ScriptVariable& returnValue, const ScriptStatement& statement) override {
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
		registerMethod(new ScriptMethodAudioPlaySound(this));
	}
	{
		//
		class ScriptMethodAudioPlaySoundAtPosition: public ScriptMethod {
		private:
			LogicMiniScript* miniScript { nullptr };
		public:
			ScriptMethodAudioPlaySoundAtPosition(LogicMiniScript* miniScript):
				ScriptMethod(
					{
						{ .type = ScriptVariableType::TYPE_STRING, .name = "id", .optional = false, .assignBack = false },
						{ .type = ScriptVariableType::TYPE_VECTOR3, .name = "position", .optional = false, .assignBack = false },
						{ .type = ScriptVariableType::TYPE_INTEGER, .name = "delay", .optional = true, .assignBack = false },
						{ .type = ScriptVariableType::TYPE_INTEGER, .name = "gain", .optional = true, .assignBack = false },
						{ .type = ScriptVariableType::TYPE_INTEGER, .name = "pitch", .optional = true, .assignBack = false },
						{ .type = ScriptVariableType::TYPE_INTEGER, .name = "ignoreIfPlaying", .optional = true, .assignBack = false }
					},
					ScriptVariableType::TYPE_STRING
				),
				miniScript(miniScript) {}
			const string getMethodName() override {
				return "audio.playAtPosition";
			}
			void executeMethod(span<ScriptVariable>& argumentValues, ScriptVariable& returnValue, const ScriptStatement& statement) override {
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
		registerMethod(new ScriptMethodAudioPlaySoundAtPosition(this));
	}
	{
		//
		class ScriptMethodLogicSignalSend: public ScriptMethod {
		private:
			LogicMiniScript* miniScript { nullptr };
		public:
			ScriptMethodLogicSignalSend(LogicMiniScript* miniScript):
				ScriptMethod({
					{ .type = ScriptVariableType::TYPE_STRING, .name = "logicId", .optional = false, .assignBack = false },
					{ .type = ScriptVariableType::TYPE_STRING, .name = "signal", .optional = false, .assignBack = false }
				}),
				miniScript(miniScript) {}
			const string getMethodName() override {
				return "logic.signal.send";
			}
			void executeMethod(span<ScriptVariable>& argumentValues, ScriptVariable& returnValue, const ScriptStatement& statement) override {
				string logicId;
				string signal;
				if (miniScript->getStringValue(argumentValues, 0, logicId) == true &&
					miniScript->getStringValue(argumentValues, 1, signal) == true) {
					auto logic = static_cast<Logic*>(miniScript->context->getLogic(logicId));
					if (logic == nullptr) {
						Console::println(getMethodName() + "(): " + miniScript->getStatementInformation(statement) + ": no logic with given id: " + logicId);
						miniScript->startErrorScript();
					} else {
						vector<ScriptVariable> arguments(argumentValues.size() - 2);
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
		registerMethod(new ScriptMethodLogicSignalSend(this));
	}
	{
		//
		class ScriptMethodLogicHas: public ScriptMethod {
		private:
			LogicMiniScript* miniScript { nullptr };
		public:
			ScriptMethodLogicHas(LogicMiniScript* miniScript):
				ScriptMethod(
					{
						{ .type = ScriptVariableType::TYPE_STRING, .name = "logicId", .optional = false, .assignBack = false },
						{ .type = ScriptVariableType::TYPE_STRING, .name = "function", .optional = false, .assignBack = false }
					},
					ScriptVariableType::TYPE_BOOLEAN
				),
				miniScript(miniScript) {}
			const string getMethodName() override {
				return "logic.has";
			}
			void executeMethod(span<ScriptVariable>& argumentValues, ScriptVariable& returnValue, const ScriptStatement& statement) override {
				string logicId;
				string function;
				if (MiniScript::getStringValue(argumentValues, 0, logicId) == false ||
					MiniScript::getStringValue(argumentValues, 1, function) == false) {
					Console::println(getMethodName() + "(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation(getMethodName()));
					miniScript->startErrorScript();
				} else {
					auto logic = dynamic_cast<MiniScriptLogic*>(miniScript->context->getLogic(logicId));
					if (logic == nullptr || logic->getMiniScript() == nullptr) {
						returnValue.setValue(false);
					} else {
						auto logicMiniScript = logic->getMiniScript();
						auto scriptIdx = logicMiniScript->getFunctionScriptIdx(function);
						if (scriptIdx == SCRIPTIDX_NONE) {
							returnValue.setValue(false);
						} else {
							returnValue.setValue(true);
						}
					}
				}
			}
			const vector<string>& getContextFunctions() {
				return CONTEXTFUNCTIONS_LOGIC;
			}
		};
		registerMethod(new ScriptMethodLogicHas(this));
	}
	{
		//
		class ScriptMethodLogicCall: public ScriptMethod {
		private:
			LogicMiniScript* miniScript { nullptr };
		public:
			ScriptMethodLogicCall(LogicMiniScript* miniScript):
				ScriptMethod(
					{
						{ .type = ScriptVariableType::TYPE_STRING, .name = "logicId", .optional = false, .assignBack = false },
						{ .type = ScriptVariableType::TYPE_STRING, .name = "function", .optional = false, .assignBack = false }
					},
					ScriptVariableType::TYPE_PSEUDO_MIXED
				),
				miniScript(miniScript) {}
			const string getMethodName() override {
				return "logic.call";
			}
			void executeMethod(span<ScriptVariable>& argumentValues, ScriptVariable& returnValue, const ScriptStatement& statement) override {
				string logicId;
				string function;
				if (MiniScript::getStringValue(argumentValues, 0, logicId) == false ||
					MiniScript::getStringValue(argumentValues, 1, function) == false) {
					Console::println(getMethodName() + "(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation(getMethodName()));
					miniScript->startErrorScript();
				} else {
					auto logic = dynamic_cast<MiniScriptLogic*>(miniScript->context->getLogic(logicId));
					if (logic == nullptr || logic->getMiniScript() == nullptr) {
						Console::println(getMethodName() + "(): " + miniScript->getStatementInformation(statement) + ": no mini script logic with given id: " + logicId);
						miniScript->startErrorScript();
					} else {
						auto logicMiniScript = logic->getMiniScript();
						auto scriptIdx = logicMiniScript->getFunctionScriptIdx(function);
						if (scriptIdx == SCRIPTIDX_NONE) {
							Console::println(getMethodName() + "(): " + miniScript->getStatementInformation(statement) + ": function not found: " + function);
							miniScript->startErrorScript();
						} else {
							#if defined (__APPLE__)
								// MACOSX currently does not support initializing span using begin and end iterators,
								// so we need to make a copy of argumentValues beginning from second element
								vector<ScriptVariable> callArgumentValues;
								for (auto i = 2; i < argumentValues.size(); i++) callArgumentValues.push_back(argumentValues[i]);
								// call
								span callArgumentValuesSpan(callArgumentValues);
								logicMiniScript->call(scriptIdx, callArgumentValuesSpan, returnValue);
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
			const vector<string>& getContextFunctions() {
				return CONTEXTFUNCTIONS_LOGIC;
			}
		};
		registerMethod(new ScriptMethodLogicCall(this));
	}
	{
		//
		class ScriptMethodLogicSignalHas: public ScriptMethod {
		private:
			LogicMiniScript* miniScript { nullptr };
		public:
			ScriptMethodLogicSignalHas(LogicMiniScript* miniScript):
				ScriptMethod({}, ScriptVariableType::TYPE_BOOLEAN),
				miniScript(miniScript) {}
			const string getMethodName() override {
				return "logic.signal.has";
			}
			void executeMethod(span<ScriptVariable>& argumentValues, ScriptVariable& returnValue, const ScriptStatement& statement) override {
				returnValue.setValue(miniScript->logic->hasSignal());
			}
			const vector<string>& getContextFunctions() {
				return CONTEXTFUNCTIONS_ALL;
			}
		};
		registerMethod(new ScriptMethodLogicSignalHas(this));
	}
	{
		//
		class ScriptMethodLogicSignalGetName: public ScriptMethod {
		private:
			LogicMiniScript* miniScript { nullptr };
		public:
			ScriptMethodLogicSignalGetName(LogicMiniScript* miniScript):
				ScriptMethod({}, ScriptVariableType::TYPE_STRING),
				miniScript(miniScript) {}
			const string getMethodName() override {
				return "logic.signal.getName";
			}
			void executeMethod(span<ScriptVariable>& argumentValues, ScriptVariable& returnValue, const ScriptStatement& statement) override {
				returnValue.setValue(miniScript->logic->getSignalName());
			}
			const vector<string>& getContextFunctions() {
				return CONTEXTFUNCTIONS_ALL;
			}
		};
		registerMethod(new ScriptMethodLogicSignalGetName(this));
	}
	{
		//
		class ScriptMethodLogicSignalGetArgument: public ScriptMethod {
		private:
			LogicMiniScript* miniScript { nullptr };
		public:
			ScriptMethodLogicSignalGetArgument(LogicMiniScript* miniScript):
				ScriptMethod(
					{
						{ .type = ScriptVariableType::TYPE_INTEGER, .name = "argumentIndex", .optional = false, .assignBack = false }
					},
					ScriptVariableType::TYPE_PSEUDO_MIXED
				),
				miniScript(miniScript) {}
			const string getMethodName() override {
				return "logic.signal.getArgument";
			}
			void executeMethod(span<ScriptVariable>& argumentValues, ScriptVariable& returnValue, const ScriptStatement& statement) override {
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
		registerMethod(new ScriptMethodLogicSignalGetArgument(this));
	}
	{
		//
		class ScriptMethodLogicSignalNext: public ScriptMethod {
		private:
			LogicMiniScript* miniScript { nullptr };
		public:
			ScriptMethodLogicSignalNext(LogicMiniScript* miniScript):
				ScriptMethod(),
				miniScript(miniScript) {}
			const string getMethodName() override {
				return "logic.signal.next";
			}
			void executeMethod(span<ScriptVariable>& argumentValues, ScriptVariable& returnValue, const ScriptStatement& statement) override {
				miniScript->logic->removeSignal();
			}
			const vector<string>& getContextFunctions() {
				return CONTEXTFUNCTIONS_ALL;
			}
		};
		registerMethod(new ScriptMethodLogicSignalNext(this));
	}
	// keyboard input
	{
		//
		class ScriptMethodInputKeyboardKEYCODE_LEFT: public ScriptMethod {
		private:
			LogicMiniScript* miniScript { nullptr };
		public:
			ScriptMethodInputKeyboardKEYCODE_LEFT(LogicMiniScript* miniScript):
				ScriptMethod({}, ScriptVariableType::TYPE_INTEGER),
				miniScript(miniScript) {}
			const string getMethodName() override {
				return "input.keyboard.KEYCODE_LEFT";
			}
			void executeMethod(span<ScriptVariable>& argumentValues, ScriptVariable& returnValue, const ScriptStatement& statement) override {
				returnValue = static_cast<int64_t>(GUIKeyboardEvent::KEYCODE_LEFT);
			}
			const vector<string>& getContextFunctions() {
				return CONTEXTFUNCTIONS_ALL;
			}
		};
		registerMethod(new ScriptMethodInputKeyboardKEYCODE_LEFT(this));
	}
	{
		//
		class ScriptMethodInputKeyboardKEYCODE_RIGHT: public ScriptMethod {
		private:
			LogicMiniScript* miniScript { nullptr };
		public:
			ScriptMethodInputKeyboardKEYCODE_RIGHT(LogicMiniScript* miniScript):
				ScriptMethod({}, ScriptVariableType::TYPE_INTEGER),
				miniScript(miniScript) {}
			const string getMethodName() override {
				return "input.keyboard.KEYCODE_RIGHT";
			}
			void executeMethod(span<ScriptVariable>& argumentValues, ScriptVariable& returnValue, const ScriptStatement& statement) override {
				returnValue = static_cast<int64_t>(GUIKeyboardEvent::KEYCODE_RIGHT);
			}
			const vector<string>& getContextFunctions() {
				return CONTEXTFUNCTIONS_ALL;
			}
		};
		registerMethod(new ScriptMethodInputKeyboardKEYCODE_RIGHT(this));
	}
	{
		//
		class ScriptMethodInputKeyboardKEYCODE_UP: public ScriptMethod {
		private:
			LogicMiniScript* miniScript { nullptr };
		public:
			ScriptMethodInputKeyboardKEYCODE_UP(LogicMiniScript* miniScript):
				ScriptMethod({}, ScriptVariableType::TYPE_INTEGER),
				miniScript(miniScript) {}
			const string getMethodName() override {
				return "input.keyboard.KEYCODE_UP";
			}
			void executeMethod(span<ScriptVariable>& argumentValues, ScriptVariable& returnValue, const ScriptStatement& statement) override {
				returnValue = static_cast<int64_t>(GUIKeyboardEvent::KEYCODE_UP);
			}
			const vector<string>& getContextFunctions() {
				return CONTEXTFUNCTIONS_ALL;
			}
		};
		registerMethod(new ScriptMethodInputKeyboardKEYCODE_UP(this));
	}
	{
		//
		class ScriptMethodInputKeyboardKEYCODE_DOWN: public ScriptMethod {
		private:
			LogicMiniScript* miniScript { nullptr };
		public:
			ScriptMethodInputKeyboardKEYCODE_DOWN(LogicMiniScript* miniScript):
				ScriptMethod({}, ScriptVariableType::TYPE_INTEGER),
				miniScript(miniScript) {}
			const string getMethodName() override {
				return "input.keyboard.KEYCODE_DOWN";
			}
			void executeMethod(span<ScriptVariable>& argumentValues, ScriptVariable& returnValue, const ScriptStatement& statement) override {
				returnValue = static_cast<int64_t>(GUIKeyboardEvent::KEYCODE_DOWN);
			}
			const vector<string>& getContextFunctions() {
				return CONTEXTFUNCTIONS_ALL;
			}
		};
		registerMethod(new ScriptMethodInputKeyboardKEYCODE_DOWN(this));
	}
	{
		//
		class ScriptMethodInputKeyboardKEYCODE_POS1: public ScriptMethod {
		private:
			LogicMiniScript* miniScript { nullptr };
		public:
			ScriptMethodInputKeyboardKEYCODE_POS1(LogicMiniScript* miniScript):
				ScriptMethod({}, ScriptVariableType::TYPE_INTEGER),
				miniScript(miniScript) {}
			const string getMethodName() override {
				return "input.keyboard.KEYCODE_POS1";
			}
			void executeMethod(span<ScriptVariable>& argumentValues, ScriptVariable& returnValue, const ScriptStatement& statement) override {
				returnValue = static_cast<int64_t>(GUIKeyboardEvent::KEYCODE_POS1);
			}
			const vector<string>& getContextFunctions() {
				return CONTEXTFUNCTIONS_ALL;
			}
		};
		registerMethod(new ScriptMethodInputKeyboardKEYCODE_POS1(this));
	}
	{
		//
		class ScriptMethodInputKeyboardKEYCODE_END: public ScriptMethod {
		private:
			LogicMiniScript* miniScript { nullptr };
		public:
			ScriptMethodInputKeyboardKEYCODE_END(LogicMiniScript* miniScript):
				ScriptMethod({}, ScriptVariableType::TYPE_INTEGER),
				miniScript(miniScript) {}
			const string getMethodName() override {
				return "input.keyboard.KEYCODE_END";
			}
			void executeMethod(span<ScriptVariable>& argumentValues, ScriptVariable& returnValue, const ScriptStatement& statement) override {
				returnValue = static_cast<int64_t>(GUIKeyboardEvent::KEYCODE_END);
			}
			const vector<string>& getContextFunctions() {
				return CONTEXTFUNCTIONS_ALL;
			}
		};
		registerMethod(new ScriptMethodInputKeyboardKEYCODE_END(this));
	}
	{
		//
		class ScriptMethodInputKeyboardKEYCODE_PAGEUP: public ScriptMethod {
		private:
			LogicMiniScript* miniScript { nullptr };
		public:
			ScriptMethodInputKeyboardKEYCODE_PAGEUP(LogicMiniScript* miniScript):
				ScriptMethod({}, ScriptVariableType::TYPE_INTEGER),
				miniScript(miniScript) {}
			const string getMethodName() override {
				return "input.keyboard.KEYCODE_PAGEUP";
			}
			void executeMethod(span<ScriptVariable>& argumentValues, ScriptVariable& returnValue, const ScriptStatement& statement) override {
				returnValue = static_cast<int64_t>(GUIKeyboardEvent::KEYCODE_PAGE_UP);
			}
			const vector<string>& getContextFunctions() {
				return CONTEXTFUNCTIONS_ALL;
			}
		};
		registerMethod(new ScriptMethodInputKeyboardKEYCODE_PAGEUP(this));
	}
	{
		//
		class ScriptMethodInputKeyboardKEYCODE_PAGEDOWN: public ScriptMethod {
		private:
			LogicMiniScript* miniScript { nullptr };
		public:
			ScriptMethodInputKeyboardKEYCODE_PAGEDOWN(LogicMiniScript* miniScript):
				ScriptMethod({}, ScriptVariableType::TYPE_INTEGER),
				miniScript(miniScript) {}
			const string getMethodName() override {
				return "input.keyboard.KEYCODE_PAGEDOWN";
			}
			void executeMethod(span<ScriptVariable>& argumentValues, ScriptVariable& returnValue, const ScriptStatement& statement) override {
				returnValue = static_cast<int64_t>(GUIKeyboardEvent::KEYCODE_PAGE_DOWN);
			}
			const vector<string>& getContextFunctions() {
				return CONTEXTFUNCTIONS_ALL;
			}
		};
		registerMethod(new ScriptMethodInputKeyboardKEYCODE_PAGEDOWN(this));
	}
	{
		//
		class ScriptMethodInputKeyboardKEYCODE_BACKSPACE: public ScriptMethod {
		private:
			LogicMiniScript* miniScript { nullptr };
		public:
			ScriptMethodInputKeyboardKEYCODE_BACKSPACE(LogicMiniScript* miniScript):
				ScriptMethod({}, ScriptVariableType::TYPE_INTEGER),
				miniScript(miniScript) {}
			const string getMethodName() override {
				return "input.keyboard.KEYCODE_BACKSPACE";
			}
			void executeMethod(span<ScriptVariable>& argumentValues, ScriptVariable& returnValue, const ScriptStatement& statement) override {
				returnValue = static_cast<int64_t>(GUIKeyboardEvent::KEYCODE_BACKSPACE);
			}
			const vector<string>& getContextFunctions() {
				return CONTEXTFUNCTIONS_ALL;
			}
		};
		registerMethod(new ScriptMethodInputKeyboardKEYCODE_BACKSPACE(this));
	}
	{
		//
		class ScriptMethodInputKeyboardKEYCODE_DELETE: public ScriptMethod {
		private:
			LogicMiniScript* miniScript { nullptr };
		public:
			ScriptMethodInputKeyboardKEYCODE_DELETE(LogicMiniScript* miniScript):
				ScriptMethod({}, ScriptVariableType::TYPE_INTEGER),
				miniScript(miniScript) {}
			const string getMethodName() override {
				return "input.keyboard.KEYCODE_DELETE";
			}
			void executeMethod(span<ScriptVariable>& argumentValues, ScriptVariable& returnValue, const ScriptStatement& statement) override {
				returnValue = static_cast<int64_t>(GUIKeyboardEvent::KEYCODE_DELETE);
			}
			const vector<string>& getContextFunctions() {
				return CONTEXTFUNCTIONS_ALL;
			}
		};
		registerMethod(new ScriptMethodInputKeyboardKEYCODE_DELETE(this));
	}
	{
		//
		class ScriptMethodInputKeyboardKEYCODE_SPACE: public ScriptMethod {
		private:
			LogicMiniScript* miniScript { nullptr };
		public:
			ScriptMethodInputKeyboardKEYCODE_SPACE(LogicMiniScript* miniScript):
				ScriptMethod({}, ScriptVariableType::TYPE_INTEGER),
				miniScript(miniScript) {}
			const string getMethodName() override {
				return "input.keyboard.KEYCODE_SPACE";
			}
			void executeMethod(span<ScriptVariable>& argumentValues, ScriptVariable& returnValue, const ScriptStatement& statement) override {
				returnValue = static_cast<int64_t>(GUIKeyboardEvent::KEYCODE_SPACE);
			}
			const vector<string>& getContextFunctions() {
				return CONTEXTFUNCTIONS_ALL;
			}
		};
		registerMethod(new ScriptMethodInputKeyboardKEYCODE_SPACE(this));
	}
	{
		//
		class ScriptMethodInputKeyboardKEYCODE_RETURN: public ScriptMethod {
		private:
			LogicMiniScript* miniScript { nullptr };
		public:
			ScriptMethodInputKeyboardKEYCODE_RETURN(LogicMiniScript* miniScript):
				ScriptMethod({}, ScriptVariableType::TYPE_INTEGER),
				miniScript(miniScript) {}
			const string getMethodName() override {
				return "input.keyboard.KEYCODE_RETURN";
			}
			void executeMethod(span<ScriptVariable>& argumentValues, ScriptVariable& returnValue, const ScriptStatement& statement) override {
				returnValue = static_cast<int64_t>(GUIKeyboardEvent::KEYCODE_RETURN);
			}
			const vector<string>& getContextFunctions() {
				return CONTEXTFUNCTIONS_ALL;
			}
		};
		registerMethod(new ScriptMethodInputKeyboardKEYCODE_RETURN(this));
	}
	{
		//
		class ScriptMethodInputKeyboardKEYCODE_ESCAPE: public ScriptMethod {
		private:
			LogicMiniScript* miniScript { nullptr };
		public:
			ScriptMethodInputKeyboardKEYCODE_ESCAPE(LogicMiniScript* miniScript):
				ScriptMethod({}, ScriptVariableType::TYPE_INTEGER),
				miniScript(miniScript) {}
			const string getMethodName() override {
				return "input.keyboard.KEYCODE_ESCAPE";
			}
			void executeMethod(span<ScriptVariable>& argumentValues, ScriptVariable& returnValue, const ScriptStatement& statement) override {
				returnValue = static_cast<int64_t>(GUIKeyboardEvent::KEYCODE_ESCAPE);
			}
			const vector<string>& getContextFunctions() {
				return CONTEXTFUNCTIONS_ALL;
			}
		};
		registerMethod(new ScriptMethodInputKeyboardKEYCODE_ESCAPE(this));
	}
	{
		//
		class ScriptMethodInputKeyboardKEYCODE_F1: public ScriptMethod {
		private:
			LogicMiniScript* miniScript { nullptr };
		public:
			ScriptMethodInputKeyboardKEYCODE_F1(LogicMiniScript* miniScript):
				ScriptMethod({}, ScriptVariableType::TYPE_INTEGER),
				miniScript(miniScript) {}
			const string getMethodName() override {
				return "input.keyboard.KEYCODE_F1";
			}
			void executeMethod(span<ScriptVariable>& argumentValues, ScriptVariable& returnValue, const ScriptStatement& statement) override {
				returnValue = static_cast<int64_t>(GUIKeyboardEvent::KEYCODE_F1);
			}
			const vector<string>& getContextFunctions() {
				return CONTEXTFUNCTIONS_ALL;
			}
		};
		registerMethod(new ScriptMethodInputKeyboardKEYCODE_F1(this));
	}
	{
		//
		class ScriptMethodInputKeyboardKEYCODE_F2: public ScriptMethod {
		private:
			LogicMiniScript* miniScript { nullptr };
		public:
			ScriptMethodInputKeyboardKEYCODE_F2(LogicMiniScript* miniScript):
				ScriptMethod({}, ScriptVariableType::TYPE_INTEGER),
				miniScript(miniScript) {}
			const string getMethodName() override {
				return "input.keyboard.KEYCODE_F2";
			}
			void executeMethod(span<ScriptVariable>& argumentValues, ScriptVariable& returnValue, const ScriptStatement& statement) override {
				returnValue = static_cast<int64_t>(GUIKeyboardEvent::KEYCODE_F2);
			}
			const vector<string>& getContextFunctions() {
				return CONTEXTFUNCTIONS_ALL;
			}
		};
		registerMethod(new ScriptMethodInputKeyboardKEYCODE_F2(this));
	}
	{
		//
		class ScriptMethodInputKeyboardKEYCODE_F3: public ScriptMethod {
		private:
			LogicMiniScript* miniScript { nullptr };
		public:
			ScriptMethodInputKeyboardKEYCODE_F3(LogicMiniScript* miniScript):
				ScriptMethod({}, ScriptVariableType::TYPE_INTEGER),
				miniScript(miniScript) {}
			const string getMethodName() override {
				return "input.keyboard.KEYCODE_F3";
			}
			void executeMethod(span<ScriptVariable>& argumentValues, ScriptVariable& returnValue, const ScriptStatement& statement) override {
				returnValue = static_cast<int64_t>(GUIKeyboardEvent::KEYCODE_F3);
			}
			const vector<string>& getContextFunctions() {
				return CONTEXTFUNCTIONS_ALL;
			}
		};
		registerMethod(new ScriptMethodInputKeyboardKEYCODE_F3(this));
	}
	{
		//
		class ScriptMethodInputKeyboardKEYCODE_F4: public ScriptMethod {
		private:
			LogicMiniScript* miniScript { nullptr };
		public:
			ScriptMethodInputKeyboardKEYCODE_F4(LogicMiniScript* miniScript):
				ScriptMethod({}, ScriptVariableType::TYPE_INTEGER),
				miniScript(miniScript) {}
			const string getMethodName() override {
				return "input.keyboard.KEYCODE_F4";
			}
			void executeMethod(span<ScriptVariable>& argumentValues, ScriptVariable& returnValue, const ScriptStatement& statement) override {
				returnValue = static_cast<int64_t>(GUIKeyboardEvent::KEYCODE_F4);
			}
			const vector<string>& getContextFunctions() {
				return CONTEXTFUNCTIONS_ALL;
			}
		};
		registerMethod(new ScriptMethodInputKeyboardKEYCODE_F4(this));
	}
	{
		//
		class ScriptMethodInputKeyboardKEYCODE_F5: public ScriptMethod {
		private:
			LogicMiniScript* miniScript { nullptr };
		public:
			ScriptMethodInputKeyboardKEYCODE_F5(LogicMiniScript* miniScript):
				ScriptMethod({}, ScriptVariableType::TYPE_INTEGER),
				miniScript(miniScript) {}
			const string getMethodName() override {
				return "input.keyboard.KEYCODE_F5";
			}
			void executeMethod(span<ScriptVariable>& argumentValues, ScriptVariable& returnValue, const ScriptStatement& statement) override {
				returnValue = static_cast<int64_t>(GUIKeyboardEvent::KEYCODE_F5);
			}
			const vector<string>& getContextFunctions() {
				return CONTEXTFUNCTIONS_ALL;
			}
		};
		registerMethod(new ScriptMethodInputKeyboardKEYCODE_F5(this));
	}
	{
		//
		class ScriptMethodInputKeyboardKEYCODE_F6: public ScriptMethod {
		private:
			LogicMiniScript* miniScript { nullptr };
		public:
			ScriptMethodInputKeyboardKEYCODE_F6(LogicMiniScript* miniScript):
				ScriptMethod({}, ScriptVariableType::TYPE_INTEGER),
				miniScript(miniScript) {}
			const string getMethodName() override {
				return "input.keyboard.KEYCODE_F6";
			}
			void executeMethod(span<ScriptVariable>& argumentValues, ScriptVariable& returnValue, const ScriptStatement& statement) override {
				returnValue = static_cast<int64_t>(GUIKeyboardEvent::KEYCODE_F6);
			}
			const vector<string>& getContextFunctions() {
				return CONTEXTFUNCTIONS_ALL;
			}
		};
		registerMethod(new ScriptMethodInputKeyboardKEYCODE_F6(this));
	}
	{
		//
		class ScriptMethodInputKeyboardKEYCODE_F7: public ScriptMethod {
		private:
			LogicMiniScript* miniScript { nullptr };
		public:
			ScriptMethodInputKeyboardKEYCODE_F7(LogicMiniScript* miniScript):
				ScriptMethod({}, ScriptVariableType::TYPE_INTEGER),
				miniScript(miniScript) {}
			const string getMethodName() override {
				return "input.keyboard.KEYCODE_F7";
			}
			void executeMethod(span<ScriptVariable>& argumentValues, ScriptVariable& returnValue, const ScriptStatement& statement) override {
				returnValue = static_cast<int64_t>(GUIKeyboardEvent::KEYCODE_F7);
			}
			const vector<string>& getContextFunctions() {
				return CONTEXTFUNCTIONS_ALL;
			}
		};
		registerMethod(new ScriptMethodInputKeyboardKEYCODE_F7(this));
	}
	{
		//
		class ScriptMethodInputKeyboardKEYCODE_F8: public ScriptMethod {
		private:
			LogicMiniScript* miniScript { nullptr };
		public:
			ScriptMethodInputKeyboardKEYCODE_F8(LogicMiniScript* miniScript):
				ScriptMethod({}, ScriptVariableType::TYPE_INTEGER),
				miniScript(miniScript) {}
			const string getMethodName() override {
				return "input.keyboard.KEYCODE_F8";
			}
			void executeMethod(span<ScriptVariable>& argumentValues, ScriptVariable& returnValue, const ScriptStatement& statement) override {
				returnValue = static_cast<int64_t>(GUIKeyboardEvent::KEYCODE_F8);
			}
			const vector<string>& getContextFunctions() {
				return CONTEXTFUNCTIONS_ALL;
			}
		};
		registerMethod(new ScriptMethodInputKeyboardKEYCODE_F8(this));
	}
	{
		//
		class ScriptMethodInputKeyboardKEYCODE_F9: public ScriptMethod {
		private:
			LogicMiniScript* miniScript { nullptr };
		public:
			ScriptMethodInputKeyboardKEYCODE_F9(LogicMiniScript* miniScript):
				ScriptMethod({}, ScriptVariableType::TYPE_INTEGER),
				miniScript(miniScript) {}
			const string getMethodName() override {
				return "input.keyboard.KEYCODE_F9";
			}
			void executeMethod(span<ScriptVariable>& argumentValues, ScriptVariable& returnValue, const ScriptStatement& statement) override {
				returnValue = static_cast<int64_t>(GUIKeyboardEvent::KEYCODE_F9);
			}
			const vector<string>& getContextFunctions() {
				return CONTEXTFUNCTIONS_ALL;
			}
		};
		registerMethod(new ScriptMethodInputKeyboardKEYCODE_F9(this));
	}
	{
		//
		class ScriptMethodInputKeyboardKEYCODE_F10: public ScriptMethod {
		private:
			LogicMiniScript* miniScript { nullptr };
		public:
			ScriptMethodInputKeyboardKEYCODE_F10(LogicMiniScript* miniScript):
				ScriptMethod({}, ScriptVariableType::TYPE_INTEGER),
				miniScript(miniScript) {}
			const string getMethodName() override {
				return "input.keyboard.KEYCODE_F10";
			}
			void executeMethod(span<ScriptVariable>& argumentValues, ScriptVariable& returnValue, const ScriptStatement& statement) override {
				returnValue = static_cast<int64_t>(GUIKeyboardEvent::KEYCODE_F10);
			}
			const vector<string>& getContextFunctions() {
				return CONTEXTFUNCTIONS_ALL;
			}
		};
		registerMethod(new ScriptMethodInputKeyboardKEYCODE_F10(this));
	}
	{
		//
		class ScriptMethodInputKeyboardKEYCODE_F11: public ScriptMethod {
		private:
			LogicMiniScript* miniScript { nullptr };
		public:
			ScriptMethodInputKeyboardKEYCODE_F11(LogicMiniScript* miniScript):
				ScriptMethod({}, ScriptVariableType::TYPE_INTEGER),
				miniScript(miniScript) {}
			const string getMethodName() override {
				return "input.keyboard.KEYCODE_F11";
			}
			void executeMethod(span<ScriptVariable>& argumentValues, ScriptVariable& returnValue, const ScriptStatement& statement) override {
				returnValue = static_cast<int64_t>(GUIKeyboardEvent::KEYCODE_F11);
			}
			const vector<string>& getContextFunctions() {
				return CONTEXTFUNCTIONS_ALL;
			}
		};
		registerMethod(new ScriptMethodInputKeyboardKEYCODE_F11(this));
	}
	{
		//
		class ScriptMethodInputKeyboardKEYCODE_F12: public ScriptMethod {
		private:
			LogicMiniScript* miniScript { nullptr };
		public:
			ScriptMethodInputKeyboardKEYCODE_F12(LogicMiniScript* miniScript):
				ScriptMethod({}, ScriptVariableType::TYPE_INTEGER),
				miniScript(miniScript) {}
			const string getMethodName() override {
				return "input.keyboard.KEYCODE_F12";
			}
			void executeMethod(span<ScriptVariable>& argumentValues, ScriptVariable& returnValue, const ScriptStatement& statement) override {
				returnValue = static_cast<int64_t>(GUIKeyboardEvent::KEYCODE_F12);
			}
			const vector<string>& getContextFunctions() {
				return CONTEXTFUNCTIONS_ALL;
			}
		};
		registerMethod(new ScriptMethodInputKeyboardKEYCODE_F12(this));
	}
	{
		//
		class ScriptMethodInputKeyboardIsKeyDown: public ScriptMethod {
		private:
			LogicMiniScript* miniScript { nullptr };
		public:
			ScriptMethodInputKeyboardIsKeyDown(LogicMiniScript* miniScript):
				ScriptMethod(
					{
						{ .type = ScriptVariableType::TYPE_INTEGER, .name = "keyCode", .optional = false, .assignBack = false }
					},
					ScriptVariableType::TYPE_BOOLEAN
				),
				miniScript(miniScript) {}
			const string getMethodName() override {
				return "input.keyboard.isKeyDown";
			}
			void executeMethod(span<ScriptVariable>& argumentValues, ScriptVariable& returnValue, const ScriptStatement& statement) override {
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
		registerMethod(new ScriptMethodInputKeyboardIsKeyDown(this));
	}
	{
		//
		class ScriptMethodInputKeyboardIsCharDown: public ScriptMethod {
		private:
			LogicMiniScript* miniScript { nullptr };
		public:
			ScriptMethodInputKeyboardIsCharDown(LogicMiniScript* miniScript):
				ScriptMethod(
					{
						{ .type = ScriptVariableType::TYPE_STRING, .name = "charAsString", .optional = false, .assignBack = false }
					},
					ScriptVariableType::TYPE_BOOLEAN
				),
				miniScript(miniScript) {}
			const string getMethodName() override {
				return "input.keyboard.isCharDown";
			}
			void executeMethod(span<ScriptVariable>& argumentValues, ScriptVariable& returnValue, const ScriptStatement& statement) override {
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
		registerMethod(new ScriptMethodInputKeyboardIsCharDown(this));
	}
	{
		//
		class ScriptMethodInputKeyboardGetTypedString: public ScriptMethod {
		private:
			LogicMiniScript* miniScript { nullptr };
		public:
			ScriptMethodInputKeyboardGetTypedString(LogicMiniScript* miniScript):
				ScriptMethod({}, ScriptVariableType::TYPE_STRING),
				miniScript(miniScript) {}
			const string getMethodName() override {
				return "input.keyboard.getTypedString";
			}
			void executeMethod(span<ScriptVariable>& argumentValues, ScriptVariable& returnValue, const ScriptStatement& statement) override {
				returnValue = miniScript->keyboardTypedChars;
			}
			const vector<string>& getContextFunctions() {
				return CONTEXTFUNCTIONS_ALL;
			}
		};
		registerMethod(new ScriptMethodInputKeyboardGetTypedString(this));
	}
	{
		//
		class ScriptMethodInputKeyboardIsControlDown: public ScriptMethod {
		private:
			LogicMiniScript* miniScript { nullptr };
		public:
			ScriptMethodInputKeyboardIsControlDown(LogicMiniScript* miniScript):
				ScriptMethod({}, ScriptVariableType::TYPE_BOOLEAN),
				miniScript(miniScript) {}
			const string getMethodName() override {
				return "input.keyboard.isControlDown";
			}
			void executeMethod(span<ScriptVariable>& argumentValues, ScriptVariable& returnValue, const ScriptStatement& statement) override {
				returnValue = miniScript->keyboardControlDown == true;
			}
			const vector<string>& getContextFunctions() {
				return CONTEXTFUNCTIONS_ALL;
			}
		};
		registerMethod(new ScriptMethodInputKeyboardIsControlDown(this));
	}
	{
		//
		class ScriptMethodInputKeyboardIsMetaDown: public ScriptMethod {
		private:
			LogicMiniScript* miniScript { nullptr };
		public:
			ScriptMethodInputKeyboardIsMetaDown(LogicMiniScript* miniScript):
				ScriptMethod({}, ScriptVariableType::TYPE_BOOLEAN),
				miniScript(miniScript) {}
			const string getMethodName() override {
				return "input.keyboard.isMetaDown";
			}
			void executeMethod(span<ScriptVariable>& argumentValues, ScriptVariable& returnValue, const ScriptStatement& statement) override {
				returnValue = miniScript->keyboardControlDown == true;
			}
			const vector<string>& getContextFunctions() {
				return CONTEXTFUNCTIONS_ALL;
			}
		};
		registerMethod(new ScriptMethodInputKeyboardIsMetaDown(this));
	}
	{
		//
		class ScriptMethodInputKeyboardIsAltDown: public ScriptMethod {
		private:
			LogicMiniScript* miniScript { nullptr };
		public:
			ScriptMethodInputKeyboardIsAltDown(LogicMiniScript* miniScript):
				ScriptMethod({}, ScriptVariableType::TYPE_BOOLEAN),
				miniScript(miniScript) {}
			const string getMethodName() override {
				return "input.keyboard.isAltDown";
			}
			void executeMethod(span<ScriptVariable>& argumentValues, ScriptVariable& returnValue, const ScriptStatement& statement) override {
				returnValue = miniScript->keyboardAltDown == true;
			}
			const vector<string>& getContextFunctions() {
				return CONTEXTFUNCTIONS_ALL;
			}
		};
		registerMethod(new ScriptMethodInputKeyboardIsAltDown(this));
	}
	{
		//
		class ScriptMethodInputKeyboardIsShiftDown: public ScriptMethod {
		private:
			LogicMiniScript* miniScript { nullptr };
		public:
			ScriptMethodInputKeyboardIsShiftDown(LogicMiniScript* miniScript):
				ScriptMethod({}, ScriptVariableType::TYPE_BOOLEAN),
				miniScript(miniScript) {}
			const string getMethodName() override {
				return "input.keyboard.isShiftDown";
			}
			void executeMethod(span<ScriptVariable>& argumentValues, ScriptVariable& returnValue, const ScriptStatement& statement) override {
				returnValue = miniScript->keyboardShiftDown == true;
			}
			const vector<string>& getContextFunctions() {
				return CONTEXTFUNCTIONS_ALL;
			}
		};
		registerMethod(new ScriptMethodInputKeyboardIsShiftDown(this));
	}
	// mouse input
	{
		//
		class ScriptMethodInputMouseBUTTON_LEFT: public ScriptMethod {
		private:
			LogicMiniScript* miniScript { nullptr };
		public:
			ScriptMethodInputMouseBUTTON_LEFT(LogicMiniScript* miniScript):
				ScriptMethod({}, ScriptVariableType::TYPE_INTEGER),
				miniScript(miniScript) {}
			const string getMethodName() override {
				return "input.mouse.BUTTON_LEFT";
			}
			void executeMethod(span<ScriptVariable>& argumentValues, ScriptVariable& returnValue, const ScriptStatement& statement) override {
				returnValue = static_cast<int64_t>(GUIMouseEvent::MOUSEEVENT_BUTTON_LEFT - 1);
			}
			const vector<string>& getContextFunctions() {
				return CONTEXTFUNCTIONS_ALL;
			}
		};
		registerMethod(new ScriptMethodInputMouseBUTTON_LEFT(this));
	}
	{
		//
		class ScriptMethodInputMouseBUTTON_MIDDLE: public ScriptMethod {
		private:
			LogicMiniScript* miniScript { nullptr };
		public:
			ScriptMethodInputMouseBUTTON_MIDDLE(LogicMiniScript* miniScript):
				ScriptMethod({}, ScriptVariableType::TYPE_INTEGER),
				miniScript(miniScript) {}
			const string getMethodName() override {
				return "input.mouse.BUTTON_MIDDLE";
			}
			void executeMethod(span<ScriptVariable>& argumentValues, ScriptVariable& returnValue, const ScriptStatement& statement) override {
				returnValue = static_cast<int64_t>(GUIMouseEvent::MOUSEEVENT_BUTTON_MIDDLE - 1);
			}
			const vector<string>& getContextFunctions() {
				return CONTEXTFUNCTIONS_ALL;
			}
		};
		registerMethod(new ScriptMethodInputMouseBUTTON_MIDDLE(this));
	}
	{
		//
		class ScriptMethodInputMouseBUTTON_RIGHT: public ScriptMethod {
		private:
			LogicMiniScript* miniScript { nullptr };
		public:
			ScriptMethodInputMouseBUTTON_RIGHT(LogicMiniScript* miniScript):
				ScriptMethod({}, ScriptVariableType::TYPE_INTEGER),
				miniScript(miniScript) {}
			const string getMethodName() override {
				return "input.mouse.BUTTON_RIGHT";
			}
			void executeMethod(span<ScriptVariable>& argumentValues, ScriptVariable& returnValue, const ScriptStatement& statement) override {
				returnValue = static_cast<int64_t>(GUIMouseEvent::MOUSEEVENT_BUTTON_RIGHT - 1);
			}
			const vector<string>& getContextFunctions() {
				return CONTEXTFUNCTIONS_ALL;
			}
		};
		registerMethod(new ScriptMethodInputMouseBUTTON_RIGHT(this));
	}
	{
		//
		class ScriptMethodInputMouseIsButtonDown: public ScriptMethod {
		private:
			LogicMiniScript* miniScript { nullptr };
		public:
			ScriptMethodInputMouseIsButtonDown(LogicMiniScript* miniScript):
				ScriptMethod(
					{
						{ .type = ScriptVariableType::TYPE_INTEGER, .name = "button", .optional = false, .assignBack = false }
					},
					ScriptVariableType::TYPE_BOOLEAN),
				miniScript(miniScript) {}
			const string getMethodName() override {
				return "input.mouse.isButtonDown";
			}
			void executeMethod(span<ScriptVariable>& argumentValues, ScriptVariable& returnValue, const ScriptStatement& statement) override {
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
		registerMethod(new ScriptMethodInputMouseIsButtonDown(this));
	}
	{
		//
		class ScriptMethodInputMouseIsButtonUp: public ScriptMethod {
		private:
			LogicMiniScript* miniScript { nullptr };
		public:
			ScriptMethodInputMouseIsButtonUp(LogicMiniScript* miniScript):
				ScriptMethod(
					{
						{ .type = ScriptVariableType::TYPE_INTEGER, .name = "button", .optional = false, .assignBack = false }
					},
					ScriptVariableType::TYPE_BOOLEAN),
				miniScript(miniScript) {}
			const string getMethodName() override {
				return "input.mouse.isButtonUp";
			}
			void executeMethod(span<ScriptVariable>& argumentValues, ScriptVariable& returnValue, const ScriptStatement& statement) override {
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
		registerMethod(new ScriptMethodInputMouseIsButtonUp(this));
	}
	{
		//
		class ScriptMethodInputMouseIsDragging: public ScriptMethod {
		private:
			LogicMiniScript* miniScript { nullptr };
		public:
			ScriptMethodInputMouseIsDragging(LogicMiniScript* miniScript):
				ScriptMethod(
					{
						{ .type = ScriptVariableType::TYPE_INTEGER, .name = "button", .optional = false, .assignBack = false }
					},
					ScriptVariableType::TYPE_BOOLEAN),
				miniScript(miniScript) {}
			const string getMethodName() override {
				return "input.mouse.isDragging";
			}
			void executeMethod(span<ScriptVariable>& argumentValues, ScriptVariable& returnValue, const ScriptStatement& statement) override {
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
		registerMethod(new ScriptMethodInputMouseIsDragging(this));
	}
	{
		//
		class ScriptMethodInputMouseHasMoved: public ScriptMethod {
		private:
			LogicMiniScript* miniScript { nullptr };
		public:
			ScriptMethodInputMouseHasMoved(LogicMiniScript* miniScript):
				ScriptMethod({}, ScriptVariableType::TYPE_BOOLEAN),
				miniScript(miniScript) {}
			const string getMethodName() override {
				return "input.mouse.hasMoved";
			}
			void executeMethod(span<ScriptVariable>& argumentValues, ScriptVariable& returnValue, const ScriptStatement& statement) override {
				returnValue = miniScript->mouseMoved;
			}
			const vector<string>& getContextFunctions() {
				return CONTEXTFUNCTIONS_ALL;
			}
		};
		registerMethod(new ScriptMethodInputMouseHasMoved(this));
	}
	{
		//
		class ScriptMethodInputMouseGetX: public ScriptMethod {
		private:
			LogicMiniScript* miniScript { nullptr };
		public:
			ScriptMethodInputMouseGetX(LogicMiniScript* miniScript):
				ScriptMethod({}, ScriptVariableType::TYPE_INTEGER),
				miniScript(miniScript) {}
			const string getMethodName() override {
				return "input.mouse.getX";
			}
			void executeMethod(span<ScriptVariable>& argumentValues, ScriptVariable& returnValue, const ScriptStatement& statement) override {
				returnValue = static_cast<int64_t>(miniScript->mouseX);
			}
			const vector<string>& getContextFunctions() {
				return CONTEXTFUNCTIONS_ALL;
			}
		};
		registerMethod(new ScriptMethodInputMouseGetX(this));
	}
	{
		//
		class ScriptMethodInputMouseGetXUnscaled: public ScriptMethod {
		private:
			LogicMiniScript* miniScript { nullptr };
		public:
			ScriptMethodInputMouseGetXUnscaled(LogicMiniScript* miniScript):
				ScriptMethod({}, ScriptVariableType::TYPE_INTEGER),
				miniScript(miniScript) {}
			const string getMethodName() override {
				return "input.mouse.getXUnscaled";
			}
			void executeMethod(span<ScriptVariable>& argumentValues, ScriptVariable& returnValue, const ScriptStatement& statement) override {
				returnValue = static_cast<int64_t>(miniScript->mouseXUnscaled);
			}
			const vector<string>& getContextFunctions() {
				return CONTEXTFUNCTIONS_ALL;
			}
		};
		registerMethod(new ScriptMethodInputMouseGetXUnscaled(this));
	}
	{
		//
		class ScriptMethodInputMouseGetY: public ScriptMethod {
		private:
			LogicMiniScript* miniScript { nullptr };
		public:
			ScriptMethodInputMouseGetY(LogicMiniScript* miniScript):
				ScriptMethod({}, ScriptVariableType::TYPE_INTEGER),
				miniScript(miniScript) {}
			const string getMethodName() override {
				return "input.mouse.getY";
			}
			void executeMethod(span<ScriptVariable>& argumentValues, ScriptVariable& returnValue, const ScriptStatement& statement) override {
				returnValue = static_cast<int64_t>(miniScript->mouseY);
			}
			const vector<string>& getContextFunctions() {
				return CONTEXTFUNCTIONS_ALL;
			}
		};
		registerMethod(new ScriptMethodInputMouseGetY(this));
	}
	{
		//
		class ScriptMethodInputMouseGetYUnscaled: public ScriptMethod {
		private:
			LogicMiniScript* miniScript { nullptr };
		public:
			ScriptMethodInputMouseGetYUnscaled(LogicMiniScript* miniScript):
				ScriptMethod({}, ScriptVariableType::TYPE_INTEGER),
				miniScript(miniScript) {}
			const string getMethodName() override {
				return "input.mouse.getYUnscaled";
			}
			void executeMethod(span<ScriptVariable>& argumentValues, ScriptVariable& returnValue, const ScriptStatement& statement) override {
				returnValue = static_cast<int64_t>(miniScript->mouseYUnscaled);
			}
			const vector<string>& getContextFunctions() {
				return CONTEXTFUNCTIONS_ALL;
			}
		};
		registerMethod(new ScriptMethodInputMouseGetYUnscaled(this));
	}
	{
		//
		class ScriptMethodInputMouseGetWheelX: public ScriptMethod {
		private:
			LogicMiniScript* miniScript { nullptr };
		public:
			ScriptMethodInputMouseGetWheelX(LogicMiniScript* miniScript):
				ScriptMethod({}, ScriptVariableType::TYPE_FLOAT),
				miniScript(miniScript) {}
			const string getMethodName() override {
				return "input.mouse.getWheelX";
			}
			void executeMethod(span<ScriptVariable>& argumentValues, ScriptVariable& returnValue, const ScriptStatement& statement) override {
				returnValue = miniScript->mouseWheelX;
			}
			const vector<string>& getContextFunctions() {
				return CONTEXTFUNCTIONS_ALL;
			}
		};
		registerMethod(new ScriptMethodInputMouseGetWheelX(this));
	}
	{
		//
		class ScriptMethodInputMouseGetWheelY: public ScriptMethod {
		private:
			LogicMiniScript* miniScript { nullptr };
		public:
			ScriptMethodInputMouseGetWheelY(LogicMiniScript* miniScript):
				ScriptMethod({}, ScriptVariableType::TYPE_FLOAT),
				miniScript(miniScript) {}
			const string getMethodName() override {
				return "input.mouse.getWheelY";
			}
			void executeMethod(span<ScriptVariable>& argumentValues, ScriptVariable& returnValue, const ScriptStatement& statement) override {
				returnValue = miniScript->mouseWheelY;
			}
			const vector<string>& getContextFunctions() {
				return CONTEXTFUNCTIONS_ALL;
			}
		};
		registerMethod(new ScriptMethodInputMouseGetWheelY(this));
	}
	{
		//
		class ScriptMethodInputMouseGetWheelZ: public ScriptMethod {
		private:
			LogicMiniScript* miniScript { nullptr };
		public:
			ScriptMethodInputMouseGetWheelZ(LogicMiniScript* miniScript):
				ScriptMethod({}, ScriptVariableType::TYPE_FLOAT),
				miniScript(miniScript) {}
			const string getMethodName() override {
				return "input.mouse.getWheelZ";
			}
			void executeMethod(span<ScriptVariable>& argumentValues, ScriptVariable& returnValue, const ScriptStatement& statement) override {
				returnValue = miniScript->mouseWheelZ;
			}
			const vector<string>& getContextFunctions() {
				return CONTEXTFUNCTIONS_ALL;
			}
		};
		registerMethod(new ScriptMethodInputMouseGetWheelZ(this));
	}
	// camera
	{
		//
		class ScriptMethodCameraGetLookFrom: public ScriptMethod {
		private:
			LogicMiniScript* miniScript { nullptr };
		public:
			ScriptMethodCameraGetLookFrom(LogicMiniScript* miniScript):
				ScriptMethod({}, ScriptVariableType::TYPE_VECTOR3),
				miniScript(miniScript) {}
			const string getMethodName() override {
				return "engine.camera.getLookFrom";
			}
			void executeMethod(span<ScriptVariable>& argumentValues, ScriptVariable& returnValue, const ScriptStatement& statement) override {
				returnValue = miniScript->context->getEngine()->getCamera()->getLookFrom();
			}
			const vector<string>& getContextFunctions() {
				return CONTEXTFUNCTIONS_ENGINE;
			}
		};
		registerMethod(new ScriptMethodCameraGetLookFrom(this));
	}
	{
		//
		class ScriptMethodCameraSetLookFrom: public ScriptMethod {
		private:
			LogicMiniScript* miniScript { nullptr };
		public:
			ScriptMethodCameraSetLookFrom(LogicMiniScript* miniScript):
				ScriptMethod(
					{
						{ .type = ScriptVariableType::TYPE_VECTOR3, .name = "lookFrom", .optional = false, .assignBack = false }
					},
					ScriptVariableType::TYPE_NULL
				),
				miniScript(miniScript) {}
			const string getMethodName() override {
				return "engine.camera.setLookFrom";
			}
			void executeMethod(span<ScriptVariable>& argumentValues, ScriptVariable& returnValue, const ScriptStatement& statement) override {
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
		registerMethod(new ScriptMethodCameraSetLookFrom(this));
	}
	{
		//
		class ScriptMethodCameraGetLookAt: public ScriptMethod {
		private:
			LogicMiniScript* miniScript { nullptr };
		public:
			ScriptMethodCameraGetLookAt(LogicMiniScript* miniScript):
				ScriptMethod({}, ScriptVariableType::TYPE_VECTOR3),
				miniScript(miniScript) {}
			const string getMethodName() override {
				return "engine.camera.getLookAt";
			}
			void executeMethod(span<ScriptVariable>& argumentValues, ScriptVariable& returnValue, const ScriptStatement& statement) override {
				returnValue = miniScript->context->getEngine()->getCamera()->getLookAt();
			}
			const vector<string>& getContextFunctions() {
				return CONTEXTFUNCTIONS_ENGINE;
			}
		};
		registerMethod(new ScriptMethodCameraGetLookAt(this));
	}
	{
		//
		class ScriptMethodCameraSetLookAt: public ScriptMethod {
		private:
			LogicMiniScript* miniScript { nullptr };
		public:
			ScriptMethodCameraSetLookAt(LogicMiniScript* miniScript):
				ScriptMethod(
					{
						{ .type = ScriptVariableType::TYPE_VECTOR3, .name = "lookAt", .optional = false, .assignBack = false }
					},
					ScriptVariableType::TYPE_NULL
				),
				miniScript(miniScript) {}
			const string getMethodName() override {
				return "engine.camera.setLookAt";
			}
			void executeMethod(span<ScriptVariable>& argumentValues, ScriptVariable& returnValue, const ScriptStatement& statement) override {
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
		registerMethod(new ScriptMethodCameraSetLookAt(this));
	}
	{
		//
		class ScriptMethodCameraGetUpVector: public ScriptMethod {
		private:
			LogicMiniScript* miniScript { nullptr };
		public:
			ScriptMethodCameraGetUpVector(LogicMiniScript* miniScript):
				ScriptMethod({}, ScriptVariableType::TYPE_VECTOR3),
				miniScript(miniScript) {}
			const string getMethodName() override {
				return "engine.camera.getUpVector";
			}
			void executeMethod(span<ScriptVariable>& argumentValues, ScriptVariable& returnValue, const ScriptStatement& statement) override {
				returnValue = miniScript->context->getEngine()->getCamera()->getUpVector();
			}
			const vector<string>& getContextFunctions() {
				return CONTEXTFUNCTIONS_ENGINE;
			}
		};
		registerMethod(new ScriptMethodCameraGetUpVector(this));
	}
	{
		//
		class ScriptMethodCameraSetUpVector: public ScriptMethod {
		private:
			LogicMiniScript* miniScript { nullptr };
		public:
			ScriptMethodCameraSetUpVector(LogicMiniScript* miniScript):
				ScriptMethod(
					{
						{ .type = ScriptVariableType::TYPE_VECTOR3, .name = "upVector", .optional = false, .assignBack = false }
					},
					ScriptVariableType::TYPE_NULL
				),
				miniScript(miniScript) {}
			const string getMethodName() override {
				return "engine.camera.setUpVector";
			}
			void executeMethod(span<ScriptVariable>& argumentValues, ScriptVariable& returnValue, const ScriptStatement& statement) override {
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
		registerMethod(new ScriptMethodCameraSetUpVector(this));
	}
	{
		//
		class ScriptMethodCameraComputeUpVector: public ScriptMethod {
		private:
			LogicMiniScript* miniScript { nullptr };
		public:
			ScriptMethodCameraComputeUpVector(LogicMiniScript* miniScript):
				ScriptMethod(
					{
						{ .type = ScriptVariableType::TYPE_VECTOR3, .name = "lookFrom", .optional = false, .assignBack = false },
						{ .type = ScriptVariableType::TYPE_VECTOR3, .name = "lookAt", .optional = false, .assignBack = false }
					},
					ScriptVariableType::TYPE_VECTOR3
				),
				miniScript(miniScript) {}
			const string getMethodName() override {
				return "engine.camera.computeUpVector";
			}
			void executeMethod(span<ScriptVariable>& argumentValues, ScriptVariable& returnValue, const ScriptStatement& statement) override {
				Vector3 lookFrom;
				Vector3 lookAt;
				if (miniScript->getVector3Value(argumentValues, 0, lookFrom) == true &&
					miniScript->getVector3Value(argumentValues, 1, lookAt) == true) {
					returnValue = Camera::computeUpVector(lookFrom, lookAt);
				} else {
					Console::println(getMethodName() + "(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation(getMethodName()));
					miniScript->startErrorScript();
				}
			}
			const vector<string>& getContextFunctions() {
				return CONTEXTFUNCTIONS_ENGINE;
			}
		};
		registerMethod(new ScriptMethodCameraComputeUpVector(this));
	}
	{
		//
		class ScriptMethodCameraGetFovX: public ScriptMethod {
		private:
			LogicMiniScript* miniScript { nullptr };
		public:
			ScriptMethodCameraGetFovX(LogicMiniScript* miniScript):
				ScriptMethod({}, ScriptVariableType::TYPE_FLOAT),
				miniScript(miniScript) {}
			const string getMethodName() override {
				return "engine.camera.getFovX";
			}
			void executeMethod(span<ScriptVariable>& argumentValues, ScriptVariable& returnValue, const ScriptStatement& statement) override {
				returnValue = miniScript->context->getEngine()->getCamera()->getFovX();
			}
			const vector<string>& getContextFunctions() {
				return CONTEXTFUNCTIONS_ENGINE;
			}
		};
		registerMethod(new ScriptMethodCameraGetFovX(this));
	}
	{
		//
		class ScriptMethodCameraSetFovX: public ScriptMethod {
		private:
			LogicMiniScript* miniScript { nullptr };
		public:
			ScriptMethodCameraSetFovX(LogicMiniScript* miniScript):
				ScriptMethod(
					{
						{ .type = ScriptVariableType::TYPE_FLOAT, .name = "fovX", .optional = false, .assignBack = false }
					},
					ScriptVariableType::TYPE_NULL
				),
				miniScript(miniScript) {}
			const string getMethodName() override {
				return "engine.camera.setFovX";
			}
			void executeMethod(span<ScriptVariable>& argumentValues, ScriptVariable& returnValue, const ScriptStatement& statement) override {
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
		registerMethod(new ScriptMethodCameraSetFovX(this));
	}
	// timing
	{
		//
		class ScriptMethodTimingGetDeltaTime: public ScriptMethod {
		private:
			LogicMiniScript* miniScript { nullptr };
		public:
			ScriptMethodTimingGetDeltaTime(LogicMiniScript* miniScript):
				ScriptMethod({}, ScriptVariableType::TYPE_INTEGER),
				miniScript(miniScript) {}
			const string getMethodName() override {
				return "engine.timing.getDeltaTime";
			}
			void executeMethod(span<ScriptVariable>& argumentValues, ScriptVariable& returnValue, const ScriptStatement& statement) override {
				returnValue = miniScript->context->getEngine()->getTiming()->getDeltaTime();
			}
			const vector<string>& getContextFunctions() {
				return CONTEXTFUNCTIONS_ENGINE;
			}
		};
		registerMethod(new ScriptMethodTimingGetDeltaTime(this));
	}
	{
		//
		class ScriptMethodTimingGetDeltaTimeSeconds: public ScriptMethod {
		private:
			LogicMiniScript* miniScript { nullptr };
		public:
			ScriptMethodTimingGetDeltaTimeSeconds(LogicMiniScript* miniScript):
				ScriptMethod({}, ScriptVariableType::TYPE_FLOAT),
				miniScript(miniScript) {}
			const string getMethodName() override {
				return "engine.timing.getDeltaTimeSeconds";
			}
			void executeMethod(span<ScriptVariable>& argumentValues, ScriptVariable& returnValue, const ScriptStatement& statement) override {
				returnValue = miniScript->context->getEngine()->getTiming()->getDeltaTimeSeconds();
			}
			const vector<string>& getContextFunctions() {
				return CONTEXTFUNCTIONS_ENGINE;
			}
		};
		registerMethod(new ScriptMethodTimingGetDeltaTimeSeconds(this));
	}
	{
		//
		class ScriptMethodTimingGetAvarageFPS: public ScriptMethod {
		private:
			LogicMiniScript* miniScript { nullptr };
		public:
			ScriptMethodTimingGetAvarageFPS(LogicMiniScript* miniScript):
				ScriptMethod({}, ScriptVariableType::TYPE_FLOAT),
				miniScript(miniScript) {}
			const string getMethodName() override {
				return "engine.timing.getAvarageFPS";
			}
			void executeMethod(span<ScriptVariable>& argumentValues, ScriptVariable& returnValue, const ScriptStatement& statement) override {
				returnValue = miniScript->context->getEngine()->getTiming()->getAvarageFPS();
			}
			const vector<string>& getContextFunctions() {
				return CONTEXTFUNCTIONS_ENGINE;
			}
		};
		registerMethod(new ScriptMethodTimingGetAvarageFPS(this));
	}
	// engine
	{
		//
		class ScriptMethodEngineGetWidth: public ScriptMethod {
		private:
			LogicMiniScript* miniScript { nullptr };
		public:
			ScriptMethodEngineGetWidth(LogicMiniScript* miniScript):
				ScriptMethod({}, ScriptVariableType::TYPE_INTEGER),
				miniScript(miniScript) {}
			const string getMethodName() override {
				return "engine.getWidth";
			}
			void executeMethod(span<ScriptVariable>& argumentValues, ScriptVariable& returnValue, const ScriptStatement& statement) override {
				returnValue = static_cast<int64_t>(miniScript->context->getEngine()->getWidth());
			}
			const vector<string>& getContextFunctions() {
				return CONTEXTFUNCTIONS_ENGINE;
			}
		};
		registerMethod(new ScriptMethodEngineGetWidth(this));
	}
	{
		//
		class ScriptMethodEngineGetHeight: public ScriptMethod {
		private:
			LogicMiniScript* miniScript { nullptr };
		public:
			ScriptMethodEngineGetHeight(LogicMiniScript* miniScript):
				ScriptMethod({}, ScriptVariableType::TYPE_INTEGER),
				miniScript(miniScript) {}
			const string getMethodName() override {
				return "engine.getHeight";
			}
			void executeMethod(span<ScriptVariable>& argumentValues, ScriptVariable& returnValue, const ScriptStatement& statement) override {
				returnValue = static_cast<int64_t>(miniScript->context->getEngine()->getHeight());
			}
			const vector<string>& getContextFunctions() {
				return CONTEXTFUNCTIONS_ENGINE;
			}
		};
		registerMethod(new ScriptMethodEngineGetHeight(this));
	}
	{
		//
		class ScriptMethodEngineDumpEntities: public ScriptMethod {
		private:
			LogicMiniScript* miniScript { nullptr };
		public:
			ScriptMethodEngineDumpEntities(LogicMiniScript* miniScript):
				ScriptMethod({}, ScriptVariableType::TYPE_NULL),
				miniScript(miniScript) {}
			const string getMethodName() override {
				return "engine.dumpEntities";
			}
			void executeMethod(span<ScriptVariable>& argumentValues, ScriptVariable& returnValue, const ScriptStatement& statement) override {
				miniScript->context->getEngine()->dumpEntities();
			}
			const vector<string>& getContextFunctions() {
				return CONTEXTFUNCTIONS_ENGINE;
			}
		};
		registerMethod(new ScriptMethodEngineDumpEntities(this));
	}
	{
		//
		class ScriptMethodEngineDumpShaders: public ScriptMethod {
		private:
			LogicMiniScript* miniScript { nullptr };
		public:
			ScriptMethodEngineDumpShaders(LogicMiniScript* miniScript):
				ScriptMethod({}, ScriptVariableType::TYPE_NULL),
				miniScript(miniScript) {}
			const string getMethodName() override {
				return "engine.dumpShaders";
			}
			void executeMethod(span<ScriptVariable>& argumentValues, ScriptVariable& returnValue, const ScriptStatement& statement) override {
				miniScript->context->getEngine()->dumpShaders();
			}
			const vector<string>& getContextFunctions() {
				return CONTEXTFUNCTIONS_ENGINE;
			}
		};
		registerMethod(new ScriptMethodEngineDumpShaders(this));
	}
	{
		//
		class ScriptMethodEngineGetEntityIdByMousePosition: public ScriptMethod {
		private:
			LogicMiniScript* miniScript { nullptr };
		public:
			ScriptMethodEngineGetEntityIdByMousePosition(LogicMiniScript* miniScript):
				ScriptMethod(
					{
						{ .type = ScriptVariableType::TYPE_INTEGER, .name = "mouseX", .optional = false, .assignBack = false },
						{ .type = ScriptVariableType::TYPE_INTEGER, .name = "mouseY", .optional = false, .assignBack = false }
					},
					ScriptVariableType::TYPE_STRING
				),
				miniScript(miniScript) {}
			const string getMethodName() override {
				return "engine.getEntityIdByMousePosition";
			}
			void executeMethod(span<ScriptVariable>& argumentValues, ScriptVariable& returnValue, const ScriptStatement& statement) override {
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
		registerMethod(new ScriptMethodEngineGetEntityIdByMousePosition(this));
	}
	{
		//
		class ScriptMethodEngineComputeWorldCoordinateByMousePosition: public ScriptMethod {
		private:
			LogicMiniScript* miniScript { nullptr };
		public:
			ScriptMethodEngineComputeWorldCoordinateByMousePosition(LogicMiniScript* miniScript):
				ScriptMethod(
					{
						{ .type = ScriptVariableType::TYPE_INTEGER, .name = "mouseX", .optional = false, .assignBack = false },
						{ .type = ScriptVariableType::TYPE_INTEGER, .name = "mouseY", .optional = false, .assignBack = false }
					},
					ScriptVariableType::TYPE_VECTOR3
				),
				miniScript(miniScript) {}
			const string getMethodName() override {
				return "engine.computeWorldCoordinateByMousePosition";
			}
			void executeMethod(span<ScriptVariable>& argumentValues, ScriptVariable& returnValue, const ScriptStatement& statement) override {
				int64_t mouseX;
				int64_t mouseY;
				if (miniScript->getIntegerValue(argumentValues, 0, mouseX) == true &&
					miniScript->getIntegerValue(argumentValues, 1, mouseY) == true) {
					returnValue = miniScript->context->getEngine()->computeWorldCoordinateByMousePosition(mouseX, mouseY);
				} else {
					Console::println(getMethodName() + "(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation(getMethodName()));
					miniScript->startErrorScript();
				}
			}
			const vector<string>& getContextFunctions() {
				return CONTEXTFUNCTIONS_ENGINE;
			}
		};
		registerMethod(new ScriptMethodEngineComputeWorldCoordinateByMousePosition(this));
	}
	{
		//
		class ScriptMethodEngineComputeScreenCoordinateByWorldCoordinate: public ScriptMethod {
		private:
			LogicMiniScript* miniScript { nullptr };
		public:
			ScriptMethodEngineComputeScreenCoordinateByWorldCoordinate(LogicMiniScript* miniScript):
				ScriptMethod(
					{
						{ .type = ScriptVariableType::TYPE_VECTOR3, .name = "worldCoodinate", .optional = false, .assignBack = false },
						{ .type = ScriptVariableType::TYPE_VECTOR2, .name = "screenCoordinate", .optional = false, .assignBack = true }
					},
					ScriptVariableType::TYPE_BOOLEAN
				),
				miniScript(miniScript) {}
			const string getMethodName() override {
				return "engine.computeScreenCoordinateByWorldCoordinate";
			}
			void executeMethod(span<ScriptVariable>& argumentValues, ScriptVariable& returnValue, const ScriptStatement& statement) override {
				Vector3 worldCoodinate;
				if (argumentValues.size() == 2 &&
					miniScript->getVector3Value(argumentValues, 0, worldCoodinate) == true) {
					Vector2 screenCoordinate;
					if (miniScript->context->getEngine()->computeScreenCoordinateByWorldCoordinate(worldCoodinate, screenCoordinate) == true) {
						argumentValues[1] = screenCoordinate;
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
		registerMethod(new ScriptMethodEngineComputeScreenCoordinateByWorldCoordinate(this));
	}
	{
		//
		class ScriptMethodEntityGetTransform: public ScriptMethod {
		private:
			LogicMiniScript* miniScript { nullptr };
		public:
			ScriptMethodEntityGetTransform(LogicMiniScript* miniScript):
				ScriptMethod(
					{
						{ .type = ScriptVariableType::TYPE_STRING, .name = "entityId", .optional = false, .assignBack = false },
						{ .type = ScriptVariableType::TYPE_STRING, .name = "childEntityId", .optional = true, .assignBack = false }
					},
					ScriptVariableType::TYPE_TRANSFORM
				),
				miniScript(miniScript) {}
			const string getMethodName() override {
				return "engine.entity.getTransform";
			}
			void executeMethod(span<ScriptVariable>& argumentValues, ScriptVariable& returnValue, const ScriptStatement& statement) override {
				string entityId;
				string childEntityId;
				if (miniScript->getStringValue(argumentValues, 0, entityId) == true &&
					miniScript->getStringValue(argumentValues, 1, childEntityId, true) == true) {
					auto entity = miniScript->getEntity(entityId, childEntityId);
					if (entity != nullptr) {
						returnValue = entity->getTransform();
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
		registerMethod(new ScriptMethodEntityGetTransform(this));
	}
	{
		//
		class ScriptMethodEntitySetTransform: public ScriptMethod {
		private:
			LogicMiniScript* miniScript { nullptr };
		public:
			ScriptMethodEntitySetTransform(LogicMiniScript* miniScript):
				ScriptMethod(
					{
						{ .type = ScriptVariableType::TYPE_STRING, .name = "entityId", .optional = false, .assignBack = false },
						{ .type = ScriptVariableType::TYPE_TRANSFORM, .name = "transform", .optional = false, .assignBack = false },
						{ .type = ScriptVariableType::TYPE_STRING, .name = "childEntityId", .optional = true, .assignBack = false }
					},
					ScriptVariableType::TYPE_NULL
				),
				miniScript(miniScript) {}
			const string getMethodName() override {
				return "engine.entity.setTransform";
			}
			void executeMethod(span<ScriptVariable>& argumentValues, ScriptVariable& returnValue, const ScriptStatement& statement) override {
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
		registerMethod(new ScriptMethodEntitySetTransform(this));
	}
	{
		//
		class ScriptMethodEntityIsEnabled: public ScriptMethod {
		private:
			LogicMiniScript* miniScript { nullptr };
		public:
			ScriptMethodEntityIsEnabled(LogicMiniScript* miniScript):
				ScriptMethod(
					{
						{ .type = ScriptVariableType::TYPE_STRING, .name = "entityId", .optional = false, .assignBack = false },
						{ .type = ScriptVariableType::TYPE_STRING, .name = "childEntityId", .optional = true, .assignBack = false }
					},
					ScriptVariableType::TYPE_BOOLEAN
				),
				miniScript(miniScript) {}
			const string getMethodName() override {
				return "engine.entity.isEnabled";
			}
			void executeMethod(span<ScriptVariable>& argumentValues, ScriptVariable& returnValue, const ScriptStatement& statement) override {
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
		registerMethod(new ScriptMethodEntityIsEnabled(this));
	}
	{
		//
		class ScriptMethodEntitySetEnabled: public ScriptMethod {
		private:
			LogicMiniScript* miniScript { nullptr };
		public:
			ScriptMethodEntitySetEnabled(LogicMiniScript* miniScript):
				ScriptMethod(
					{
						{ .type = ScriptVariableType::TYPE_STRING, .name = "entityId", .optional = false, .assignBack = false },
						{ .type = ScriptVariableType::TYPE_BOOLEAN, .name = "enabled", .optional = false, .assignBack = false },
						{ .type = ScriptVariableType::TYPE_STRING, .name = "childEntityId", .optional = true, .assignBack = false }
					},
					ScriptVariableType::TYPE_NULL
				),
				miniScript(miniScript) {}
			const string getMethodName() override {
				return "engine.entity.setEnabled";
			}
			void executeMethod(span<ScriptVariable>& argumentValues, ScriptVariable& returnValue, const ScriptStatement& statement) override {
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
		registerMethod(new ScriptMethodEntitySetEnabled(this));
	}
	{
		//
		class ScriptMethodEntityIsPickable: public ScriptMethod {
		private:
			LogicMiniScript* miniScript { nullptr };
		public:
			ScriptMethodEntityIsPickable(LogicMiniScript* miniScript):
				ScriptMethod(
					{
						{ .type = ScriptVariableType::TYPE_STRING, .name = "entityId", .optional = false, .assignBack = false },
						{ .type = ScriptVariableType::TYPE_STRING, .name = "childEntityId", .optional = true, .assignBack = false }
					},
					ScriptVariableType::TYPE_BOOLEAN
				),
				miniScript(miniScript) {}
			const string getMethodName() override {
				return "engine.entity.isPickable";
			}
			void executeMethod(span<ScriptVariable>& argumentValues, ScriptVariable& returnValue, const ScriptStatement& statement) override {
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
		registerMethod(new ScriptMethodEntityIsPickable(this));
	}
	{
		//
		class ScriptMethodEntitySetPickable: public ScriptMethod {
		private:
			LogicMiniScript* miniScript { nullptr };
		public:
			ScriptMethodEntitySetPickable(LogicMiniScript* miniScript):
				ScriptMethod(
					{
						{ .type = ScriptVariableType::TYPE_STRING, .name = "entityId", .optional = false, .assignBack = false },
						{ .type = ScriptVariableType::TYPE_BOOLEAN, .name = "pickable", .optional = false, .assignBack = false },
						{ .type = ScriptVariableType::TYPE_STRING, .name = "childEntityId", .optional = true, .assignBack = false }
					},
					ScriptVariableType::TYPE_NULL
				),
				miniScript(miniScript) {}
			const string getMethodName() override {
				return "engine.entity.setPickable";
			}
			void executeMethod(span<ScriptVariable>& argumentValues, ScriptVariable& returnValue, const ScriptStatement& statement) override {
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
		registerMethod(new ScriptMethodEntitySetPickable(this));
	}
	{
		//
		class ScriptMethodEntityGetEffectColorMul: public ScriptMethod {
		private:
			LogicMiniScript* miniScript { nullptr };
		public:
			ScriptMethodEntityGetEffectColorMul(LogicMiniScript* miniScript):
				ScriptMethod(
					{
						{ .type = ScriptVariableType::TYPE_STRING, .name = "entityId", .optional = false, .assignBack = false },
						{ .type = ScriptVariableType::TYPE_STRING, .name = "childEntityId", .optional = true, .assignBack = false }
					},
					ScriptVariableType::TYPE_VECTOR4
				),
				miniScript(miniScript) {}
			const string getMethodName() override {
				return "engine.entity.getEffectColorMul";
			}
			void executeMethod(span<ScriptVariable>& argumentValues, ScriptVariable& returnValue, const ScriptStatement& statement) override {
				string entityId;
				string childEntityId;
				if (miniScript->getStringValue(argumentValues, 0, entityId) == true &&
					miniScript->getStringValue(argumentValues, 1, childEntityId, true) == true) {
					auto entity = miniScript->getEntity(entityId, childEntityId);
					if (entity != nullptr) {
						auto effectColorMul = entity->getEffectColorMul();
						returnValue.setValue(Vector4(effectColorMul.getRed(), effectColorMul.getGreen(), effectColorMul.getBlue(), effectColorMul.getAlpha()));
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
		registerMethod(new ScriptMethodEntityGetEffectColorMul(this));
	}
	{
		//
		class ScriptMethodEntitySetEffectColorMul: public ScriptMethod {
		private:
			LogicMiniScript* miniScript { nullptr };
		public:
			ScriptMethodEntitySetEffectColorMul(LogicMiniScript* miniScript):
				ScriptMethod(
					{
						{ .type = ScriptVariableType::TYPE_STRING, .name = "entityId", .optional = false, .assignBack = false },
						{ .type = ScriptVariableType::TYPE_VECTOR4, .name = "effectColorMul", .optional = false, .assignBack = false },
						{ .type = ScriptVariableType::TYPE_STRING, .name = "childEntityId", .optional = true, .assignBack = false }
					},
					ScriptVariableType::TYPE_NULL
				),
				miniScript(miniScript) {}
			const string getMethodName() override {
				return "engine.entity.setEffectColorMul";
			}
			void executeMethod(span<ScriptVariable>& argumentValues, ScriptVariable& returnValue, const ScriptStatement& statement) override {
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
		registerMethod(new ScriptMethodEntitySetEffectColorMul(this));
	}
	{
		//
		class ScriptMethodEntityGetEffectColorAdd: public ScriptMethod {
		private:
			LogicMiniScript* miniScript { nullptr };
		public:
			ScriptMethodEntityGetEffectColorAdd(LogicMiniScript* miniScript):
				ScriptMethod(
					{
						{ .type = ScriptVariableType::TYPE_STRING, .name = "entityId", .optional = false, .assignBack = false },
						{ .type = ScriptVariableType::TYPE_STRING, .name = "childEntityId", .optional = true, .assignBack = false }
					},
					ScriptVariableType::TYPE_VECTOR4
				),
				miniScript(miniScript) {}
			const string getMethodName() override {
				return "engine.entity.getEffectColorAdd";
			}
			void executeMethod(span<ScriptVariable>& argumentValues, ScriptVariable& returnValue, const ScriptStatement& statement) override {
				string entityId;
				string childEntityId;
				if (miniScript->getStringValue(argumentValues, 0, entityId) == true &&
					miniScript->getStringValue(argumentValues, 1, childEntityId, true) == true) {
					auto entity = miniScript->getEntity(entityId, childEntityId);
					if (entity != nullptr) {
						auto effectColorAdd = entity->getEffectColorAdd();
						returnValue.setValue(Vector4(effectColorAdd.getRed(), effectColorAdd.getGreen(), effectColorAdd.getBlue(), effectColorAdd.getAlpha()));
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
		registerMethod(new ScriptMethodEntityGetEffectColorAdd(this));
	}
	{
		//
		class ScriptMethodEntitySetEffectColorAdd: public ScriptMethod {
		private:
			LogicMiniScript* miniScript { nullptr };
		public:
			ScriptMethodEntitySetEffectColorAdd(LogicMiniScript* miniScript):
				ScriptMethod(
					{
						{ .type = ScriptVariableType::TYPE_STRING, .name = "entityId", .optional = false, .assignBack = false },
						{ .type = ScriptVariableType::TYPE_VECTOR4, .name = "effectColorAdd", .optional = false, .assignBack = false },
						{ .type = ScriptVariableType::TYPE_STRING, .name = "childEntityId", .optional = true, .assignBack = false }
					},
					ScriptVariableType::TYPE_NULL
				),
				miniScript(miniScript) {}
			const string getMethodName() override {
				return "engine.entity.setEffectColorAdd";
			}
			void executeMethod(span<ScriptVariable>& argumentValues, ScriptVariable& returnValue, const ScriptStatement& statement) override {
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
		registerMethod(new ScriptMethodEntitySetEffectColorAdd(this));
	}
	{
		//
		class ScriptMethodEntityGetAnimation: public ScriptMethod {
		private:
			LogicMiniScript* miniScript { nullptr };
		public:
			ScriptMethodEntityGetAnimation(LogicMiniScript* miniScript):
				ScriptMethod(
					{
						{ .type = ScriptVariableType::TYPE_STRING, .name = "entityId", .optional = false, .assignBack = false },
						{ .type = ScriptVariableType::TYPE_STRING, .name = "childEntityId", .optional = true, .assignBack = false }
					},
					ScriptVariableType::TYPE_STRING
				),
				miniScript(miniScript) {}
			const string getMethodName() override {
				return "engine.entity.getAnimation";
			}
			void executeMethod(span<ScriptVariable>& argumentValues, ScriptVariable& returnValue, const ScriptStatement& statement) override {
				string entityId;
				string childEntityId;
				if (miniScript->getStringValue(argumentValues, 0, entityId) == true &&
					miniScript->getStringValue(argumentValues, 1, childEntityId, true) == true) {
					auto object = dynamic_cast<Object*>(miniScript->getEntity(entityId, childEntityId));
					if (object != nullptr) {
						returnValue.setValue(object->getAnimation());
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
		registerMethod(new ScriptMethodEntityGetAnimation(this));
	}
	{
		//
		class ScriptMethodEntitySetAnimation: public ScriptMethod {
		private:
			LogicMiniScript* miniScript { nullptr };
		public:
			ScriptMethodEntitySetAnimation(LogicMiniScript* miniScript):
				ScriptMethod(
					{
						{ .type = ScriptVariableType::TYPE_STRING, .name = "entityId", .optional = false, .assignBack = false },
						{ .type = ScriptVariableType::TYPE_STRING, .name = "animation", .optional = false, .assignBack = false },
						{ .type = ScriptVariableType::TYPE_FLOAT, .name = "speed", .optional = true, .assignBack = false },
						{ .type = ScriptVariableType::TYPE_STRING, .name = "childEntityId", .optional = true, .assignBack = false },
					},
					ScriptVariableType::TYPE_NULL
				),
				miniScript(miniScript) {}
			const string getMethodName() override {
				return "engine.entity.setAnimation";
			}
			void executeMethod(span<ScriptVariable>& argumentValues, ScriptVariable& returnValue, const ScriptStatement& statement) override {
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
		registerMethod(new ScriptMethodEntitySetAnimation(this));
	}
	{
		//
		class ScriptMethodEntitySetAnimationSpeed: public ScriptMethod {
		private:
			LogicMiniScript* miniScript { nullptr };
		public:
			ScriptMethodEntitySetAnimationSpeed(LogicMiniScript* miniScript):
				ScriptMethod(
					{
						{ .type = ScriptVariableType::TYPE_STRING, .name = "entityId", .optional = false, .assignBack = false },
						{ .type = ScriptVariableType::TYPE_FLOAT, .name = "speed", .optional = false, .assignBack = false },
						{ .type = ScriptVariableType::TYPE_STRING, .name = "childEntityId", .optional = true, .assignBack = false },
					},
					ScriptVariableType::TYPE_NULL
				),
				miniScript(miniScript) {}
			const string getMethodName() override {
				return "engine.entity.setAnimationSpeed";
			}
			void executeMethod(span<ScriptVariable>& argumentValues, ScriptVariable& returnValue, const ScriptStatement& statement) override {
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
		registerMethod(new ScriptMethodEntitySetAnimationSpeed(this));
	}
	{
		//
		class ScriptMethodEntityGetAnimationTime: public ScriptMethod {
		private:
			LogicMiniScript* miniScript { nullptr };
		public:
			ScriptMethodEntityGetAnimationTime(LogicMiniScript* miniScript):
				ScriptMethod(
					{
						{ .type = ScriptVariableType::TYPE_STRING, .name = "entityId", .optional = false, .assignBack = false },
						{ .type = ScriptVariableType::TYPE_STRING, .name = "childEntityId", .optional = true, .assignBack = false },
					},
					ScriptVariableType::TYPE_FLOAT
				),
				miniScript(miniScript) {}
			const string getMethodName() override {
				return "engine.entity.getAnimationTime";
			}
			void executeMethod(span<ScriptVariable>& argumentValues, ScriptVariable& returnValue, const ScriptStatement& statement) override {
				string entityId;
				string childEntityId;
				if (miniScript->getStringValue(argumentValues, 0, entityId) == true &&
					miniScript->getStringValue(argumentValues, 1, childEntityId, true) == true) {
					auto object = dynamic_cast<Object*>(miniScript->getEntity(entityId, childEntityId));
					if (object != nullptr) {
						returnValue.setValue(object->getAnimationTime());
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
		registerMethod(new ScriptMethodEntityGetAnimationTime(this));
	}
	{
		//
		class ScriptMethodEntityHasOverlayAnimation: public ScriptMethod {
		private:
			LogicMiniScript* miniScript { nullptr };
		public:
			ScriptMethodEntityHasOverlayAnimation(LogicMiniScript* miniScript):
				ScriptMethod(
					{
						{ .type = ScriptVariableType::TYPE_STRING, .name = "entityId", .optional = false, .assignBack = false },
						{ .type = ScriptVariableType::TYPE_STRING, .name = "animation", .optional = false, .assignBack = false },
						{ .type = ScriptVariableType::TYPE_STRING, .name = "childEntityId", .optional = true, .assignBack = false },
					},
					ScriptVariableType::TYPE_BOOLEAN
				),
				miniScript(miniScript) {}
			const string getMethodName() override {
				return "engine.entity.hasOverlayAnimation";
			}
			void executeMethod(span<ScriptVariable>& argumentValues, ScriptVariable& returnValue, const ScriptStatement& statement) override {
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
		registerMethod(new ScriptMethodEntityHasOverlayAnimation(this));
	}
	{
		//
		class ScriptMethodEntityAddOverlayAnimation: public ScriptMethod {
		private:
			LogicMiniScript* miniScript { nullptr };
		public:
			ScriptMethodEntityAddOverlayAnimation(LogicMiniScript* miniScript):
				ScriptMethod(
					{
						{ .type = ScriptVariableType::TYPE_STRING, .name = "entityId", .optional = false, .assignBack = false },
						{ .type = ScriptVariableType::TYPE_STRING, .name = "animation", .optional = false, .assignBack = false },
						{ .type = ScriptVariableType::TYPE_STRING, .name = "childEntityId", .optional = true, .assignBack = false },
					},
					ScriptVariableType::TYPE_NULL
				),
				miniScript(miniScript) {}
			const string getMethodName() override {
				return "engine.entity.addOverlayAnimation";
			}
			void executeMethod(span<ScriptVariable>& argumentValues, ScriptVariable& returnValue, const ScriptStatement& statement) override {
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
		registerMethod(new ScriptMethodEntityAddOverlayAnimation(this));
	}
	{
		//
		class ScriptMethodEntityRemoveOverlayAnimation: public ScriptMethod {
		private:
			LogicMiniScript* miniScript { nullptr };
		public:
			ScriptMethodEntityRemoveOverlayAnimation(LogicMiniScript* miniScript):
				ScriptMethod(
					{
						{ .type = ScriptVariableType::TYPE_STRING, .name = "entityId", .optional = false, .assignBack = false },
						{ .type = ScriptVariableType::TYPE_STRING, .name = "animation", .optional = false, .assignBack = false },
						{ .type = ScriptVariableType::TYPE_STRING, .name = "childEntityId", .optional = true, .assignBack = false },
					},
					ScriptVariableType::TYPE_NULL
				),
				miniScript(miniScript) {}
			const string getMethodName() override {
				return "engine.entity.removeOverlayAnimation";
			}
			void executeMethod(span<ScriptVariable>& argumentValues, ScriptVariable& returnValue, const ScriptStatement& statement) override {
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
		registerMethod(new ScriptMethodEntityRemoveOverlayAnimation(this));
	}
	{
		//
		class ScriptMethodEntityRemoveFinishedOverlayAnimations: public ScriptMethod {
		private:
			LogicMiniScript* miniScript { nullptr };
		public:
			ScriptMethodEntityRemoveFinishedOverlayAnimations(LogicMiniScript* miniScript):
				ScriptMethod(
					{
						{ .type = ScriptVariableType::TYPE_STRING, .name = "entityId", .optional = false, .assignBack = false },
						{ .type = ScriptVariableType::TYPE_STRING, .name = "childEntityId", .optional = true, .assignBack = false },
					},
					ScriptVariableType::TYPE_NULL
				),
				miniScript(miniScript) {}
			const string getMethodName() override {
				return "engine.entity.removeFinishedOverlayAnimations";
			}
			void executeMethod(span<ScriptVariable>& argumentValues, ScriptVariable& returnValue, const ScriptStatement& statement) override {
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
		registerMethod(new ScriptMethodEntityRemoveFinishedOverlayAnimations(this));
	}
	{
		//
		class ScriptMethodEntityRemoveOverlayAnimations: public ScriptMethod {
		private:
			LogicMiniScript* miniScript { nullptr };
		public:
			ScriptMethodEntityRemoveOverlayAnimations(LogicMiniScript* miniScript):
				ScriptMethod(
					{
						{ .type = ScriptVariableType::TYPE_STRING, .name = "entityId", .optional = false, .assignBack = false },
						{ .type = ScriptVariableType::TYPE_STRING, .name = "childEntityId", .optional = true, .assignBack = false },
					},
					ScriptVariableType::TYPE_NULL
				),
				miniScript(miniScript) {}
			const string getMethodName() override {
				return "engine.entity.removeOverlayAnimations";
			}
			void executeMethod(span<ScriptVariable>& argumentValues, ScriptVariable& returnValue, const ScriptStatement& statement) override {
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
		registerMethod(new ScriptMethodEntityRemoveOverlayAnimations(this));
	}
	{
		//
		class ScriptMethodEntityGetOverlayAnimationTime: public ScriptMethod {
		private:
			LogicMiniScript* miniScript { nullptr };
		public:
			ScriptMethodEntityGetOverlayAnimationTime(LogicMiniScript* miniScript):
				ScriptMethod(
					{
						{ .type = ScriptVariableType::TYPE_STRING, .name = "entityId", .optional = false, .assignBack = false },
						{ .type = ScriptVariableType::TYPE_STRING, .name = "animation", .optional = false, .assignBack = false },
						{ .type = ScriptVariableType::TYPE_STRING, .name = "childEntityId", .optional = true, .assignBack = false },
					},
					ScriptVariableType::TYPE_FLOAT
				),
				miniScript(miniScript) {}
			const string getMethodName() override {
				return "engine.entity.getOverlayAnimationTime";
			}
			void executeMethod(span<ScriptVariable>& argumentValues, ScriptVariable& returnValue, const ScriptStatement& statement) override {
				string entityId;
				string animation;
				string childEntityId;
				if (miniScript->getStringValue(argumentValues, 0, entityId) == true &&
					miniScript->getStringValue(argumentValues, 1, animation) == true &&
					miniScript->getStringValue(argumentValues, 2, childEntityId, true) == true) {
					auto object = dynamic_cast<Object*>(miniScript->getEntity(entityId, childEntityId));
					if (object != nullptr) {
						returnValue.setValue(object->getOverlayAnimationTime(animation));
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
		registerMethod(new ScriptMethodEntityGetOverlayAnimationTime(this));
	}
	{
		//
		class ScriptMethodEntityGetNodeTransformMatrix: public ScriptMethod {
		private:
			LogicMiniScript* miniScript { nullptr };
		public:
			ScriptMethodEntityGetNodeTransformMatrix(LogicMiniScript* miniScript):
				ScriptMethod(
					{
						{ .type = ScriptVariableType::TYPE_STRING, .name = "entityId", .optional = false, .assignBack = false },
						{ .type = ScriptVariableType::TYPE_STRING, .name = "nodeId", .optional = false, .assignBack = false },
						{ .type = ScriptVariableType::TYPE_STRING, .name = "childEntityId", .optional = true, .assignBack = false },
					},
					ScriptVariableType::TYPE_MATRIX4x4
				),
				miniScript(miniScript) {}
			const string getMethodName() override {
				return "engine.entity.getNodeTransformMatrix";
			}
			void executeMethod(span<ScriptVariable>& argumentValues, ScriptVariable& returnValue, const ScriptStatement& statement) override {
				string entityId;
				string nodeId;
				string childEntityId;
				if (miniScript->getStringValue(argumentValues, 0, entityId) == true &&
					miniScript->getStringValue(argumentValues, 1, nodeId) == true &&
					miniScript->getStringValue(argumentValues, 2, childEntityId, true) == true) {
					auto object = dynamic_cast<Object*>(miniScript->getEntity(entityId, childEntityId));
					if (object != nullptr) {
						returnValue.setValue(object->getNodeTransformMatrix(nodeId));
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
		registerMethod(new ScriptMethodEntityGetNodeTransformMatrix(this));
	}
	{
		//
		class ScriptMethodEntityGetNodeTransform: public ScriptMethod {
		private:
			LogicMiniScript* miniScript { nullptr };
		public:
			ScriptMethodEntityGetNodeTransform(LogicMiniScript* miniScript):
				ScriptMethod(
					{
						{ .type = ScriptVariableType::TYPE_STRING, .name = "entityId", .optional = false, .assignBack = false },
						{ .type = ScriptVariableType::TYPE_STRING, .name = "nodeId", .optional = false, .assignBack = false },
						{ .type = ScriptVariableType::TYPE_STRING, .name = "childEntityId", .optional = true, .assignBack = false },
					},
					ScriptVariableType::TYPE_TRANSFORM
				),
				miniScript(miniScript) {}
			const string getMethodName() override {
				return "engine.entity.getNodeTransform";
			}
			void executeMethod(span<ScriptVariable>& argumentValues, ScriptVariable& returnValue, const ScriptStatement& statement) override {
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
						returnValue.setValue(transform);
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
		registerMethod(new ScriptMethodEntityGetNodeTransform(this));
	}
	{
		//
		class ScriptMethodEntitySetNodeTransformMatrix: public ScriptMethod {
		private:
			LogicMiniScript* miniScript { nullptr };
		public:
			ScriptMethodEntitySetNodeTransformMatrix(LogicMiniScript* miniScript):
				ScriptMethod(
					{
						{ .type = ScriptVariableType::TYPE_STRING, .name = "entityId", .optional = false, .assignBack = false },
						{ .type = ScriptVariableType::TYPE_STRING, .name = "nodeId", .optional = false, .assignBack = false },
						{ .type = ScriptVariableType::TYPE_MATRIX4x4, .name = "matrix", .optional = false, .assignBack = false },
						{ .type = ScriptVariableType::TYPE_STRING, .name = "childEntityId", .optional = true, .assignBack = false },
					},
					ScriptVariableType::TYPE_NULL
				),
				miniScript(miniScript) {}
			const string getMethodName() override {
				return "engine.entity.setNodeTransformMatrix";
			}
			void executeMethod(span<ScriptVariable>& argumentValues, ScriptVariable& returnValue, const ScriptStatement& statement) override {
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
		registerMethod(new ScriptMethodEntitySetNodeTransformMatrix(this));
	}
	{
		//
		class ScriptMethodEntitySetNodeTransform: public ScriptMethod {
		private:
			LogicMiniScript* miniScript { nullptr };
		public:
			ScriptMethodEntitySetNodeTransform(LogicMiniScript* miniScript):
				ScriptMethod(
					{
						{ .type = ScriptVariableType::TYPE_STRING, .name = "entityId", .optional = false, .assignBack = false },
						{ .type = ScriptVariableType::TYPE_STRING, .name = "nodeId", .optional = false, .assignBack = false },
						{ .type = ScriptVariableType::TYPE_TRANSFORM, .name = "transform", .optional = false, .assignBack = false },
						{ .type = ScriptVariableType::TYPE_STRING, .name = "childEntityId", .optional = true, .assignBack = false },
					},
					ScriptVariableType::TYPE_NULL
				),
				miniScript(miniScript) {}
			const string getMethodName() override {
				return "engine.entity.setNodeTransform";
			}
			void executeMethod(span<ScriptVariable>& argumentValues, ScriptVariable& returnValue, const ScriptStatement& statement) override {
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
		registerMethod(new ScriptMethodEntitySetNodeTransform(this));
	}
	{
		//
		class ScriptMethodEntityUnsetNodeTransformMatrix: public ScriptMethod {
		private:
			LogicMiniScript* miniScript { nullptr };
		public:
			ScriptMethodEntityUnsetNodeTransformMatrix(LogicMiniScript* miniScript):
				ScriptMethod(
					{
						{ .type = ScriptVariableType::TYPE_STRING, .name = "entityId", .optional = false, .assignBack = false },
						{ .type = ScriptVariableType::TYPE_STRING, .name = "nodeId", .optional = false, .assignBack = false },
						{ .type = ScriptVariableType::TYPE_STRING, .name = "childEntityId", .optional = true, .assignBack = false },
					},
					ScriptVariableType::TYPE_NULL
				),
				miniScript(miniScript) {}
			const string getMethodName() override {
				return "engine.entity.unsetNodeTransformMatrix";
			}
			void executeMethod(span<ScriptVariable>& argumentValues, ScriptVariable& returnValue, const ScriptStatement& statement) override {
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
		registerMethod(new ScriptMethodEntityUnsetNodeTransformMatrix(this));
	}
	{
		//
		class ScriptMethodEntityUnsetNodeTransform: public ScriptMethod {
		private:
			LogicMiniScript* miniScript { nullptr };
		public:
			ScriptMethodEntityUnsetNodeTransform(LogicMiniScript* miniScript):
				ScriptMethod(
					{
						{ .type = ScriptVariableType::TYPE_STRING, .name = "entityId", .optional = false, .assignBack = false },
						{ .type = ScriptVariableType::TYPE_STRING, .name = "nodeId", .optional = false, .assignBack = false },
						{ .type = ScriptVariableType::TYPE_STRING, .name = "childEntityId", .optional = true, .assignBack = false },
					},
					ScriptVariableType::TYPE_NULL
				),
				miniScript(miniScript) {}
			const string getMethodName() override {
				return "engine.entity.unsetNodeTransform";
			}
			void executeMethod(span<ScriptVariable>& argumentValues, ScriptVariable& returnValue, const ScriptStatement& statement) override {
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
		registerMethod(new ScriptMethodEntityUnsetNodeTransform(this));
	}
	{
		//
		class ScriptMethodEntityEmitParticles: public ScriptMethod {
		private:
			LogicMiniScript* miniScript { nullptr };
		public:
			ScriptMethodEntityEmitParticles(LogicMiniScript* miniScript):
				ScriptMethod(
					{
						{ .type = ScriptVariableType::TYPE_STRING, .name = "entityId", .optional = false, .assignBack = false },
						{ .type = ScriptVariableType::TYPE_STRING, .name = "childEntityId", .optional = true, .assignBack = false },
					},
					ScriptVariableType::TYPE_INTEGER
				),
				miniScript(miniScript) {}
			const string getMethodName() override {
				return "engine.entity.emitParticles";
			}
			void executeMethod(span<ScriptVariable>& argumentValues, ScriptVariable& returnValue, const ScriptStatement& statement) override {
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
		registerMethod(new ScriptMethodEntityEmitParticles(this));
	}
	// physics
	{
		//
		class ScriptMethodBodyTYPE_STATIC: public ScriptMethod {
		private:
			LogicMiniScript* miniScript { nullptr };
		public:
			ScriptMethodBodyTYPE_STATIC(LogicMiniScript* miniScript):
				ScriptMethod({}, ScriptVariableType::TYPE_INTEGER),
				miniScript(miniScript) {}
			const string getMethodName() override {
				return "world.body.TYPE_STATIC";
			}
			void executeMethod(span<ScriptVariable>& argumentValues, ScriptVariable& returnValue, const ScriptStatement& statement) override {
				returnValue = static_cast<int64_t>(Body::BODYTYPE_STATIC);
			}
			const vector<string>& getContextFunctions() {
				return CONTEXTFUNCTIONS_LOGIC;
			}
		};
		registerMethod(new ScriptMethodBodyTYPE_STATIC(this));
	}
	{
		//
		class ScriptMethodBodyTYPE_DYNAMIC: public ScriptMethod {
		private:
			LogicMiniScript* miniScript { nullptr };
		public:
			ScriptMethodBodyTYPE_DYNAMIC(LogicMiniScript* miniScript):
				ScriptMethod({}, ScriptVariableType::TYPE_INTEGER),
				miniScript(miniScript) {}
			const string getMethodName() override {
				return "world.body.TYPE_DYNAMIC";
			}
			void executeMethod(span<ScriptVariable>& argumentValues, ScriptVariable& returnValue, const ScriptStatement& statement) override {
				returnValue = static_cast<int64_t>(Body::BODYTYPE_DYNAMIC);
			}
			const vector<string>& getContextFunctions() {
				return CONTEXTFUNCTIONS_LOGIC;
			}
		};
		registerMethod(new ScriptMethodBodyTYPE_DYNAMIC(this));
	}
	{
		//
		class ScriptMethodBodyTYPE_COLLISIONSTATIC: public ScriptMethod {
		private:
			LogicMiniScript* miniScript { nullptr };
		public:
			ScriptMethodBodyTYPE_COLLISIONSTATIC(LogicMiniScript* miniScript):
				ScriptMethod({}, ScriptVariableType::TYPE_INTEGER),
				miniScript(miniScript) {}
			const string getMethodName() override {
				return "world.body.TYPE_COLLISION_STATIC";
			}
			void executeMethod(span<ScriptVariable>& argumentValues, ScriptVariable& returnValue, const ScriptStatement& statement) override {
				returnValue = static_cast<int64_t>(Body::BODYTYPE_COLLISION_STATIC);
			}
			const vector<string>& getContextFunctions() {
				return CONTEXTFUNCTIONS_LOGIC;
			}
		};
		registerMethod(new ScriptMethodBodyTYPE_COLLISIONSTATIC(this));
	}
	{
		//
		class ScriptMethodBodyTYPE_COLLISIONDYNAMIC: public ScriptMethod {
		private:
			LogicMiniScript* miniScript { nullptr };
		public:
			ScriptMethodBodyTYPE_COLLISIONDYNAMIC(LogicMiniScript* miniScript):
				ScriptMethod({}, ScriptVariableType::TYPE_INTEGER),
				miniScript(miniScript) {}
			const string getMethodName() override {
				return "world.body.TYPE_COLLISION_DYNAMIC";
			}
			void executeMethod(span<ScriptVariable>& argumentValues, ScriptVariable& returnValue, const ScriptStatement& statement) override {
				returnValue = static_cast<int64_t>(Body::BODYTYPE_COLLISION_DYNAMIC);
			}
			const vector<string>& getContextFunctions() {
				return CONTEXTFUNCTIONS_LOGIC;
			}
		};
		registerMethod(new ScriptMethodBodyTYPE_COLLISIONDYNAMIC(this));
	}
	{
		//
		class ScriptMethodBodyCOLLISION_TYPEID_STATIC: public ScriptMethod {
		private:
			LogicMiniScript* miniScript { nullptr };
		public:
			ScriptMethodBodyCOLLISION_TYPEID_STATIC(LogicMiniScript* miniScript):
				ScriptMethod({}, ScriptVariableType::TYPE_INTEGER),
				miniScript(miniScript) {}
			const string getMethodName() override {
				return "world.body.COLLISION_TYPEID_STATIC";
			}
			void executeMethod(span<ScriptVariable>& argumentValues, ScriptVariable& returnValue, const ScriptStatement& statement) override {
				returnValue = static_cast<int64_t>(Body::COLLISION_TYPEID_STATIC);
			}
			const vector<string>& getContextFunctions() {
				return CONTEXTFUNCTIONS_LOGIC;
			}
		};
		registerMethod(new ScriptMethodBodyCOLLISION_TYPEID_STATIC(this));
	}
	{
		//
		class ScriptMethodBodyCOLLISION_TYPEID_DYNAMIC: public ScriptMethod {
		private:
			LogicMiniScript* miniScript { nullptr };
		public:
			ScriptMethodBodyCOLLISION_TYPEID_DYNAMIC(LogicMiniScript* miniScript):
				ScriptMethod({}, ScriptVariableType::TYPE_INTEGER),
				miniScript(miniScript) {}
			const string getMethodName() override {
				return "world.body.COLLISION_TYPEID_DYNAMIC";
			}
			void executeMethod(span<ScriptVariable>& argumentValues, ScriptVariable& returnValue, const ScriptStatement& statement) override {
				returnValue = static_cast<int64_t>(Body::COLLISION_TYPEID_DYNAMIC);
			}
			const vector<string>& getContextFunctions() {
				return CONTEXTFUNCTIONS_LOGIC;
			}
		};
		registerMethod(new ScriptMethodBodyCOLLISION_TYPEID_DYNAMIC(this));
	}
	{
		//
		class ScriptMethodBodyCOLLISION_TYPEID_3: public ScriptMethod {
		private:
			LogicMiniScript* miniScript { nullptr };
		public:
			ScriptMethodBodyCOLLISION_TYPEID_3(LogicMiniScript* miniScript):
				ScriptMethod({}, ScriptVariableType::TYPE_INTEGER),
				miniScript(miniScript) {}
			const string getMethodName() override {
				return "world.body.COLLISION_TYPEID_3";
			}
			void executeMethod(span<ScriptVariable>& argumentValues, ScriptVariable& returnValue, const ScriptStatement& statement) override {
				returnValue = static_cast<int64_t>(Body::COLLISION_TYPEID_3);
			}
			const vector<string>& getContextFunctions() {
				return CONTEXTFUNCTIONS_LOGIC;
			}
		};
		registerMethod(new ScriptMethodBodyCOLLISION_TYPEID_3(this));
	}
	{
		//
		class ScriptMethodBodyCOLLISION_TYPEID_4: public ScriptMethod {
		private:
			LogicMiniScript* miniScript { nullptr };
		public:
			ScriptMethodBodyCOLLISION_TYPEID_4(LogicMiniScript* miniScript):
				ScriptMethod({}, ScriptVariableType::TYPE_INTEGER),
				miniScript(miniScript) {}
			const string getMethodName() override {
				return "world.body.COLLISION_TYPEID_4";
			}
			void executeMethod(span<ScriptVariable>& argumentValues, ScriptVariable& returnValue, const ScriptStatement& statement) override {
				returnValue = static_cast<int64_t>(Body::COLLISION_TYPEID_4);
			}
			const vector<string>& getContextFunctions() {
				return CONTEXTFUNCTIONS_LOGIC;
			}
		};
		registerMethod(new ScriptMethodBodyCOLLISION_TYPEID_4(this));
	}
	{
		//
		class ScriptMethodBodyCOLLISION_TYPEID_5: public ScriptMethod {
		private:
			LogicMiniScript* miniScript { nullptr };
		public:
			ScriptMethodBodyCOLLISION_TYPEID_5(LogicMiniScript* miniScript):
				ScriptMethod({}, ScriptVariableType::TYPE_INTEGER),
				miniScript(miniScript) {}
			const string getMethodName() override {
				return "world.body.COLLISION_TYPEID_5";
			}
			void executeMethod(span<ScriptVariable>& argumentValues, ScriptVariable& returnValue, const ScriptStatement& statement) override {
				returnValue = static_cast<int64_t>(Body::COLLISION_TYPEID_5);
			}
			const vector<string>& getContextFunctions() {
				return CONTEXTFUNCTIONS_LOGIC;
			}
		};
		registerMethod(new ScriptMethodBodyCOLLISION_TYPEID_5(this));
	}
	{
		//
		class ScriptMethodBodyCOLLISION_TYPEID_6: public ScriptMethod {
		private:
			LogicMiniScript* miniScript { nullptr };
		public:
			ScriptMethodBodyCOLLISION_TYPEID_6(LogicMiniScript* miniScript):
				ScriptMethod({}, ScriptVariableType::TYPE_INTEGER),
				miniScript(miniScript) {}
			const string getMethodName() override {
				return "world.body.COLLISION_TYPEID_6";
			}
			void executeMethod(span<ScriptVariable>& argumentValues, ScriptVariable& returnValue, const ScriptStatement& statement) override {
				returnValue = static_cast<int64_t>(Body::COLLISION_TYPEID_6);
			}
			const vector<string>& getContextFunctions() {
				return CONTEXTFUNCTIONS_LOGIC;
			}
		};
		registerMethod(new ScriptMethodBodyCOLLISION_TYPEID_6(this));
	}
	{
		//
		class ScriptMethodBodyCOLLISION_TYPEID_7: public ScriptMethod {
		private:
			LogicMiniScript* miniScript { nullptr };
		public:
			ScriptMethodBodyCOLLISION_TYPEID_7(LogicMiniScript* miniScript):
				ScriptMethod({}, ScriptVariableType::TYPE_INTEGER),
				miniScript(miniScript) {}
			const string getMethodName() override {
				return "world.body.COLLISION_TYPEID_7";
			}
			void executeMethod(span<ScriptVariable>& argumentValues, ScriptVariable& returnValue, const ScriptStatement& statement) override {
				returnValue = static_cast<int64_t>(Body::COLLISION_TYPEID_7);
			}
			const vector<string>& getContextFunctions() {
				return CONTEXTFUNCTIONS_LOGIC;
			}
		};
		registerMethod(new ScriptMethodBodyCOLLISION_TYPEID_7(this));
	}
	{
		//
		class ScriptMethodBodyCOLLISION_TYPEID_8: public ScriptMethod {
		private:
			LogicMiniScript* miniScript { nullptr };
		public:
			ScriptMethodBodyCOLLISION_TYPEID_8(LogicMiniScript* miniScript):
				ScriptMethod({}, ScriptVariableType::TYPE_INTEGER),
				miniScript(miniScript) {}
			const string getMethodName() override {
				return "world.body.COLLISION_TYPEID_8";
			}
			void executeMethod(span<ScriptVariable>& argumentValues, ScriptVariable& returnValue, const ScriptStatement& statement) override {
				returnValue = static_cast<int64_t>(Body::COLLISION_TYPEID_8);
			}
			const vector<string>& getContextFunctions() {
				return CONTEXTFUNCTIONS_LOGIC;
			}
		};
		registerMethod(new ScriptMethodBodyCOLLISION_TYPEID_8(this));
	}
	{
		//
		class ScriptMethodBodyCOLLISION_TYPEID_9: public ScriptMethod {
		private:
			LogicMiniScript* miniScript { nullptr };
		public:
			ScriptMethodBodyCOLLISION_TYPEID_9(LogicMiniScript* miniScript):
				ScriptMethod({}, ScriptVariableType::TYPE_INTEGER),
				miniScript(miniScript) {}
			const string getMethodName() override {
				return "world.body.COLLISION_TYPEID_9";
			}
			void executeMethod(span<ScriptVariable>& argumentValues, ScriptVariable& returnValue, const ScriptStatement& statement) override {
				returnValue = static_cast<int64_t>(Body::COLLISION_TYPEID_9);
			}
			const vector<string>& getContextFunctions() {
				return CONTEXTFUNCTIONS_LOGIC;
			}
		};
		registerMethod(new ScriptMethodBodyCOLLISION_TYPEID_9(this));
	}
	{
		//
		class ScriptMethodBodyCOLLISION_TYPEID_10: public ScriptMethod {
		private:
			LogicMiniScript* miniScript { nullptr };
		public:
			ScriptMethodBodyCOLLISION_TYPEID_10(LogicMiniScript* miniScript):
				ScriptMethod({}, ScriptVariableType::TYPE_INTEGER),
				miniScript(miniScript) {}
			const string getMethodName() override {
				return "world.body.COLLISION_TYPEID_10";
			}
			void executeMethod(span<ScriptVariable>& argumentValues, ScriptVariable& returnValue, const ScriptStatement& statement) override {
				returnValue = static_cast<int64_t>(Body::COLLISION_TYPEID_10);
			}
			const vector<string>& getContextFunctions() {
				return CONTEXTFUNCTIONS_LOGIC;
			}
		};
		registerMethod(new ScriptMethodBodyCOLLISION_TYPEID_10(this));
	}
	{
		//
		class ScriptMethodBodyCOLLISION_TYPEID_11: public ScriptMethod {
		private:
			LogicMiniScript* miniScript { nullptr };
		public:
			ScriptMethodBodyCOLLISION_TYPEID_11(LogicMiniScript* miniScript):
				ScriptMethod({}, ScriptVariableType::TYPE_INTEGER),
				miniScript(miniScript) {}
			const string getMethodName() override {
				return "world.body.COLLISION_TYPEID_11";
			}
			void executeMethod(span<ScriptVariable>& argumentValues, ScriptVariable& returnValue, const ScriptStatement& statement) override {
				returnValue = static_cast<int64_t>(Body::COLLISION_TYPEID_11);
			}
			const vector<string>& getContextFunctions() {
				return CONTEXTFUNCTIONS_LOGIC;
			}
		};
		registerMethod(new ScriptMethodBodyCOLLISION_TYPEID_11(this));
	}
	{
		//
		class ScriptMethodBodyCOLLISION_TYPEID_12: public ScriptMethod {
		private:
			LogicMiniScript* miniScript { nullptr };
		public:
			ScriptMethodBodyCOLLISION_TYPEID_12(LogicMiniScript* miniScript):
				ScriptMethod({}, ScriptVariableType::TYPE_INTEGER),
				miniScript(miniScript) {}
			const string getMethodName() override {
				return "world.body.COLLISION_TYPEID_12";
			}
			void executeMethod(span<ScriptVariable>& argumentValues, ScriptVariable& returnValue, const ScriptStatement& statement) override {
				returnValue = static_cast<int64_t>(Body::COLLISION_TYPEID_12);
			}
			const vector<string>& getContextFunctions() {
				return CONTEXTFUNCTIONS_LOGIC;
			}
		};
		registerMethod(new ScriptMethodBodyCOLLISION_TYPEID_12(this));
	}
	{
		//
		class ScriptMethodBodyCOLLISION_TYPEID_13: public ScriptMethod {
		private:
			LogicMiniScript* miniScript { nullptr };
		public:
			ScriptMethodBodyCOLLISION_TYPEID_13(LogicMiniScript* miniScript):
				ScriptMethod({}, ScriptVariableType::TYPE_INTEGER),
				miniScript(miniScript) {}
			const string getMethodName() override {
				return "world.body.COLLISION_TYPEID_13";
			}
			void executeMethod(span<ScriptVariable>& argumentValues, ScriptVariable& returnValue, const ScriptStatement& statement) override {
				returnValue = static_cast<int64_t>(Body::COLLISION_TYPEID_13);
			}
			const vector<string>& getContextFunctions() {
				return CONTEXTFUNCTIONS_LOGIC;
			}
		};
		registerMethod(new ScriptMethodBodyCOLLISION_TYPEID_13(this));
	}
	{
		//
		class ScriptMethodBodyCOLLISION_TYPEID_14: public ScriptMethod {
		private:
			LogicMiniScript* miniScript { nullptr };
		public:
			ScriptMethodBodyCOLLISION_TYPEID_14(LogicMiniScript* miniScript):
				ScriptMethod({}, ScriptVariableType::TYPE_INTEGER),
				miniScript(miniScript) {}
			const string getMethodName() override {
				return "world.body.COLLISION_TYPEID_14";
			}
			void executeMethod(span<ScriptVariable>& argumentValues, ScriptVariable& returnValue, const ScriptStatement& statement) override {
				returnValue = static_cast<int64_t>(Body::COLLISION_TYPEID_14);
			}
			const vector<string>& getContextFunctions() {
				return CONTEXTFUNCTIONS_LOGIC;
			}
		};
		registerMethod(new ScriptMethodBodyCOLLISION_TYPEID_14(this));
	}
	{
		//
		class ScriptMethodBodyCOLLISION_TYPEID_15: public ScriptMethod {
		private:
			LogicMiniScript* miniScript { nullptr };
		public:
			ScriptMethodBodyCOLLISION_TYPEID_15(LogicMiniScript* miniScript):
				ScriptMethod({}, ScriptVariableType::TYPE_INTEGER),
				miniScript(miniScript) {}
			const string getMethodName() override {
				return "world.body.COLLISION_TYPEID_15";
			}
			void executeMethod(span<ScriptVariable>& argumentValues, ScriptVariable& returnValue, const ScriptStatement& statement) override {
				returnValue = static_cast<int64_t>(Body::COLLISION_TYPEID_15);
			}
			const vector<string>& getContextFunctions() {
				return CONTEXTFUNCTIONS_LOGIC;
			}
		};
		registerMethod(new ScriptMethodBodyCOLLISION_TYPEID_15(this));
	}
	{
		//
		class ScriptMethodBodyCOLLISION_TYPEID_16: public ScriptMethod {
		private:
			LogicMiniScript* miniScript { nullptr };
		public:
			ScriptMethodBodyCOLLISION_TYPEID_16(LogicMiniScript* miniScript):
				ScriptMethod({}, ScriptVariableType::TYPE_INTEGER),
				miniScript(miniScript) {}
			const string getMethodName() override {
				return "world.body.COLLISION_TYPEID_16";
			}
			void executeMethod(span<ScriptVariable>& argumentValues, ScriptVariable& returnValue, const ScriptStatement& statement) override {
				returnValue = static_cast<int64_t>(Body::COLLISION_TYPEID_16);
			}
			const vector<string>& getContextFunctions() {
				return CONTEXTFUNCTIONS_LOGIC;
			}
		};
		registerMethod(new ScriptMethodBodyCOLLISION_TYPEID_16(this));
	}
	{
		//
		class ScriptMethodBodyCOLLISION_TYPEID_ALL: public ScriptMethod {
		private:
			LogicMiniScript* miniScript { nullptr };
		public:
			ScriptMethodBodyCOLLISION_TYPEID_ALL(LogicMiniScript* miniScript):
				ScriptMethod({}, ScriptVariableType::TYPE_INTEGER),
				miniScript(miniScript) {}
			const string getMethodName() override {
				return "world.body.COLLISION_TYPEID_ALL";
			}
			void executeMethod(span<ScriptVariable>& argumentValues, ScriptVariable& returnValue, const ScriptStatement& statement) override {
				returnValue = static_cast<int64_t>(Body::COLLISION_TYPEID_ALL);
			}
			const vector<string>& getContextFunctions() {
				return CONTEXTFUNCTIONS_LOGIC;
			}
		};
		registerMethod(new ScriptMethodBodyCOLLISION_TYPEID_ALL(this));
	}
	{
		//
		class ScriptMethodBodyIsEnabled: public ScriptMethod {
		private:
			LogicMiniScript* miniScript { nullptr };
		public:
			ScriptMethodBodyIsEnabled(LogicMiniScript* miniScript):
				ScriptMethod(
					{
						{ .type = ScriptVariableType::TYPE_STRING, .name = "bodyId", .optional = false, .assignBack = false }
					},
					ScriptVariableType::TYPE_BOOLEAN
				),
				miniScript(miniScript) {}
			const string getMethodName() override {
				return "world.body.isEnabled";
			}
			void executeMethod(span<ScriptVariable>& argumentValues, ScriptVariable& returnValue, const ScriptStatement& statement) override {
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
		registerMethod(new ScriptMethodBodyIsEnabled(this));
	}
	{
		//
		class ScriptMethodBodySetEnabled: public ScriptMethod {
		private:
			LogicMiniScript* miniScript { nullptr };
		public:
			ScriptMethodBodySetEnabled(LogicMiniScript* miniScript):
				ScriptMethod(
					{
						{ .type = ScriptVariableType::TYPE_STRING, .name = "bodyId", .optional = false, .assignBack = false },
						{ .type = ScriptVariableType::TYPE_BOOLEAN, .name = "enabled", .optional = false, .assignBack = false }
					},
					ScriptVariableType::TYPE_NULL
				),
				miniScript(miniScript) {}
			const string getMethodName() override {
				return "world.body.setEnabled";
			}
			void executeMethod(span<ScriptVariable>& argumentValues, ScriptVariable& returnValue, const ScriptStatement& statement) override {
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
		registerMethod(new ScriptMethodBodySetEnabled(this));
	}
	{
		//
		class ScriptMethodBodyGetType: public ScriptMethod {
		private:
			LogicMiniScript* miniScript { nullptr };
		public:
			ScriptMethodBodyGetType(LogicMiniScript* miniScript):
				ScriptMethod(
					{
						{ .type = ScriptVariableType::TYPE_STRING, .name = "bodyId", .optional = false, .assignBack = false }
					},
					ScriptVariableType::TYPE_INTEGER
				),
				miniScript(miniScript) {}
			const string getMethodName() override {
				return "world.body.getType";
			}
			void executeMethod(span<ScriptVariable>& argumentValues, ScriptVariable& returnValue, const ScriptStatement& statement) override {
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
		registerMethod(new ScriptMethodBodyGetType(this));
	}
	{
		//
		class ScriptMethodBodyGetCollisionTypeId: public ScriptMethod {
		private:
			LogicMiniScript* miniScript { nullptr };
		public:
			ScriptMethodBodyGetCollisionTypeId(LogicMiniScript* miniScript):
				ScriptMethod(
					{
						{ .type = ScriptVariableType::TYPE_STRING, .name = "bodyId", .optional = false, .assignBack = false }
					},
					ScriptVariableType::TYPE_INTEGER
				),
				miniScript(miniScript) {}
			const string getMethodName() override {
				return "world.body.getCollisionTypeId";
			}
			void executeMethod(span<ScriptVariable>& argumentValues, ScriptVariable& returnValue, const ScriptStatement& statement) override {
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
		registerMethod(new ScriptMethodBodyGetCollisionTypeId(this));
	}
	{
		//
		class ScriptMethodBodySetCollisionTypeId: public ScriptMethod {
		private:
			LogicMiniScript* miniScript { nullptr };
		public:
			ScriptMethodBodySetCollisionTypeId(LogicMiniScript* miniScript):
				ScriptMethod(
					{
						{ .type = ScriptVariableType::TYPE_STRING, .name = "bodyId", .optional = false, .assignBack = false },
						{ .type = ScriptVariableType::TYPE_INTEGER, .name = "collisionTypeId", .optional = false, .assignBack = false }
					},
					ScriptVariableType::TYPE_NULL
				),
				miniScript(miniScript) {}
			const string getMethodName() override {
				return "world.body.setCollisionTypeId";
			}
			void executeMethod(span<ScriptVariable>& argumentValues, ScriptVariable& returnValue, const ScriptStatement& statement) override {
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
		registerMethod(new ScriptMethodBodySetCollisionTypeId(this));
	}
	{
		//
		class ScriptMethodBodyGetCollisionTypeIds: public ScriptMethod {
		private:
			LogicMiniScript* miniScript { nullptr };
		public:
			ScriptMethodBodyGetCollisionTypeIds(LogicMiniScript* miniScript):
				ScriptMethod(
					{
						{ .type = ScriptVariableType::TYPE_STRING, .name = "bodyId", .optional = false, .assignBack = false }
					},
					ScriptVariableType::TYPE_INTEGER
				),
				miniScript(miniScript) {}
			const string getMethodName() override {
				return "world.body.getCollisionTypeIds";
			}
			void executeMethod(span<ScriptVariable>& argumentValues, ScriptVariable& returnValue, const ScriptStatement& statement) override {
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
		registerMethod(new ScriptMethodBodyGetCollisionTypeIds(this));
	}
	{
		//
		class ScriptMethodBodySetCollisionTypeIds: public ScriptMethod {
		private:
			LogicMiniScript* miniScript { nullptr };
		public:
			ScriptMethodBodySetCollisionTypeIds(LogicMiniScript* miniScript):
				ScriptMethod(
					{
						{ .type = ScriptVariableType::TYPE_STRING, .name = "bodyId", .optional = false, .assignBack = false },
						{ .type = ScriptVariableType::TYPE_INTEGER, .name = "collisionTypeIds", .optional = false, .assignBack = false }
					},
					ScriptVariableType::TYPE_NULL
				),
				miniScript(miniScript) {}
			const string getMethodName() override {
				return "world.body.setCollisionTypeIds";
			}
			void executeMethod(span<ScriptVariable>& argumentValues, ScriptVariable& returnValue, const ScriptStatement& statement) override {
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
		registerMethod(new ScriptMethodBodySetCollisionTypeIds(this));
	}
	{
		//
		class ScriptMethodBodyGetLinearDamping: public ScriptMethod {
		private:
			LogicMiniScript* miniScript { nullptr };
		public:
			ScriptMethodBodyGetLinearDamping(LogicMiniScript* miniScript):
				ScriptMethod(
					{
						{ .type = ScriptVariableType::TYPE_STRING, .name = "bodyId", .optional = false, .assignBack = false }
					},
					ScriptVariableType::TYPE_FLOAT
				),
				miniScript(miniScript) {}
			const string getMethodName() override {
				return "world.body.getLinearDamping";
			}
			void executeMethod(span<ScriptVariable>& argumentValues, ScriptVariable& returnValue, const ScriptStatement& statement) override {
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
		registerMethod(new ScriptMethodBodyGetLinearDamping(this));
	}
	{
		//
		class ScriptMethodBodySetLinearDamping: public ScriptMethod {
		private:
			LogicMiniScript* miniScript { nullptr };
		public:
			ScriptMethodBodySetLinearDamping(LogicMiniScript* miniScript):
				ScriptMethod(
					{
						{ .type = ScriptVariableType::TYPE_STRING, .name = "bodyId", .optional = false, .assignBack = false },
						{ .type = ScriptVariableType::TYPE_FLOAT, .name = "linearDamping", .optional = false, .assignBack = false }
					},
					ScriptVariableType::TYPE_NULL
				),
				miniScript(miniScript) {}
			const string getMethodName() override {
				return "world.body.setLinearDamping";
			}
			void executeMethod(span<ScriptVariable>& argumentValues, ScriptVariable& returnValue, const ScriptStatement& statement) override {
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
		registerMethod(new ScriptMethodBodySetLinearDamping(this));
	}
	{
		//
		class ScriptMethodBodyGetAngularDamping: public ScriptMethod {
		private:
			LogicMiniScript* miniScript { nullptr };
		public:
			ScriptMethodBodyGetAngularDamping(LogicMiniScript* miniScript):
				ScriptMethod(
					{
						{ .type = ScriptVariableType::TYPE_STRING, .name = "bodyId", .optional = false, .assignBack = false }
					},
					ScriptVariableType::TYPE_FLOAT
				),
				miniScript(miniScript) {}
			const string getMethodName() override {
				return "world.body.getAngularDamping";
			}
			void executeMethod(span<ScriptVariable>& argumentValues, ScriptVariable& returnValue, const ScriptStatement& statement) override {
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
		registerMethod(new ScriptMethodBodyGetAngularDamping(this));
	}
	{
		//
		class ScriptMethodBodySetAngularDamping: public ScriptMethod {
		private:
			LogicMiniScript* miniScript { nullptr };
		public:
			ScriptMethodBodySetAngularDamping(LogicMiniScript* miniScript):
				ScriptMethod(
					{
						{ .type = ScriptVariableType::TYPE_STRING, .name = "bodyId", .optional = false, .assignBack = false },
						{ .type = ScriptVariableType::TYPE_FLOAT, .name = "angularDamping", .optional = false, .assignBack = false }
					},
					ScriptVariableType::TYPE_NULL
				),
				miniScript(miniScript) {}
			const string getMethodName() override {
				return "world.body.setAngularDamping";
			}
			void executeMethod(span<ScriptVariable>& argumentValues, ScriptVariable& returnValue, const ScriptStatement& statement) override {
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
		registerMethod(new ScriptMethodBodySetAngularDamping(this));
	}
	{
		//
		class ScriptMethodBodyGetLinearVelocity: public ScriptMethod {
		private:
			LogicMiniScript* miniScript { nullptr };
		public:
			ScriptMethodBodyGetLinearVelocity(LogicMiniScript* miniScript):
				ScriptMethod(
					{
						{ .type = ScriptVariableType::TYPE_STRING, .name = "bodyId", .optional = false, .assignBack = false }
					},
					ScriptVariableType::TYPE_VECTOR3
				),
				miniScript(miniScript) {}
			const string getMethodName() override {
				return "world.body.getLinearVelocity";
			}
			void executeMethod(span<ScriptVariable>& argumentValues, ScriptVariable& returnValue, const ScriptStatement& statement) override {
				string bodyId;
				if (miniScript->getStringValue(argumentValues, 0, bodyId) == true) {
					auto body = miniScript->context->getWorld()->getBody(bodyId);
					if (body != nullptr) {
						returnValue = body->getLinearVelocity();
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
		registerMethod(new ScriptMethodBodyGetLinearVelocity(this));
	}
	{
		//
		class ScriptMethodBodySetLinearVelocity: public ScriptMethod {
		private:
			LogicMiniScript* miniScript { nullptr };
		public:
			ScriptMethodBodySetLinearVelocity(LogicMiniScript* miniScript):
				ScriptMethod(
					{
						{ .type = ScriptVariableType::TYPE_STRING, .name = "bodyId", .optional = false, .assignBack = false },
						{ .type = ScriptVariableType::TYPE_VECTOR3, .name = "linearVelocity", .optional = false, .assignBack = false }
					},
					ScriptVariableType::TYPE_NULL
				),
				miniScript(miniScript) {}
			const string getMethodName() override {
				return "world.body.setLinearVelocity";
			}
			void executeMethod(span<ScriptVariable>& argumentValues, ScriptVariable& returnValue, const ScriptStatement& statement) override {
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
		registerMethod(new ScriptMethodBodySetLinearVelocity(this));
	}
	{
		//
		class ScriptMethodBodyGetAngularVelocity: public ScriptMethod {
		private:
			LogicMiniScript* miniScript { nullptr };
		public:
			ScriptMethodBodyGetAngularVelocity(LogicMiniScript* miniScript):
				ScriptMethod(
					{
						{ .type = ScriptVariableType::TYPE_STRING, .name = "bodyId", .optional = false, .assignBack = false }
					},
					ScriptVariableType::TYPE_VECTOR3
				),
				miniScript(miniScript) {}
			const string getMethodName() override {
				return "world.body.getAngularVelocity";
			}
			void executeMethod(span<ScriptVariable>& argumentValues, ScriptVariable& returnValue, const ScriptStatement& statement) override {
				string bodyId;
				if (miniScript->getStringValue(argumentValues, 0, bodyId) == true) {
					auto body = miniScript->context->getWorld()->getBody(bodyId);
					if (body != nullptr) {
						returnValue = body->getAngularVelocity();
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
		registerMethod(new ScriptMethodBodyGetAngularVelocity(this));
	}
	{
		//
		class ScriptMethodBodySetAngularVelocity: public ScriptMethod {
		private:
			LogicMiniScript* miniScript { nullptr };
		public:
			ScriptMethodBodySetAngularVelocity(LogicMiniScript* miniScript):
				ScriptMethod(
					{
						{ .type = ScriptVariableType::TYPE_STRING, .name = "bodyId", .optional = false, .assignBack = false },
						{ .type = ScriptVariableType::TYPE_VECTOR3, .name = "angularVelocity", .optional = false, .assignBack = false }
					},
					ScriptVariableType::TYPE_NULL
				),
				miniScript(miniScript) {}
			const string getMethodName() override {
				return "world.body.setAngularVelocity";
			}
			void executeMethod(span<ScriptVariable>& argumentValues, ScriptVariable& returnValue, const ScriptStatement& statement) override {
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
		registerMethod(new ScriptMethodBodySetAngularVelocity(this));
	}
	{
		//
		class ScriptMethodBodyAddForce: public ScriptMethod {
		private:
			LogicMiniScript* miniScript { nullptr };
		public:
			ScriptMethodBodyAddForce(LogicMiniScript* miniScript):
				ScriptMethod(
					{
						{ .type = ScriptVariableType::TYPE_STRING, .name = "bodyId", .optional = false, .assignBack = false },
						{ .type = ScriptVariableType::TYPE_VECTOR3, .name = "force", .optional = false, .assignBack = false },
						{ .type = ScriptVariableType::TYPE_VECTOR3, .name = "origin", .optional = true, .assignBack = false }
					},
					ScriptVariableType::TYPE_NULL
				),
				miniScript(miniScript) {}
			const string getMethodName() override {
				return "world.body.addForce";
			}
			void executeMethod(span<ScriptVariable>& argumentValues, ScriptVariable& returnValue, const ScriptStatement& statement) override {
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
		registerMethod(new ScriptMethodBodyAddForce(this));
	}
	{
		//
		class ScriptMethodBodyAddTorque: public ScriptMethod {
		private:
			LogicMiniScript* miniScript { nullptr };
		public:
			ScriptMethodBodyAddTorque(LogicMiniScript* miniScript):
				ScriptMethod(
					{
						{ .type = ScriptVariableType::TYPE_STRING, .name = "bodyId", .optional = false, .assignBack = false },
						{ .type = ScriptVariableType::TYPE_VECTOR3, .name = "torque", .optional = false, .assignBack = false }
					},
					ScriptVariableType::TYPE_NULL
				),
				miniScript(miniScript) {}
			const string getMethodName() override {
				return "world.body.addTorque";
			}
			void executeMethod(span<ScriptVariable>& argumentValues, ScriptVariable& returnValue, const ScriptStatement& statement) override {
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
		registerMethod(new ScriptMethodBodyAddTorque(this));
	}
	{
		//
		class ScriptMethodBodyGetTransform: public ScriptMethod {
		private:
			LogicMiniScript* miniScript { nullptr };
		public:
			ScriptMethodBodyGetTransform(LogicMiniScript* miniScript):
				ScriptMethod(
					{
						{ .type = ScriptVariableType::TYPE_STRING, .name = "bodyId", .optional = false, .assignBack = false }
					},
					ScriptVariableType::TYPE_TRANSFORM
				),
				miniScript(miniScript) {}
			const string getMethodName() override {
				return "world.body.getTransform";
			}
			void executeMethod(span<ScriptVariable>& argumentValues, ScriptVariable& returnValue, const ScriptStatement& statement) override {
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
						returnValue = transform;
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
		registerMethod(new ScriptMethodBodyGetTransform(this));
	}
	{
		//
		class ScriptMethodBodySetTransform: public ScriptMethod {
		private:
			LogicMiniScript* miniScript { nullptr };
		public:
			ScriptMethodBodySetTransform(LogicMiniScript* miniScript):
				ScriptMethod(
					{
						{ .type = ScriptVariableType::TYPE_STRING, .name = "bodyId", .optional = false, .assignBack = false },
						{ .type = ScriptVariableType::TYPE_TRANSFORM, .name = "transform", .optional = false, .assignBack = false }
					},
					ScriptVariableType::TYPE_NULL
				),
				miniScript(miniScript) {}
			const string getMethodName() override {
				return "world.body.setTransform";
			}
			void executeMethod(span<ScriptVariable>& argumentValues, ScriptVariable& returnValue, const ScriptStatement& statement) override {
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
		registerMethod(new ScriptMethodBodySetTransform(this));
	}
	{
		//
		class ScriptMethodWorldDetermineHeight: public ScriptMethod {
		private:
			LogicMiniScript* miniScript { nullptr };
		public:
			ScriptMethodWorldDetermineHeight(LogicMiniScript* miniScript):
				ScriptMethod(
					{
						{ .type = ScriptVariableType::TYPE_INTEGER, .name = "collisionTypeIds", .optional = false, .assignBack = false },
						{ .type = ScriptVariableType::TYPE_FLOAT, .name = "stepUpMax", .optional = false, .assignBack = false },
						{ .type = ScriptVariableType::TYPE_VECTOR3, .name = "point", .optional = false, .assignBack = false },
						{ .type = ScriptVariableType::TYPE_VECTOR3, .name = "heightPoint", .optional = false, .assignBack = true },
						{ .type = ScriptVariableType::TYPE_STRING, .name = "bodyId", .optional = true, .assignBack = true },
						{ .type = ScriptVariableType::TYPE_FLOAT, .name = "minHeight", .optional = true, .assignBack = false },
						{ .type = ScriptVariableType::TYPE_FLOAT, .name = "maxHeight", .optional = true, .assignBack = false }
					},
					ScriptVariableType::TYPE_BOOLEAN
				),
				miniScript(miniScript) {}
			const string getMethodName() override {
				return "world.determineHeight";
			}
			void executeMethod(span<ScriptVariable>& argumentValues, ScriptVariable& returnValue, const ScriptStatement& statement) override {
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
						argumentValues[3] = heightPoint;
						if (argumentValues.size() >= 5) argumentValues[4] = body->getId();
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
		registerMethod(new ScriptMethodWorldDetermineHeight(this));
	}
	{
		//
		class ScriptMethodWorldDoRayCasting: public ScriptMethod {
		private:
			LogicMiniScript* miniScript { nullptr };
		public:
			ScriptMethodWorldDoRayCasting(LogicMiniScript* miniScript):
				ScriptMethod(
					{
						{ .type = ScriptVariableType::TYPE_INTEGER, .name = "collisionTypeIds", .optional = false, .assignBack = false },
						{ .type = ScriptVariableType::TYPE_VECTOR3, .name = "start", .optional = false, .assignBack = false },
						{ .type = ScriptVariableType::TYPE_VECTOR3, .name = "end", .optional = false, .assignBack = false },
						{ .type = ScriptVariableType::TYPE_VECTOR3, .name = "hitPoint", .optional = false, .assignBack = true },
						{ .type = ScriptVariableType::TYPE_STRING, .name = "bodyId", .optional = true, .assignBack = true },
						{ .type = ScriptVariableType::TYPE_STRING, .name = "actorId", .optional = true, .assignBack = false },
					},
					ScriptVariableType::TYPE_BOOLEAN
				),
				miniScript(miniScript) {}
			const string getMethodName() override {
				return "world.doRayCasting";
			}
			void executeMethod(span<ScriptVariable>& argumentValues, ScriptVariable& returnValue, const ScriptStatement& statement) override {
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
						argumentValues[3] = hitPoint;
						if (argumentValues.size() >= 5) argumentValues[4] = body->getId();
						returnValue.setValue(true);
					} else {
						returnValue.setValue(false);
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
		registerMethod(new ScriptMethodWorldDoRayCasting(this));
	}
	{
		//
		class ScriptMethodWorldDoCollide: public ScriptMethod {
		private:
			LogicMiniScript* miniScript { nullptr };
		public:
			ScriptMethodWorldDoCollide(LogicMiniScript* miniScript):
				ScriptMethod(
					{
						{ .type = ScriptVariableType::TYPE_STRING, .name = "bodyId1", .optional = false, .assignBack = false },
						{ .type = ScriptVariableType::TYPE_STRING, .name = "bodyId2", .optional = false, .assignBack = false }
					},
					ScriptVariableType::TYPE_BOOLEAN
				),
				miniScript(miniScript) {}
			const string getMethodName() override {
				return "world.doCollide";
			}
			void executeMethod(span<ScriptVariable>& argumentValues, ScriptVariable& returnValue, const ScriptStatement& statement) override {
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
		registerMethod(new ScriptMethodWorldDoCollide(this));
	}
	{
		//
		class ScriptMethodWorldDoesCollideWith: public ScriptMethod {
		private:
			LogicMiniScript* miniScript { nullptr };
		public:
			ScriptMethodWorldDoesCollideWith(LogicMiniScript* miniScript):
				ScriptMethod(
					{
						{ .type = ScriptVariableType::TYPE_INTEGER, .name = "collisionTypeIds", .optional = false, .assignBack = false },
						{ .type = ScriptVariableType::TYPE_STRING, .name = "bodyId", .optional = false, .assignBack = false }
					},
					ScriptVariableType::TYPE_ARRAY
				),
				miniScript(miniScript) {}
			const string getMethodName() override {
				return "world.doesCollideWith";
			}
			void executeMethod(span<ScriptVariable>& argumentValues, ScriptVariable& returnValue, const ScriptStatement& statement) override {
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
						returnValue.setType(MiniScript::TYPE_ARRAY);
						for (auto collisionBody: collisionBodies) {
							returnValue.pushArrayValue(collisionBody->getId());
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
		registerMethod(new ScriptMethodWorldDoesCollideWith(this));
	}
	// path finding
	{
		//
		class ScriptMethodPathFindingSTATE_IDLE: public ScriptMethod {
		private:
			LogicMiniScript* miniScript { nullptr };
		public:
			ScriptMethodPathFindingSTATE_IDLE(LogicMiniScript* miniScript):
				ScriptMethod({}, ScriptVariableType::TYPE_INTEGER),
				miniScript(miniScript) {}
			const string getMethodName() override {
				return "pathfinding.STATE_IDLE";
			}
			void executeMethod(span<ScriptVariable>& argumentValues, ScriptVariable& returnValue, const ScriptStatement& statement) override {
				returnValue = static_cast<int64_t>(Context::PathFindingThread::STATE_IDLE);
			}
			const vector<string>& getContextFunctions() {
				return CONTEXTFUNCTIONS_LOGIC;
			}
		};
		registerMethod(new ScriptMethodPathFindingSTATE_IDLE(this));
	}
	{
		//
		class ScriptMethodPathFindingSTATE_TRYLOCK_FAILED: public ScriptMethod {
		private:
			LogicMiniScript* miniScript { nullptr };
		public:
			ScriptMethodPathFindingSTATE_TRYLOCK_FAILED(LogicMiniScript* miniScript):
				ScriptMethod({}, ScriptVariableType::TYPE_INTEGER),
				miniScript(miniScript) {}
			const string getMethodName() override {
				return "pathfinding.STATE_TRYLOCK_FAILED";
			}
			void executeMethod(span<ScriptVariable>& argumentValues, ScriptVariable& returnValue, const ScriptStatement& statement) override {
				returnValue = static_cast<int64_t>(Context::PathFindingThread::STATE_TRYLOCK_FAILED);
			}
			const vector<string>& getContextFunctions() {
				return CONTEXTFUNCTIONS_LOGIC;
			}
		};
		registerMethod(new ScriptMethodPathFindingSTATE_TRYLOCK_FAILED(this));
	}
	{
		//
		class ScriptMethodPathFindingSTATE_PATHFINDING_OTHER: public ScriptMethod {
		private:
			LogicMiniScript* miniScript { nullptr };
		public:
			ScriptMethodPathFindingSTATE_PATHFINDING_OTHER(LogicMiniScript* miniScript):
				ScriptMethod({}, ScriptVariableType::TYPE_INTEGER),
				miniScript(miniScript) {}
			const string getMethodName() override {
				return "pathfinding.STATE_PATHFINDING_OTHER";
			}
			void executeMethod(span<ScriptVariable>& argumentValues, ScriptVariable& returnValue, const ScriptStatement& statement) override {
				returnValue = static_cast<int64_t>(Context::PathFindingThread::STATE_PATHFINDING_OTHER);
			}
			const vector<string>& getContextFunctions() {
				return CONTEXTFUNCTIONS_LOGIC;
			}
		};
		registerMethod(new ScriptMethodPathFindingSTATE_PATHFINDING_OTHER(this));
	}
	{
		//
		class ScriptMethodPathFindingSTATE_PATHFINDING: public ScriptMethod {
		private:
			LogicMiniScript* miniScript { nullptr };
		public:
			ScriptMethodPathFindingSTATE_PATHFINDING(LogicMiniScript* miniScript):
				ScriptMethod({}, ScriptVariableType::TYPE_INTEGER),
				miniScript(miniScript) {}
			const string getMethodName() override {
				return "pathfinding.STATE_PATHFINDING";
			}
			void executeMethod(span<ScriptVariable>& argumentValues, ScriptVariable& returnValue, const ScriptStatement& statement) override {
				returnValue = static_cast<int64_t>(Context::PathFindingThread::STATE_PATHFINDING);
			}
			const vector<string>& getContextFunctions() {
				return CONTEXTFUNCTIONS_LOGIC;
			}
		};
		registerMethod(new ScriptMethodPathFindingSTATE_PATHFINDING(this));
	}
	{
		//
		class ScriptMethodPathFindingSTATE_PATHFINDING_FAILED: public ScriptMethod {
		private:
			LogicMiniScript* miniScript { nullptr };
		public:
			ScriptMethodPathFindingSTATE_PATHFINDING_FAILED(LogicMiniScript* miniScript):
				ScriptMethod({}, ScriptVariableType::TYPE_INTEGER),
				miniScript(miniScript) {}
			const string getMethodName() override {
				return "pathfinding.STATE_PATHFINDING_FAILED";
			}
			void executeMethod(span<ScriptVariable>& argumentValues, ScriptVariable& returnValue, const ScriptStatement& statement) override {
				returnValue = static_cast<int64_t>(Context::PathFindingThread::STATE_PATHFINDING_FAILED);
			}
			const vector<string>& getContextFunctions() {
				return CONTEXTFUNCTIONS_LOGIC;
			}
		};
		registerMethod(new ScriptMethodPathFindingSTATE_PATHFINDING_FAILED(this));
	}
	{
		//
		class ScriptMethodPathFindingSTATE_PATHFINDING_SUCCESS: public ScriptMethod {
		private:
			LogicMiniScript* miniScript { nullptr };
		public:
			ScriptMethodPathFindingSTATE_PATHFINDING_SUCCESS(LogicMiniScript* miniScript):
				ScriptMethod({}, ScriptVariableType::TYPE_INTEGER),
				miniScript(miniScript) {}
			const string getMethodName() override {
				return "pathfinding.STATE_PATHFINDING_SUCCESS";
			}
			void executeMethod(span<ScriptVariable>& argumentValues, ScriptVariable& returnValue, const ScriptStatement& statement) override {
				returnValue = static_cast<int64_t>(Context::PathFindingThread::STATE_PATHFINDING_SUCCESS);
			}
			const vector<string>& getContextFunctions() {
				return CONTEXTFUNCTIONS_LOGIC;
			}
		};
		registerMethod(new ScriptMethodPathFindingSTATE_PATHFINDING_SUCCESS(this));
	}
	{
		//
		class ScriptMethodPathFindingFindPath: public ScriptMethod {
		private:
			LogicMiniScript* miniScript { nullptr };
		public:
			ScriptMethodPathFindingFindPath(LogicMiniScript* miniScript):
				ScriptMethod(
					{
						{ .type = ScriptVariableType::TYPE_STRING, .name = "logicId", .optional = false, .assignBack = false },
						{ .type = ScriptVariableType::TYPE_VECTOR3, .name = "startPosition", .optional = false, .assignBack = false },
						{ .type = ScriptVariableType::TYPE_VECTOR3, .name = "endPosition", .optional = false, .assignBack = false },
						{ .type = ScriptVariableType::TYPE_ARRAY, .name = "path", .optional = false, .assignBack = true },
					},
					ScriptVariableType::TYPE_INTEGER
				),
				miniScript(miniScript) {}
			const string getMethodName() override {
				return "pathfinding.findPath";
			}
			void executeMethod(span<ScriptVariable>& argumentValues, ScriptVariable& returnValue, const ScriptStatement& statement) override {
				string logicId;
				Vector3 startPosition;
				Vector3 endPosition;
				if (argumentValues.size() == 4 &&
					miniScript->getStringValue(argumentValues, 0, logicId) == true &&
					miniScript->getVector3Value(argumentValues, 1, startPosition) == true &&
					miniScript->getVector3Value(argumentValues, 2, endPosition) == true) {
					argumentValues[3].setType(MiniScript::TYPE_ARRAY);
					vector<Vector3> path;
					auto pathFindingState = miniScript->context->getPathFinding()->findPath(logicId, logicId, startPosition, endPosition, path);
					returnValue = static_cast<int64_t>(pathFindingState);
					for (auto& position: path) {
						argumentValues[3].pushArrayValue(position);
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
		registerMethod(new ScriptMethodPathFindingFindPath(this));
	}
	// scene
	{
		//
		class ScriptMethodSceneGetWidth: public ScriptMethod {
		private:
			LogicMiniScript* miniScript { nullptr };
		public:
			ScriptMethodSceneGetWidth(LogicMiniScript* miniScript):
				ScriptMethod({}, ScriptVariableType::TYPE_FLOAT),
				miniScript(miniScript) {}
			const string getMethodName() override {
				return "scene.getWidth";
			}
			void executeMethod(span<ScriptVariable>& argumentValues, ScriptVariable& returnValue, const ScriptStatement& statement) override {
				returnValue = miniScript->context->getScene()->getBoundingBox()->getDimensions().getX();
			}
			const vector<string>& getContextFunctions() {
				return CONTEXTFUNCTIONS_ALL;
			}
		};
		registerMethod(new ScriptMethodSceneGetWidth(this));
	}
	{
		//
		class ScriptMethodSceneGetHeight: public ScriptMethod {
		private:
			LogicMiniScript* miniScript { nullptr };
		public:
			ScriptMethodSceneGetHeight(LogicMiniScript* miniScript):
				ScriptMethod({}, ScriptVariableType::TYPE_FLOAT),
				miniScript(miniScript) {}
			const string getMethodName() override {
				return "scene.getHeight";
			}
			void executeMethod(span<ScriptVariable>& argumentValues, ScriptVariable& returnValue, const ScriptStatement& statement) override {
				returnValue = miniScript->context->getScene()->getBoundingBox()->getDimensions().getY();
			}
			const vector<string>& getContextFunctions() {
				return CONTEXTFUNCTIONS_ALL;
			}
		};
		registerMethod(new ScriptMethodSceneGetHeight(this));
	}
	{
		//
		class ScriptMethodSceneGetDepth: public ScriptMethod {
		private:
			LogicMiniScript* miniScript { nullptr };
		public:
			ScriptMethodSceneGetDepth(LogicMiniScript* miniScript):
				ScriptMethod({}, ScriptVariableType::TYPE_FLOAT),
				miniScript(miniScript) {}
			const string getMethodName() override {
				return "scene.getDepth";
			}
			void executeMethod(span<ScriptVariable>& argumentValues, ScriptVariable& returnValue, const ScriptStatement& statement) override {
				returnValue = miniScript->context->getScene()->getBoundingBox()->getDimensions().getZ();
			}
			const vector<string>& getContextFunctions() {
				return CONTEXTFUNCTIONS_ALL;
			}
		};
		registerMethod(new ScriptMethodSceneGetDepth(this));
	}
	// sceneconnector
	{
		//
		class ScriptMethodSceneConnectorSpawnPrototype: public ScriptMethod {
		private:
			LogicMiniScript* miniScript { nullptr };
		public:
			ScriptMethodSceneConnectorSpawnPrototype(LogicMiniScript* miniScript):
				ScriptMethod(
					{
						{ .type = ScriptVariableType::TYPE_STRING, .name = "pathName", .optional = false, .assignBack = false },
						{ .type = ScriptVariableType::TYPE_STRING, .name = "fileName", .optional = false, .assignBack = false },
						{ .type = ScriptVariableType::TYPE_STRING, .name = "id", .optional = false, .assignBack = false },
						{ .type = ScriptVariableType::TYPE_TRANSFORM, .name = "transform", .optional = false, .assignBack = false },
						{ .type = ScriptVariableType::TYPE_STRING, .name = "hierarchyId", .optional = true, .assignBack = false },
						{ .type = ScriptVariableType::TYPE_STRING, .name = "hierarchyParentId", .optional = true, .assignBack = false },
					},
					ScriptVariableType::TYPE_NULL
				),
				miniScript(miniScript) {}
			const string getMethodName() override {
				return "sceneconnector.spawnPrototype";
			}
			void executeMethod(span<ScriptVariable>& argumentValues, ScriptVariable& returnValue, const ScriptStatement& statement) override {
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
							_pathName = FileSystem::getInstance()->getCanonicalPath(miniScript->context->getApplicationRootPathName(), pathName);
						}
						Prototype* prototype = nullptr;
						auto canonicalPath = FileSystem::getInstance()->getCanonicalPath(_pathName, fileName);
						auto prototypeIt = miniScript->prototypes.find(canonicalPath);
						if (prototypeIt != miniScript->prototypes.end()) {
							prototypeIt->second.counter++;
							prototype = prototypeIt->second.prototype;
						} else {
							prototype = PrototypeReader::read(_pathName, fileName);
							miniScript->prototypes[canonicalPath] = {
								.counter = 1,
								.prototype = prototype
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
						Console::println("ScriptMethodSceneConnectorSpawnPrototype::executeMethod(): An error occurred: " + string(exception.what()));
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
		registerMethod(new ScriptMethodSceneConnectorSpawnPrototype(this));
	}
	{
		//
		class ScriptMethodSceneConnectorAttachPrototype: public ScriptMethod {
		private:
			LogicMiniScript* miniScript { nullptr };
		public:
			ScriptMethodSceneConnectorAttachPrototype(LogicMiniScript* miniScript):
				ScriptMethod(
					{
						{ .type = ScriptVariableType::TYPE_STRING, .name = "pathName", .optional = false, .assignBack = false },
						{ .type = ScriptVariableType::TYPE_STRING, .name = "fileName", .optional = false, .assignBack = false },
						{ .type = ScriptVariableType::TYPE_STRING, .name = "id", .optional = false, .assignBack = false },
						{ .type = ScriptVariableType::TYPE_STRING, .name = "attachNodeId", .optional = false, .assignBack = false },
						{ .type = ScriptVariableType::TYPE_TRANSFORM, .name = "transform", .optional = false, .assignBack = false },
						{ .type = ScriptVariableType::TYPE_STRING, .name = "parentId", .optional = true, .assignBack = false },
					},
					ScriptVariableType::TYPE_NULL
				),
				miniScript(miniScript) {}
			const string getMethodName() override {
				return "sceneconnector.attachPrototype";
			}
			void executeMethod(span<ScriptVariable>& argumentValues, ScriptVariable& returnValue, const ScriptStatement& statement) override {
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
							_pathName = FileSystem::getInstance()->getCanonicalPath(miniScript->context->getApplicationRootPathName(), pathName);
						}
						Prototype* prototype = nullptr;
						auto canonicalPath = FileSystem::getInstance()->getCanonicalPath(_pathName, fileName);
						auto prototypeIt = miniScript->prototypes.find(canonicalPath);
						if (prototypeIt != miniScript->prototypes.end()) {
							prototypeIt->second.counter++;
							prototype = prototypeIt->second.prototype;
						} else {
							prototype = PrototypeReader::read(_pathName, fileName);
							miniScript->prototypes[canonicalPath] = {
								.counter = 1,
								.prototype = prototype
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
						Console::println("ScriptMethodSceneConnectorAttachPrototype::executeMethod(): An error occurred: " + string(exception.what()));
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
		registerMethod(new ScriptMethodSceneConnectorAttachPrototype(this));
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
	for (auto& event: keyEvents) {
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
	for (auto& event: mouseEvents) {
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
