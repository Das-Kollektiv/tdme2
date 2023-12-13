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
		class MethodTimeGetCurrentMillis: public MiniScript::Method {
		private:
			MiniScript* miniScript { nullptr };
		public:
			MethodTimeGetCurrentMillis(MiniScript* miniScript):
				MiniScript::Method({}, MiniScript::TYPE_INTEGER),
				miniScript(miniScript) {}
			const string getMethodName() override {
				return "time.getCurrentMillis";
			}
			void executeMethod(span<MiniScript::Variable>& arguments, MiniScript::Variable& returnValue, const MiniScript::Statement& statement) override {
				returnValue.setValue(Time::getCurrentMillis());
			}
		};
		miniScript->registerMethod(new MethodTimeGetCurrentMillis(miniScript));
	}
	{
		//
		class MethodTimeGetAsString: public MiniScript::Method {
		private:
			MiniScript* miniScript { nullptr };
		public:
			MethodTimeGetAsString(MiniScript* miniScript):
				MiniScript::Method(
					{
						{ .type = MiniScript::TYPE_STRING, .name = "format", .optional = true, .reference = false, .nullable = false }
					},
					MiniScript::TYPE_STRING
				),
				miniScript(miniScript) {}
			const string getMethodName() override {
				return "time.getAsString";
			}
			void executeMethod(span<MiniScript::Variable>& arguments, MiniScript::Variable& returnValue, const MiniScript::Statement& statement) override {
				string format = "%Y-%m-%d %H:%M:%S";
				if (MiniScript::getStringValue(arguments, 0, format, true) == false) {
					Console::println(getMethodName() + "(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation(getMethodName()));
					miniScript->startErrorScript();
				} else {
					returnValue.setValue(Time::getAsString(format));
				}
			}
		};
		miniScript->registerMethod(new MethodTimeGetAsString(miniScript));
	}
}
