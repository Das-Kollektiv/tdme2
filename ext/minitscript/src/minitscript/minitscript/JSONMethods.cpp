#include <span>

#include <minitscript/minitscript.h>
#include <minitscript/minitscript/JSONMethods.h>
#include <minitscript/minitscript/MinitScript.h>
#include <minitscript/utilities/Console.h>
#include <minitscript/utilities/StringTools.h>

using std::span;

using minitscript::minitscript::JSONMethods;

using minitscript::minitscript::MinitScript;

using _Console = minitscript::utilities::Console;
using _StringTools = minitscript::utilities::StringTools;

void JSONMethods::registerConstants(MinitScript* minitScript) {
}

void JSONMethods::registerMethods(MinitScript* minitScript) {
	// json
	{
		//
		class MethodJSONSerialize: public MinitScript::Method {
		private:
			MinitScript* minitScript { nullptr };
		public:
			MethodJSONSerialize(MinitScript* minitScript):
				MinitScript::Method(
					{
						{ .type = MinitScript::TYPE_PSEUDO_MIXED, .name = "value", .optional = false, .reference = false, .nullable = false },
					},
					MinitScript::TYPE_STRING
				),
				minitScript(minitScript) {}
			const string getMethodName() override {
				return "json.serialize";
			}
			void executeMethod(span<MinitScript::Variable>& arguments, MinitScript::Variable& returnValue, const MinitScript::SubStatement& subStatement) override {
				if (arguments.size() == 1) {
					returnValue.setValue(arguments[0].getValueAsString(false, true));
				} else {
					MINITSCRIPT_METHODUSAGE_COMPLAIN(getMethodName());
				}
			}
		};
		minitScript->registerMethod(new MethodJSONSerialize(minitScript));
	}
	{
		//
		class MethodJSONDeserialize: public MinitScript::Method {
		private:
			MinitScript* minitScript { nullptr };
		public:
			MethodJSONDeserialize(MinitScript* minitScript):
				MinitScript::Method(
					{
						{ .type = MinitScript::TYPE_STRING, .name = "json", .optional = false, .reference = false, .nullable = false },
					},
					MinitScript::TYPE_PSEUDO_MIXED
				),
				minitScript(minitScript) {}
			const string getMethodName() override {
				return "json.deserialize";
			}
			void executeMethod(span<MinitScript::Variable>& arguments, MinitScript::Variable& returnValue, const MinitScript::SubStatement& subStatement) override {
				string json;
				if (arguments.size() == 1 &&
					MinitScript::getStringValue(arguments, 0, json) == true) {
					json = _StringTools::trim(json);
					if (_StringTools::startsWith(json, "{") == true) {
						returnValue.setValue(MinitScript::initializeMapSet("json.deserialize", json, minitScript, MinitScript::SCRIPTIDX_NONE, *subStatement.statement));
					} else
					if (_StringTools::startsWith(json, "[") == true) {
						returnValue.setValue(MinitScript::initializeArray("json.deserialize", json, minitScript, MinitScript::SCRIPTIDX_NONE, *subStatement.statement));
					} else {
						minitScript->complain(getMethodName(), subStatement, "JSON string not valid");
					}
				} else {
					MINITSCRIPT_METHODUSAGE_COMPLAIN(getMethodName());
				}
			}
		};
		minitScript->registerMethod(new MethodJSONDeserialize(minitScript));
	}
}
