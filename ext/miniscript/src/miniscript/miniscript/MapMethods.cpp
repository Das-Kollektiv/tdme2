#include <span>

#include <miniscript/miniscript.h>
#include <miniscript/miniscript/MapMethods.h>
#include <miniscript/miniscript/MiniScript.h>
#include <miniscript/utilities/Console.h>

using std::span;

using miniscript::miniscript::MapMethods;

using miniscript::miniscript::MiniScript;

using _Console = miniscript::utilities::Console;

void MapMethods::registerConstants(MiniScript* miniScript) {
}

void MapMethods::registerMethods(MiniScript* miniScript) {
	// map
	{
		//
		class MethodMap: public MiniScript::Method {
		private:
			MiniScript* miniScript { nullptr };
		public:
			MethodMap(MiniScript* miniScript):
				MiniScript::Method(
					{},
					MiniScript::TYPE_MAP
				),
				miniScript(miniScript) {}
			const string getMethodName() override {
				return "Map";
			}
			void executeMethod(span<MiniScript::Variable>& arguments, MiniScript::Variable& returnValue, const MiniScript::Statement& statement) override {
				returnValue.setType(MiniScript::TYPE_MAP);
			}
		};
		miniScript->registerMethod(new MethodMap(miniScript));
	}
	{
		//
		class MethodMapSet: public MiniScript::Method {
		private:
			MiniScript* miniScript { nullptr };
		public:
			MethodMapSet(MiniScript* miniScript):
				MiniScript::Method(
					{
						{ .type = MiniScript::TYPE_MAP, .name = "map", .optional = false, .reference = true, .nullable = false },
						{ .type = MiniScript::TYPE_STRING, .name = "key", .optional = false, .reference = false, .nullable = false },
						{ .type = MiniScript::TYPE_PSEUDO_MIXED, .name = "value", .optional = false, .reference = false, .nullable = false }
					},
					MiniScript::TYPE_NULL
				),
				miniScript(miniScript) {}
			const string getMethodName() override {
				return "Map::set";
			}
			void executeMethod(span<MiniScript::Variable>& arguments, MiniScript::Variable& returnValue, const MiniScript::Statement& statement) override {
				//
				string key;
				if (arguments.size() != 3 ||
					arguments[0].getType() != MiniScript::TYPE_MAP ||
					MiniScript::getStringValue(arguments, 1, key, false) == false) {
					_Console::printLine(getMethodName() + "(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation(getMethodName()));
					miniScript->startErrorScript();
				} else {
					arguments[0].setMapEntry(key, arguments[2]);
				}
			}
		};
		miniScript->registerMethod(new MethodMapSet(miniScript));
	}
	{
		//
		class MethodMapHas: public MiniScript::Method {
		private:
			MiniScript* miniScript { nullptr };
		public:
			MethodMapHas(MiniScript* miniScript):
				MiniScript::Method(
					{
						{ .type = MiniScript::TYPE_MAP, .name = "map", .optional = false, .reference = false, .nullable = false },
						{ .type = MiniScript::TYPE_STRING, .name = "key", .optional = false, .reference = false, .nullable = false }
					},
					MiniScript::TYPE_BOOLEAN
				),
				miniScript(miniScript) {}
			const string getMethodName() override {
				return "Map::has";
			}
			void executeMethod(span<MiniScript::Variable>& arguments, MiniScript::Variable& returnValue, const MiniScript::Statement& statement) override {
				//
				string key;
				if (arguments.size() < 2 ||
					arguments[0].getType() != MiniScript::TYPE_MAP ||
					MiniScript::getStringValue(arguments, 1, key, false) == false) {
					_Console::printLine(getMethodName() + "(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation(getMethodName()));
					miniScript->startErrorScript();
				} else {
					returnValue.setValue(arguments[0].hasMapEntry(key));
				}
			}
		};
		miniScript->registerMethod(new MethodMapHas(miniScript));
	}
	{
		//
		class MethodMapGet: public MiniScript::Method {
		private:
			MiniScript* miniScript { nullptr };
		public:
			MethodMapGet(MiniScript* miniScript):
				MiniScript::Method(
					{
						{ .type = MiniScript::TYPE_MAP, .name = "map", .optional = false, .reference = false, .nullable = false },
						{ .type = MiniScript::TYPE_STRING, .name = "key", .optional = false, .reference = false, .nullable = false }
					},
					MiniScript::TYPE_PSEUDO_MIXED
				),
				miniScript(miniScript) {}
			const string getMethodName() override {
				return "Map::get";
			}
			void executeMethod(span<MiniScript::Variable>& arguments, MiniScript::Variable& returnValue, const MiniScript::Statement& statement) override {
				//
				string key;
				if (arguments.size() < 2 ||
					arguments[0].getType() != MiniScript::TYPE_MAP ||
					MiniScript::getStringValue(arguments, 1, key, false) == false) {
					_Console::printLine(getMethodName() + "(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation(getMethodName()));
					miniScript->startErrorScript();
				} else {
					returnValue = arguments[0].getMapEntry(key);
				}
			}
		};
		miniScript->registerMethod(new MethodMapGet(miniScript));
	}
	{
		//
		class MethodMapRemove: public MiniScript::Method {
		private:
			MiniScript* miniScript { nullptr };
		public:
			MethodMapRemove(MiniScript* miniScript):
				MiniScript::Method(
					{
						{ .type = MiniScript::TYPE_MAP, .name = "map", .optional = false, .reference = true, .nullable = false },
						{ .type = MiniScript::TYPE_STRING, .name = "key", .optional = false, .reference = false, .nullable = false }
					},
					MiniScript::TYPE_NULL
				),
				miniScript(miniScript) {}
			const string getMethodName() override {
				return "Map::remove";
			}
			void executeMethod(span<MiniScript::Variable>& arguments, MiniScript::Variable& returnValue, const MiniScript::Statement& statement) override {
				//
				string key;
				if (arguments.size() < 2 ||
					arguments[0].getType() != MiniScript::TYPE_MAP ||
					MiniScript::getStringValue(arguments, 1, key, false) == false) {
					_Console::printLine(getMethodName() + "(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation(getMethodName()));
					miniScript->startErrorScript();
				} else {
					arguments[0].removeMapEntry(key);
				}
			}
		};
		miniScript->registerMethod(new MethodMapRemove(miniScript));
	}
	{
		//
		class MethodMapGetKeys: public MiniScript::Method {
		private:
			MiniScript* miniScript { nullptr };
		public:
			MethodMapGetKeys(MiniScript* miniScript):
				MiniScript::Method(
					{
						{ .type = MiniScript::TYPE_MAP, .name = "map", .optional = false, .reference = false, .nullable = false },
					},
					MiniScript::TYPE_ARRAY
				),
				miniScript(miniScript) {}
			const string getMethodName() override {
				return "Map::getKeys";
			}
			void executeMethod(span<MiniScript::Variable>& arguments, MiniScript::Variable& returnValue, const MiniScript::Statement& statement) override {
				//
				if (arguments.size() != 1 ||
					arguments[0].getType() != MiniScript::TYPE_MAP) {
					_Console::printLine(getMethodName() + "(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation(getMethodName()));
					miniScript->startErrorScript();
				} else {
					auto keys = arguments[0].getMapKeys();
					returnValue.setType(MiniScript::TYPE_ARRAY);
					for (const auto& key: keys) {
						returnValue.pushArrayEntry(key);
					}
				}
			}
		};
		miniScript->registerMethod(new MethodMapGetKeys(miniScript));
	}
	{
		//
		class MethodMapGetValues: public MiniScript::Method {
		private:
			MiniScript* miniScript { nullptr };
		public:
			MethodMapGetValues(MiniScript* miniScript):
				MiniScript::Method(
					{
						{ .type = MiniScript::TYPE_MAP, .name = "map", .optional = false, .reference = false, .nullable = false },
					},
					MiniScript::TYPE_ARRAY
				),
				miniScript(miniScript) {}
			const string getMethodName() override {
				return "Map::getValues";
			}
			void executeMethod(span<MiniScript::Variable>& arguments, MiniScript::Variable& returnValue, const MiniScript::Statement& statement) override {
				//
				if (arguments.size() != 1 ||
					arguments[0].getType() != MiniScript::TYPE_MAP) {
					_Console::printLine(getMethodName() + "(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation(getMethodName()));
					miniScript->startErrorScript();
				} else {
					auto values = arguments[0].getMapValues();
					returnValue.setType(MiniScript::TYPE_ARRAY);
					for (const auto value: values) {
						returnValue.pushArrayEntry(*value);
					}
				}
			}
		};
		miniScript->registerMethod(new MethodMapGetValues(miniScript));
	}
	{
		//
		class MethodMapClear: public MiniScript::Method {
		private:
			MiniScript* miniScript { nullptr };
		public:
			MethodMapClear(MiniScript* miniScript):
				MiniScript::Method(
					{
						{ .type = MiniScript::TYPE_MAP, .name = "map", .optional = false, .reference = true, .nullable = false }
					},
					MiniScript::TYPE_NULL
				),
				miniScript(miniScript) {}
			const string getMethodName() override {
				return "Map::clear";
			}
			void executeMethod(span<MiniScript::Variable>& arguments, MiniScript::Variable& returnValue, const MiniScript::Statement& statement) override {
				if (arguments.size() != 1 || arguments[0].getType() != MiniScript::TYPE_MAP) {
					_Console::printLine(getMethodName() + "(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation(getMethodName()));
					miniScript->startErrorScript();
				} else {
					arguments[0].clearMap();
				}
			}
		};
		miniScript->registerMethod(new MethodMapClear(miniScript));
	}
	{
		//
		class MethodMapForEach: public MiniScript::Method {
		private:
			MiniScript* miniScript { nullptr };
		public:
			MethodMapForEach(MiniScript* miniScript):
				MiniScript::Method(
					{
						{ .type = MiniScript::TYPE_MAP, .name = "map", .optional = false, .reference = false, .nullable = false },
						{ .type = MiniScript::TYPE_FUNCTION_ASSIGNMENT, .name = "function", .optional = false, .reference = false, .nullable = false },
						{ .type = MiniScript::TYPE_PSEUDO_MIXED, .name = "cookie", .optional = true, .reference = true, .nullable = false }
					},
					MiniScript::TYPE_NULL
				),
				miniScript(miniScript) {}
			const string getMethodName() override {
				return "Map::forEach";
			}
			void executeMethod(span<MiniScript::Variable>& arguments, MiniScript::Variable& returnValue, const MiniScript::Statement& statement) override {
				string function;
				if ((arguments.size() != 2 && arguments.size() != 3) ||
					arguments[0].getType() != MiniScript::TYPE_MAP ||
					MiniScript::getStringValue(arguments, 1, function, false) == false) {
					_Console::printLine(getMethodName() + "(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation(getMethodName()));
					miniScript->startErrorScript();
				} else {
					auto mapPtr = arguments[0].getMapPointer();
					if (mapPtr != nullptr) {
						for (const auto& [mapKey, mapValue]: *mapPtr) {
							vector<MiniScript::Variable> functionArguments { MiniScript::Variable(mapKey), MiniScript::Variable::createReferenceVariable(mapValue) };
							if (arguments.size() == 3) functionArguments.push_back(arguments[2]);
							span functionArgumentsSpan(functionArguments);
							MiniScript::Variable functionReturnValue;
							miniScript->call(function, functionArgumentsSpan, functionReturnValue);
							// exit condition
							bool result = false;
							functionReturnValue.getBooleanValue(result, false);
							if (result == true) break;
						}
					}
				}
			}
		};
		miniScript->registerMethod(new MethodMapForEach(miniScript));
	}
}
