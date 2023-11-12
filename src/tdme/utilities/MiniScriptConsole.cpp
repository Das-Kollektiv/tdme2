#include <span>

#include <tdme/tdme.h>
#include <tdme/utilities/Console.h>
#include <tdme/utilities/MiniScript.h>
#include <tdme/utilities/MiniScriptConsole.h>

using std::span;

using tdme::utilities::MiniScriptConsole;

using tdme::utilities::MiniScript;
using tdme::utilities::Console;

void MiniScriptConsole::registerMethods(MiniScript* miniScript) {
	// console
	{
		//
		class ScriptMethodConsoleLog: public MiniScript::ScriptMethod {
		private:
			MiniScript* miniScript { nullptr };
		public:
			ScriptMethodConsoleLog(MiniScript* miniScript): MiniScript::ScriptMethod(), miniScript(miniScript) {}
			const string getMethodName() override {
				return "console.log";
			}
			void executeMethod(span<MiniScript::ScriptVariable>& argumentValues, MiniScript::ScriptVariable& returnValue, const MiniScript::ScriptStatement& statement) override {
				for (const auto& argumentValue: argumentValues) {
					Console::print(argumentValue.getValueAsString());
				}
				Console::println();
			}
			bool isVariadic() const override {
				return true;
			}
		};
		miniScript->registerMethod(new ScriptMethodConsoleLog(miniScript));
	}
	{
		//
		class ScriptMethodConsoleDump: public MiniScript::ScriptMethod {
		private:
			MiniScript* miniScript { nullptr };
		public:
			ScriptMethodConsoleDump(MiniScript* miniScript):
				MiniScript::ScriptMethod(
					{
						{ .type = MiniScript::TYPE_PSEUDO_MIXED, .name = "value", .optional = false, .reference = false, .nullable = false }
					}
				),
				miniScript(miniScript) {}
			const string getMethodName() override {
				return "console.dump";
			}
			void executeMethod(span<MiniScript::ScriptVariable>& argumentValues, MiniScript::ScriptVariable& returnValue, const MiniScript::ScriptStatement& statement) override {
				if (argumentValues.size() != 1) {
					Console::println(getMethodName() + "(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation(getMethodName()));
					miniScript->startErrorScript();
				} else {
					Console::println(argumentValues[0].getValueAsString(true));
				}
			}
		};
		miniScript->registerMethod(new ScriptMethodConsoleDump(miniScript));
	}
}
