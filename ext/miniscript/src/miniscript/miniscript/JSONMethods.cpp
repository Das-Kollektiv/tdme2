#include <span>

#include <miniscript/miniscript.h>
#include <miniscript/miniscript/JSONMethods.h>
#include <miniscript/miniscript/MiniScript.h>
#include <miniscript/utilities/Console.h>
#include <miniscript/utilities/StringTools.h>

using std::span;

using miniscript::miniscript::JSONMethods;

using miniscript::miniscript::MiniScript;
using miniscript::utilities::Console;
using miniscript::utilities::StringTools;

void JSONMethods::registerMethods(MiniScript* miniScript) {
	// json
	{
		//
		class ScriptMethodJSONSerialize: public MiniScript::ScriptMethod {
		private:
			MiniScript* miniScript { nullptr };
		public:
			ScriptMethodJSONSerialize(MiniScript* miniScript):
				MiniScript::ScriptMethod(
					{
						{ .type = MiniScript::TYPE_PSEUDO_MIXED, .name = "value", .optional = false, .reference = false, .nullable = false },
					},
					MiniScript::TYPE_STRING
				),
				miniScript(miniScript) {}
			const string getMethodName() override {
				return "json.serialize";
			}
			void executeMethod(span<MiniScript::ScriptVariable>& argumentValues, MiniScript::ScriptVariable& returnValue, const MiniScript::ScriptStatement& statement) override {
				//
				if (argumentValues.size() != 1) {
					Console::println(getMethodName() + "(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation(getMethodName()));
					miniScript->startErrorScript();
				} else {
					returnValue.setValue(argumentValues[0].getValueAsString(false, true));
				}
			}
		};
		miniScript->registerMethod(new ScriptMethodJSONSerialize(miniScript));
	}
	{
		//
		class ScriptMethodJSONDeserialize: public MiniScript::ScriptMethod {
		private:
			MiniScript* miniScript { nullptr };
		public:
			ScriptMethodJSONDeserialize(MiniScript* miniScript):
				MiniScript::ScriptMethod(
					{
						{ .type = MiniScript::TYPE_STRING, .name = "json", .optional = false, .reference = false, .nullable = false },
					},
					MiniScript::TYPE_PSEUDO_MIXED
				),
				miniScript(miniScript) {}
			const string getMethodName() override {
				return "json.deserialize";
			}
			void executeMethod(span<MiniScript::ScriptVariable>& argumentValues, MiniScript::ScriptVariable& returnValue, const MiniScript::ScriptStatement& statement) override {
				string json;
				if (MiniScript::getStringValue(argumentValues, 0, json, false) == false) {
					Console::println(getMethodName() + "(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation(getMethodName()));
					miniScript->startErrorScript();
				} else {
					json = StringTools::trim(json);
					if (StringTools::startsWith(json, "{") == true) {
						returnValue = MiniScript::initializeMapSet(json, miniScript, statement);
					} else
					if (StringTools::startsWith(json, "[") == true) {
						returnValue = MiniScript::initializeArray(json, miniScript, statement);
					} else {
						Console::println(getMethodName() + "(): " + miniScript->getStatementInformation(statement) + ": JSON string not valid");
					}
				}
			}
		};
		miniScript->registerMethod(new ScriptMethodJSONDeserialize(miniScript));
	}
}
