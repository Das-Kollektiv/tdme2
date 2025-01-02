#include <span>

#include <minitscript/minitscript.h>
#include <minitscript/minitscript/MinitScript.h>
#include <minitscript/minitscript/TimeMethods.h>
#include <minitscript/utilities/Console.h>
#include <minitscript/utilities/Time.h>

using std::span;

using minitscript::minitscript::TimeMethods;

using minitscript::minitscript::MinitScript;

using _Console = minitscript::utilities::Console;
using _Time = minitscript::utilities::Time;

void TimeMethods::registerConstants(MinitScript* minitScript) {
}

void TimeMethods::registerMethods(MinitScript* minitScript) {
	// time
	{
		//
		class MethodTimeGetCurrentMillis: public MinitScript::Method {
		private:
			MinitScript* minitScript { nullptr };
		public:
			MethodTimeGetCurrentMillis(MinitScript* minitScript):
				MinitScript::Method({}, MinitScript::TYPE_INTEGER),
				minitScript(minitScript) {}
			const string getMethodName() override {
				return "time.getCurrentMillis";
			}
			void executeMethod(span<MinitScript::Variable>& arguments, MinitScript::Variable& returnValue, const MinitScript::SubStatement& subStatement) override {
				if (arguments.size() == 0) {
					returnValue.setValue(_Time::getCurrentMillis());
				} else {
					MINITSCRIPT_METHODUSAGE_COMPLAIN(getMethodName());
				}
			}
		};
		minitScript->registerMethod(new MethodTimeGetCurrentMillis(minitScript));
	}
	{
		//
		class MethodTimeGetAsString: public MinitScript::Method {
		private:
			MinitScript* minitScript { nullptr };
		public:
			MethodTimeGetAsString(MinitScript* minitScript):
				MinitScript::Method(
					{
						{ .type = MinitScript::TYPE_STRING, .name = "format", .optional = true, .reference = false, .nullable = false }
					},
					MinitScript::TYPE_STRING
				),
				minitScript(minitScript) {}
			const string getMethodName() override {
				return "time.getAsString";
			}
			void executeMethod(span<MinitScript::Variable>& arguments, MinitScript::Variable& returnValue, const MinitScript::SubStatement& subStatement) override {
				string format = "%Y-%m-%d %H:%M:%S";
				if ((arguments.size() == 0 || arguments.size() == 1) &&
					MinitScript::getStringValue(arguments, 0, format, true) == true) {
					returnValue.setValue(_Time::getAsString(format));
				} else {
					MINITSCRIPT_METHODUSAGE_COMPLAIN(getMethodName());
				}
			}
		};
		minitScript->registerMethod(new MethodTimeGetAsString(minitScript));
	}
}
