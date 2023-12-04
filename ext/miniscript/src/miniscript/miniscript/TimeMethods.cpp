#include <span>

#include <miniscript/miniscript.h>
#include <miniscript/miniscript/MiniScript.h>
#include <miniscript/miniscript/TimeMethods.h>
#include <miniscript/utilities/Console.h>
#include <miniscript/utilities/Time.h>

using std::span;

using miniscript::miniscript::TimeMethods;

using miniscript::miniscript::MiniScript;
using miniscript::utilities::Console;
using miniscript::utilities::Time;

void TimeMethods::registerMethods(MiniScript* miniScript) {
	// time
	{
		//
		class ScriptMethodTimeGetCurrentMillis: public MiniScript::ScriptMethod {
		private:
			MiniScript* miniScript { nullptr };
		public:
			ScriptMethodTimeGetCurrentMillis(MiniScript* miniScript):
				MiniScript::ScriptMethod({}, MiniScript::TYPE_INTEGER),
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
						{ .type = MiniScript::TYPE_STRING, .name = "format", .optional = true, .reference = false, .nullable = false }
					},
					MiniScript::TYPE_STRING
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
