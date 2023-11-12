#include <span>

#include <tdme/tdme.h>
#include <tdme/gui/GUIParser.h>
#include <tdme/utilities/MiniScript.h>
#include <tdme/utilities/MiniScriptTime.h>
#include <tdme/utilities/Time.h>

using std::span;

using tdme::utilities::MiniScriptTime;

using tdme::gui::GUIParser;
using tdme::utilities::MiniScript;
using tdme::utilities::Time;

void MiniScriptTime::registerMethods(MiniScript* miniScript) {
	// time
	{
		//
		class ScriptMethodTimeGetCurrentMillis: public MiniScript::ScriptMethod {
		private:
			MiniScript* miniScript { nullptr };
		public:
			ScriptMethodTimeGetCurrentMillis(MiniScript* miniScript):
				MiniScript::ScriptMethod({}, MiniScript::ScriptVariableType::TYPE_INTEGER),
				miniScript(miniScript) {}
			const string getMethodName() override {
				return "time.getCurrentMillis";
			}
			void executeMethod(span<MiniScript::ScriptVariable>& argumentValues, MiniScript::ScriptVariable& returnValue, const MiniScript::ScriptStatement& statement) override {
				returnValue.setValue(Time::getCurrentMillis());
			}
		};
		miniScript->registerMethod(new ScriptMethodTimeGetCurrentMillis(miniScript));
	}
	{
		//
		class ScriptMethodTimeGetAsString: public MiniScript::ScriptMethod {
		private:
			MiniScript* miniScript { nullptr };
		public:
			ScriptMethodTimeGetAsString(MiniScript* miniScript):
				MiniScript::ScriptMethod(
					{
						{ .type = MiniScript::ScriptVariableType::TYPE_STRING, .name = "format", .optional = true, .reference = false, .nullable = false }
					},
					MiniScript::ScriptVariableType::TYPE_STRING
				),
				miniScript(miniScript) {}
			const string getMethodName() override {
				return "time.getAsString";
			}
			void executeMethod(span<MiniScript::ScriptVariable>& argumentValues, MiniScript::ScriptVariable& returnValue, const MiniScript::ScriptStatement& statement) override {
				string format = "%Y-%m-%d %H:%M:%S";
				if (MiniScript::getStringValue(argumentValues, 0, format, true) == false) {
					Console::println(getMethodName() + "(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation(getMethodName()));
					miniScript->startErrorScript();
				} else {
					returnValue.setValue(Time::getAsString(format));
				}
			}
		};
		miniScript->registerMethod(new ScriptMethodTimeGetAsString(miniScript));
	}
}
