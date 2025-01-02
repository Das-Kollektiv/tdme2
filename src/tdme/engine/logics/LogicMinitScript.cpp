#include <tdme/engine/logics/LogicMinitScript.h>

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
#include <tdme/engine/logics/MinitScriptLogic.h>
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
#include <tdme/minitscript/EngineMinitScript.h>
#include <tdme/utilities/UTF8CharacterIterator.h>

using std::move;
using std::span;
using std::string;
using std::to_string;
using std::unique_ptr;
using std::vector;

using tdme::engine::logics::LogicMinitScript;

using tdme::audio::Audio;
using tdme::engine::fileio::prototypes::PrototypeReader;
using tdme::engine::logics::Context;
using tdme::engine::logics::Logic;
using tdme::engine::logics::MinitScriptLogic;
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
using tdme::minitscript::EngineMinitScript;
using tdme::utilities::UTF8CharacterIterator;

const vector<string> LogicMinitScript::CONTEXTFUNCTIONS_ENGINE = { "initializeEngine", "updateEngine" };
const vector<string> LogicMinitScript::CONTEXTFUNCTIONS_LOGIC = { "initializeLogic", "updateLogic", "onLogicAdded", "onLogicsProcessed" };
const vector<string> LogicMinitScript::CONTEXTFUNCTIONS_ENGINELOGIC = {
	// engine
	"initializeEngine", "updateEngine",
	// logic
	"initializeLogic", "updateLogic", "onLogicAdded", "onLogicsProcessed"
};

LogicMinitScript::LogicMinitScript(): EngineMinitScript(), prototypesToAddMutex("prototypetoadd-mutex") {
}

LogicMinitScript::~LogicMinitScript() {
}

const string LogicMinitScript::getBaseClassHeader() {
	return "tdme/engine/logics/LogicMinitScript.h";
}

const string LogicMinitScript::getBaseClass() {
	return "tdme::engine::logics::LogicMinitScript";
}

const vector<string> LogicMinitScript::getTranspilationUnits() {
	auto transpilationUnits = EngineMinitScript::getTranspilationUnits();
	transpilationUnits.push_back("src/tdme/engine/logics/LogicMinitScript.cpp");
	return transpilationUnits;
}

inline Entity* LogicMinitScript::getEntity(const string& entityId, const string& childEntityId) {
	auto entity = context->getEngine()->getEntity(entityId);
	if (entity == nullptr) return entity;
	if (childEntityId.empty() == false) {
		if (entity->getEntityType() == Entity::ENTITYTYPE_ENTITYHIERARCHY) {
			auto entityHierarchy = static_cast<EntityHierarchy*>(entity);
			return entityHierarchy->getEntity(childEntityId);
		} else {
			Console::printLine("LogicMinitScript::getEntity(): no entity hierarchy: can not resolve child entity by given id: " + childEntityId);
			return nullptr;
		}
	} else {
		return entity;
	}
}

void LogicMinitScript::registerStateMachineStates() {
	EngineMinitScript::registerStateMachineStates();
}

void LogicMinitScript::registerMethods() {
	EngineMinitScript::registerMethods();
	{
		//
		class MethodApplicationRunsInEditor: public Method {
		private:
			LogicMinitScript* minitScript { nullptr };
		public:
			MethodApplicationRunsInEditor(LogicMinitScript* minitScript):
				Method({}, VariableType::TYPE_BOOLEAN),
				minitScript(minitScript) {}
			const string getMethodName() override {
				return "application.runsInEditor";
			}
			void executeMethod(span<Variable>& arguments, Variable& returnValue, const SubStatement& subStatement) override {
				minitScript->setValue(returnValue, minitScript->logic->isRunningInEditor());
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
			LogicMinitScript* minitScript { nullptr };
		public:
			MethodApplicationIsFullScreen(LogicMinitScript* minitScript):
				Method({}, VariableType::TYPE_BOOLEAN),
				minitScript(minitScript) {}
			const string getMethodName() override {
				return "application.isFullScreen";
			}
			void executeMethod(span<Variable>& arguments, Variable& returnValue, const SubStatement& subStatement) override {
				minitScript->setValue(returnValue, Editor::getInstance() != nullptr?Editor::getInstance()->isFullScreen():false);
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
			LogicMinitScript* minitScript { nullptr };
		public:
			MethodLogicGetId(LogicMinitScript* minitScript):
				Method({}, VariableType::TYPE_STRING),
				minitScript(minitScript) {}
			const string getMethodName() override {
				return "logic.getId";
			}
			void executeMethod(span<Variable>& arguments, Variable& returnValue, const SubStatement& subStatement) override {
				minitScript->setValue(returnValue, minitScript->logic->getId());
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
			LogicMinitScript* minitScript { nullptr };
		public:
			MethodLogicGetHierarchyId(LogicMinitScript* minitScript):
				Method({}, VariableType::TYPE_STRING),
				minitScript(minitScript) {}
			const string getMethodName() override {
				return "logic.getHierarchyId";
			}
			void executeMethod(span<Variable>& arguments, Variable& returnValue, const SubStatement& subStatement) override {
				minitScript->setValue(returnValue, minitScript->logic->getHierarchyId());
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
			LogicMinitScript* minitScript { nullptr };
		public:
			MethodLogicGetHierarchyParentId(LogicMinitScript* minitScript):
				Method({}, VariableType::TYPE_STRING),
				minitScript(minitScript) {}
			const string getMethodName() override {
				return "logic.getHierarchyParentId";
			}
			void executeMethod(span<Variable>& arguments, Variable& returnValue, const SubStatement& subStatement) override {
				minitScript->setValue(returnValue, minitScript->logic->getHierarchyParentId());
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
			LogicMinitScript* minitScript { nullptr };
		public:
			MethodLogicGetLogicIds(LogicMinitScript* minitScript):
				Method({}, VariableType::TYPE_ARRAY),
				minitScript(minitScript) {}
			const string getMethodName() override {
				return "logic.getLogicIds";
			}
			void executeMethod(span<Variable>& arguments, Variable& returnValue, const SubStatement& subStatement) override {
				const auto& contextLogics = minitScript->logic->getContext()->getLogics();
				returnValue.setType(EngineMinitScript::TYPE_ARRAY);
				for (auto contextLogic: contextLogics) {
					returnValue.pushArrayEntry(EngineMinitScript::Variable(contextLogic->getId()));
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
			LogicMinitScript* minitScript { nullptr };
		public:
			MethodAudioGetListenerPosition(LogicMinitScript* minitScript):
				Method(
					{},
					TYPE_VECTOR3
				),
				minitScript(minitScript) {}
			const string getMethodName() override {
				return "audio.getListenerPosition";
			}
			void executeMethod(span<Variable>& arguments, Variable& returnValue, const SubStatement& subStatement) override {
				minitScript->setValue(returnValue, minitScript->logic->getContext()->getAudio()->getListenerPosition());
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
			LogicMinitScript* minitScript { nullptr };
		public:
			MethodAudioSetListenerPosition(LogicMinitScript* minitScript):
				Method(
					{
						{ .type = TYPE_VECTOR3, .name = "position", .optional = false, .reference = false, .nullable = false }
					},
					VariableType::TYPE_NULL
				),
				minitScript(minitScript) {}
			const string getMethodName() override {
				return "audio.setListenerPosition";
			}
			void executeMethod(span<Variable>& arguments, Variable& returnValue, const SubStatement& subStatement) override {
				Vector3 position;
				if (minitScript->getVector3Value(arguments, 0, position) == true) {
					minitScript->logic->getContext()->getAudio()->setListenerPosition(position);
				} else {
					Console::printLine(getMethodName() + "(): " + minitScript->getSubStatementInformation(subStatement) + ": argument mismatch: expected arguments: " + minitScript->getArgumentsInformation(getMethodName()));
					minitScript->startErrorScript();
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
			LogicMinitScript* minitScript { nullptr };
		public:
			MethodAudioGetListenerOrientationUp(LogicMinitScript* minitScript):
				Method(
					{},
					TYPE_VECTOR3
				),
				minitScript(minitScript) {}
			const string getMethodName() override {
				return "audio.getListenerOrientationUp";
			}
			void executeMethod(span<Variable>& arguments, Variable& returnValue, const SubStatement& subStatement) override {
				minitScript->setValue(returnValue, minitScript->logic->getContext()->getAudio()->getListenerOrientationUp());
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
			LogicMinitScript* minitScript { nullptr };
		public:
			MethodAudioSetListenerOrientationUp(LogicMinitScript* minitScript):
				Method(
					{
						{ .type = TYPE_VECTOR3, .name = "orientation", .optional = false, .reference = false, .nullable = false }
					},
					VariableType::TYPE_NULL
				),
				minitScript(minitScript) {}
			const string getMethodName() override {
				return "audio.setListenerOrientationUp";
			}
			void executeMethod(span<Variable>& arguments, Variable& returnValue, const SubStatement& subStatement) override {
				Vector3 orientation;
				if (minitScript->getVector3Value(arguments, 0, orientation) == true) {
					minitScript->logic->getContext()->getAudio()->setListenerOrientationUp(orientation);
				} else {
					Console::printLine(getMethodName() + "(): " + minitScript->getSubStatementInformation(subStatement) + ": argument mismatch: expected arguments: " + minitScript->getArgumentsInformation(getMethodName()));
					minitScript->startErrorScript();
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
			LogicMinitScript* minitScript { nullptr };
		public:
			MethodAudioGetListenerOrientationAt(LogicMinitScript* minitScript):
				Method(
					{},
					TYPE_VECTOR3
				),
				minitScript(minitScript) {}
			const string getMethodName() override {
				return "audio.getListenerOrientationAt";
			}
			void executeMethod(span<Variable>& arguments, Variable& returnValue, const SubStatement& subStatement) override {
				minitScript->setValue(returnValue, minitScript->logic->getContext()->getAudio()->getListenerOrientationAt());
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
			LogicMinitScript* minitScript { nullptr };
		public:
			MethodAudioSetListenerOrientationAt(LogicMinitScript* minitScript):
				Method(
					{
						{ .type = TYPE_VECTOR3, .name = "orientation", .optional = false, .reference = false, .nullable = false }
					},
					VariableType::TYPE_NULL
				),
				minitScript(minitScript) {}
			const string getMethodName() override {
				return "audio.setListenerOrientationAt";
			}
			void executeMethod(span<Variable>& arguments, Variable& returnValue, const SubStatement& subStatement) override {
				Vector3 orientation;
				if (minitScript->getVector3Value(arguments, 0, orientation) == true) {
					minitScript->logic->getContext()->getAudio()->setListenerOrientationAt(orientation);
				} else {
					Console::printLine(getMethodName() + "(): " + minitScript->getSubStatementInformation(subStatement) + ": argument mismatch: expected arguments: " + minitScript->getArgumentsInformation(getMethodName()));
					minitScript->startErrorScript();
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
			LogicMinitScript* minitScript { nullptr };
		public:
			MethodAudioPlaySound(LogicMinitScript* minitScript):
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
				minitScript(minitScript) {}
			const string getMethodName() override {
				return "audio.play";
			}
			void executeMethod(span<Variable>& arguments, Variable& returnValue, const SubStatement& subStatement) override {
				string id;
				int64_t delay = 0;
				auto gain = 1.0f;
				auto pitch = 1.0f;
				auto ignoreIfPlaying = false;
				if (minitScript->getStringValue(arguments, 0, id) == true &&
					minitScript->getIntegerValue(arguments, 1, delay, true) == true &&
					minitScript->getFloatValue(arguments, 2, gain, true) == true &&
					minitScript->getFloatValue(arguments, 3, pitch, true) == true &&
					minitScript->getBooleanValue(arguments, 4, ignoreIfPlaying, true) == true) {
					minitScript->logic->playSound(minitScript->logic->getId() + "." + id, delay, gain, pitch, ignoreIfPlaying);
				} else {
					Console::printLine(getMethodName() + "(): " + minitScript->getSubStatementInformation(subStatement) + ": argument mismatch: expected arguments: " + minitScript->getArgumentsInformation(getMethodName()));
					minitScript->startErrorScript();
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
			LogicMinitScript* minitScript { nullptr };
		public:
			MethodAudioPlaySoundAtPosition(LogicMinitScript* minitScript):
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
				minitScript(minitScript) {}
			const string getMethodName() override {
				return "audio.playAtPosition";
			}
			void executeMethod(span<Variable>& arguments, Variable& returnValue, const SubStatement& subStatement) override {
				string id;
				Vector3 position;
				int64_t delay = 0;
				auto gain = 1.0f;
				auto pitch = 1.0f;
				auto ignoreIfPlaying = false;
				if (minitScript->getStringValue(arguments, 0, id) == true &&
					minitScript->getVector3Value(arguments, 1, position) == true &&
					minitScript->getIntegerValue(arguments, 2, delay, true) == true &&
					minitScript->getFloatValue(arguments, 3, gain, true) == true &&
					minitScript->getFloatValue(arguments, 4, pitch, true) == true &&
					minitScript->getBooleanValue(arguments, 5, ignoreIfPlaying, true) == true) {
					minitScript->logic->playSound(minitScript->logic->getId() + "." + id, position, delay, gain, pitch, ignoreIfPlaying);
				} else {
					Console::printLine(getMethodName() + "(): " + minitScript->getSubStatementInformation(subStatement) + ": argument mismatch: expected arguments: " + minitScript->getArgumentsInformation(getMethodName()));
					minitScript->startErrorScript();
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
			LogicMinitScript* minitScript { nullptr };
		public:
			MethodLogicSignalSend(LogicMinitScript* minitScript):
				Method({
					{ .type = VariableType::TYPE_STRING, .name = "logicId", .optional = false, .reference = false, .nullable = false },
					{ .type = VariableType::TYPE_STRING, .name = "signal", .optional = false, .reference = false, .nullable = false }
				}),
				minitScript(minitScript) {}
			const string getMethodName() override {
				return "logic.signal.send";
			}
			void executeMethod(span<Variable>& arguments, Variable& returnValue, const SubStatement& subStatement) override {
				string logicId;
				string signal;
				if (minitScript->getStringValue(arguments, 0, logicId) == true &&
					minitScript->getStringValue(arguments, 1, signal) == true) {
					auto logic = static_cast<Logic*>(minitScript->context->getLogic(logicId));
					if (logic == nullptr) {
						Console::printLine(getMethodName() + "(): " + minitScript->getSubStatementInformation(subStatement) + ": no logic with given id: " + logicId);
						minitScript->startErrorScript();
					} else {
						vector<Variable> arguments(arguments.size() - 2);
						for (auto i = 2; i < arguments.size(); i++) arguments.push_back(arguments[i]);
						logic->addSignal(signal, arguments);
					}
				} else {
					Console::printLine(getMethodName() + "(): " + minitScript->getSubStatementInformation(subStatement) + ": argument mismatch: expected arguments: " + minitScript->getArgumentsInformation(getMethodName()));
					minitScript->startErrorScript();
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
			LogicMinitScript* minitScript { nullptr };
		public:
			MethodLogicHas(LogicMinitScript* minitScript):
				Method(
					{
						{ .type = VariableType::TYPE_STRING, .name = "logicId", .optional = false, .reference = false, .nullable = false },
						{ .type = VariableType::TYPE_STRING, .name = "callable", .optional = false, .reference = false, .nullable = false }
					},
					VariableType::TYPE_BOOLEAN
				),
				minitScript(minitScript) {}
			const string getMethodName() override {
				return "logic.has";
			}
			void executeMethod(span<Variable>& arguments, Variable& returnValue, const SubStatement& subStatement) override {
				string logicId;
				string callable;
				if (EngineMinitScript::getStringValue(arguments, 0, logicId) == false ||
					EngineMinitScript::getStringValue(arguments, 1, callable) == false) {
					Console::printLine(getMethodName() + "(): " + minitScript->getSubStatementInformation(subStatement) + ": argument mismatch: expected arguments: " + minitScript->getArgumentsInformation(getMethodName()));
					minitScript->startErrorScript();
				} else {
					auto logic = dynamic_cast<MinitScriptLogic*>(minitScript->context->getLogic(logicId));
					if (logic == nullptr || logic->getMinitScript() == nullptr) {
						minitScript->setValue(returnValue, false);
					} else {
						auto logicMinitScript = logic->getMinitScript();
						auto scriptIdx = logicMinitScript->getFunctionScriptIdx(callable);
						if (scriptIdx == SCRIPTIDX_NONE || logicMinitScript->getScripts()[scriptIdx].callable == false) {
							minitScript->setValue(returnValue, false);
						} else {
							minitScript->setValue(returnValue, true);
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
			LogicMinitScript* minitScript { nullptr };
		public:
			MethodLogicCall(LogicMinitScript* minitScript):
				Method(
					{
						{ .type = VariableType::TYPE_STRING, .name = "logicId", .optional = false, .reference = false, .nullable = false },
						{ .type = VariableType::TYPE_STRING, .name = "callable", .optional = false, .reference = false, .nullable = false }
					},
					VariableType::TYPE_PSEUDO_MIXED
				),
				minitScript(minitScript) {}
			const string getMethodName() override {
				return "logic.call";
			}
			void executeMethod(span<Variable>& arguments, Variable& returnValue, const SubStatement& subStatement) override {
				string logicId;
				string callable;
				if (EngineMinitScript::getStringValue(arguments, 0, logicId) == false ||
					EngineMinitScript::getStringValue(arguments, 1, callable) == false) {
					Console::printLine(getMethodName() + "(): " + minitScript->getSubStatementInformation(subStatement) + ": argument mismatch: expected arguments: " + minitScript->getArgumentsInformation(getMethodName()));
					minitScript->startErrorScript();
				} else {
					auto logic = dynamic_cast<MinitScriptLogic*>(minitScript->context->getLogic(logicId));
					if (logic == nullptr || logic->getMinitScript() == nullptr) {
						Console::printLine(getMethodName() + "(): " + minitScript->getSubStatementInformation(subStatement) + ": no mini script logic with given id: " + logicId);
						minitScript->startErrorScript();
					} else {
						auto logicMinitScript = logic->getMinitScript();
						auto scriptIdx = logicMinitScript->getFunctionScriptIdx(callable);
						if (scriptIdx == SCRIPTIDX_NONE || logicMinitScript->getScripts()[scriptIdx].callable == false) {
							Console::printLine(getMethodName() + "(): " + minitScript->getSubStatementInformation(subStatement) + ": callable not found: " + callable);
							minitScript->startErrorScript();
						} else {
							#if defined (__clang__)
								// MACOSX currently does not support initializing span using begin and end iterators,
								vector<Variable> callArguments(arguments.size() - 2);
								for (auto i = 2; i < arguments.size(); i++) callArguments[i - 2] = move(arguments[i]);
								// call
								span callArgumentsSpan(callArguments);
								logicMinitScript->call(scriptIdx, callArgumentsSpan, returnValue);
								// move back arguments
								for (auto i = 2; i < arguments.size(); i++) arguments[i] = move(callArguments[i - 2]);
							#else
								span callArgumentsSpan(arguments.begin() + 2, arguments.end());
								logicMinitScript->call(scriptIdx, callArgumentsSpan, returnValue);
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
			LogicMinitScript* minitScript { nullptr };
		public:
			MethodLogicSignalHas(LogicMinitScript* minitScript):
				Method({}, VariableType::TYPE_BOOLEAN),
				minitScript(minitScript) {}
			const string getMethodName() override {
				return "logic.signal.has";
			}
			void executeMethod(span<Variable>& arguments, Variable& returnValue, const SubStatement& subStatement) override {
				minitScript->setValue(returnValue, minitScript->logic->hasSignal());
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
			LogicMinitScript* minitScript { nullptr };
		public:
			MethodLogicSignalGetName(LogicMinitScript* minitScript):
				Method({}, VariableType::TYPE_STRING),
				minitScript(minitScript) {}
			const string getMethodName() override {
				return "logic.signal.getName";
			}
			void executeMethod(span<Variable>& arguments, Variable& returnValue, const SubStatement& subStatement) override {
				minitScript->setValue(returnValue, minitScript->logic->getSignalName());
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
			LogicMinitScript* minitScript { nullptr };
		public:
			MethodLogicSignalGetArgument(LogicMinitScript* minitScript):
				Method(
					{
						{ .type = VariableType::TYPE_INTEGER, .name = "argumentIndex", .optional = false, .reference = false, .nullable = false }
					},
					VariableType::TYPE_PSEUDO_MIXED
				),
				minitScript(minitScript) {}
			const string getMethodName() override {
				return "logic.signal.getArgument";
			}
			void executeMethod(span<Variable>& arguments, Variable& returnValue, const SubStatement& subStatement) override {
				int64_t argumentIndex;
				if (minitScript->getIntegerValue(arguments, 0, argumentIndex) == true) {
					returnValue = minitScript->logic->getSignalArgument(argumentIndex);
				} else {
					Console::printLine(getMethodName() + "(): " + minitScript->getSubStatementInformation(subStatement) + ": argument mismatch: expected arguments: " + minitScript->getArgumentsInformation(getMethodName()));
					minitScript->startErrorScript();
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
			LogicMinitScript* minitScript { nullptr };
		public:
			MethodLogicSignalNext(LogicMinitScript* minitScript):
				Method(),
				minitScript(minitScript) {}
			const string getMethodName() override {
				return "logic.signal.next";
			}
			void executeMethod(span<Variable>& arguments, Variable& returnValue, const SubStatement& subStatement) override {
				minitScript->logic->removeSignal();
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
			LogicMinitScript* minitScript { nullptr };
		public:
			MethodInputKeyboardKEYCODE_LEFT(LogicMinitScript* minitScript):
				Method({}, VariableType::TYPE_INTEGER),
				minitScript(minitScript) {}
			const string getMethodName() override {
				return "input.keyboard.KEYCODE_LEFT";
			}
			void executeMethod(span<Variable>& arguments, Variable& returnValue, const SubStatement& subStatement) override {
				minitScript->setValue(returnValue, static_cast<int64_t>(GUIKeyboardEvent::KEYCODE_LEFT));
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
			LogicMinitScript* minitScript { nullptr };
		public:
			MethodInputKeyboardKEYCODE_RIGHT(LogicMinitScript* minitScript):
				Method({}, VariableType::TYPE_INTEGER),
				minitScript(minitScript) {}
			const string getMethodName() override {
				return "input.keyboard.KEYCODE_RIGHT";
			}
			void executeMethod(span<Variable>& arguments, Variable& returnValue, const SubStatement& subStatement) override {
				minitScript->setValue(returnValue, static_cast<int64_t>(GUIKeyboardEvent::KEYCODE_RIGHT));
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
			LogicMinitScript* minitScript { nullptr };
		public:
			MethodInputKeyboardKEYCODE_UP(LogicMinitScript* minitScript):
				Method({}, VariableType::TYPE_INTEGER),
				minitScript(minitScript) {}
			const string getMethodName() override {
				return "input.keyboard.KEYCODE_UP";
			}
			void executeMethod(span<Variable>& arguments, Variable& returnValue, const SubStatement& subStatement) override {
				minitScript->setValue(returnValue, static_cast<int64_t>(GUIKeyboardEvent::KEYCODE_UP));
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
			LogicMinitScript* minitScript { nullptr };
		public:
			MethodInputKeyboardKEYCODE_DOWN(LogicMinitScript* minitScript):
				Method({}, VariableType::TYPE_INTEGER),
				minitScript(minitScript) {}
			const string getMethodName() override {
				return "input.keyboard.KEYCODE_DOWN";
			}
			void executeMethod(span<Variable>& arguments, Variable& returnValue, const SubStatement& subStatement) override {
				minitScript->setValue(returnValue, static_cast<int64_t>(GUIKeyboardEvent::KEYCODE_DOWN));
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
			LogicMinitScript* minitScript { nullptr };
		public:
			MethodInputKeyboardKEYCODE_POS1(LogicMinitScript* minitScript):
				Method({}, VariableType::TYPE_INTEGER),
				minitScript(minitScript) {}
			const string getMethodName() override {
				return "input.keyboard.KEYCODE_POS1";
			}
			void executeMethod(span<Variable>& arguments, Variable& returnValue, const SubStatement& subStatement) override {
				minitScript->setValue(returnValue, static_cast<int64_t>(GUIKeyboardEvent::KEYCODE_POS1));
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
			LogicMinitScript* minitScript { nullptr };
		public:
			MethodInputKeyboardKEYCODE_END(LogicMinitScript* minitScript):
				Method({}, VariableType::TYPE_INTEGER),
				minitScript(minitScript) {}
			const string getMethodName() override {
				return "input.keyboard.KEYCODE_END";
			}
			void executeMethod(span<Variable>& arguments, Variable& returnValue, const SubStatement& subStatement) override {
				minitScript->setValue(returnValue, static_cast<int64_t>(GUIKeyboardEvent::KEYCODE_END));
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
			LogicMinitScript* minitScript { nullptr };
		public:
			MethodInputKeyboardKEYCODE_PAGEUP(LogicMinitScript* minitScript):
				Method({}, VariableType::TYPE_INTEGER),
				minitScript(minitScript) {}
			const string getMethodName() override {
				return "input.keyboard.KEYCODE_PAGEUP";
			}
			void executeMethod(span<Variable>& arguments, Variable& returnValue, const SubStatement& subStatement) override {
				minitScript->setValue(returnValue, static_cast<int64_t>(GUIKeyboardEvent::KEYCODE_PAGE_UP));
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
			LogicMinitScript* minitScript { nullptr };
		public:
			MethodInputKeyboardKEYCODE_PAGEDOWN(LogicMinitScript* minitScript):
				Method({}, VariableType::TYPE_INTEGER),
				minitScript(minitScript) {}
			const string getMethodName() override {
				return "input.keyboard.KEYCODE_PAGEDOWN";
			}
			void executeMethod(span<Variable>& arguments, Variable& returnValue, const SubStatement& subStatement) override {
				minitScript->setValue(returnValue, static_cast<int64_t>(GUIKeyboardEvent::KEYCODE_PAGE_DOWN));
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
			LogicMinitScript* minitScript { nullptr };
		public:
			MethodInputKeyboardKEYCODE_BACKSPACE(LogicMinitScript* minitScript):
				Method({}, VariableType::TYPE_INTEGER),
				minitScript(minitScript) {}
			const string getMethodName() override {
				return "input.keyboard.KEYCODE_BACKSPACE";
			}
			void executeMethod(span<Variable>& arguments, Variable& returnValue, const SubStatement& subStatement) override {
				minitScript->setValue(returnValue, static_cast<int64_t>(GUIKeyboardEvent::KEYCODE_BACKSPACE));
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
			LogicMinitScript* minitScript { nullptr };
		public:
			MethodInputKeyboardKEYCODE_DELETE(LogicMinitScript* minitScript):
				Method({}, VariableType::TYPE_INTEGER),
				minitScript(minitScript) {}
			const string getMethodName() override {
				return "input.keyboard.KEYCODE_DELETE";
			}
			void executeMethod(span<Variable>& arguments, Variable& returnValue, const SubStatement& subStatement) override {
				minitScript->setValue(returnValue, static_cast<int64_t>(GUIKeyboardEvent::KEYCODE_DELETE));
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
			LogicMinitScript* minitScript { nullptr };
		public:
			MethodInputKeyboardKEYCODE_SPACE(LogicMinitScript* minitScript):
				Method({}, VariableType::TYPE_INTEGER),
				minitScript(minitScript) {}
			const string getMethodName() override {
				return "input.keyboard.KEYCODE_SPACE";
			}
			void executeMethod(span<Variable>& arguments, Variable& returnValue, const SubStatement& subStatement) override {
				minitScript->setValue(returnValue, static_cast<int64_t>(GUIKeyboardEvent::KEYCODE_SPACE));
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
			LogicMinitScript* minitScript { nullptr };
		public:
			MethodInputKeyboardKEYCODE_RETURN(LogicMinitScript* minitScript):
				Method({}, VariableType::TYPE_INTEGER),
				minitScript(minitScript) {}
			const string getMethodName() override {
				return "input.keyboard.KEYCODE_RETURN";
			}
			void executeMethod(span<Variable>& arguments, Variable& returnValue, const SubStatement& subStatement) override {
				minitScript->setValue(returnValue, static_cast<int64_t>(GUIKeyboardEvent::KEYCODE_RETURN));
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
			LogicMinitScript* minitScript { nullptr };
		public:
			MethodInputKeyboardKEYCODE_ESCAPE(LogicMinitScript* minitScript):
				Method({}, VariableType::TYPE_INTEGER),
				minitScript(minitScript) {}
			const string getMethodName() override {
				return "input.keyboard.KEYCODE_ESCAPE";
			}
			void executeMethod(span<Variable>& arguments, Variable& returnValue, const SubStatement& subStatement) override {
				minitScript->setValue(returnValue, static_cast<int64_t>(GUIKeyboardEvent::KEYCODE_ESCAPE));
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
			LogicMinitScript* minitScript { nullptr };
		public:
			MethodInputKeyboardKEYCODE_F1(LogicMinitScript* minitScript):
				Method({}, VariableType::TYPE_INTEGER),
				minitScript(minitScript) {}
			const string getMethodName() override {
				return "input.keyboard.KEYCODE_F1";
			}
			void executeMethod(span<Variable>& arguments, Variable& returnValue, const SubStatement& subStatement) override {
				minitScript->setValue(returnValue, static_cast<int64_t>(GUIKeyboardEvent::KEYCODE_F1));
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
			LogicMinitScript* minitScript { nullptr };
		public:
			MethodInputKeyboardKEYCODE_F2(LogicMinitScript* minitScript):
				Method({}, VariableType::TYPE_INTEGER),
				minitScript(minitScript) {}
			const string getMethodName() override {
				return "input.keyboard.KEYCODE_F2";
			}
			void executeMethod(span<Variable>& arguments, Variable& returnValue, const SubStatement& subStatement) override {
				minitScript->setValue(returnValue, static_cast<int64_t>(GUIKeyboardEvent::KEYCODE_F2));
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
			LogicMinitScript* minitScript { nullptr };
		public:
			MethodInputKeyboardKEYCODE_F3(LogicMinitScript* minitScript):
				Method({}, VariableType::TYPE_INTEGER),
				minitScript(minitScript) {}
			const string getMethodName() override {
				return "input.keyboard.KEYCODE_F3";
			}
			void executeMethod(span<Variable>& arguments, Variable& returnValue, const SubStatement& subStatement) override {
				minitScript->setValue(returnValue, static_cast<int64_t>(GUIKeyboardEvent::KEYCODE_F3));
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
			LogicMinitScript* minitScript { nullptr };
		public:
			MethodInputKeyboardKEYCODE_F4(LogicMinitScript* minitScript):
				Method({}, VariableType::TYPE_INTEGER),
				minitScript(minitScript) {}
			const string getMethodName() override {
				return "input.keyboard.KEYCODE_F4";
			}
			void executeMethod(span<Variable>& arguments, Variable& returnValue, const SubStatement& subStatement) override {
				minitScript->setValue(returnValue, static_cast<int64_t>(GUIKeyboardEvent::KEYCODE_F4));
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
			LogicMinitScript* minitScript { nullptr };
		public:
			MethodInputKeyboardKEYCODE_F5(LogicMinitScript* minitScript):
				Method({}, VariableType::TYPE_INTEGER),
				minitScript(minitScript) {}
			const string getMethodName() override {
				return "input.keyboard.KEYCODE_F5";
			}
			void executeMethod(span<Variable>& arguments, Variable& returnValue, const SubStatement& subStatement) override {
				minitScript->setValue(returnValue, static_cast<int64_t>(GUIKeyboardEvent::KEYCODE_F5));
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
			LogicMinitScript* minitScript { nullptr };
		public:
			MethodInputKeyboardKEYCODE_F6(LogicMinitScript* minitScript):
				Method({}, VariableType::TYPE_INTEGER),
				minitScript(minitScript) {}
			const string getMethodName() override {
				return "input.keyboard.KEYCODE_F6";
			}
			void executeMethod(span<Variable>& arguments, Variable& returnValue, const SubStatement& subStatement) override {
				minitScript->setValue(returnValue, static_cast<int64_t>(GUIKeyboardEvent::KEYCODE_F6));
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
			LogicMinitScript* minitScript { nullptr };
		public:
			MethodInputKeyboardKEYCODE_F7(LogicMinitScript* minitScript):
				Method({}, VariableType::TYPE_INTEGER),
				minitScript(minitScript) {}
			const string getMethodName() override {
				return "input.keyboard.KEYCODE_F7";
			}
			void executeMethod(span<Variable>& arguments, Variable& returnValue, const SubStatement& subStatement) override {
				minitScript->setValue(returnValue, static_cast<int64_t>(GUIKeyboardEvent::KEYCODE_F7));
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
			LogicMinitScript* minitScript { nullptr };
		public:
			MethodInputKeyboardKEYCODE_F8(LogicMinitScript* minitScript):
				Method({}, VariableType::TYPE_INTEGER),
				minitScript(minitScript) {}
			const string getMethodName() override {
				return "input.keyboard.KEYCODE_F8";
			}
			void executeMethod(span<Variable>& arguments, Variable& returnValue, const SubStatement& subStatement) override {
				minitScript->setValue(returnValue, static_cast<int64_t>(GUIKeyboardEvent::KEYCODE_F8));
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
			LogicMinitScript* minitScript { nullptr };
		public:
			MethodInputKeyboardKEYCODE_F9(LogicMinitScript* minitScript):
				Method({}, VariableType::TYPE_INTEGER),
				minitScript(minitScript) {}
			const string getMethodName() override {
				return "input.keyboard.KEYCODE_F9";
			}
			void executeMethod(span<Variable>& arguments, Variable& returnValue, const SubStatement& subStatement) override {
				minitScript->setValue(returnValue, static_cast<int64_t>(GUIKeyboardEvent::KEYCODE_F9));
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
			LogicMinitScript* minitScript { nullptr };
		public:
			MethodInputKeyboardKEYCODE_F10(LogicMinitScript* minitScript):
				Method({}, VariableType::TYPE_INTEGER),
				minitScript(minitScript) {}
			const string getMethodName() override {
				return "input.keyboard.KEYCODE_F10";
			}
			void executeMethod(span<Variable>& arguments, Variable& returnValue, const SubStatement& subStatement) override {
				minitScript->setValue(returnValue, static_cast<int64_t>(GUIKeyboardEvent::KEYCODE_F10));
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
			LogicMinitScript* minitScript { nullptr };
		public:
			MethodInputKeyboardKEYCODE_F11(LogicMinitScript* minitScript):
				Method({}, VariableType::TYPE_INTEGER),
				minitScript(minitScript) {}
			const string getMethodName() override {
				return "input.keyboard.KEYCODE_F11";
			}
			void executeMethod(span<Variable>& arguments, Variable& returnValue, const SubStatement& subStatement) override {
				minitScript->setValue(returnValue, static_cast<int64_t>(GUIKeyboardEvent::KEYCODE_F11));
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
			LogicMinitScript* minitScript { nullptr };
		public:
			MethodInputKeyboardKEYCODE_F12(LogicMinitScript* minitScript):
				Method({}, VariableType::TYPE_INTEGER),
				minitScript(minitScript) {}
			const string getMethodName() override {
				return "input.keyboard.KEYCODE_F12";
			}
			void executeMethod(span<Variable>& arguments, Variable& returnValue, const SubStatement& subStatement) override {
				minitScript->setValue(returnValue, static_cast<int64_t>(GUIKeyboardEvent::KEYCODE_F12));
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
			LogicMinitScript* minitScript { nullptr };
		public:
			MethodInputKeyboardIsKeyDown(LogicMinitScript* minitScript):
				Method(
					{
						{ .type = VariableType::TYPE_INTEGER, .name = "keyCode", .optional = false, .reference = false, .nullable = false }
					},
					VariableType::TYPE_BOOLEAN
				),
				minitScript(minitScript) {}
			const string getMethodName() override {
				return "input.keyboard.isKeyDown";
			}
			void executeMethod(span<Variable>& arguments, Variable& returnValue, const SubStatement& subStatement) override {
				int64_t keyCode;
				if (minitScript->getIntegerValue(arguments, 0, keyCode) == true) {
					minitScript->setValue(returnValue, minitScript->keyboardKeys.find(keyCode) != minitScript->keyboardKeys.end());
				} else {
					Console::printLine(getMethodName() + "(): " + minitScript->getSubStatementInformation(subStatement) + ": argument mismatch: expected arguments: " + minitScript->getArgumentsInformation(getMethodName()));
					minitScript->startErrorScript();
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
			LogicMinitScript* minitScript { nullptr };
		public:
			MethodInputKeyboardIsCharDown(LogicMinitScript* minitScript):
				Method(
					{
						{ .type = VariableType::TYPE_STRING, .name = "charAsString", .optional = false, .reference = false, .nullable = false }
					},
					VariableType::TYPE_BOOLEAN
				),
				minitScript(minitScript) {}
			const string getMethodName() override {
				return "input.keyboard.isCharDown";
			}
			void executeMethod(span<Variable>& arguments, Variable& returnValue, const SubStatement& subStatement) override {
				string charAsString;
				if (minitScript->getStringValue(arguments, 0, charAsString) == true) {
					UTF8CharacterIterator u8It(charAsString);
					auto keyChar = u8It.hasNext() == true?u8It.next():-1;
					minitScript->setValue(returnValue, minitScript->keyboardChars.find(keyChar) != minitScript->keyboardChars.end());
				} else {
					Console::printLine(getMethodName() + "(): " + minitScript->getSubStatementInformation(subStatement) + ": argument mismatch: expected arguments: " + minitScript->getArgumentsInformation(getMethodName()));
					minitScript->startErrorScript();
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
			LogicMinitScript* minitScript { nullptr };
		public:
			MethodInputKeyboardGetTypedString(LogicMinitScript* minitScript):
				Method({}, VariableType::TYPE_STRING),
				minitScript(minitScript) {}
			const string getMethodName() override {
				return "input.keyboard.getTypedString";
			}
			void executeMethod(span<Variable>& arguments, Variable& returnValue, const SubStatement& subStatement) override {
				minitScript->setValue(returnValue, minitScript->keyboardTypedChars);
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
			LogicMinitScript* minitScript { nullptr };
		public:
			MethodInputKeyboardIsControlDown(LogicMinitScript* minitScript):
				Method({}, VariableType::TYPE_BOOLEAN),
				minitScript(minitScript) {}
			const string getMethodName() override {
				return "input.keyboard.isControlDown";
			}
			void executeMethod(span<Variable>& arguments, Variable& returnValue, const SubStatement& subStatement) override {
				minitScript->setValue(returnValue, minitScript->keyboardControlDown == true);
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
			LogicMinitScript* minitScript { nullptr };
		public:
			MethodInputKeyboardIsMetaDown(LogicMinitScript* minitScript):
				Method({}, VariableType::TYPE_BOOLEAN),
				minitScript(minitScript) {}
			const string getMethodName() override {
				return "input.keyboard.isMetaDown";
			}
			void executeMethod(span<Variable>& arguments, Variable& returnValue, const SubStatement& subStatement) override {
				minitScript->setValue(returnValue, minitScript->keyboardControlDown == true);
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
			LogicMinitScript* minitScript { nullptr };
		public:
			MethodInputKeyboardIsAltDown(LogicMinitScript* minitScript):
				Method({}, VariableType::TYPE_BOOLEAN),
				minitScript(minitScript) {}
			const string getMethodName() override {
				return "input.keyboard.isAltDown";
			}
			void executeMethod(span<Variable>& arguments, Variable& returnValue, const SubStatement& subStatement) override {
				minitScript->setValue(returnValue, minitScript->keyboardAltDown == true);
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
			LogicMinitScript* minitScript { nullptr };
		public:
			MethodInputKeyboardIsShiftDown(LogicMinitScript* minitScript):
				Method({}, VariableType::TYPE_BOOLEAN),
				minitScript(minitScript) {}
			const string getMethodName() override {
				return "input.keyboard.isShiftDown";
			}
			void executeMethod(span<Variable>& arguments, Variable& returnValue, const SubStatement& subStatement) override {
				minitScript->setValue(returnValue, minitScript->keyboardShiftDown == true);
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
			LogicMinitScript* minitScript { nullptr };
		public:
			MethodInputMouseBUTTON_LEFT(LogicMinitScript* minitScript):
				Method({}, VariableType::TYPE_INTEGER),
				minitScript(minitScript) {}
			const string getMethodName() override {
				return "input.mouse.BUTTON_LEFT";
			}
			void executeMethod(span<Variable>& arguments, Variable& returnValue, const SubStatement& subStatement) override {
				minitScript->setValue(returnValue, static_cast<int64_t>(GUIMouseEvent::MOUSEEVENT_BUTTON_LEFT - 1));
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
			LogicMinitScript* minitScript { nullptr };
		public:
			MethodInputMouseBUTTON_MIDDLE(LogicMinitScript* minitScript):
				Method({}, VariableType::TYPE_INTEGER),
				minitScript(minitScript) {}
			const string getMethodName() override {
				return "input.mouse.BUTTON_MIDDLE";
			}
			void executeMethod(span<Variable>& arguments, Variable& returnValue, const SubStatement& subStatement) override {
				minitScript->setValue(returnValue, static_cast<int64_t>(GUIMouseEvent::MOUSEEVENT_BUTTON_MIDDLE - 1));
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
			LogicMinitScript* minitScript { nullptr };
		public:
			MethodInputMouseBUTTON_RIGHT(LogicMinitScript* minitScript):
				Method({}, VariableType::TYPE_INTEGER),
				minitScript(minitScript) {}
			const string getMethodName() override {
				return "input.mouse.BUTTON_RIGHT";
			}
			void executeMethod(span<Variable>& arguments, Variable& returnValue, const SubStatement& subStatement) override {
				minitScript->setValue(returnValue, static_cast<int64_t>(GUIMouseEvent::MOUSEEVENT_BUTTON_RIGHT - 1));
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
			LogicMinitScript* minitScript { nullptr };
		public:
			MethodInputMouseIsButtonDown(LogicMinitScript* minitScript):
				Method(
					{
						{ .type = VariableType::TYPE_INTEGER, .name = "button", .optional = false, .reference = false, .nullable = false }
					},
					VariableType::TYPE_BOOLEAN),
				minitScript(minitScript) {}
			const string getMethodName() override {
				return "input.mouse.isButtonDown";
			}
			void executeMethod(span<Variable>& arguments, Variable& returnValue, const SubStatement& subStatement) override {
				int64_t button;
				if (minitScript->getIntegerValue(arguments, 0, button) == true) {
					minitScript->setValue(returnValue, button >= 0 && button <= 3?minitScript->mouseDown[button]:false);
				} else {
					Console::printLine(getMethodName() + "(): " + minitScript->getSubStatementInformation(subStatement) + ": argument mismatch: expected arguments: " + minitScript->getArgumentsInformation(getMethodName()));
					minitScript->startErrorScript();
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
			LogicMinitScript* minitScript { nullptr };
		public:
			MethodInputMouseIsButtonUp(LogicMinitScript* minitScript):
				Method(
					{
						{ .type = VariableType::TYPE_INTEGER, .name = "button", .optional = false, .reference = false, .nullable = false }
					},
					VariableType::TYPE_BOOLEAN),
				minitScript(minitScript) {}
			const string getMethodName() override {
				return "input.mouse.isButtonUp";
			}
			void executeMethod(span<Variable>& arguments, Variable& returnValue, const SubStatement& subStatement) override {
				int64_t button;
				if (minitScript->getIntegerValue(arguments, 0, button) == true) {
					minitScript->setValue(returnValue, button >= 0 && button <= 3?minitScript->mouseUp[button]:false);
				} else {
					Console::printLine(getMethodName() + "(): " + minitScript->getSubStatementInformation(subStatement) + ": argument mismatch: expected arguments: " + minitScript->getArgumentsInformation(getMethodName()));
					minitScript->startErrorScript();
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
			LogicMinitScript* minitScript { nullptr };
		public:
			MethodInputMouseIsDragging(LogicMinitScript* minitScript):
				Method(
					{
						{ .type = VariableType::TYPE_INTEGER, .name = "button", .optional = false, .reference = false, .nullable = false }
					},
					VariableType::TYPE_BOOLEAN),
				minitScript(minitScript) {}
			const string getMethodName() override {
				return "input.mouse.isDragging";
			}
			void executeMethod(span<Variable>& arguments, Variable& returnValue, const SubStatement& subStatement) override {
				int64_t button;
				if (minitScript->getIntegerValue(arguments, 0, button) == true) {
					minitScript->setValue(returnValue, button >= 0 && button <= 3?minitScript->mouseDragging[button]:false);
				} else {
					Console::printLine(getMethodName() + "(): " + minitScript->getSubStatementInformation(subStatement) + ": argument mismatch: expected arguments: " + minitScript->getArgumentsInformation(getMethodName()));
					minitScript->startErrorScript();
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
			LogicMinitScript* minitScript { nullptr };
		public:
			MethodInputMouseHasMoved(LogicMinitScript* minitScript):
				Method({}, VariableType::TYPE_BOOLEAN),
				minitScript(minitScript) {}
			const string getMethodName() override {
				return "input.mouse.hasMoved";
			}
			void executeMethod(span<Variable>& arguments, Variable& returnValue, const SubStatement& subStatement) override {
				minitScript->setValue(returnValue, minitScript->mouseMoved);
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
			LogicMinitScript* minitScript { nullptr };
		public:
			MethodInputMouseGetX(LogicMinitScript* minitScript):
				Method({}, VariableType::TYPE_INTEGER),
				minitScript(minitScript) {}
			const string getMethodName() override {
				return "input.mouse.getX";
			}
			void executeMethod(span<Variable>& arguments, Variable& returnValue, const SubStatement& subStatement) override {
				minitScript->setValue(returnValue, static_cast<int64_t>(minitScript->mouseX));
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
			LogicMinitScript* minitScript { nullptr };
		public:
			MethodInputMouseGetXUnscaled(LogicMinitScript* minitScript):
				Method({}, VariableType::TYPE_INTEGER),
				minitScript(minitScript) {}
			const string getMethodName() override {
				return "input.mouse.getXUnscaled";
			}
			void executeMethod(span<Variable>& arguments, Variable& returnValue, const SubStatement& subStatement) override {
				minitScript->setValue(returnValue, static_cast<int64_t>(minitScript->mouseXUnscaled));
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
			LogicMinitScript* minitScript { nullptr };
		public:
			MethodInputMouseGetY(LogicMinitScript* minitScript):
				Method({}, VariableType::TYPE_INTEGER),
				minitScript(minitScript) {}
			const string getMethodName() override {
				return "input.mouse.getY";
			}
			void executeMethod(span<Variable>& arguments, Variable& returnValue, const SubStatement& subStatement) override {
				minitScript->setValue(returnValue, static_cast<int64_t>(minitScript->mouseY));
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
			LogicMinitScript* minitScript { nullptr };
		public:
			MethodInputMouseGetYUnscaled(LogicMinitScript* minitScript):
				Method({}, VariableType::TYPE_INTEGER),
				minitScript(minitScript) {}
			const string getMethodName() override {
				return "input.mouse.getYUnscaled";
			}
			void executeMethod(span<Variable>& arguments, Variable& returnValue, const SubStatement& subStatement) override {
				minitScript->setValue(returnValue, static_cast<int64_t>(minitScript->mouseYUnscaled));
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
			LogicMinitScript* minitScript { nullptr };
		public:
			MethodInputMouseGetWheelX(LogicMinitScript* minitScript):
				Method({}, VariableType::TYPE_FLOAT),
				minitScript(minitScript) {}
			const string getMethodName() override {
				return "input.mouse.getWheelX";
			}
			void executeMethod(span<Variable>& arguments, Variable& returnValue, const SubStatement& subStatement) override {
				minitScript->setValue(returnValue, minitScript->mouseWheelX);
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
			LogicMinitScript* minitScript { nullptr };
		public:
			MethodInputMouseGetWheelY(LogicMinitScript* minitScript):
				Method({}, VariableType::TYPE_FLOAT),
				minitScript(minitScript) {}
			const string getMethodName() override {
				return "input.mouse.getWheelY";
			}
			void executeMethod(span<Variable>& arguments, Variable& returnValue, const SubStatement& subStatement) override {
				minitScript->setValue(returnValue, minitScript->mouseWheelY);
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
			LogicMinitScript* minitScript { nullptr };
		public:
			MethodInputMouseGetWheelZ(LogicMinitScript* minitScript):
				Method({}, VariableType::TYPE_FLOAT),
				minitScript(minitScript) {}
			const string getMethodName() override {
				return "input.mouse.getWheelZ";
			}
			void executeMethod(span<Variable>& arguments, Variable& returnValue, const SubStatement& subStatement) override {
				minitScript->setValue(returnValue, minitScript->mouseWheelZ);
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
			LogicMinitScript* minitScript { nullptr };
		public:
			MethodCameraGetLookFrom(LogicMinitScript* minitScript):
				Method({}, TYPE_VECTOR3),
				minitScript(minitScript) {}
			const string getMethodName() override {
				return "engine.camera.getLookFrom";
			}
			void executeMethod(span<Variable>& arguments, Variable& returnValue, const SubStatement& subStatement) override {
				minitScript->setValue(returnValue, minitScript->context->getEngine()->getCamera()->getLookFrom());
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
			LogicMinitScript* minitScript { nullptr };
		public:
			MethodCameraSetLookFrom(LogicMinitScript* minitScript):
				Method(
					{
						{ .type = TYPE_VECTOR3, .name = "lookFrom", .optional = false, .reference = false, .nullable = false }
					},
					VariableType::TYPE_NULL
				),
				minitScript(minitScript) {}
			const string getMethodName() override {
				return "engine.camera.setLookFrom";
			}
			void executeMethod(span<Variable>& arguments, Variable& returnValue, const SubStatement& subStatement) override {
				Vector3 lookFrom;
				if (minitScript->getVector3Value(arguments, 0, lookFrom) == true) {
					minitScript->context->getEngine()->getCamera()->setLookFrom(lookFrom);
				} else {
					Console::printLine(getMethodName() + "(): " + minitScript->getSubStatementInformation(subStatement) + ": argument mismatch: expected arguments: " + minitScript->getArgumentsInformation(getMethodName()));
					minitScript->startErrorScript();
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
			LogicMinitScript* minitScript { nullptr };
		public:
			MethodCameraGetLookAt(LogicMinitScript* minitScript):
				Method({}, TYPE_VECTOR3),
				minitScript(minitScript) {}
			const string getMethodName() override {
				return "engine.camera.getLookAt";
			}
			void executeMethod(span<Variable>& arguments, Variable& returnValue, const SubStatement& subStatement) override {
				minitScript->setValue(returnValue, minitScript->context->getEngine()->getCamera()->getLookAt());
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
			LogicMinitScript* minitScript { nullptr };
		public:
			MethodCameraSetLookAt(LogicMinitScript* minitScript):
				Method(
					{
						{ .type = TYPE_VECTOR3, .name = "lookAt", .optional = false, .reference = false, .nullable = false }
					},
					VariableType::TYPE_NULL
				),
				minitScript(minitScript) {}
			const string getMethodName() override {
				return "engine.camera.setLookAt";
			}
			void executeMethod(span<Variable>& arguments, Variable& returnValue, const SubStatement& subStatement) override {
				Vector3 lookAt;
				if (minitScript->getVector3Value(arguments, 0, lookAt) == true) {
					minitScript->context->getEngine()->getCamera()->setLookAt(lookAt);
				} else {
					Console::printLine(getMethodName() + "(): " + minitScript->getSubStatementInformation(subStatement) + ": argument mismatch: expected arguments: " + minitScript->getArgumentsInformation(getMethodName()));
					minitScript->startErrorScript();
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
			LogicMinitScript* minitScript { nullptr };
		public:
			MethodCameraGetUpVector(LogicMinitScript* minitScript):
				Method({}, TYPE_VECTOR3),
				minitScript(minitScript) {}
			const string getMethodName() override {
				return "engine.camera.getUpVector";
			}
			void executeMethod(span<Variable>& arguments, Variable& returnValue, const SubStatement& subStatement) override {
				minitScript->setValue(returnValue, minitScript->context->getEngine()->getCamera()->getUpVector());
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
			LogicMinitScript* minitScript { nullptr };
		public:
			MethodCameraSetUpVector(LogicMinitScript* minitScript):
				Method(
					{
						{ .type = TYPE_VECTOR3, .name = "upVector", .optional = false, .reference = false, .nullable = false }
					},
					VariableType::TYPE_NULL
				),
				minitScript(minitScript) {}
			const string getMethodName() override {
				return "engine.camera.setUpVector";
			}
			void executeMethod(span<Variable>& arguments, Variable& returnValue, const SubStatement& subStatement) override {
				Vector3 upVector;
				if (minitScript->getVector3Value(arguments, 0, upVector) == true) {
					minitScript->context->getEngine()->getCamera()->setUpVector(upVector);
				} else {
					Console::printLine(getMethodName() + "(): " + minitScript->getSubStatementInformation(subStatement) + ": argument mismatch: expected arguments: " + minitScript->getArgumentsInformation(getMethodName()));
					minitScript->startErrorScript();
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
			LogicMinitScript* minitScript { nullptr };
		public:
			MethodCameraComputeUpVector(LogicMinitScript* minitScript):
				Method(
					{
						{ .type = TYPE_VECTOR3, .name = "lookFrom", .optional = false, .reference = false, .nullable = false },
						{ .type = TYPE_VECTOR3, .name = "lookAt", .optional = false, .reference = false, .nullable = false }
					},
					TYPE_VECTOR3
				),
				minitScript(minitScript) {}
			const string getMethodName() override {
				return "engine.camera.computeUpVector";
			}
			void executeMethod(span<Variable>& arguments, Variable& returnValue, const SubStatement& subStatement) override {
				Vector3 lookFrom;
				Vector3 lookAt;
				if (minitScript->getVector3Value(arguments, 0, lookFrom) == true &&
					minitScript->getVector3Value(arguments, 1, lookAt) == true) {
					minitScript->setValue(returnValue, Camera::computeUpVector(lookFrom, lookAt));
				} else {
					Console::printLine(getMethodName() + "(): " + minitScript->getSubStatementInformation(subStatement) + ": argument mismatch: expected arguments: " + minitScript->getArgumentsInformation(getMethodName()));
					minitScript->startErrorScript();
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
			LogicMinitScript* minitScript { nullptr };
		public:
			MethodCameraGetFovX(LogicMinitScript* minitScript):
				Method({}, VariableType::TYPE_FLOAT),
				minitScript(minitScript) {}
			const string getMethodName() override {
				return "engine.camera.getFovX";
			}
			void executeMethod(span<Variable>& arguments, Variable& returnValue, const SubStatement& subStatement) override {
				minitScript->setValue(returnValue, minitScript->context->getEngine()->getCamera()->getFovX());
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
			LogicMinitScript* minitScript { nullptr };
		public:
			MethodCameraSetFovX(LogicMinitScript* minitScript):
				Method(
					{
						{ .type = VariableType::TYPE_FLOAT, .name = "fovX", .optional = false, .reference = false, .nullable = false }
					},
					VariableType::TYPE_NULL
				),
				minitScript(minitScript) {}
			const string getMethodName() override {
				return "engine.camera.setFovX";
			}
			void executeMethod(span<Variable>& arguments, Variable& returnValue, const SubStatement& subStatement) override {
				float fovX;
				if (minitScript->getFloatValue(arguments, 0, fovX) == true) {
					minitScript->context->getEngine()->getCamera()->setFovX(fovX);
				} else {
					Console::printLine(getMethodName() + "(): " + minitScript->getSubStatementInformation(subStatement) + ": argument mismatch: expected arguments: " + minitScript->getArgumentsInformation(getMethodName()));
					minitScript->startErrorScript();
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
			LogicMinitScript* minitScript { nullptr };
		public:
			MethodTimingGetDeltaTime(LogicMinitScript* minitScript):
				Method({}, VariableType::TYPE_INTEGER),
				minitScript(minitScript) {}
			const string getMethodName() override {
				return "engine.timing.getDeltaTime";
			}
			void executeMethod(span<Variable>& arguments, Variable& returnValue, const SubStatement& subStatement) override {
				minitScript->setValue(returnValue, minitScript->context->getEngine()->getTiming()->getDeltaTime());
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
			LogicMinitScript* minitScript { nullptr };
		public:
			MethodTimingGetDeltaTimeSeconds(LogicMinitScript* minitScript):
				Method({}, VariableType::TYPE_FLOAT),
				minitScript(minitScript) {}
			const string getMethodName() override {
				return "engine.timing.getDeltaTimeSeconds";
			}
			void executeMethod(span<Variable>& arguments, Variable& returnValue, const SubStatement& subStatement) override {
				minitScript->setValue(returnValue, minitScript->context->getEngine()->getTiming()->getDeltaTimeSeconds());
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
			LogicMinitScript* minitScript { nullptr };
		public:
			MethodTimingGetAvarageFPS(LogicMinitScript* minitScript):
				Method({}, VariableType::TYPE_FLOAT),
				minitScript(minitScript) {}
			const string getMethodName() override {
				return "engine.timing.getAvarageFPS";
			}
			void executeMethod(span<Variable>& arguments, Variable& returnValue, const SubStatement& subStatement) override {
				minitScript->setValue(returnValue, minitScript->context->getEngine()->getTiming()->getAvarageFPS());
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
			LogicMinitScript* minitScript { nullptr };
		public:
			MethodEngineGetAnimationComputationReduction1Distance(LogicMinitScript* minitScript):
				Method({}, VariableType::TYPE_FLOAT),
				minitScript(minitScript) {}
			const string getMethodName() override {
				return "engine.getAnimationComputationReduction1Distance";
			}
			void executeMethod(span<Variable>& arguments, Variable& returnValue, const SubStatement& subStatement) override {
				minitScript->setValue(returnValue, Engine::getAnimationComputationReduction1Distance());
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
			LogicMinitScript* minitScript { nullptr };
		public:
			MethodEngineSetAnimationComputationReduction1Distance(LogicMinitScript* minitScript):
				Method(
					{
						{ .type = VariableType::TYPE_FLOAT, .name = "animationComputationReduction1Distance", .optional = false, .reference = false, .nullable = false }
					},
					VariableType::TYPE_NULL
				),
				minitScript(minitScript) {}
			const string getMethodName() override {
				return "engine.setAnimationComputationReduction1Distance";
			}
			void executeMethod(span<Variable>& arguments, Variable& returnValue, const SubStatement& subStatement) override {
				float animationComputationReduction1Distance;
				if (minitScript->getFloatValue(arguments, 0, animationComputationReduction1Distance) == true) {
					Engine::setAnimationComputationReduction1Distance(animationComputationReduction1Distance);
				} else {
					Console::printLine(getMethodName() + "(): " + minitScript->getSubStatementInformation(subStatement) + ": argument mismatch: expected arguments: " + minitScript->getArgumentsInformation(getMethodName()));
					minitScript->startErrorScript();
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
			LogicMinitScript* minitScript { nullptr };
		public:
			MethodEngineGetAnimationComputationReduction2Distance(LogicMinitScript* minitScript):
				Method({}, VariableType::TYPE_FLOAT),
				minitScript(minitScript) {}
			const string getMethodName() override {
				return "engine.getAnimationComputationReduction2Distance";
			}
			void executeMethod(span<Variable>& arguments, Variable& returnValue, const SubStatement& subStatement) override {
				minitScript->setValue(returnValue, Engine::getAnimationComputationReduction2Distance());
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
			LogicMinitScript* minitScript { nullptr };
		public:
			MethodEngineSetAnimationComputationReduction2Distance(LogicMinitScript* minitScript):
				Method(
					{
						{ .type = VariableType::TYPE_FLOAT, .name = "animationComputationReduction2Distance", .optional = false, .reference = false, .nullable = false }
					},
					VariableType::TYPE_NULL
				),
				minitScript(minitScript) {}
			const string getMethodName() override {
				return "engine.setAnimationComputationReduction2Distance";
			}
			void executeMethod(span<Variable>& arguments, Variable& returnValue, const SubStatement& subStatement) override {
				float animationComputationReduction2Distance;
				if (minitScript->getFloatValue(arguments, 0, animationComputationReduction2Distance) == true) {
					Engine::setAnimationComputationReduction2Distance(animationComputationReduction2Distance);
				} else {
					Console::printLine(getMethodName() + "(): " + minitScript->getSubStatementInformation(subStatement) + ": argument mismatch: expected arguments: " + minitScript->getArgumentsInformation(getMethodName()));
					minitScript->startErrorScript();
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
			LogicMinitScript* minitScript { nullptr };
		public:
			MethodEngineGetWidth(LogicMinitScript* minitScript):
				Method({}, VariableType::TYPE_INTEGER),
				minitScript(minitScript) {}
			const string getMethodName() override {
				return "engine.getWidth";
			}
			void executeMethod(span<Variable>& arguments, Variable& returnValue, const SubStatement& subStatement) override {
				minitScript->setValue(returnValue, static_cast<int64_t>(minitScript->context->getEngine()->getWidth()));
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
			LogicMinitScript* minitScript { nullptr };
		public:
			MethodEngineGetHeight(LogicMinitScript* minitScript):
				Method({}, VariableType::TYPE_INTEGER),
				minitScript(minitScript) {}
			const string getMethodName() override {
				return "engine.getHeight";
			}
			void executeMethod(span<Variable>& arguments, Variable& returnValue, const SubStatement& subStatement) override {
				minitScript->setValue(returnValue, static_cast<int64_t>(minitScript->context->getEngine()->getHeight()));
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
			LogicMinitScript* minitScript { nullptr };
		public:
			MethodEngineDumpEntities(LogicMinitScript* minitScript):
				Method({}, VariableType::TYPE_NULL),
				minitScript(minitScript) {}
			const string getMethodName() override {
				return "engine.dumpEntities";
			}
			void executeMethod(span<Variable>& arguments, Variable& returnValue, const SubStatement& subStatement) override {
				minitScript->context->getEngine()->dumpEntities();
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
			LogicMinitScript* minitScript { nullptr };
		public:
			MethodEngineDumpShaders(LogicMinitScript* minitScript):
				Method({}, VariableType::TYPE_NULL),
				minitScript(minitScript) {}
			const string getMethodName() override {
				return "engine.dumpShaders";
			}
			void executeMethod(span<Variable>& arguments, Variable& returnValue, const SubStatement& subStatement) override {
				minitScript->context->getEngine()->dumpShaders();
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
			LogicMinitScript* minitScript { nullptr };
		public:
			MethodEngineGetEntityIdByMousePosition(LogicMinitScript* minitScript):
				Method(
					{
						{ .type = VariableType::TYPE_INTEGER, .name = "mouseX", .optional = false, .reference = false, .nullable = false },
						{ .type = VariableType::TYPE_INTEGER, .name = "mouseY", .optional = false, .reference = false, .nullable = false }
					},
					VariableType::TYPE_STRING
				),
				minitScript(minitScript) {}
			const string getMethodName() override {
				return "engine.getEntityIdByMousePosition";
			}
			void executeMethod(span<Variable>& arguments, Variable& returnValue, const SubStatement& subStatement) override {
				int64_t mouseX;
				int64_t mouseY;
				if (minitScript->getIntegerValue(arguments, 0, mouseX) == true &&
					minitScript->getIntegerValue(arguments, 1, mouseY) == true) {
					auto entity = minitScript->context->getEngine()->getEntityByMousePosition(mouseX, mouseY);
					if (entity != nullptr) minitScript->setValue(returnValue, entity->getId());
				} else {
					Console::printLine(getMethodName() + "(): " + minitScript->getSubStatementInformation(subStatement) + ": argument mismatch: expected arguments: " + minitScript->getArgumentsInformation(getMethodName()));
					minitScript->startErrorScript();
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
			LogicMinitScript* minitScript { nullptr };
		public:
			MethodEngineComputeWorldCoordinateByMousePosition(LogicMinitScript* minitScript):
				Method(
					{
						{ .type = VariableType::TYPE_INTEGER, .name = "mouseX", .optional = false, .reference = false, .nullable = false },
						{ .type = VariableType::TYPE_INTEGER, .name = "mouseY", .optional = false, .reference = false, .nullable = false }
					},
					TYPE_VECTOR3
				),
				minitScript(minitScript) {}
			const string getMethodName() override {
				return "engine.computeWorldCoordinateByMousePosition";
			}
			void executeMethod(span<Variable>& arguments, Variable& returnValue, const SubStatement& subStatement) override {
				int64_t mouseX;
				int64_t mouseY;
				if (minitScript->getIntegerValue(arguments, 0, mouseX) == true &&
					minitScript->getIntegerValue(arguments, 1, mouseY) == true) {
					minitScript->setValue(returnValue, minitScript->context->getEngine()->computeWorldCoordinateByMousePosition(mouseX, mouseY));
				} else {
					Console::printLine(getMethodName() + "(): " + minitScript->getSubStatementInformation(subStatement) + ": argument mismatch: expected arguments: " + minitScript->getArgumentsInformation(getMethodName()));
					minitScript->startErrorScript();
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
			LogicMinitScript* minitScript { nullptr };
		public:
			MethodEngineComputeScreenCoordinateByWorldCoordinate(LogicMinitScript* minitScript):
				Method(
					{
						{ .type = TYPE_VECTOR3, .name = "worldCoodinate", .optional = false, .reference = false, .nullable = false },
						{ .type = TYPE_VECTOR2, .name = "screenCoordinate", .optional = false, .reference = true, .nullable = false }
					},
					VariableType::TYPE_BOOLEAN
				),
				minitScript(minitScript) {}
			const string getMethodName() override {
				return "engine.computeScreenCoordinateByWorldCoordinate";
			}
			void executeMethod(span<Variable>& arguments, Variable& returnValue, const SubStatement& subStatement) override {
				Vector3 worldCoodinate;
				if (arguments.size() == 2 &&
					minitScript->getVector3Value(arguments, 0, worldCoodinate) == true) {
					Vector2 screenCoordinate;
					if (minitScript->context->getEngine()->computeScreenCoordinateByWorldCoordinate(worldCoodinate, screenCoordinate) == true) {
						minitScript->setValue(arguments[1], screenCoordinate);
						minitScript->setValue(returnValue, true);
					} else {
						minitScript->setValue(returnValue, false);
					}
				} else {
					Console::printLine(getMethodName() + "(): " + minitScript->getSubStatementInformation(subStatement) + ": argument mismatch: expected arguments: " + minitScript->getArgumentsInformation(getMethodName()));
					minitScript->startErrorScript();
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
			LogicMinitScript* minitScript { nullptr };
		public:
			MethodEntityGetTransform(LogicMinitScript* minitScript):
				Method(
					{
						{ .type = VariableType::TYPE_STRING, .name = "entityId", .optional = false, .reference = false, .nullable = false },
						{ .type = VariableType::TYPE_STRING, .name = "childEntityId", .optional = true, .reference = false, .nullable = false }
					},
					TYPE_TRANSFORM
				),
				minitScript(minitScript) {}
			const string getMethodName() override {
				return "engine.entity.getTransform";
			}
			void executeMethod(span<Variable>& arguments, Variable& returnValue, const SubStatement& subStatement) override {
				string entityId;
				string childEntityId;
				if (minitScript->getStringValue(arguments, 0, entityId) == true &&
					minitScript->getStringValue(arguments, 1, childEntityId, true) == true) {
					auto entity = minitScript->getEntity(entityId, childEntityId);
					if (entity != nullptr) {
						minitScript->setValue(returnValue, entity->getTransform());
					} else {
						Console::printLine(getMethodName() + "(): " + minitScript->getSubStatementInformation(subStatement) + ": entity not found: " + (childEntityId.empty() == true?entityId:childEntityId + "@" + entityId));
					}
				} else {
					Console::printLine(getMethodName() + "(): " + minitScript->getSubStatementInformation(subStatement) + ": argument mismatch: expected arguments: " + minitScript->getArgumentsInformation(getMethodName()));
					minitScript->startErrorScript();
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
			LogicMinitScript* minitScript { nullptr };
		public:
			MethodEntitySetTransform(LogicMinitScript* minitScript):
				Method(
					{
						{ .type = VariableType::TYPE_STRING, .name = "entityId", .optional = false, .reference = false, .nullable = false },
						{ .type = TYPE_TRANSFORM, .name = "transform", .optional = false, .reference = false, .nullable = false },
						{ .type = VariableType::TYPE_STRING, .name = "childEntityId", .optional = true, .reference = false, .nullable = false }
					},
					VariableType::TYPE_NULL
				),
				minitScript(minitScript) {}
			const string getMethodName() override {
				return "engine.entity.setTransform";
			}
			void executeMethod(span<Variable>& arguments, Variable& returnValue, const SubStatement& subStatement) override {
				string entityId;
				Transform transform;
				string childEntityId;
				if (minitScript->getStringValue(arguments, 0, entityId) == true &&
					minitScript->getTransformValue(arguments, 1, transform) == true &&
					minitScript->getStringValue(arguments, 2, childEntityId, true) == true) {
					auto entity = minitScript->getEntity(entityId, childEntityId);
					if (entity != nullptr) {
						entity->setTransform(transform);
					} else {
						Console::printLine(getMethodName() + "(): " + minitScript->getSubStatementInformation(subStatement) + ": entity not found: " + (childEntityId.empty() == true?entityId:childEntityId + "@" + entityId));
					}
				} else {
					Console::printLine(getMethodName() + "(): " + minitScript->getSubStatementInformation(subStatement) + ": argument mismatch: expected arguments: " + minitScript->getArgumentsInformation(getMethodName()));
					minitScript->startErrorScript();
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
			LogicMinitScript* minitScript { nullptr };
		public:
			MethodEntityIsEnabled(LogicMinitScript* minitScript):
				Method(
					{
						{ .type = VariableType::TYPE_STRING, .name = "entityId", .optional = false, .reference = false, .nullable = false },
						{ .type = VariableType::TYPE_STRING, .name = "childEntityId", .optional = true, .reference = false, .nullable = false }
					},
					VariableType::TYPE_BOOLEAN
				),
				minitScript(minitScript) {}
			const string getMethodName() override {
				return "engine.entity.isEnabled";
			}
			void executeMethod(span<Variable>& arguments, Variable& returnValue, const SubStatement& subStatement) override {
				string entityId;
				string childEntityId;
				if (minitScript->getStringValue(arguments, 0, entityId) == true &&
					minitScript->getStringValue(arguments, 1, childEntityId, true) == true) {
					auto entity = minitScript->getEntity(entityId, childEntityId);
					if (entity != nullptr) {
						minitScript->setValue(returnValue, entity->isEnabled());
					} else {
						Console::printLine(getMethodName() + "(): " + minitScript->getSubStatementInformation(subStatement) + ": entity not found: " + (childEntityId.empty() == true?entityId:childEntityId + "@" + entityId));
					}
				} else {
					Console::printLine(getMethodName() + "(): " + minitScript->getSubStatementInformation(subStatement) + ": argument mismatch: expected arguments: " + minitScript->getArgumentsInformation(getMethodName()));
					minitScript->startErrorScript();
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
			LogicMinitScript* minitScript { nullptr };
		public:
			MethodEntitySetEnabled(LogicMinitScript* minitScript):
				Method(
					{
						{ .type = VariableType::TYPE_STRING, .name = "entityId", .optional = false, .reference = false, .nullable = false },
						{ .type = VariableType::TYPE_BOOLEAN, .name = "enabled", .optional = false, .reference = false, .nullable = false },
						{ .type = VariableType::TYPE_STRING, .name = "childEntityId", .optional = true, .reference = false, .nullable = false }
					},
					VariableType::TYPE_NULL
				),
				minitScript(minitScript) {}
			const string getMethodName() override {
				return "engine.entity.setEnabled";
			}
			void executeMethod(span<Variable>& arguments, Variable& returnValue, const SubStatement& subStatement) override {
				string entityId;
				bool enabled;
				string childEntityId;
				if (minitScript->getStringValue(arguments, 0, entityId) == true &&
					minitScript->getBooleanValue(arguments, 1, enabled) == true &&
					minitScript->getStringValue(arguments, 2, childEntityId, true) == true) {
					auto entity = minitScript->getEntity(entityId, childEntityId);
					if (entity != nullptr) {
						entity->setEnabled(enabled);
					} else {
						Console::printLine(getMethodName() + "(): " + minitScript->getSubStatementInformation(subStatement) + ": entity not found: " + (childEntityId.empty() == true?entityId:childEntityId + "@" + entityId));
					}
				} else {
					Console::printLine(getMethodName() + "(): " + minitScript->getSubStatementInformation(subStatement) + ": argument mismatch: expected arguments: " + minitScript->getArgumentsInformation(getMethodName()));
					minitScript->startErrorScript();
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
			LogicMinitScript* minitScript { nullptr };
		public:
			MethodEntityIsPickable(LogicMinitScript* minitScript):
				Method(
					{
						{ .type = VariableType::TYPE_STRING, .name = "entityId", .optional = false, .reference = false, .nullable = false },
						{ .type = VariableType::TYPE_STRING, .name = "childEntityId", .optional = true, .reference = false, .nullable = false }
					},
					VariableType::TYPE_BOOLEAN
				),
				minitScript(minitScript) {}
			const string getMethodName() override {
				return "engine.entity.isPickable";
			}
			void executeMethod(span<Variable>& arguments, Variable& returnValue, const SubStatement& subStatement) override {
				string entityId;
				string childEntityId;
				if (minitScript->getStringValue(arguments, 0, entityId) == true &&
					minitScript->getStringValue(arguments, 1, childEntityId, true) == true) {
					auto entity = minitScript->getEntity(entityId, childEntityId);
					if (entity != nullptr) {
						minitScript->setValue(returnValue, entity->isPickable());
					} else {
						Console::printLine(getMethodName() + "(): " + minitScript->getSubStatementInformation(subStatement) + ": entity not found: " + (childEntityId.empty() == true?entityId:childEntityId + "@" + entityId));
					}
				} else {
					Console::printLine(getMethodName() + "(): " + minitScript->getSubStatementInformation(subStatement) + ": argument mismatch: expected arguments: " + minitScript->getArgumentsInformation(getMethodName()));
					minitScript->startErrorScript();
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
			LogicMinitScript* minitScript { nullptr };
		public:
			MethodEntitySetPickable(LogicMinitScript* minitScript):
				Method(
					{
						{ .type = VariableType::TYPE_STRING, .name = "entityId", .optional = false, .reference = false, .nullable = false },
						{ .type = VariableType::TYPE_BOOLEAN, .name = "pickable", .optional = false, .reference = false, .nullable = false },
						{ .type = VariableType::TYPE_STRING, .name = "childEntityId", .optional = true, .reference = false, .nullable = false }
					},
					VariableType::TYPE_NULL
				),
				minitScript(minitScript) {}
			const string getMethodName() override {
				return "engine.entity.setPickable";
			}
			void executeMethod(span<Variable>& arguments, Variable& returnValue, const SubStatement& subStatement) override {
				string entityId;
				bool pickable;
				string childEntityId;
				if (minitScript->getStringValue(arguments, 0, entityId) == true &&
					minitScript->getBooleanValue(arguments, 1, pickable) == true &&
					minitScript->getStringValue(arguments, 2, childEntityId, true) == true) {
					auto entity = minitScript->getEntity(entityId, childEntityId);
					if (entity != nullptr) {
						entity->setPickable(pickable);
					} else {
						Console::printLine(getMethodName() + "(): " + minitScript->getSubStatementInformation(subStatement) + ": entity not found: " + (childEntityId.empty() == true?entityId:childEntityId + "@" + entityId));
					}
				} else {
					Console::printLine(getMethodName() + "(): " + minitScript->getSubStatementInformation(subStatement) + ": argument mismatch: expected arguments: " + minitScript->getArgumentsInformation(getMethodName()));
					minitScript->startErrorScript();
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
			LogicMinitScript* minitScript { nullptr };
		public:
			MethodEntityGetEffectColorMul(LogicMinitScript* minitScript):
				Method(
					{
						{ .type = VariableType::TYPE_STRING, .name = "entityId", .optional = false, .reference = false, .nullable = false },
						{ .type = VariableType::TYPE_STRING, .name = "childEntityId", .optional = true, .reference = false, .nullable = false }
					},
					TYPE_VECTOR4
				),
				minitScript(minitScript) {}
			const string getMethodName() override {
				return "engine.entity.getEffectColorMul";
			}
			void executeMethod(span<Variable>& arguments, Variable& returnValue, const SubStatement& subStatement) override {
				string entityId;
				string childEntityId;
				if (minitScript->getStringValue(arguments, 0, entityId) == true &&
					minitScript->getStringValue(arguments, 1, childEntityId, true) == true) {
					auto entity = minitScript->getEntity(entityId, childEntityId);
					if (entity != nullptr) {
						auto effectColorMul = entity->getEffectColorMul();
						minitScript->setValue(returnValue, Vector4(effectColorMul.getRed(), effectColorMul.getGreen(), effectColorMul.getBlue(), effectColorMul.getAlpha()));
					} else {
						Console::printLine(getMethodName() + "(): " + minitScript->getSubStatementInformation(subStatement) + ": entity not found: " + (childEntityId.empty() == true?entityId:childEntityId + "@" + entityId));
					}
				} else {
					Console::printLine(getMethodName() + "(): " + minitScript->getSubStatementInformation(subStatement) + ": argument mismatch: expected arguments: " + minitScript->getArgumentsInformation(getMethodName()));
					minitScript->startErrorScript();
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
			LogicMinitScript* minitScript { nullptr };
		public:
			MethodEntitySetEffectColorMul(LogicMinitScript* minitScript):
				Method(
					{
						{ .type = VariableType::TYPE_STRING, .name = "entityId", .optional = false, .reference = false, .nullable = false },
						{ .type = TYPE_VECTOR4, .name = "effectColorMul", .optional = false, .reference = false, .nullable = false },
						{ .type = VariableType::TYPE_STRING, .name = "childEntityId", .optional = true, .reference = false, .nullable = false }
					},
					VariableType::TYPE_NULL
				),
				minitScript(minitScript) {}
			const string getMethodName() override {
				return "engine.entity.setEffectColorMul";
			}
			void executeMethod(span<Variable>& arguments, Variable& returnValue, const SubStatement& subStatement) override {
				string entityId;
				Vector4 effectColorMul;
				string childEntityId;
				if (minitScript->getStringValue(arguments, 0, entityId) == true &&
					minitScript->getVector4Value(arguments, 1, effectColorMul) == true &&
					minitScript->getStringValue(arguments, 2, childEntityId, true) == true) {
					auto entity = minitScript->getEntity(entityId, childEntityId);
					if (entity != nullptr) {
						entity->setEffectColorMul(Color4(effectColorMul.getX(), effectColorMul.getY(), effectColorMul.getZ(), effectColorMul.getW()));
					} else {
						Console::printLine(getMethodName() + "(): " + minitScript->getSubStatementInformation(subStatement) + ": entity not found: " + (childEntityId.empty() == true?entityId:childEntityId + "@" + entityId));
					}
				} else {
					Console::printLine(getMethodName() + "(): " + minitScript->getSubStatementInformation(subStatement) + ": argument mismatch: expected arguments: " + minitScript->getArgumentsInformation(getMethodName()));
					minitScript->startErrorScript();
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
			LogicMinitScript* minitScript { nullptr };
		public:
			MethodEntityGetEffectColorAdd(LogicMinitScript* minitScript):
				Method(
					{
						{ .type = VariableType::TYPE_STRING, .name = "entityId", .optional = false, .reference = false, .nullable = false },
						{ .type = VariableType::TYPE_STRING, .name = "childEntityId", .optional = true, .reference = false, .nullable = false }
					},
					TYPE_VECTOR4
				),
				minitScript(minitScript) {}
			const string getMethodName() override {
				return "engine.entity.getEffectColorAdd";
			}
			void executeMethod(span<Variable>& arguments, Variable& returnValue, const SubStatement& subStatement) override {
				string entityId;
				string childEntityId;
				if (minitScript->getStringValue(arguments, 0, entityId) == true &&
					minitScript->getStringValue(arguments, 1, childEntityId, true) == true) {
					auto entity = minitScript->getEntity(entityId, childEntityId);
					if (entity != nullptr) {
						auto effectColorAdd = entity->getEffectColorAdd();
						minitScript->setValue(returnValue, Vector4(effectColorAdd.getRed(), effectColorAdd.getGreen(), effectColorAdd.getBlue(), effectColorAdd.getAlpha()));
					} else {
						Console::printLine(getMethodName() + "(): " + minitScript->getSubStatementInformation(subStatement) + ": entity not found: " + (childEntityId.empty() == true?entityId:childEntityId + "@" + entityId));
					}
				} else {
					Console::printLine(getMethodName() + "(): " + minitScript->getSubStatementInformation(subStatement) + ": argument mismatch: expected arguments: " + minitScript->getArgumentsInformation(getMethodName()));
					minitScript->startErrorScript();
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
			LogicMinitScript* minitScript { nullptr };
		public:
			MethodEntitySetEffectColorAdd(LogicMinitScript* minitScript):
				Method(
					{
						{ .type = VariableType::TYPE_STRING, .name = "entityId", .optional = false, .reference = false, .nullable = false },
						{ .type = TYPE_VECTOR4, .name = "effectColorAdd", .optional = false, .reference = false, .nullable = false },
						{ .type = VariableType::TYPE_STRING, .name = "childEntityId", .optional = true, .reference = false, .nullable = false }
					},
					VariableType::TYPE_NULL
				),
				minitScript(minitScript) {}
			const string getMethodName() override {
				return "engine.entity.setEffectColorAdd";
			}
			void executeMethod(span<Variable>& arguments, Variable& returnValue, const SubStatement& subStatement) override {
				string entityId;
				Vector4 effectColorAdd;
				string childEntityId;
				if (minitScript->getStringValue(arguments, 0, entityId) == true &&
					minitScript->getVector4Value(arguments, 1, effectColorAdd) == true &&
					minitScript->getStringValue(arguments, 2, childEntityId, true) == true) {
					auto entity = minitScript->getEntity(entityId, childEntityId);
					if (entity != nullptr) {
						entity->setEffectColorAdd(Color4(effectColorAdd.getX(), effectColorAdd.getY(), effectColorAdd.getZ(), effectColorAdd.getW()));
					} else {
						Console::printLine(getMethodName() + "(): " + minitScript->getSubStatementInformation(subStatement) + ": entity not found: " + (childEntityId.empty() == true?entityId:childEntityId + "@" + entityId));
					}
				} else {
					Console::printLine(getMethodName() + "(): " + minitScript->getSubStatementInformation(subStatement) + ": argument mismatch: expected arguments: " + minitScript->getArgumentsInformation(getMethodName()));
					minitScript->startErrorScript();
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
			LogicMinitScript* minitScript { nullptr };
		public:
			MethodEntityGetAnimation(LogicMinitScript* minitScript):
				Method(
					{
						{ .type = VariableType::TYPE_STRING, .name = "entityId", .optional = false, .reference = false, .nullable = false },
						{ .type = VariableType::TYPE_STRING, .name = "childEntityId", .optional = true, .reference = false, .nullable = false }
					},
					VariableType::TYPE_STRING
				),
				minitScript(minitScript) {}
			const string getMethodName() override {
				return "engine.entity.getAnimation";
			}
			void executeMethod(span<Variable>& arguments, Variable& returnValue, const SubStatement& subStatement) override {
				string entityId;
				string childEntityId;
				if (minitScript->getStringValue(arguments, 0, entityId) == true &&
					minitScript->getStringValue(arguments, 1, childEntityId, true) == true) {
					auto object = dynamic_cast<Object*>(minitScript->getEntity(entityId, childEntityId));
					if (object != nullptr) {
						minitScript->setValue(returnValue, object->getAnimation());
					} else {
						Console::printLine(getMethodName() + "(): " + minitScript->getSubStatementInformation(subStatement) + ": object entity not found: " + (childEntityId.empty() == true?entityId:childEntityId + "@" + entityId));
					}
				} else {
					Console::printLine(getMethodName() + "(): " + minitScript->getSubStatementInformation(subStatement) + ": argument mismatch: expected arguments: " + minitScript->getArgumentsInformation(getMethodName()));
					minitScript->startErrorScript();
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
			LogicMinitScript* minitScript { nullptr };
		public:
			MethodEntitySetAnimation(LogicMinitScript* minitScript):
				Method(
					{
						{ .type = VariableType::TYPE_STRING, .name = "entityId", .optional = false, .reference = false, .nullable = false },
						{ .type = VariableType::TYPE_STRING, .name = "animation", .optional = false, .reference = false, .nullable = false },
						{ .type = VariableType::TYPE_FLOAT, .name = "speed", .optional = true, .reference = false, .nullable = false },
						{ .type = VariableType::TYPE_STRING, .name = "childEntityId", .optional = true, .reference = false, .nullable = false },
					},
					VariableType::TYPE_NULL
				),
				minitScript(minitScript) {}
			const string getMethodName() override {
				return "engine.entity.setAnimation";
			}
			void executeMethod(span<Variable>& arguments, Variable& returnValue, const SubStatement& subStatement) override {
				string entityId;
				string animation;
				float speed = 1.0f;
				string childEntityId;
				if (minitScript->getStringValue(arguments, 0, entityId) == true &&
					minitScript->getStringValue(arguments, 1, animation) == true &&
					minitScript->getFloatValue(arguments, 2, speed, true) == true &&
					minitScript->getStringValue(arguments, 3, childEntityId, true) == true) {
					auto object = dynamic_cast<Object*>(minitScript->getEntity(entityId, childEntityId));
					if (object != nullptr) {
						object->setAnimation(animation, speed);
					} else {
						Console::printLine(getMethodName() + "(): " + minitScript->getSubStatementInformation(subStatement) + ": object entity not found: " + (childEntityId.empty() == true?entityId:childEntityId + "@" + entityId));
					}
				} else {
					Console::printLine(getMethodName() + "(): " + minitScript->getSubStatementInformation(subStatement) + ": argument mismatch: expected arguments: " + minitScript->getArgumentsInformation(getMethodName()));
					minitScript->startErrorScript();
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
			LogicMinitScript* minitScript { nullptr };
		public:
			MethodEntitySetAnimationSpeed(LogicMinitScript* minitScript):
				Method(
					{
						{ .type = VariableType::TYPE_STRING, .name = "entityId", .optional = false, .reference = false, .nullable = false },
						{ .type = VariableType::TYPE_FLOAT, .name = "speed", .optional = false, .reference = false, .nullable = false },
						{ .type = VariableType::TYPE_STRING, .name = "childEntityId", .optional = true, .reference = false, .nullable = false },
					},
					VariableType::TYPE_NULL
				),
				minitScript(minitScript) {}
			const string getMethodName() override {
				return "engine.entity.setAnimationSpeed";
			}
			void executeMethod(span<Variable>& arguments, Variable& returnValue, const SubStatement& subStatement) override {
				string entityId;
				float speed;
				string childEntityId;
				if (minitScript->getStringValue(arguments, 0, entityId) == true &&
					minitScript->getFloatValue(arguments, 1, speed) == true &&
					minitScript->getStringValue(arguments, 2, childEntityId, true) == true) {
					auto object = dynamic_cast<Object*>(minitScript->getEntity(entityId, childEntityId));
					if (object != nullptr) {
						object->setAnimationSpeed(speed);
					} else {
						Console::printLine(getMethodName() + "(): " + minitScript->getSubStatementInformation(subStatement) + ": object entity not found: " + (childEntityId.empty() == true?entityId:childEntityId + "@" + entityId));
					}
				} else {
					Console::printLine(getMethodName() + "(): " + minitScript->getSubStatementInformation(subStatement) + ": argument mismatch: expected arguments: " + minitScript->getArgumentsInformation(getMethodName()));
					minitScript->startErrorScript();
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
			LogicMinitScript* minitScript { nullptr };
		public:
			MethodEntityGetAnimationTime(LogicMinitScript* minitScript):
				Method(
					{
						{ .type = VariableType::TYPE_STRING, .name = "entityId", .optional = false, .reference = false, .nullable = false },
						{ .type = VariableType::TYPE_STRING, .name = "childEntityId", .optional = true, .reference = false, .nullable = false },
					},
					VariableType::TYPE_FLOAT
				),
				minitScript(minitScript) {}
			const string getMethodName() override {
				return "engine.entity.getAnimationTime";
			}
			void executeMethod(span<Variable>& arguments, Variable& returnValue, const SubStatement& subStatement) override {
				string entityId;
				string childEntityId;
				if (minitScript->getStringValue(arguments, 0, entityId) == true &&
					minitScript->getStringValue(arguments, 1, childEntityId, true) == true) {
					auto object = dynamic_cast<Object*>(minitScript->getEntity(entityId, childEntityId));
					if (object != nullptr) {
						minitScript->setValue(returnValue, object->getAnimationTime());
					} else {
						Console::printLine(getMethodName() + "(): " + minitScript->getSubStatementInformation(subStatement) + ": object entity not found: " + (childEntityId.empty() == true?entityId:childEntityId + "@" + entityId));
					}
				} else {
					Console::printLine(getMethodName() + "(): " + minitScript->getSubStatementInformation(subStatement) + ": argument mismatch: expected arguments: " + minitScript->getArgumentsInformation(getMethodName()));
					minitScript->startErrorScript();
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
			LogicMinitScript* minitScript { nullptr };
		public:
			MethodEntityHasOverlayAnimation(LogicMinitScript* minitScript):
				Method(
					{
						{ .type = VariableType::TYPE_STRING, .name = "entityId", .optional = false, .reference = false, .nullable = false },
						{ .type = VariableType::TYPE_STRING, .name = "animation", .optional = false, .reference = false, .nullable = false },
						{ .type = VariableType::TYPE_STRING, .name = "childEntityId", .optional = true, .reference = false, .nullable = false },
					},
					VariableType::TYPE_BOOLEAN
				),
				minitScript(minitScript) {}
			const string getMethodName() override {
				return "engine.entity.hasOverlayAnimation";
			}
			void executeMethod(span<Variable>& arguments, Variable& returnValue, const SubStatement& subStatement) override {
				string entityId;
				string animation;
				string childEntityId;
				if (minitScript->getStringValue(arguments, 0, entityId) == true &&
					minitScript->getStringValue(arguments, 1, animation) == true &&
					minitScript->getStringValue(arguments, 2, childEntityId, true) == true) {
					auto object = dynamic_cast<Object*>(minitScript->getEntity(entityId, childEntityId));
					if (object != nullptr) {
						minitScript->setValue(returnValue, object->hasOverlayAnimation(animation));
					} else {
						Console::printLine(getMethodName() + "(): " + minitScript->getSubStatementInformation(subStatement) + ": object entity not found: " + (childEntityId.empty() == true?entityId:childEntityId + "@" + entityId));
					}
				} else {
					Console::printLine(getMethodName() + "(): " + minitScript->getSubStatementInformation(subStatement) + ": argument mismatch: expected arguments: " + minitScript->getArgumentsInformation(getMethodName()));
					minitScript->startErrorScript();
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
			LogicMinitScript* minitScript { nullptr };
		public:
			MethodEntityAddOverlayAnimation(LogicMinitScript* minitScript):
				Method(
					{
						{ .type = VariableType::TYPE_STRING, .name = "entityId", .optional = false, .reference = false, .nullable = false },
						{ .type = VariableType::TYPE_STRING, .name = "animation", .optional = false, .reference = false, .nullable = false },
						{ .type = VariableType::TYPE_STRING, .name = "childEntityId", .optional = true, .reference = false, .nullable = false },
					},
					VariableType::TYPE_NULL
				),
				minitScript(minitScript) {}
			const string getMethodName() override {
				return "engine.entity.addOverlayAnimation";
			}
			void executeMethod(span<Variable>& arguments, Variable& returnValue, const SubStatement& subStatement) override {
				string entityId;
				string animation;
				string childEntityId;
				if (minitScript->getStringValue(arguments, 0, entityId) == true &&
					minitScript->getStringValue(arguments, 1, animation) == true &&
					minitScript->getStringValue(arguments, 2, childEntityId, true) == true) {
					auto object = dynamic_cast<Object*>(minitScript->getEntity(entityId, childEntityId));
					if (object != nullptr) {
						object->addOverlayAnimation(animation);
					} else {
						Console::printLine(getMethodName() + "(): " + minitScript->getSubStatementInformation(subStatement) + ": object entity not found: " + (childEntityId.empty() == true?entityId:childEntityId + "@" + entityId));
					}
				} else {
					Console::printLine(getMethodName() + "(): " + minitScript->getSubStatementInformation(subStatement) + ": argument mismatch: expected arguments: " + minitScript->getArgumentsInformation(getMethodName()));
					minitScript->startErrorScript();
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
			LogicMinitScript* minitScript { nullptr };
		public:
			MethodEntityRemoveOverlayAnimation(LogicMinitScript* minitScript):
				Method(
					{
						{ .type = VariableType::TYPE_STRING, .name = "entityId", .optional = false, .reference = false, .nullable = false },
						{ .type = VariableType::TYPE_STRING, .name = "animation", .optional = false, .reference = false, .nullable = false },
						{ .type = VariableType::TYPE_STRING, .name = "childEntityId", .optional = true, .reference = false, .nullable = false },
					},
					VariableType::TYPE_NULL
				),
				minitScript(minitScript) {}
			const string getMethodName() override {
				return "engine.entity.removeOverlayAnimation";
			}
			void executeMethod(span<Variable>& arguments, Variable& returnValue, const SubStatement& subStatement) override {
				string entityId;
				string animation;
				string childEntityId;
				if (minitScript->getStringValue(arguments, 0, entityId) == true &&
					minitScript->getStringValue(arguments, 1, animation) == true &&
					minitScript->getStringValue(arguments, 2, childEntityId, true) == true) {
					auto object = dynamic_cast<Object*>(minitScript->getEntity(entityId, childEntityId));
					if (object != nullptr) {
						object->removeOverlayAnimation(animation);
					} else {
						Console::printLine(getMethodName() + "(): " + minitScript->getSubStatementInformation(subStatement) + ": object entity not found: " + (childEntityId.empty() == true?entityId:childEntityId + "@" + entityId));
					}
				} else {
					Console::printLine(getMethodName() + "(): " + minitScript->getSubStatementInformation(subStatement) + ": argument mismatch: expected arguments: " + minitScript->getArgumentsInformation(getMethodName()));
					minitScript->startErrorScript();
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
			LogicMinitScript* minitScript { nullptr };
		public:
			MethodEntityRemoveFinishedOverlayAnimations(LogicMinitScript* minitScript):
				Method(
					{
						{ .type = VariableType::TYPE_STRING, .name = "entityId", .optional = false, .reference = false, .nullable = false },
						{ .type = VariableType::TYPE_STRING, .name = "childEntityId", .optional = true, .reference = false, .nullable = false },
					},
					VariableType::TYPE_NULL
				),
				minitScript(minitScript) {}
			const string getMethodName() override {
				return "engine.entity.removeFinishedOverlayAnimations";
			}
			void executeMethod(span<Variable>& arguments, Variable& returnValue, const SubStatement& subStatement) override {
				string entityId;
				string childEntityId;
				if (minitScript->getStringValue(arguments, 0, entityId) == true &&
					minitScript->getStringValue(arguments, 1, childEntityId, true) == true) {
					auto object = dynamic_cast<Object*>(minitScript->getEntity(entityId, childEntityId));
					if (object != nullptr) {
						object->removeFinishedOverlayAnimations();
					} else {
						Console::printLine(getMethodName() + "(): " + minitScript->getSubStatementInformation(subStatement) + ": object entity not found: " + (childEntityId.empty() == true?entityId:childEntityId + "@" + entityId));
					}
				} else {
					Console::printLine(getMethodName() + "(): " + minitScript->getSubStatementInformation(subStatement) + ": argument mismatch: expected arguments: " + minitScript->getArgumentsInformation(getMethodName()));
					minitScript->startErrorScript();
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
			LogicMinitScript* minitScript { nullptr };
		public:
			MethodEntityRemoveOverlayAnimations(LogicMinitScript* minitScript):
				Method(
					{
						{ .type = VariableType::TYPE_STRING, .name = "entityId", .optional = false, .reference = false, .nullable = false },
						{ .type = VariableType::TYPE_STRING, .name = "childEntityId", .optional = true, .reference = false, .nullable = false },
					},
					VariableType::TYPE_NULL
				),
				minitScript(minitScript) {}
			const string getMethodName() override {
				return "engine.entity.removeOverlayAnimations";
			}
			void executeMethod(span<Variable>& arguments, Variable& returnValue, const SubStatement& subStatement) override {
				string entityId;
				string childEntityId;
				if (minitScript->getStringValue(arguments, 0, entityId) == true &&
					minitScript->getStringValue(arguments, 1, childEntityId, true) == true) {
					auto object = dynamic_cast<Object*>(minitScript->getEntity(entityId, childEntityId));
					if (object != nullptr) {
						object->removeOverlayAnimations();
					} else {
						Console::printLine(getMethodName() + "(): " + minitScript->getSubStatementInformation(subStatement) + ": object entity not found: " + (childEntityId.empty() == true?entityId:childEntityId + "@" + entityId));
					}
				} else {
					Console::printLine(getMethodName() + "(): " + minitScript->getSubStatementInformation(subStatement) + ": argument mismatch: expected arguments: " + minitScript->getArgumentsInformation(getMethodName()));
					minitScript->startErrorScript();
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
			LogicMinitScript* minitScript { nullptr };
		public:
			MethodEntityGetOverlayAnimationTime(LogicMinitScript* minitScript):
				Method(
					{
						{ .type = VariableType::TYPE_STRING, .name = "entityId", .optional = false, .reference = false, .nullable = false },
						{ .type = VariableType::TYPE_STRING, .name = "animation", .optional = false, .reference = false, .nullable = false },
						{ .type = VariableType::TYPE_STRING, .name = "childEntityId", .optional = true, .reference = false, .nullable = false },
					},
					VariableType::TYPE_FLOAT
				),
				minitScript(minitScript) {}
			const string getMethodName() override {
				return "engine.entity.getOverlayAnimationTime";
			}
			void executeMethod(span<Variable>& arguments, Variable& returnValue, const SubStatement& subStatement) override {
				string entityId;
				string animation;
				string childEntityId;
				if (minitScript->getStringValue(arguments, 0, entityId) == true &&
					minitScript->getStringValue(arguments, 1, animation) == true &&
					minitScript->getStringValue(arguments, 2, childEntityId, true) == true) {
					auto object = dynamic_cast<Object*>(minitScript->getEntity(entityId, childEntityId));
					if (object != nullptr) {
						minitScript->setValue(returnValue, object->getOverlayAnimationTime(animation));
					} else {
						Console::printLine(getMethodName() + "(): " + minitScript->getSubStatementInformation(subStatement) + ": object entity not found: " + (childEntityId.empty() == true?entityId:childEntityId + "@" + entityId));
					}
				} else {
					Console::printLine(getMethodName() + "(): " + minitScript->getSubStatementInformation(subStatement) + ": argument mismatch: expected arguments: " + minitScript->getArgumentsInformation(getMethodName()));
					minitScript->startErrorScript();
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
			LogicMinitScript* minitScript { nullptr };
		public:
			MethodEntityGetNodeTransformMatrix(LogicMinitScript* minitScript):
				Method(
					{
						{ .type = VariableType::TYPE_STRING, .name = "entityId", .optional = false, .reference = false, .nullable = false },
						{ .type = VariableType::TYPE_STRING, .name = "nodeId", .optional = false, .reference = false, .nullable = false },
						{ .type = VariableType::TYPE_STRING, .name = "childEntityId", .optional = true, .reference = false, .nullable = false },
					},
					TYPE_MATRIX4x4
				),
				minitScript(minitScript) {}
			const string getMethodName() override {
				return "engine.entity.getNodeTransformMatrix";
			}
			void executeMethod(span<Variable>& arguments, Variable& returnValue, const SubStatement& subStatement) override {
				string entityId;
				string nodeId;
				string childEntityId;
				if (minitScript->getStringValue(arguments, 0, entityId) == true &&
					minitScript->getStringValue(arguments, 1, nodeId) == true &&
					minitScript->getStringValue(arguments, 2, childEntityId, true) == true) {
					auto object = dynamic_cast<Object*>(minitScript->getEntity(entityId, childEntityId));
					if (object != nullptr) {
						minitScript->setValue(returnValue, object->getNodeTransformMatrix(nodeId));
					} else {
						Console::printLine(getMethodName() + "(): " + minitScript->getSubStatementInformation(subStatement) + ": object entity not found: " + (childEntityId.empty() == true?entityId:childEntityId + "@" + entityId));
					}
				} else {
					Console::printLine(getMethodName() + "(): " + minitScript->getSubStatementInformation(subStatement) + ": argument mismatch: expected arguments: " + minitScript->getArgumentsInformation(getMethodName()));
					minitScript->startErrorScript();
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
			LogicMinitScript* minitScript { nullptr };
		public:
			MethodEntityGetNodeTransform(LogicMinitScript* minitScript):
				Method(
					{
						{ .type = VariableType::TYPE_STRING, .name = "entityId", .optional = false, .reference = false, .nullable = false },
						{ .type = VariableType::TYPE_STRING, .name = "nodeId", .optional = false, .reference = false, .nullable = false },
						{ .type = VariableType::TYPE_STRING, .name = "childEntityId", .optional = true, .reference = false, .nullable = false },
					},
					TYPE_TRANSFORM
				),
				minitScript(minitScript) {}
			const string getMethodName() override {
				return "engine.entity.getNodeTransform";
			}
			void executeMethod(span<Variable>& arguments, Variable& returnValue, const SubStatement& subStatement) override {
				string entityId;
				string nodeId;
				string childEntityId;
				if (minitScript->getStringValue(arguments, 0, entityId) == true &&
					minitScript->getStringValue(arguments, 1, nodeId) == true &&
					minitScript->getStringValue(arguments, 2, childEntityId, true) == true) {
					auto object = dynamic_cast<Object*>(minitScript->getEntity(entityId, childEntityId));
					if (object != nullptr) {
						Transform transform;
						transform.fromMatrix(object->getNodeTransformMatrix(nodeId), RotationOrder::ZYX);
						minitScript->setValue(returnValue, transform);
					} else {
						Console::printLine(getMethodName() + "(): " + minitScript->getSubStatementInformation(subStatement) + ": object entity not found: " + (childEntityId.empty() == true?entityId:childEntityId + "@" + entityId));
					}
				} else {
					Console::printLine(getMethodName() + "(): " + minitScript->getSubStatementInformation(subStatement) + ": argument mismatch: expected arguments: " + minitScript->getArgumentsInformation(getMethodName()));
					minitScript->startErrorScript();
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
			LogicMinitScript* minitScript { nullptr };
		public:
			MethodEntitySetNodeTransformMatrix(LogicMinitScript* minitScript):
				Method(
					{
						{ .type = VariableType::TYPE_STRING, .name = "entityId", .optional = false, .reference = false, .nullable = false },
						{ .type = VariableType::TYPE_STRING, .name = "nodeId", .optional = false, .reference = false, .nullable = false },
						{ .type = TYPE_MATRIX4x4, .name = "matrix", .optional = false, .reference = false, .nullable = false },
						{ .type = VariableType::TYPE_STRING, .name = "childEntityId", .optional = true, .reference = false, .nullable = false },
					},
					VariableType::TYPE_NULL
				),
				minitScript(minitScript) {}
			const string getMethodName() override {
				return "engine.entity.setNodeTransformMatrix";
			}
			void executeMethod(span<Variable>& arguments, Variable& returnValue, const SubStatement& subStatement) override {
				string entityId;
				string nodeId;
				Matrix4x4 matrix;
				string childEntityId;
				if (minitScript->getStringValue(arguments, 0, entityId) == true &&
					minitScript->getStringValue(arguments, 1, nodeId) == true &&
					minitScript->getMatrix4x4Value(arguments, 2, matrix) == true &&
					minitScript->getStringValue(arguments, 3, childEntityId, true) == true) {
					auto object = dynamic_cast<Object*>(minitScript->getEntity(entityId, childEntityId));
					if (object != nullptr) {
						object->setNodeTransformMatrix(nodeId, matrix);
					} else {
						Console::printLine(getMethodName() + "(): " + minitScript->getSubStatementInformation(subStatement) + ": object entity not found: " + (childEntityId.empty() == true?entityId:childEntityId + "@" + entityId));
					}
				} else {
					Console::printLine(getMethodName() + "(): " + minitScript->getSubStatementInformation(subStatement) + ": argument mismatch: expected arguments: " + minitScript->getArgumentsInformation(getMethodName()));
					minitScript->startErrorScript();
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
			LogicMinitScript* minitScript { nullptr };
		public:
			MethodEntitySetNodeTransform(LogicMinitScript* minitScript):
				Method(
					{
						{ .type = VariableType::TYPE_STRING, .name = "entityId", .optional = false, .reference = false, .nullable = false },
						{ .type = VariableType::TYPE_STRING, .name = "nodeId", .optional = false, .reference = false, .nullable = false },
						{ .type = TYPE_TRANSFORM, .name = "transform", .optional = false, .reference = false, .nullable = false },
						{ .type = VariableType::TYPE_STRING, .name = "childEntityId", .optional = true, .reference = false, .nullable = false },
					},
					VariableType::TYPE_NULL
				),
				minitScript(minitScript) {}
			const string getMethodName() override {
				return "engine.entity.setNodeTransform";
			}
			void executeMethod(span<Variable>& arguments, Variable& returnValue, const SubStatement& subStatement) override {
				string entityId;
				string nodeId;
				Transform transform;
				string childEntityId;
				if (minitScript->getStringValue(arguments, 0, entityId) == true &&
					minitScript->getStringValue(arguments, 1, nodeId) == true &&
					minitScript->getTransformValue(arguments, 2, transform) == true &&
					minitScript->getStringValue(arguments, 3, childEntityId, true) == true) {
					auto object = dynamic_cast<Object*>(minitScript->getEntity(entityId, childEntityId));
					if (object != nullptr) {
						object->setNodeTransformMatrix(nodeId, transform.getTransformMatrix());
					} else {
						Console::printLine(getMethodName() + "(): " + minitScript->getSubStatementInformation(subStatement) + ": object entity not found: " + (childEntityId.empty() == true?entityId:childEntityId + "@" + entityId));
					}
				} else {
					Console::printLine(getMethodName() + "(): " + minitScript->getSubStatementInformation(subStatement) + ": argument mismatch: expected arguments: " + minitScript->getArgumentsInformation(getMethodName()));
					minitScript->startErrorScript();
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
			LogicMinitScript* minitScript { nullptr };
		public:
			MethodEntityUnsetNodeTransformMatrix(LogicMinitScript* minitScript):
				Method(
					{
						{ .type = VariableType::TYPE_STRING, .name = "entityId", .optional = false, .reference = false, .nullable = false },
						{ .type = VariableType::TYPE_STRING, .name = "nodeId", .optional = false, .reference = false, .nullable = false },
						{ .type = VariableType::TYPE_STRING, .name = "childEntityId", .optional = true, .reference = false, .nullable = false },
					},
					VariableType::TYPE_NULL
				),
				minitScript(minitScript) {}
			const string getMethodName() override {
				return "engine.entity.unsetNodeTransformMatrix";
			}
			void executeMethod(span<Variable>& arguments, Variable& returnValue, const SubStatement& subStatement) override {
				string entityId;
				string nodeId;
				string childEntityId;
				if (minitScript->getStringValue(arguments, 0, entityId) == true &&
					minitScript->getStringValue(arguments, 1, nodeId) == true &&
					minitScript->getStringValue(arguments, 2, childEntityId, true) == true) {
					auto object = dynamic_cast<Object*>(minitScript->getEntity(entityId, childEntityId));
					if (object != nullptr) {
						object->unsetNodeTransformMatrix(nodeId);
					} else {
						Console::printLine(getMethodName() + "(): " + minitScript->getSubStatementInformation(subStatement) + ": object entity not found: " + (childEntityId.empty() == true?entityId:childEntityId + "@" + entityId));
					}
				} else {
					Console::printLine(getMethodName() + "(): " + minitScript->getSubStatementInformation(subStatement) + ": argument mismatch: expected arguments: " + minitScript->getArgumentsInformation(getMethodName()));
					minitScript->startErrorScript();
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
			LogicMinitScript* minitScript { nullptr };
		public:
			MethodEntityUnsetNodeTransform(LogicMinitScript* minitScript):
				Method(
					{
						{ .type = VariableType::TYPE_STRING, .name = "entityId", .optional = false, .reference = false, .nullable = false },
						{ .type = VariableType::TYPE_STRING, .name = "nodeId", .optional = false, .reference = false, .nullable = false },
						{ .type = VariableType::TYPE_STRING, .name = "childEntityId", .optional = true, .reference = false, .nullable = false },
					},
					VariableType::TYPE_NULL
				),
				minitScript(minitScript) {}
			const string getMethodName() override {
				return "engine.entity.unsetNodeTransform";
			}
			void executeMethod(span<Variable>& arguments, Variable& returnValue, const SubStatement& subStatement) override {
				string entityId;
				string nodeId;
				string childEntityId;
				if (minitScript->getStringValue(arguments, 0, entityId) == true &&
					minitScript->getStringValue(arguments, 1, nodeId) == true &&
					minitScript->getStringValue(arguments, 2, childEntityId, true) == true) {
					auto object = dynamic_cast<Object*>(minitScript->getEntity(entityId, childEntityId));
					if (object != nullptr) {
						object->unsetNodeTransformMatrix(nodeId);
					} else {
						Console::printLine(getMethodName() + "(): " + minitScript->getSubStatementInformation(subStatement) + ": object entity not found: " + (childEntityId.empty() == true?entityId:childEntityId + "@" + entityId));
					}
				} else {
					Console::printLine(getMethodName() + "(): " + minitScript->getSubStatementInformation(subStatement) + ": argument mismatch: expected arguments: " + minitScript->getArgumentsInformation(getMethodName()));
					minitScript->startErrorScript();
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
			LogicMinitScript* minitScript { nullptr };
		public:
			MethodEntityEmitParticles(LogicMinitScript* minitScript):
				Method(
					{
						{ .type = VariableType::TYPE_STRING, .name = "entityId", .optional = false, .reference = false, .nullable = false },
						{ .type = VariableType::TYPE_STRING, .name = "childEntityId", .optional = true, .reference = false, .nullable = false },
					},
					VariableType::TYPE_INTEGER
				),
				minitScript(minitScript) {}
			const string getMethodName() override {
				return "engine.entity.emitParticles";
			}
			void executeMethod(span<Variable>& arguments, Variable& returnValue, const SubStatement& subStatement) override {
				string entityId;
				string childEntityId;
				if (minitScript->getStringValue(arguments, 0, entityId) == true &&
					minitScript->getStringValue(arguments, 1, childEntityId, true) == true) {
					auto entity = dynamic_cast<ParticleSystem*>(minitScript->getEntity(entityId, childEntityId));
					if (entity != nullptr) {
						minitScript->setValue(returnValue, static_cast<int64_t>(entity->emitParticles()));
					} else {
						Console::printLine(getMethodName() + "(): " + minitScript->getSubStatementInformation(subStatement) + ": particle system entity not found: " + (childEntityId.empty() == true?entityId:childEntityId + "@" + entityId));
					}
				} else {
					Console::printLine(getMethodName() + "(): " + minitScript->getSubStatementInformation(subStatement) + ": argument mismatch: expected arguments: " + minitScript->getArgumentsInformation(getMethodName()));
					minitScript->startErrorScript();
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
			LogicMinitScript* minitScript { nullptr };
		public:
			MethodBodyTYPE_STATIC(LogicMinitScript* minitScript):
				Method({}, VariableType::TYPE_INTEGER),
				minitScript(minitScript) {}
			const string getMethodName() override {
				return "world.body.TYPE_STATIC";
			}
			void executeMethod(span<Variable>& arguments, Variable& returnValue, const SubStatement& subStatement) override {
				minitScript->setValue(returnValue, static_cast<int64_t>(Body::BODYTYPE_STATIC));
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
			LogicMinitScript* minitScript { nullptr };
		public:
			MethodBodyTYPE_DYNAMIC(LogicMinitScript* minitScript):
				Method({}, VariableType::TYPE_INTEGER),
				minitScript(minitScript) {}
			const string getMethodName() override {
				return "world.body.TYPE_DYNAMIC";
			}
			void executeMethod(span<Variable>& arguments, Variable& returnValue, const SubStatement& subStatement) override {
				minitScript->setValue(returnValue, static_cast<int64_t>(Body::BODYTYPE_DYNAMIC));
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
			LogicMinitScript* minitScript { nullptr };
		public:
			MethodBodyTYPE_COLLISIONSTATIC(LogicMinitScript* minitScript):
				Method({}, VariableType::TYPE_INTEGER),
				minitScript(minitScript) {}
			const string getMethodName() override {
				return "world.body.TYPE_COLLISION_STATIC";
			}
			void executeMethod(span<Variable>& arguments, Variable& returnValue, const SubStatement& subStatement) override {
				minitScript->setValue(returnValue, static_cast<int64_t>(Body::BODYTYPE_COLLISION_STATIC));
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
			LogicMinitScript* minitScript { nullptr };
		public:
			MethodBodyTYPE_COLLISIONDYNAMIC(LogicMinitScript* minitScript):
				Method({}, VariableType::TYPE_INTEGER),
				minitScript(minitScript) {}
			const string getMethodName() override {
				return "world.body.TYPE_COLLISION_DYNAMIC";
			}
			void executeMethod(span<Variable>& arguments, Variable& returnValue, const SubStatement& subStatement) override {
				minitScript->setValue(returnValue, static_cast<int64_t>(Body::BODYTYPE_COLLISION_DYNAMIC));
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
			LogicMinitScript* minitScript { nullptr };
		public:
			MethodBodyCOLLISION_TYPEID_STATIC(LogicMinitScript* minitScript):
				Method({}, VariableType::TYPE_INTEGER),
				minitScript(minitScript) {}
			const string getMethodName() override {
				return "world.body.COLLISION_TYPEID_STATIC";
			}
			void executeMethod(span<Variable>& arguments, Variable& returnValue, const SubStatement& subStatement) override {
				minitScript->setValue(returnValue, static_cast<int64_t>(Body::COLLISION_TYPEID_STATIC));
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
			LogicMinitScript* minitScript { nullptr };
		public:
			MethodBodyCOLLISION_TYPEID_DYNAMIC(LogicMinitScript* minitScript):
				Method({}, VariableType::TYPE_INTEGER),
				minitScript(minitScript) {}
			const string getMethodName() override {
				return "world.body.COLLISION_TYPEID_DYNAMIC";
			}
			void executeMethod(span<Variable>& arguments, Variable& returnValue, const SubStatement& subStatement) override {
				minitScript->setValue(returnValue, static_cast<int64_t>(Body::COLLISION_TYPEID_DYNAMIC));
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
			LogicMinitScript* minitScript { nullptr };
		public:
			MethodBodyCOLLISION_TYPEID_3(LogicMinitScript* minitScript):
				Method({}, VariableType::TYPE_INTEGER),
				minitScript(minitScript) {}
			const string getMethodName() override {
				return "world.body.COLLISION_TYPEID_3";
			}
			void executeMethod(span<Variable>& arguments, Variable& returnValue, const SubStatement& subStatement) override {
				minitScript->setValue(returnValue, static_cast<int64_t>(Body::COLLISION_TYPEID_3));
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
			LogicMinitScript* minitScript { nullptr };
		public:
			MethodBodyCOLLISION_TYPEID_4(LogicMinitScript* minitScript):
				Method({}, VariableType::TYPE_INTEGER),
				minitScript(minitScript) {}
			const string getMethodName() override {
				return "world.body.COLLISION_TYPEID_4";
			}
			void executeMethod(span<Variable>& arguments, Variable& returnValue, const SubStatement& subStatement) override {
				minitScript->setValue(returnValue, static_cast<int64_t>(Body::COLLISION_TYPEID_4));
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
			LogicMinitScript* minitScript { nullptr };
		public:
			MethodBodyCOLLISION_TYPEID_5(LogicMinitScript* minitScript):
				Method({}, VariableType::TYPE_INTEGER),
				minitScript(minitScript) {}
			const string getMethodName() override {
				return "world.body.COLLISION_TYPEID_5";
			}
			void executeMethod(span<Variable>& arguments, Variable& returnValue, const SubStatement& subStatement) override {
				minitScript->setValue(returnValue, static_cast<int64_t>(Body::COLLISION_TYPEID_5));
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
			LogicMinitScript* minitScript { nullptr };
		public:
			MethodBodyCOLLISION_TYPEID_6(LogicMinitScript* minitScript):
				Method({}, VariableType::TYPE_INTEGER),
				minitScript(minitScript) {}
			const string getMethodName() override {
				return "world.body.COLLISION_TYPEID_6";
			}
			void executeMethod(span<Variable>& arguments, Variable& returnValue, const SubStatement& subStatement) override {
				minitScript->setValue(returnValue, static_cast<int64_t>(Body::COLLISION_TYPEID_6));
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
			LogicMinitScript* minitScript { nullptr };
		public:
			MethodBodyCOLLISION_TYPEID_7(LogicMinitScript* minitScript):
				Method({}, VariableType::TYPE_INTEGER),
				minitScript(minitScript) {}
			const string getMethodName() override {
				return "world.body.COLLISION_TYPEID_7";
			}
			void executeMethod(span<Variable>& arguments, Variable& returnValue, const SubStatement& subStatement) override {
				minitScript->setValue(returnValue, static_cast<int64_t>(Body::COLLISION_TYPEID_7));
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
			LogicMinitScript* minitScript { nullptr };
		public:
			MethodBodyCOLLISION_TYPEID_8(LogicMinitScript* minitScript):
				Method({}, VariableType::TYPE_INTEGER),
				minitScript(minitScript) {}
			const string getMethodName() override {
				return "world.body.COLLISION_TYPEID_8";
			}
			void executeMethod(span<Variable>& arguments, Variable& returnValue, const SubStatement& subStatement) override {
				minitScript->setValue(returnValue, static_cast<int64_t>(Body::COLLISION_TYPEID_8));
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
			LogicMinitScript* minitScript { nullptr };
		public:
			MethodBodyCOLLISION_TYPEID_9(LogicMinitScript* minitScript):
				Method({}, VariableType::TYPE_INTEGER),
				minitScript(minitScript) {}
			const string getMethodName() override {
				return "world.body.COLLISION_TYPEID_9";
			}
			void executeMethod(span<Variable>& arguments, Variable& returnValue, const SubStatement& subStatement) override {
				minitScript->setValue(returnValue, static_cast<int64_t>(Body::COLLISION_TYPEID_9));
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
			LogicMinitScript* minitScript { nullptr };
		public:
			MethodBodyCOLLISION_TYPEID_10(LogicMinitScript* minitScript):
				Method({}, VariableType::TYPE_INTEGER),
				minitScript(minitScript) {}
			const string getMethodName() override {
				return "world.body.COLLISION_TYPEID_10";
			}
			void executeMethod(span<Variable>& arguments, Variable& returnValue, const SubStatement& subStatement) override {
				minitScript->setValue(returnValue, static_cast<int64_t>(Body::COLLISION_TYPEID_10));
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
			LogicMinitScript* minitScript { nullptr };
		public:
			MethodBodyCOLLISION_TYPEID_11(LogicMinitScript* minitScript):
				Method({}, VariableType::TYPE_INTEGER),
				minitScript(minitScript) {}
			const string getMethodName() override {
				return "world.body.COLLISION_TYPEID_11";
			}
			void executeMethod(span<Variable>& arguments, Variable& returnValue, const SubStatement& subStatement) override {
				minitScript->setValue(returnValue, static_cast<int64_t>(Body::COLLISION_TYPEID_11));
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
			LogicMinitScript* minitScript { nullptr };
		public:
			MethodBodyCOLLISION_TYPEID_12(LogicMinitScript* minitScript):
				Method({}, VariableType::TYPE_INTEGER),
				minitScript(minitScript) {}
			const string getMethodName() override {
				return "world.body.COLLISION_TYPEID_12";
			}
			void executeMethod(span<Variable>& arguments, Variable& returnValue, const SubStatement& subStatement) override {
				minitScript->setValue(returnValue, static_cast<int64_t>(Body::COLLISION_TYPEID_12));
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
			LogicMinitScript* minitScript { nullptr };
		public:
			MethodBodyCOLLISION_TYPEID_13(LogicMinitScript* minitScript):
				Method({}, VariableType::TYPE_INTEGER),
				minitScript(minitScript) {}
			const string getMethodName() override {
				return "world.body.COLLISION_TYPEID_13";
			}
			void executeMethod(span<Variable>& arguments, Variable& returnValue, const SubStatement& subStatement) override {
				minitScript->setValue(returnValue, static_cast<int64_t>(Body::COLLISION_TYPEID_13));
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
			LogicMinitScript* minitScript { nullptr };
		public:
			MethodBodyCOLLISION_TYPEID_14(LogicMinitScript* minitScript):
				Method({}, VariableType::TYPE_INTEGER),
				minitScript(minitScript) {}
			const string getMethodName() override {
				return "world.body.COLLISION_TYPEID_14";
			}
			void executeMethod(span<Variable>& arguments, Variable& returnValue, const SubStatement& subStatement) override {
				minitScript->setValue(returnValue, static_cast<int64_t>(Body::COLLISION_TYPEID_14));
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
			LogicMinitScript* minitScript { nullptr };
		public:
			MethodBodyCOLLISION_TYPEID_15(LogicMinitScript* minitScript):
				Method({}, VariableType::TYPE_INTEGER),
				minitScript(minitScript) {}
			const string getMethodName() override {
				return "world.body.COLLISION_TYPEID_15";
			}
			void executeMethod(span<Variable>& arguments, Variable& returnValue, const SubStatement& subStatement) override {
				minitScript->setValue(returnValue, static_cast<int64_t>(Body::COLLISION_TYPEID_15));
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
			LogicMinitScript* minitScript { nullptr };
		public:
			MethodBodyCOLLISION_TYPEID_16(LogicMinitScript* minitScript):
				Method({}, VariableType::TYPE_INTEGER),
				minitScript(minitScript) {}
			const string getMethodName() override {
				return "world.body.COLLISION_TYPEID_16";
			}
			void executeMethod(span<Variable>& arguments, Variable& returnValue, const SubStatement& subStatement) override {
				minitScript->setValue(returnValue, static_cast<int64_t>(Body::COLLISION_TYPEID_16));
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
			LogicMinitScript* minitScript { nullptr };
		public:
			MethodBodyCOLLISION_TYPEID_ALL(LogicMinitScript* minitScript):
				Method({}, VariableType::TYPE_INTEGER),
				minitScript(minitScript) {}
			const string getMethodName() override {
				return "world.body.COLLISION_TYPEID_ALL";
			}
			void executeMethod(span<Variable>& arguments, Variable& returnValue, const SubStatement& subStatement) override {
				minitScript->setValue(returnValue, static_cast<int64_t>(Body::COLLISION_TYPEID_ALL));
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
			LogicMinitScript* minitScript { nullptr };
		public:
			MethodBodyIsEnabled(LogicMinitScript* minitScript):
				Method(
					{
						{ .type = VariableType::TYPE_STRING, .name = "bodyId", .optional = false, .reference = false, .nullable = false }
					},
					VariableType::TYPE_BOOLEAN
				),
				minitScript(minitScript) {}
			const string getMethodName() override {
				return "world.body.isEnabled";
			}
			void executeMethod(span<Variable>& arguments, Variable& returnValue, const SubStatement& subStatement) override {
				string bodyId;
				if (minitScript->getStringValue(arguments, 0, bodyId) == true) {
					auto body = minitScript->context->getWorld()->getBody(bodyId);
					if (body != nullptr) {
						minitScript->setValue(returnValue, body->isEnabled());
					} else {
						Console::printLine(getMethodName() + "(): " + minitScript->getSubStatementInformation(subStatement) + ": body not found: " + bodyId);
					}
				} else {
					Console::printLine(getMethodName() + "(): " + minitScript->getSubStatementInformation(subStatement) + ": argument mismatch: expected arguments: " + minitScript->getArgumentsInformation(getMethodName()));
					minitScript->startErrorScript();
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
			LogicMinitScript* minitScript { nullptr };
		public:
			MethodBodySetEnabled(LogicMinitScript* minitScript):
				Method(
					{
						{ .type = VariableType::TYPE_STRING, .name = "bodyId", .optional = false, .reference = false, .nullable = false },
						{ .type = VariableType::TYPE_BOOLEAN, .name = "enabled", .optional = false, .reference = false, .nullable = false }
					},
					VariableType::TYPE_NULL
				),
				minitScript(minitScript) {}
			const string getMethodName() override {
				return "world.body.setEnabled";
			}
			void executeMethod(span<Variable>& arguments, Variable& returnValue, const SubStatement& subStatement) override {
				string bodyId;
				bool enabled;
				if (minitScript->getStringValue(arguments, 0, bodyId) == true &&
					minitScript->getBooleanValue(arguments, 1, enabled) == true) {
					auto body = minitScript->context->getWorld()->getBody(bodyId);
					if (body != nullptr) {
						body->setEnabled(enabled);
					} else {
						Console::printLine(getMethodName() + "(): " + minitScript->getSubStatementInformation(subStatement) + ": body not found: " + bodyId);
					}
				} else {
					Console::printLine(getMethodName() + "(): " + minitScript->getSubStatementInformation(subStatement) + ": argument mismatch: expected arguments: " + minitScript->getArgumentsInformation(getMethodName()));
					minitScript->startErrorScript();
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
			LogicMinitScript* minitScript { nullptr };
		public:
			MethodBodyGetType(LogicMinitScript* minitScript):
				Method(
					{
						{ .type = VariableType::TYPE_STRING, .name = "bodyId", .optional = false, .reference = false, .nullable = false }
					},
					VariableType::TYPE_INTEGER
				),
				minitScript(minitScript) {}
			const string getMethodName() override {
				return "world.body.getType";
			}
			void executeMethod(span<Variable>& arguments, Variable& returnValue, const SubStatement& subStatement) override {
				string bodyId;
				if (minitScript->getStringValue(arguments, 0, bodyId) == true) {
					auto body = minitScript->context->getWorld()->getBody(bodyId);
					if (body != nullptr) {
						minitScript->setValue(returnValue, static_cast<int64_t>(body->getType()));
					} else {
						Console::printLine(getMethodName() + "(): " + minitScript->getSubStatementInformation(subStatement) + ": body not found: " + bodyId);
					}
				} else {
					Console::printLine(getMethodName() + "(): " + minitScript->getSubStatementInformation(subStatement) + ": argument mismatch: expected arguments: " + minitScript->getArgumentsInformation(getMethodName()));
					minitScript->startErrorScript();
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
			LogicMinitScript* minitScript { nullptr };
		public:
			MethodBodyGetCollisionTypeId(LogicMinitScript* minitScript):
				Method(
					{
						{ .type = VariableType::TYPE_STRING, .name = "bodyId", .optional = false, .reference = false, .nullable = false }
					},
					VariableType::TYPE_INTEGER
				),
				minitScript(minitScript) {}
			const string getMethodName() override {
				return "world.body.getCollisionTypeId";
			}
			void executeMethod(span<Variable>& arguments, Variable& returnValue, const SubStatement& subStatement) override {
				string bodyId;
				if (minitScript->getStringValue(arguments, 0, bodyId) == true) {
					auto body = minitScript->context->getWorld()->getBody(bodyId);
					if (body != nullptr) {
						minitScript->setValue(returnValue, static_cast<int64_t>(body->getCollisionTypeId()));
					} else {
						Console::printLine(getMethodName() + "(): " + minitScript->getSubStatementInformation(subStatement) + ": body not found: " + bodyId);
					}
				} else {
					Console::printLine(getMethodName() + "(): " + minitScript->getSubStatementInformation(subStatement) + ": argument mismatch: expected arguments: " + minitScript->getArgumentsInformation(getMethodName()));
					minitScript->startErrorScript();
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
			LogicMinitScript* minitScript { nullptr };
		public:
			MethodBodySetCollisionTypeId(LogicMinitScript* minitScript):
				Method(
					{
						{ .type = VariableType::TYPE_STRING, .name = "bodyId", .optional = false, .reference = false, .nullable = false },
						{ .type = VariableType::TYPE_INTEGER, .name = "collisionTypeId", .optional = false, .reference = false, .nullable = false }
					},
					VariableType::TYPE_NULL
				),
				minitScript(minitScript) {}
			const string getMethodName() override {
				return "world.body.setCollisionTypeId";
			}
			void executeMethod(span<Variable>& arguments, Variable& returnValue, const SubStatement& subStatement) override {
				string bodyId;
				int64_t collisionTypeId;
				if (minitScript->getStringValue(arguments, 0, bodyId) == true &&
					minitScript->getIntegerValue(arguments, 1, collisionTypeId) == true) {
					auto body = minitScript->context->getWorld()->getBody(bodyId);
					if (body != nullptr) {
						body->setCollisionTypeId(collisionTypeId);
					} else {
						Console::printLine(getMethodName() + "(): " + minitScript->getSubStatementInformation(subStatement) + ": body not found: " + bodyId);
					}
				} else {
					Console::printLine(getMethodName() + "(): " + minitScript->getSubStatementInformation(subStatement) + ": argument mismatch: expected arguments: " + minitScript->getArgumentsInformation(getMethodName()));
					minitScript->startErrorScript();
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
			LogicMinitScript* minitScript { nullptr };
		public:
			MethodBodyGetCollisionTypeIds(LogicMinitScript* minitScript):
				Method(
					{
						{ .type = VariableType::TYPE_STRING, .name = "bodyId", .optional = false, .reference = false, .nullable = false }
					},
					VariableType::TYPE_INTEGER
				),
				minitScript(minitScript) {}
			const string getMethodName() override {
				return "world.body.getCollisionTypeIds";
			}
			void executeMethod(span<Variable>& arguments, Variable& returnValue, const SubStatement& subStatement) override {
				string bodyId;
				if (minitScript->getStringValue(arguments, 0, bodyId) == true) {
					auto body = minitScript->context->getWorld()->getBody(bodyId);
					if (body != nullptr) {
						minitScript->setValue(returnValue, static_cast<int64_t>(body->getCollisionTypeIds()));
					} else {
						Console::printLine(getMethodName() + "(): " + minitScript->getSubStatementInformation(subStatement) + ": body not found: " + bodyId);
					}
				} else {
					Console::printLine(getMethodName() + "(): " + minitScript->getSubStatementInformation(subStatement) + ": argument mismatch: expected arguments: " + minitScript->getArgumentsInformation(getMethodName()));
					minitScript->startErrorScript();
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
			LogicMinitScript* minitScript { nullptr };
		public:
			MethodBodySetCollisionTypeIds(LogicMinitScript* minitScript):
				Method(
					{
						{ .type = VariableType::TYPE_STRING, .name = "bodyId", .optional = false, .reference = false, .nullable = false },
						{ .type = VariableType::TYPE_INTEGER, .name = "collisionTypeIds", .optional = false, .reference = false, .nullable = false }
					},
					VariableType::TYPE_NULL
				),
				minitScript(minitScript) {}
			const string getMethodName() override {
				return "world.body.setCollisionTypeIds";
			}
			void executeMethod(span<Variable>& arguments, Variable& returnValue, const SubStatement& subStatement) override {
				string bodyId;
				int64_t collisionTypeIds;
				if (minitScript->getStringValue(arguments, 0, bodyId) == true &&
					minitScript->getIntegerValue(arguments, 1, collisionTypeIds) == true) {
					auto body = minitScript->context->getWorld()->getBody(bodyId);
					if (body != nullptr) {
						body->setCollisionTypeIds(collisionTypeIds);
					} else {
						Console::printLine(getMethodName() + "(): " + minitScript->getSubStatementInformation(subStatement) + ": body not found: " + bodyId);
					}
				} else {
					Console::printLine(getMethodName() + "(): " + minitScript->getSubStatementInformation(subStatement) + ": argument mismatch: expected arguments: " + minitScript->getArgumentsInformation(getMethodName()));
					minitScript->startErrorScript();
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
			LogicMinitScript* minitScript { nullptr };
		public:
			MethodBodyGetLinearDamping(LogicMinitScript* minitScript):
				Method(
					{
						{ .type = VariableType::TYPE_STRING, .name = "bodyId", .optional = false, .reference = false, .nullable = false }
					},
					VariableType::TYPE_FLOAT
				),
				minitScript(minitScript) {}
			const string getMethodName() override {
				return "world.body.getLinearDamping";
			}
			void executeMethod(span<Variable>& arguments, Variable& returnValue, const SubStatement& subStatement) override {
				string bodyId;
				if (minitScript->getStringValue(arguments, 0, bodyId) == true) {
					auto body = minitScript->context->getWorld()->getBody(bodyId);
					if (body != nullptr) {
						minitScript->setValue(returnValue, body->getLinearDamping());
					} else {
						Console::printLine(getMethodName() + "(): " + minitScript->getSubStatementInformation(subStatement) + ": body not found: " + bodyId);
					}
				} else {
					Console::printLine(getMethodName() + "(): " + minitScript->getSubStatementInformation(subStatement) + ": argument mismatch: expected arguments: " + minitScript->getArgumentsInformation(getMethodName()));
					minitScript->startErrorScript();
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
			LogicMinitScript* minitScript { nullptr };
		public:
			MethodBodySetLinearDamping(LogicMinitScript* minitScript):
				Method(
					{
						{ .type = VariableType::TYPE_STRING, .name = "bodyId", .optional = false, .reference = false, .nullable = false },
						{ .type = VariableType::TYPE_FLOAT, .name = "linearDamping", .optional = false, .reference = false, .nullable = false }
					},
					VariableType::TYPE_NULL
				),
				minitScript(minitScript) {}
			const string getMethodName() override {
				return "world.body.setLinearDamping";
			}
			void executeMethod(span<Variable>& arguments, Variable& returnValue, const SubStatement& subStatement) override {
				string bodyId;
				float linearDamping;
				if (minitScript->getStringValue(arguments, 0, bodyId) == true &&
					minitScript->getFloatValue(arguments, 1, linearDamping) == true) {
					auto body = minitScript->context->getWorld()->getBody(bodyId);
					if (body != nullptr) {
						body->setLinearDamping(linearDamping);
					} else {
						Console::printLine(getMethodName() + "(): " + minitScript->getSubStatementInformation(subStatement) + ": body not found: " + bodyId);
					}
				} else {
					Console::printLine(getMethodName() + "(): " + minitScript->getSubStatementInformation(subStatement) + ": argument mismatch: expected arguments: " + minitScript->getArgumentsInformation(getMethodName()));
					minitScript->startErrorScript();
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
			LogicMinitScript* minitScript { nullptr };
		public:
			MethodBodyGetAngularDamping(LogicMinitScript* minitScript):
				Method(
					{
						{ .type = VariableType::TYPE_STRING, .name = "bodyId", .optional = false, .reference = false, .nullable = false }
					},
					VariableType::TYPE_FLOAT
				),
				minitScript(minitScript) {}
			const string getMethodName() override {
				return "world.body.getAngularDamping";
			}
			void executeMethod(span<Variable>& arguments, Variable& returnValue, const SubStatement& subStatement) override {
				string bodyId;
				if (minitScript->getStringValue(arguments, 0, bodyId) == true) {
					auto body = minitScript->context->getWorld()->getBody(bodyId);
					if (body != nullptr) {
						minitScript->setValue(returnValue, body->getAngularDamping());
					} else {
						Console::printLine(getMethodName() + "(): " + minitScript->getSubStatementInformation(subStatement) + ": body not found: " + bodyId);
					}
				} else {
					Console::printLine(getMethodName() + "(): " + minitScript->getSubStatementInformation(subStatement) + ": argument mismatch: expected arguments: " + minitScript->getArgumentsInformation(getMethodName()));
					minitScript->startErrorScript();
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
			LogicMinitScript* minitScript { nullptr };
		public:
			MethodBodySetAngularDamping(LogicMinitScript* minitScript):
				Method(
					{
						{ .type = VariableType::TYPE_STRING, .name = "bodyId", .optional = false, .reference = false, .nullable = false },
						{ .type = VariableType::TYPE_FLOAT, .name = "angularDamping", .optional = false, .reference = false, .nullable = false }
					},
					VariableType::TYPE_NULL
				),
				minitScript(minitScript) {}
			const string getMethodName() override {
				return "world.body.setAngularDamping";
			}
			void executeMethod(span<Variable>& arguments, Variable& returnValue, const SubStatement& subStatement) override {
				string bodyId;
				float angularDamping;
				if (minitScript->getStringValue(arguments, 0, bodyId) == true &&
					minitScript->getFloatValue(arguments, 1, angularDamping) == true) {
					auto body = minitScript->context->getWorld()->getBody(bodyId);
					if (body != nullptr) {
						body->setAngularDamping(angularDamping);
					} else {
						Console::printLine(getMethodName() + "(): " + minitScript->getSubStatementInformation(subStatement) + ": body not found: " + bodyId);
					}
				} else {
					Console::printLine(getMethodName() + "(): " + minitScript->getSubStatementInformation(subStatement) + ": argument mismatch: expected arguments: " + minitScript->getArgumentsInformation(getMethodName()));
					minitScript->startErrorScript();
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
			LogicMinitScript* minitScript { nullptr };
		public:
			MethodBodyGetLinearVelocity(LogicMinitScript* minitScript):
				Method(
					{
						{ .type = VariableType::TYPE_STRING, .name = "bodyId", .optional = false, .reference = false, .nullable = false }
					},
					TYPE_VECTOR3
				),
				minitScript(minitScript) {}
			const string getMethodName() override {
				return "world.body.getLinearVelocity";
			}
			void executeMethod(span<Variable>& arguments, Variable& returnValue, const SubStatement& subStatement) override {
				string bodyId;
				if (minitScript->getStringValue(arguments, 0, bodyId) == true) {
					auto body = minitScript->context->getWorld()->getBody(bodyId);
					if (body != nullptr) {
						minitScript->setValue(returnValue, body->getLinearVelocity());
					} else {
						Console::printLine(getMethodName() + "(): " + minitScript->getSubStatementInformation(subStatement) + ": body not found: " + bodyId);
					}
				} else {
					Console::printLine(getMethodName() + "(): " + minitScript->getSubStatementInformation(subStatement) + ": argument mismatch: expected arguments: " + minitScript->getArgumentsInformation(getMethodName()));
					minitScript->startErrorScript();
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
			LogicMinitScript* minitScript { nullptr };
		public:
			MethodBodySetLinearVelocity(LogicMinitScript* minitScript):
				Method(
					{
						{ .type = VariableType::TYPE_STRING, .name = "bodyId", .optional = false, .reference = false, .nullable = false },
						{ .type = TYPE_VECTOR3, .name = "linearVelocity", .optional = false, .reference = false, .nullable = false }
					},
					VariableType::TYPE_NULL
				),
				minitScript(minitScript) {}
			const string getMethodName() override {
				return "world.body.setLinearVelocity";
			}
			void executeMethod(span<Variable>& arguments, Variable& returnValue, const SubStatement& subStatement) override {
				string bodyId;
				Vector3 linearVelocity;
				if (minitScript->getStringValue(arguments, 0, bodyId) == true &&
					minitScript->getVector3Value(arguments, 1, linearVelocity) == true) {
					auto body = minitScript->context->getWorld()->getBody(bodyId);
					if (body != nullptr) {
						body->setLinearVelocity(linearVelocity);
					} else {
						Console::printLine(getMethodName() + "(): " + minitScript->getSubStatementInformation(subStatement) + ": body not found: " + bodyId);
					}
				} else {
					Console::printLine(getMethodName() + "(): " + minitScript->getSubStatementInformation(subStatement) + ": argument mismatch: expected arguments: " + minitScript->getArgumentsInformation(getMethodName()));
					minitScript->startErrorScript();
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
			LogicMinitScript* minitScript { nullptr };
		public:
			MethodBodyGetAngularVelocity(LogicMinitScript* minitScript):
				Method(
					{
						{ .type = VariableType::TYPE_STRING, .name = "bodyId", .optional = false, .reference = false, .nullable = false }
					},
					TYPE_VECTOR3
				),
				minitScript(minitScript) {}
			const string getMethodName() override {
				return "world.body.getAngularVelocity";
			}
			void executeMethod(span<Variable>& arguments, Variable& returnValue, const SubStatement& subStatement) override {
				string bodyId;
				if (minitScript->getStringValue(arguments, 0, bodyId) == true) {
					auto body = minitScript->context->getWorld()->getBody(bodyId);
					if (body != nullptr) {
						minitScript->setValue(returnValue, body->getAngularVelocity());
					} else {
						Console::printLine(getMethodName() + "(): " + minitScript->getSubStatementInformation(subStatement) + ": body not found: " + bodyId);
					}
				} else {
					Console::printLine(getMethodName() + "(): " + minitScript->getSubStatementInformation(subStatement) + ": argument mismatch: expected arguments: " + minitScript->getArgumentsInformation(getMethodName()));
					minitScript->startErrorScript();
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
			LogicMinitScript* minitScript { nullptr };
		public:
			MethodBodySetAngularVelocity(LogicMinitScript* minitScript):
				Method(
					{
						{ .type = VariableType::TYPE_STRING, .name = "bodyId", .optional = false, .reference = false, .nullable = false },
						{ .type = TYPE_VECTOR3, .name = "angularVelocity", .optional = false, .reference = false, .nullable = false }
					},
					VariableType::TYPE_NULL
				),
				minitScript(minitScript) {}
			const string getMethodName() override {
				return "world.body.setAngularVelocity";
			}
			void executeMethod(span<Variable>& arguments, Variable& returnValue, const SubStatement& subStatement) override {
				string bodyId;
				Vector3 angularVelocity;
				if (minitScript->getStringValue(arguments, 0, bodyId) == true &&
					minitScript->getVector3Value(arguments, 1, angularVelocity) == true) {
					auto body = minitScript->context->getWorld()->getBody(bodyId);
					if (body != nullptr) {
						body->setAngularVelocity(angularVelocity);
					} else {
						Console::printLine(getMethodName() + "(): " + minitScript->getSubStatementInformation(subStatement) + ": body not found: " + bodyId);
					}
				} else {
					Console::printLine(getMethodName() + "(): " + minitScript->getSubStatementInformation(subStatement) + ": argument mismatch: expected arguments: " + minitScript->getArgumentsInformation(getMethodName()));
					minitScript->startErrorScript();
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
			LogicMinitScript* minitScript { nullptr };
		public:
			MethodBodyAddForce(LogicMinitScript* minitScript):
				Method(
					{
						{ .type = VariableType::TYPE_STRING, .name = "bodyId", .optional = false, .reference = false, .nullable = false },
						{ .type = TYPE_VECTOR3, .name = "force", .optional = false, .reference = false, .nullable = false },
						{ .type = TYPE_VECTOR3, .name = "origin", .optional = true, .reference = false, .nullable = false }
					},
					VariableType::TYPE_NULL
				),
				minitScript(minitScript) {}
			const string getMethodName() override {
				return "world.body.addForce";
			}
			void executeMethod(span<Variable>& arguments, Variable& returnValue, const SubStatement& subStatement) override {
				string bodyId;
				Vector3 force;
				Vector3 forceOrigin;
				if (minitScript->getStringValue(arguments, 0, bodyId) == true &&
					minitScript->getVector3Value(arguments, 1, force) == true &&
					minitScript->getVector3Value(arguments, 2, forceOrigin, true) == true) {
					auto body = minitScript->context->getWorld()->getBody(bodyId);
					if (body != nullptr) {
						if (arguments.size() == 2) {
							body->addForce(force);
						} else
						if (arguments.size() == 3) {
							body->addForce(forceOrigin, force);
						} else {
							Console::printLine(getMethodName() + "(): " + minitScript->getSubStatementInformation(subStatement) + ": argument mismatch: expected arguments: " + minitScript->getArgumentsInformation(getMethodName()));
							minitScript->startErrorScript();
						}
					} else {
						Console::printLine(getMethodName() + "(): " + minitScript->getSubStatementInformation(subStatement) + ": body not found: " + bodyId);
					}
				} else {
					Console::printLine(getMethodName() + "(): " + minitScript->getSubStatementInformation(subStatement) + ": argument mismatch: expected arguments: " + minitScript->getArgumentsInformation(getMethodName()));
					minitScript->startErrorScript();
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
			LogicMinitScript* minitScript { nullptr };
		public:
			MethodBodyAddTorque(LogicMinitScript* minitScript):
				Method(
					{
						{ .type = VariableType::TYPE_STRING, .name = "bodyId", .optional = false, .reference = false, .nullable = false },
						{ .type = TYPE_VECTOR3, .name = "torque", .optional = false, .reference = false, .nullable = false }
					},
					VariableType::TYPE_NULL
				),
				minitScript(minitScript) {}
			const string getMethodName() override {
				return "world.body.addTorque";
			}
			void executeMethod(span<Variable>& arguments, Variable& returnValue, const SubStatement& subStatement) override {
				string bodyId;
				Vector3 torque;
				if (minitScript->getStringValue(arguments, 0, bodyId) == true &&
					minitScript->getVector3Value(arguments, 1, torque) == true) {
					auto body = minitScript->context->getWorld()->getBody(bodyId);
					if (body != nullptr) {
						body->addTorque(torque);
					} else {
						Console::printLine(getMethodName() + "(): " + minitScript->getSubStatementInformation(subStatement) + ": body not found: " + bodyId);
					}
				} else {
					Console::printLine(getMethodName() + "(): " + minitScript->getSubStatementInformation(subStatement) + ": argument mismatch: expected arguments: " + minitScript->getArgumentsInformation(getMethodName()));
					minitScript->startErrorScript();
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
			LogicMinitScript* minitScript { nullptr };
		public:
			MethodBodyGetTransform(LogicMinitScript* minitScript):
				Method(
					{
						{ .type = VariableType::TYPE_STRING, .name = "bodyId", .optional = false, .reference = false, .nullable = false }
					},
					TYPE_TRANSFORM
				),
				minitScript(minitScript) {}
			const string getMethodName() override {
				return "world.body.getTransform";
			}
			void executeMethod(span<Variable>& arguments, Variable& returnValue, const SubStatement& subStatement) override {
				string bodyId;
				if (minitScript->getStringValue(arguments, 0, bodyId) == true) {
					auto body = minitScript->context->getWorld()->getBody(bodyId);
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
						minitScript->setValue(returnValue, transform);
					} else {
						Console::printLine(getMethodName() + "(): " + minitScript->getSubStatementInformation(subStatement) + ": body not found: " + bodyId);
					}
				} else {
					Console::printLine(getMethodName() + "(): " + minitScript->getSubStatementInformation(subStatement) + ": argument mismatch: expected arguments: " + minitScript->getArgumentsInformation(getMethodName()));
					minitScript->startErrorScript();
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
			LogicMinitScript* minitScript { nullptr };
		public:
			MethodBodySetTransform(LogicMinitScript* minitScript):
				Method(
					{
						{ .type = VariableType::TYPE_STRING, .name = "bodyId", .optional = false, .reference = false, .nullable = false },
						{ .type = TYPE_TRANSFORM, .name = "transform", .optional = false, .reference = false, .nullable = false }
					},
					VariableType::TYPE_NULL
				),
				minitScript(minitScript) {}
			const string getMethodName() override {
				return "world.body.setTransform";
			}
			void executeMethod(span<Variable>& arguments, Variable& returnValue, const SubStatement& subStatement) override {
				string bodyId;
				Transform transform;
				if (minitScript->getStringValue(arguments, 0, bodyId) == true &&
					minitScript->getTransformValue(arguments, 1, transform) == true) {
					auto body = minitScript->context->getWorld()->getBody(bodyId);
					if (body != nullptr) {
						body->setTransform(transform);
					} else {
						Console::printLine(getMethodName() + "(): " + minitScript->getSubStatementInformation(subStatement) + ": body not found: " + bodyId);
					}
				} else {
					Console::printLine(getMethodName() + "(): " + minitScript->getSubStatementInformation(subStatement) + ": argument mismatch: expected arguments: " + minitScript->getArgumentsInformation(getMethodName()));
					minitScript->startErrorScript();
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
			LogicMinitScript* minitScript { nullptr };
		public:
			MethodWorldDetermineHeight(LogicMinitScript* minitScript):
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
				minitScript(minitScript) {}
			const string getMethodName() override {
				return "world.determineHeight";
			}
			void executeMethod(span<Variable>& arguments, Variable& returnValue, const SubStatement& subStatement) override {
				int64_t collisionTypeIds;
				float stepUpMax;
				Vector3 point;
				Vector3 heightPoint;
				float minHeight = -10000.0f;
				float maxHeight = 10000.0f;
				if (minitScript->getIntegerValue(arguments, 0, collisionTypeIds) == true &&
					minitScript->getFloatValue(arguments, 1, stepUpMax) == true &&
					minitScript->getVector3Value(arguments, 2, point) == true &&
					minitScript->getVector3Value(arguments, 3, heightPoint) == true &&
					minitScript->getFloatValue(arguments, 5, minHeight, true) == true &&
					minitScript->getFloatValue(arguments, 6, maxHeight, true) == true) {
					auto body = minitScript->context->getWorld()->determineHeight(collisionTypeIds, stepUpMax, point, heightPoint, minHeight, maxHeight);
					if (body != nullptr) {
						minitScript->setValue(arguments[3], heightPoint);
						if (arguments.size() >= 5) arguments[4].setValue(body->getId());
						minitScript->setValue(returnValue, true);
					} else {
						minitScript->setValue(returnValue, false);
					}
				} else {
					Console::printLine(getMethodName() + "(): " + minitScript->getSubStatementInformation(subStatement) + ": argument mismatch: expected arguments: " + minitScript->getArgumentsInformation(getMethodName()));
					minitScript->startErrorScript();
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
			LogicMinitScript* minitScript { nullptr };
		public:
			MethodWorldDoRayCasting(LogicMinitScript* minitScript):
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
				minitScript(minitScript) {}
			const string getMethodName() override {
				return "world.doRayCasting";
			}
			void executeMethod(span<Variable>& arguments, Variable& returnValue, const SubStatement& subStatement) override {
				int64_t collisionTypeIds;
				Vector3 start;
				Vector3 end;
				Vector3 hitPoint;
				string actorId;
				if (minitScript->getIntegerValue(arguments, 0, collisionTypeIds) == true &&
					minitScript->getVector3Value(arguments, 1, start) == true &&
					minitScript->getVector3Value(arguments, 2, end) == true &&
					minitScript->getStringValue(arguments, 5, actorId, true) == true) {
					auto body = minitScript->context->getWorld()->doRayCasting(collisionTypeIds, start, end, hitPoint, actorId);
					if (body != nullptr) {
						minitScript->setValue(arguments[3], hitPoint);
						if (arguments.size() >= 5) arguments[4].setValue(body->getId());
						minitScript->setValue(returnValue, true);
					} else {
						minitScript->setValue(returnValue, false);
					}
				} else {
					Console::printLine(getMethodName() + "(): " + minitScript->getSubStatementInformation(subStatement) + ": argument mismatch: expected arguments: " + minitScript->getArgumentsInformation(getMethodName()));
					minitScript->startErrorScript();
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
			LogicMinitScript* minitScript { nullptr };
		public:
			MethodWorldDoCollide(LogicMinitScript* minitScript):
				Method(
					{
						{ .type = VariableType::TYPE_STRING, .name = "bodyId1", .optional = false, .reference = false, .nullable = false },
						{ .type = VariableType::TYPE_STRING, .name = "bodyId2", .optional = false, .reference = false, .nullable = false }
					},
					VariableType::TYPE_BOOLEAN
				),
				minitScript(minitScript) {}
			const string getMethodName() override {
				return "world.doCollide";
			}
			void executeMethod(span<Variable>& arguments, Variable& returnValue, const SubStatement& subStatement) override {
				string bodyId1;
				string bodyId2;
				if (minitScript->getStringValue(arguments, 0, bodyId1) == true &&
					minitScript->getStringValue(arguments, 1, bodyId2) == true) {
					auto body1 = minitScript->context->getWorld()->getBody(bodyId1);
					auto body2 = minitScript->context->getWorld()->getBody(bodyId2);
					if (body1 == nullptr) {
						Console::printLine(getMethodName() + "(): " + minitScript->getSubStatementInformation(subStatement) + ": body1 not found: " + bodyId1);
					} else
					if (body2 == nullptr) {
						Console::printLine(getMethodName() + "(): " + minitScript->getSubStatementInformation(subStatement) + ": body2 not found: " + bodyId2);
					} else {
						minitScript->setValue(returnValue, minitScript->context->getWorld()->doCollide(body1, body2));
					}
				} else {
					Console::printLine(getMethodName() + "(): " + minitScript->getSubStatementInformation(subStatement) + ": argument mismatch: expected arguments: " + minitScript->getArgumentsInformation(getMethodName()));
					minitScript->startErrorScript();
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
			LogicMinitScript* minitScript { nullptr };
		public:
			MethodWorldDoesCollideWith(LogicMinitScript* minitScript):
				Method(
					{
						{ .type = VariableType::TYPE_INTEGER, .name = "collisionTypeIds", .optional = false, .reference = false, .nullable = false },
						{ .type = VariableType::TYPE_STRING, .name = "bodyId", .optional = false, .reference = false, .nullable = false }
					},
					VariableType::TYPE_ARRAY
				),
				minitScript(minitScript) {}
			const string getMethodName() override {
				return "world.doesCollideWith";
			}
			void executeMethod(span<Variable>& arguments, Variable& returnValue, const SubStatement& subStatement) override {
				int64_t collisionTypeIds;
				string bodyId;
				if (minitScript->getIntegerValue(arguments, 0, collisionTypeIds) == true &&
					minitScript->getStringValue(arguments, 1, bodyId) == true) {
					auto body = minitScript->context->getWorld()->getBody(bodyId);
					if (body == nullptr) {
						Console::printLine(getMethodName() + "(): " + minitScript->getSubStatementInformation(subStatement) + ": body not found: " + bodyId);
					} else {
						vector<Body*> collisionBodies;
						minitScript->context->getWorld()->doesCollideWith(collisionTypeIds, body, collisionBodies);
						returnValue.setType(EngineMinitScript::TYPE_ARRAY);
						for (auto collisionBody: collisionBodies) {
							returnValue.pushArrayEntry(collisionBody->getId());
						}
					}
				} else {
					Console::printLine(getMethodName() + "(): " + minitScript->getSubStatementInformation(subStatement) + ": argument mismatch: expected arguments: " + minitScript->getArgumentsInformation(getMethodName()));
					minitScript->startErrorScript();
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
			LogicMinitScript* minitScript { nullptr };
		public:
			MethodPathFindingSTATE_IDLE(LogicMinitScript* minitScript):
				Method({}, VariableType::TYPE_INTEGER),
				minitScript(minitScript) {}
			const string getMethodName() override {
				return "pathfinding.STATE_IDLE";
			}
			void executeMethod(span<Variable>& arguments, Variable& returnValue, const SubStatement& subStatement) override {
				minitScript->setValue(returnValue, static_cast<int64_t>(Context::PathFindingThread::STATE_IDLE));
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
			LogicMinitScript* minitScript { nullptr };
		public:
			MethodPathFindingSTATE_TRYLOCK_FAILED(LogicMinitScript* minitScript):
				Method({}, VariableType::TYPE_INTEGER),
				minitScript(minitScript) {}
			const string getMethodName() override {
				return "pathfinding.STATE_TRYLOCK_FAILED";
			}
			void executeMethod(span<Variable>& arguments, Variable& returnValue, const SubStatement& subStatement) override {
				minitScript->setValue(returnValue, static_cast<int64_t>(Context::PathFindingThread::STATE_TRYLOCK_FAILED));
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
			LogicMinitScript* minitScript { nullptr };
		public:
			MethodPathFindingSTATE_PATHFINDING_OTHER(LogicMinitScript* minitScript):
				Method({}, VariableType::TYPE_INTEGER),
				minitScript(minitScript) {}
			const string getMethodName() override {
				return "pathfinding.STATE_PATHFINDING_OTHER";
			}
			void executeMethod(span<Variable>& arguments, Variable& returnValue, const SubStatement& subStatement) override {
				minitScript->setValue(returnValue, static_cast<int64_t>(Context::PathFindingThread::STATE_PATHFINDING_OTHER));
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
			LogicMinitScript* minitScript { nullptr };
		public:
			MethodPathFindingSTATE_PATHFINDING(LogicMinitScript* minitScript):
				Method({}, VariableType::TYPE_INTEGER),
				minitScript(minitScript) {}
			const string getMethodName() override {
				return "pathfinding.STATE_PATHFINDING";
			}
			void executeMethod(span<Variable>& arguments, Variable& returnValue, const SubStatement& subStatement) override {
				minitScript->setValue(returnValue, static_cast<int64_t>(Context::PathFindingThread::STATE_PATHFINDING));
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
			LogicMinitScript* minitScript { nullptr };
		public:
			MethodPathFindingSTATE_PATHFINDING_FAILED(LogicMinitScript* minitScript):
				Method({}, VariableType::TYPE_INTEGER),
				minitScript(minitScript) {}
			const string getMethodName() override {
				return "pathfinding.STATE_PATHFINDING_FAILED";
			}
			void executeMethod(span<Variable>& arguments, Variable& returnValue, const SubStatement& subStatement) override {
				minitScript->setValue(returnValue, static_cast<int64_t>(Context::PathFindingThread::STATE_PATHFINDING_FAILED));
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
			LogicMinitScript* minitScript { nullptr };
		public:
			MethodPathFindingSTATE_PATHFINDING_SUCCESS(LogicMinitScript* minitScript):
				Method({}, VariableType::TYPE_INTEGER),
				minitScript(minitScript) {}
			const string getMethodName() override {
				return "pathfinding.STATE_PATHFINDING_SUCCESS";
			}
			void executeMethod(span<Variable>& arguments, Variable& returnValue, const SubStatement& subStatement) override {
				minitScript->setValue(returnValue, static_cast<int64_t>(Context::PathFindingThread::STATE_PATHFINDING_SUCCESS));
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
			LogicMinitScript* minitScript { nullptr };
		public:
			MethodPathFindingFindPath(LogicMinitScript* minitScript):
				Method(
					{
						{ .type = VariableType::TYPE_STRING, .name = "logicId", .optional = false, .reference = false, .nullable = false },
						{ .type = TYPE_VECTOR3, .name = "startPosition", .optional = false, .reference = false, .nullable = false },
						{ .type = TYPE_VECTOR3, .name = "endPosition", .optional = false, .reference = false, .nullable = false },
						{ .type = VariableType::TYPE_ARRAY, .name = "path", .optional = false, .reference = true, .nullable = false },
					},
					VariableType::TYPE_INTEGER
				),
				minitScript(minitScript) {}
			const string getMethodName() override {
				return "pathfinding.findPath";
			}
			void executeMethod(span<Variable>& arguments, Variable& returnValue, const SubStatement& subStatement) override {
				string logicId;
				Vector3 startPosition;
				Vector3 endPosition;
				if (arguments.size() == 4 &&
					minitScript->getStringValue(arguments, 0, logicId) == true &&
					minitScript->getVector3Value(arguments, 1, startPosition) == true &&
					minitScript->getVector3Value(arguments, 2, endPosition) == true) {
					arguments[3].setType(EngineMinitScript::TYPE_ARRAY);
					vector<Vector3> path;
					auto pathFindingState = minitScript->context->getPathFinding()->findPath(logicId, logicId, startPosition, endPosition, path);
					minitScript->setValue(returnValue, static_cast<int64_t>(pathFindingState));
					for (const auto& position: path) {
						MinitScript::Variable positionVariable;
						minitScript->setValue(positionVariable, position);
						arguments[3].pushArrayEntry(positionVariable);
					};
				} else {
					Console::printLine(getMethodName() + "(): " + minitScript->getSubStatementInformation(subStatement) + ": argument mismatch: expected arguments: " + minitScript->getArgumentsInformation(getMethodName()));
					minitScript->startErrorScript();
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
			LogicMinitScript* minitScript { nullptr };
		public:
			MethodSceneGetWidth(LogicMinitScript* minitScript):
				Method({}, VariableType::TYPE_FLOAT),
				minitScript(minitScript) {}
			const string getMethodName() override {
				return "scene.getWidth";
			}
			void executeMethod(span<Variable>& arguments, Variable& returnValue, const SubStatement& subStatement) override {
				minitScript->setValue(returnValue, minitScript->context->getScene()->getBoundingBox()->getDimensions().getX());
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
			LogicMinitScript* minitScript { nullptr };
		public:
			MethodSceneGetHeight(LogicMinitScript* minitScript):
				Method({}, VariableType::TYPE_FLOAT),
				minitScript(minitScript) {}
			const string getMethodName() override {
				return "scene.getHeight";
			}
			void executeMethod(span<Variable>& arguments, Variable& returnValue, const SubStatement& subStatement) override {
				minitScript->setValue(returnValue, minitScript->context->getScene()->getBoundingBox()->getDimensions().getY());
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
			LogicMinitScript* minitScript { nullptr };
		public:
			MethodSceneGetDepth(LogicMinitScript* minitScript):
				Method({}, VariableType::TYPE_FLOAT),
				minitScript(minitScript) {}
			const string getMethodName() override {
				return "scene.getDepth";
			}
			void executeMethod(span<Variable>& arguments, Variable& returnValue, const SubStatement& subStatement) override {
				minitScript->setValue(returnValue, minitScript->context->getScene()->getBoundingBox()->getDimensions().getZ());
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
			LogicMinitScript* minitScript { nullptr };
		public:
			MethodSceneConnectorSpawnPrototype(LogicMinitScript* minitScript):
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
				minitScript(minitScript) {}
			const string getMethodName() override {
				return "sceneconnector.spawnPrototype";
			}
			void executeMethod(span<Variable>& arguments, Variable& returnValue, const SubStatement& subStatement) override {
				string pathName;
				string fileName;
				string id;
				Transform transform;
				string hierarchyId;
				string hierarchyParentId;
				if (minitScript->getStringValue(arguments, 0, pathName) == true &&
					minitScript->getStringValue(arguments, 1, fileName) == true &&
					minitScript->getStringValue(arguments, 2, id) == true &&
					minitScript->getTransformValue(arguments, 3, transform) == true &&
					minitScript->getStringValue(arguments, 4, hierarchyId, true) == true &&
					minitScript->getStringValue(arguments, 5, hierarchyParentId, true) == true) {
					minitScript->prototypesToAddMutex.lock();
					try {
						auto _pathName = pathName;
						if (minitScript->context->getApplicationRootPathName().empty() == false) {
							_pathName = FileSystem::getInstance()->getCanonicalURI(minitScript->context->getApplicationRootPathName(), pathName);
						}
						Prototype* prototype = nullptr;
						auto canonicalPath = FileSystem::getInstance()->getCanonicalURI(_pathName, fileName);
						auto prototypeIt = minitScript->prototypes.find(canonicalPath);
						if (prototypeIt != minitScript->prototypes.end()) {
							prototypeIt->second.counter++;
							prototype = prototypeIt->second.prototype.get();
						} else {
							prototype = PrototypeReader::read(_pathName, fileName);
							minitScript->prototypes[canonicalPath] = {
								.counter = 1,
								.prototype = unique_ptr<Prototype>(prototype)
							};
						}
						minitScript->enginePrototypesToAdd.emplace_back(
							PrototypeToAdd::TYPE_SPAWN,
							prototype,
							id,
							string(),
							transform,
							hierarchyId,
							hierarchyParentId
						);
						minitScript->physicsPrototypesToAdd.emplace_back(
							PrototypeToAdd::TYPE_SPAWN,
							prototype,
							id,
							string(),
							transform,
							hierarchyId,
							hierarchyParentId
						);
					} catch (Exception& exception) {
						minitScript->prototypesToAddMutex.unlock();
						Console::printLine("MethodSceneConnectorSpawnPrototype::executeMethod(): An error occurred: " + string(exception.what()));
						minitScript->startErrorScript();
					}
					minitScript->prototypesToAddMutex.unlock();
				} else {
					Console::printLine(getMethodName() + "(): " + minitScript->getSubStatementInformation(subStatement) + ": argument mismatch: expected arguments: " + minitScript->getArgumentsInformation(getMethodName()));
					minitScript->startErrorScript();
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
			LogicMinitScript* minitScript { nullptr };
		public:
			MethodSceneConnectorAttachPrototype(LogicMinitScript* minitScript):
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
				minitScript(minitScript) {}
			const string getMethodName() override {
				return "sceneconnector.attachPrototype";
			}
			void executeMethod(span<Variable>& arguments, Variable& returnValue, const SubStatement& subStatement) override {
				string pathName;
				string fileName;
				string id;
				string attachNodeId;
				Transform transform;
				string hierarchyParentId;
				if (minitScript->getStringValue(arguments, 0, pathName) == true &&
					minitScript->getStringValue(arguments, 1, fileName) == true &&
					minitScript->getStringValue(arguments, 2, id) == true &&
					minitScript->getStringValue(arguments, 3, attachNodeId) == true &&
					minitScript->getTransformValue(arguments, 4, transform) == true &&
					minitScript->getStringValue(arguments, 5, hierarchyParentId, true) == true) {
					minitScript->prototypesToAddMutex.lock();
					try {
						auto _pathName = pathName;
						if (minitScript->context->getApplicationRootPathName().empty() == false) {
							_pathName = FileSystem::getInstance()->getCanonicalURI(minitScript->context->getApplicationRootPathName(), pathName);
						}
						Prototype* prototype = nullptr;
						auto canonicalPath = FileSystem::getInstance()->getCanonicalURI(_pathName, fileName);
						auto prototypeIt = minitScript->prototypes.find(canonicalPath);
						if (prototypeIt != minitScript->prototypes.end()) {
							prototypeIt->second.counter++;
							prototype = prototypeIt->second.prototype.get();
						} else {
							prototype = PrototypeReader::read(_pathName, fileName);
							minitScript->prototypes[canonicalPath] = {
								.counter = 1,
								.prototype = unique_ptr<Prototype>(prototype)
							};
						}
						minitScript->enginePrototypesToAdd.emplace_back(
							PrototypeToAdd::TYPE_ATTACH,
							prototype,
							id,
							attachNodeId,
							transform,
							minitScript->logic->getId(),
							hierarchyParentId
						);
						minitScript->physicsPrototypesToAdd.emplace_back(
							PrototypeToAdd::TYPE_ATTACH,
							prototype,
							id,
							attachNodeId,
							transform,
							minitScript->logic->getId(),
							hierarchyParentId
						);
					} catch (Exception& exception) {
						minitScript->prototypesToAddMutex.unlock();
						Console::printLine("MethodSceneConnectorAttachPrototype::executeMethod(): An error occurred: " + string(exception.what()));
						minitScript->startErrorScript();
					}
					minitScript->prototypesToAddMutex.unlock();
				} else {
					Console::printLine(getMethodName() + "(): " + minitScript->getSubStatementInformation(subStatement) + ": argument mismatch: expected arguments: " + minitScript->getArgumentsInformation(getMethodName()));
					minitScript->startErrorScript();
				}
			}
			const vector<string>& getContextFunctions() {
				return CONTEXTFUNCTIONS_LOGIC;
			}
		};
		registerMethod(new MethodSceneConnectorAttachPrototype(this));
	}
}

void LogicMinitScript::registerVariables() {
}

void LogicMinitScript::collectHIDEvents(vector<GUIMouseEvent>& mouseEvents, vector<GUIKeyboardEvent>& keyEvents) {
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
