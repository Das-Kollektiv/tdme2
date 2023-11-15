#include <span>

#include <miniscript/miniscript.h>
#include <miniscript/miniscript/MapMethods.h>
#include <miniscript/miniscript/MiniScript.h>
#include <miniscript/utilities/Console.h>

using std::span;

using miniscript::miniscript::MapMethods;

using miniscript::miniscript::MiniScript;
using miniscript::utilities::Console;

void MapMethods::registerMethods(MiniScript* miniScript) {
	// map
	{
		//
		class ScriptMethodMap: public MiniScript::ScriptMethod {
		private:
			MiniScript* miniScript { nullptr };
		public:
			ScriptMethodMap(MiniScript* miniScript):
				MiniScript::ScriptMethod(
					{},
					MiniScript::TYPE_MAP
				),
				miniScript(miniScript) {}
			const string getMethodName() override {
				return "map";
			}
			void executeMethod(span<MiniScript::ScriptVariable>& argumentValues, MiniScript::ScriptVariable& returnValue, const MiniScript::ScriptStatement& statement) override {
				returnValue.setType(MiniScript::TYPE_MAP);
			}
		};
		miniScript->registerMethod(new ScriptMethodMap(miniScript));
	}
	{
		//
		class ScriptMethodMapSet: public MiniScript::ScriptMethod {
		private:
			MiniScript* miniScript { nullptr };
		public:
			ScriptMethodMapSet(MiniScript* miniScript):
				MiniScript::ScriptMethod(
					{
						{ .type = MiniScript::TYPE_MAP, .name = "map", .optional = false, .reference = true, .nullable = false },
						{ .type = MiniScript::TYPE_STRING, .name = "key", .optional = false, .reference = false, .nullable = false },
						{ .type = MiniScript::TYPE_PSEUDO_MIXED, .name = "value", .optional = false, .reference = false, .nullable = false }
					},
					MiniScript::TYPE_NULL
				),
				miniScript(miniScript) {}
			const string getMethodName() override {
				return "map.set";
			}
			void executeMethod(span<MiniScript::ScriptVariable>& argumentValues, MiniScript::ScriptVariable& returnValue, const MiniScript::ScriptStatement& statement) override {
				//
				string key;
				if (argumentValues.size() != 3 ||
					argumentValues[0].getType() != MiniScript::TYPE_MAP ||
					MiniScript::getStringValue(argumentValues, 1, key, false) == false) {
					Console::println(getMethodName() + "(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation(getMethodName()));
					miniScript->startErrorScript();
				} else {
					argumentValues[0].setMapEntry(key, argumentValues[2]);
				}
			}
		};
		miniScript->registerMethod(new ScriptMethodMapSet(miniScript));
	}
	{
		//
		class ScriptMethodMapHas: public MiniScript::ScriptMethod {
		private:
			MiniScript* miniScript { nullptr };
		public:
			ScriptMethodMapHas(MiniScript* miniScript):
				MiniScript::ScriptMethod(
					{
						{ .type = MiniScript::TYPE_MAP, .name = "map", .optional = false, .reference = false, .nullable = false },
						{ .type = MiniScript::TYPE_STRING, .name = "key", .optional = false, .reference = false, .nullable = false }
					},
					MiniScript::TYPE_BOOLEAN
				),
				miniScript(miniScript) {}
			const string getMethodName() override {
				return "map.has";
			}
			void executeMethod(span<MiniScript::ScriptVariable>& argumentValues, MiniScript::ScriptVariable& returnValue, const MiniScript::ScriptStatement& statement) override {
				//
				string key;
				if (argumentValues.size() < 2 ||
					argumentValues[0].getType() != MiniScript::TYPE_MAP ||
					MiniScript::getStringValue(argumentValues, 1, key, false) == false) {
					Console::println(getMethodName() + "(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation(getMethodName()));
					miniScript->startErrorScript();
				} else {
					returnValue.setValue(argumentValues[0].hasMapEntry(key));
				}
			}
		};
		miniScript->registerMethod(new ScriptMethodMapHas(miniScript));
	}
	{
		//
		class ScriptMethodMapGet: public MiniScript::ScriptMethod {
		private:
			MiniScript* miniScript { nullptr };
		public:
			ScriptMethodMapGet(MiniScript* miniScript):
				MiniScript::ScriptMethod(
					{
						{ .type = MiniScript::TYPE_MAP, .name = "map", .optional = false, .reference = false, .nullable = false },
						{ .type = MiniScript::TYPE_STRING, .name = "key", .optional = false, .reference = false, .nullable = false }
					},
					MiniScript::TYPE_PSEUDO_MIXED
				),
				miniScript(miniScript) {}
			const string getMethodName() override {
				return "map.get";
			}
			void executeMethod(span<MiniScript::ScriptVariable>& argumentValues, MiniScript::ScriptVariable& returnValue, const MiniScript::ScriptStatement& statement) override {
				//
				string key;
				if (argumentValues.size() < 2 ||
					argumentValues[0].getType() != MiniScript::TYPE_MAP ||
					MiniScript::getStringValue(argumentValues, 1, key, false) == false) {
					Console::println(getMethodName() + "(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation(getMethodName()));
					miniScript->startErrorScript();
				} else {
					returnValue = argumentValues[0].getMapEntry(key);
				}
			}
		};
		miniScript->registerMethod(new ScriptMethodMapGet(miniScript));
	}
	{
		//
		class ScriptMethodMapRemove: public MiniScript::ScriptMethod {
		private:
			MiniScript* miniScript { nullptr };
		public:
			ScriptMethodMapRemove(MiniScript* miniScript):
				MiniScript::ScriptMethod(
					{
						{ .type = MiniScript::TYPE_MAP, .name = "map", .optional = false, .reference = true, .nullable = false },
						{ .type = MiniScript::TYPE_STRING, .name = "key", .optional = false, .reference = false, .nullable = false }
					},
					MiniScript::TYPE_NULL
				),
				miniScript(miniScript) {}
			const string getMethodName() override {
				return "map.remove";
			}
			void executeMethod(span<MiniScript::ScriptVariable>& argumentValues, MiniScript::ScriptVariable& returnValue, const MiniScript::ScriptStatement& statement) override {
				//
				string key;
				if (argumentValues.size() < 2 ||
					argumentValues[0].getType() != MiniScript::TYPE_MAP ||
					MiniScript::getStringValue(argumentValues, 1, key, false) == false) {
					Console::println(getMethodName() + "(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation(getMethodName()));
					miniScript->startErrorScript();
				} else {
					argumentValues[0].removeMapEntry(key);
				}
			}
		};
		miniScript->registerMethod(new ScriptMethodMapRemove(miniScript));
	}
	{
		//
		class ScriptMethodMapGetKeys: public MiniScript::ScriptMethod {
		private:
			MiniScript* miniScript { nullptr };
		public:
			ScriptMethodMapGetKeys(MiniScript* miniScript):
				MiniScript::ScriptMethod(
					{
						{ .type = MiniScript::TYPE_MAP, .name = "map", .optional = false, .reference = false, .nullable = false },
					},
					MiniScript::TYPE_ARRAY
				),
				miniScript(miniScript) {}
			const string getMethodName() override {
				return "map.getKeys";
			}
			void executeMethod(span<MiniScript::ScriptVariable>& argumentValues, MiniScript::ScriptVariable& returnValue, const MiniScript::ScriptStatement& statement) override {
				//
				if (argumentValues.size() != 1 ||
					argumentValues[0].getType() != MiniScript::TYPE_MAP) {
					Console::println(getMethodName() + "(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation(getMethodName()));
					miniScript->startErrorScript();
				} else {
					auto keys = argumentValues[0].getMapKeys();
					returnValue.setType(MiniScript::TYPE_ARRAY);
					for (const auto& key: keys) {
						returnValue.pushArrayEntry(key);
					}
				}
			}
		};
		miniScript->registerMethod(new ScriptMethodMapGetKeys(miniScript));
	}
	{
		//
		class ScriptMethodMapGetValues: public MiniScript::ScriptMethod {
		private:
			MiniScript* miniScript { nullptr };
		public:
			ScriptMethodMapGetValues(MiniScript* miniScript):
				MiniScript::ScriptMethod(
					{
						{ .type = MiniScript::TYPE_MAP, .name = "map", .optional = false, .reference = false, .nullable = false },
					},
					MiniScript::TYPE_ARRAY
				),
				miniScript(miniScript) {}
			const string getMethodName() override {
				return "map.getValues";
			}
			void executeMethod(span<MiniScript::ScriptVariable>& argumentValues, MiniScript::ScriptVariable& returnValue, const MiniScript::ScriptStatement& statement) override {
				//
				if (argumentValues.size() != 1 ||
					argumentValues[0].getType() != MiniScript::TYPE_MAP) {
					Console::println(getMethodName() + "(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation(getMethodName()));
					miniScript->startErrorScript();
				} else {
					auto values = argumentValues[0].getMapValues();
					returnValue.setType(MiniScript::TYPE_ARRAY);
					for (const auto value: values) {
						returnValue.pushArrayEntry(*value);
					}
				}
			}
		};
		miniScript->registerMethod(new ScriptMethodMapGetValues(miniScript));
	}
}
