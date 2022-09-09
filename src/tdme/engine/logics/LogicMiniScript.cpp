#include <tdme/engine/logics/LogicMiniScript.h>

#include <span>
#include <string>
#include <vector>

#include <tdme/tdme.h>
#include <tdme/engine/logics/Context.h>
#include <tdme/engine/logics/Logic.h>
#include <tdme/utilities/Console.h>
#include <tdme/utilities/MiniScript.h>

using std::span;
using std::string;
using std::to_string;
using std::vector;

using tdme::engine::logics::LogicMiniScript;

using tdme::engine::logics::Context;
using tdme::engine::logics::Logic;
using tdme::utilities::Console;
using tdme::utilities::MiniScript;

LogicMiniScript::LogicMiniScript(): MiniScript() {
}

LogicMiniScript::~LogicMiniScript() {
}


void LogicMiniScript::registerStateMachineStates() {
	MiniScript::registerStateMachineStates();
}

void LogicMiniScript::registerMethods() {
	MiniScript::registerMethods();
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
			void executeMethod(const span<ScriptVariable>& argumentValues, ScriptVariable& returnValue, const ScriptStatement& statement) override {
				returnValue.setValue(miniScript->logic->getId());
			}
		};
		registerMethod(new ScriptMethodLogicGetId(this));
	}
	{
		//
		class ScriptMethodLogicSignalSend: public ScriptMethod {
		private:
			LogicMiniScript* miniScript { nullptr };
		public:
			ScriptMethodLogicSignalSend(LogicMiniScript* miniScript):
				ScriptMethod({
					{ .type = ScriptVariableType::TYPE_STRING, .name = "logicId", .optional = false },
					{ .type = ScriptVariableType::TYPE_STRING, .name = "signal", .optional = false }
				}),
				miniScript(miniScript) {}
			const string getMethodName() override {
				return "logic.signal.send";
			}
			void executeMethod(const span<ScriptVariable>& argumentValues, ScriptVariable& returnValue, const ScriptStatement& statement) override {
				string logicId;
				string signal;
				if (miniScript->getStringValue(argumentValues, 0, logicId) == true &&
					miniScript->getStringValue(argumentValues, 1, signal) == true) {
					auto logic = static_cast<Logic*>(miniScript->context->getLogic(logicId));
					if (logic == nullptr) {
						Console::println("ScriptMethodLogicSignalSend::executeMethod(): " + getMethodName() + "(): no logic with given id: " + logicId);
						return;
					} else {
						vector<ScriptVariable> arguments(argumentValues.size() - 2);
						for (auto i = 2; i < argumentValues.size(); i++) arguments.push_back(argumentValues[i]);
						logic->addSignal(signal, arguments);
					}
				} else {
					Console::println("ScriptMethodLogicSignalSend::executeMethod(): " + getMethodName() + "(): parameter type mismatch @ argument 0: string expected, argument 1: string expected");
					miniScript->startErrorScript();
				}
			}
			bool isVariadic() override {
				return true;
			}
		};
		registerMethod(new ScriptMethodLogicSignalSend(this));
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
			void executeMethod(const span<ScriptVariable>& argumentValues, ScriptVariable& returnValue, const ScriptStatement& statement) override {
				returnValue.setValue(miniScript->logic->hasSignal());
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
			void executeMethod(const span<ScriptVariable>& argumentValues, ScriptVariable& returnValue, const ScriptStatement& statement) override {
				returnValue.setValue(miniScript->logic->getSignalName());
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
						{ .type = ScriptVariableType::TYPE_INTEGER, .name = "argumentIndex", .optional = false }
					},
					ScriptVariableType::TYPE_PSEUDO_MIXED
				),
				miniScript(miniScript) {}
			const string getMethodName() override {
				return "logic.signal.getArgument";
			}
			void executeMethod(const span<ScriptVariable>& argumentValues, ScriptVariable& returnValue, const ScriptStatement& statement) override {
				int64_t argumentIndex;
				if (miniScript->getIntegerValue(argumentValues, 0, argumentIndex) == true) {
					returnValue = miniScript->logic->getSignalArgument(argumentIndex);
				} else {
					Console::println("ScriptMethodLogicSignalGetArgument::executeMethod(): " + getMethodName() + "(): parameter type mismatch @ argument 0: integer expected");
					miniScript->startErrorScript();
				}
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
			void executeMethod(const span<ScriptVariable>& argumentValues, ScriptVariable& returnValue, const ScriptStatement& statement) override {
				miniScript->logic->removeSignal();
			}
		};
		registerMethod(new ScriptMethodLogicSignalNext(this));
	}
}

void LogicMiniScript::registerVariables() {
}


