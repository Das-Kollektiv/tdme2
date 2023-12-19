#include <span>

#include <miniscript/miniscript.h>
#include <miniscript/miniscript/JSONMethods.h>
#include <miniscript/miniscript/MiniScript.h>
#include <miniscript/utilities/Console.h>
#include <miniscript/utilities/StringTools.h>

using std::span;

using miniscript::miniscript::JSONMethods;

using miniscript::miniscript::MiniScript;

using _Console = miniscript::utilities::Console;
using _StringTools = miniscript::utilities::StringTools;

void JSONMethods::registerMethods(MiniScript* miniScript) {
	// json
	{
		//
		class MethodJSONSerialize: public MiniScript::Method {
		private:
			MiniScript* miniScript { nullptr };
		public:
			MethodJSONSerialize(MiniScript* miniScript):
				MiniScript::Method(
					{
						{ .type = MiniScript::TYPE_PSEUDO_MIXED, .name = "value", .optional = false, .reference = false, .nullable = false },
					},
					MiniScript::TYPE_STRING
				),
				miniScript(miniScript) {}
			const string getMethodName() override {
				return "json.serialize";
			}
			void executeMethod(span<MiniScript::Variable>& arguments, MiniScript::Variable& returnValue, const MiniScript::Statement& statement) override {
				//
				if (arguments.size() != 1) {
					_Console::println(getMethodName() + "(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation(getMethodName()));
					miniScript->startErrorScript();
				} else {
					returnValue.setValue(arguments[0].getValueAsString(false, true));
				}
			}
		};
		miniScript->registerMethod(new MethodJSONSerialize(miniScript));
	}
	{
		//
		class MethodJSONDeserialize: public MiniScript::Method {
		private:
			MiniScript* miniScript { nullptr };
		public:
			MethodJSONDeserialize(MiniScript* miniScript):
				MiniScript::Method(
					{
						{ .type = MiniScript::TYPE_STRING, .name = "json", .optional = false, .reference = false, .nullable = false },
					},
					MiniScript::TYPE_PSEUDO_MIXED
				),
				miniScript(miniScript) {}
			const string getMethodName() override {
				return "json.deserialize";
			}
			void executeMethod(span<MiniScript::Variable>& arguments, MiniScript::Variable& returnValue, const MiniScript::Statement& statement) override {
				string json;
				if (MiniScript::getStringValue(arguments, 0, json, false) == false) {
					_Console::println(getMethodName() + "(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation(getMethodName()));
					miniScript->startErrorScript();
				} else {
					json = _StringTools::trim(json);
					if (_StringTools::startsWith(json, "{") == true) {
						returnValue = MiniScript::initializeMapSet(json, miniScript, statement);
					} else
					if (_StringTools::startsWith(json, "[") == true) {
						returnValue = MiniScript::initializeArray(json, miniScript, statement);
					} else {
						_Console::println(getMethodName() + "(): " + miniScript->getStatementInformation(statement) + ": JSON string not valid");
					}
				}
			}
		};
		miniScript->registerMethod(new MethodJSONDeserialize(miniScript));
	}
}
