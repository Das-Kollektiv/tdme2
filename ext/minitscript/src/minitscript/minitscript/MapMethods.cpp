#include <span>

#include <minitscript/minitscript.h>
#include <minitscript/minitscript/MapMethods.h>
#include <minitscript/minitscript/MinitScript.h>
#include <minitscript/utilities/Console.h>

using std::span;

using minitscript::minitscript::MapMethods;

using minitscript::minitscript::MinitScript;

using _Console = minitscript::utilities::Console;

void MapMethods::registerConstants(MinitScript* minitScript) {
}

void MapMethods::registerMethods(MinitScript* minitScript) {
	// map
	{
		//
		class MethodMap: public MinitScript::Method {
		private:
			MinitScript* minitScript { nullptr };
		public:
			MethodMap(MinitScript* minitScript):
				MinitScript::Method(
					{},
					MinitScript::TYPE_MAP
				),
				minitScript(minitScript) {}
			const string getMethodName() override {
				return "Map";
			}
			void executeMethod(span<MinitScript::Variable>& arguments, MinitScript::Variable& returnValue, const MinitScript::SubStatement& subStatement) override {
				if (arguments.size() == 0) {
					returnValue.setType(MinitScript::TYPE_MAP);
				} else {
					MINITSCRIPT_METHODUSAGE_COMPLAIN(getMethodName());
				}
			}
		};
		minitScript->registerMethod(new MethodMap(minitScript));
	}
	{
		//
		class MethodMapGetSize: public MinitScript::Method {
		private:
			MinitScript* minitScript { nullptr };
		public:
			MethodMapGetSize(MinitScript* minitScript):
				MinitScript::Method(
					{
						{ .type = MinitScript::TYPE_MAP, .name = "map", .optional = false, .reference = false, .nullable = false },
					},
					MinitScript::TYPE_INTEGER
				),
				minitScript(minitScript) {}
			const string getMethodName() override {
				return "Map::getSize";
			}
			void executeMethod(span<MinitScript::Variable>& arguments, MinitScript::Variable& returnValue, const MinitScript::SubStatement& subStatement) override {
				string key;
				if (arguments.size() == 1 &&
					arguments[0].getType() == MinitScript::TYPE_MAP) {
					returnValue.setValue(static_cast<int64_t>(arguments[0].getMapSize()));
				} else {
					MINITSCRIPT_METHODUSAGE_COMPLAIN(getMethodName());
				}
			}
		};
		minitScript->registerMethod(new MethodMapGetSize(minitScript));
	}
	{
		//
		class MethodMapIsEmpty: public MinitScript::Method {
		private:
			MinitScript* minitScript { nullptr };
		public:
			MethodMapIsEmpty(MinitScript* minitScript):
				MinitScript::Method(
					{
						{ .type = MinitScript::TYPE_MAP, .name = "map", .optional = false, .reference = false, .nullable = false },
					},
					MinitScript::TYPE_BOOLEAN
				),
				minitScript(minitScript) {}
			const string getMethodName() override {
				return "Map::isEmpty";
			}
			void executeMethod(span<MinitScript::Variable>& arguments, MinitScript::Variable& returnValue, const MinitScript::SubStatement& subStatement) override {
				string key;
				if (arguments.size() == 1 &&
					arguments[0].getType() == MinitScript::TYPE_MAP) {
					returnValue.setValue(arguments[0].getMapSize() == 0);
				} else {
					MINITSCRIPT_METHODUSAGE_COMPLAIN(getMethodName());
				}
			}
		};
		minitScript->registerMethod(new MethodMapIsEmpty(minitScript));
	}
	{
		//
		class MethodMapSet: public MinitScript::Method {
		private:
			MinitScript* minitScript { nullptr };
		public:
			MethodMapSet(MinitScript* minitScript):
				MinitScript::Method(
					{
						{ .type = MinitScript::TYPE_MAP, .name = "map", .optional = false, .reference = true, .nullable = false },
						{ .type = MinitScript::TYPE_STRING, .name = "key", .optional = false, .reference = false, .nullable = false },
						{ .type = MinitScript::TYPE_PSEUDO_MIXED, .name = "value", .optional = false, .reference = false, .nullable = false }
					},
					MinitScript::TYPE_NULL
				),
				minitScript(minitScript) {}
			const string getMethodName() override {
				return "Map::set";
			}
			void executeMethod(span<MinitScript::Variable>& arguments, MinitScript::Variable& returnValue, const MinitScript::SubStatement& subStatement) override {
				//
				string key;
				if (arguments.size() == 3 &&
					arguments[0].getType() == MinitScript::TYPE_MAP &&
					MinitScript::getStringValue(arguments, 1, key) == true) {
					arguments[0].setMapEntry(key, MinitScript::Variable::createNonReferenceVariable(&arguments[2]));
				} else {
					MINITSCRIPT_METHODUSAGE_COMPLAIN(getMethodName());
				}
			}
		};
		minitScript->registerMethod(new MethodMapSet(minitScript));
	}
	{
		//
		class MethodMapContains: public MinitScript::Method {
		private:
			MinitScript* minitScript { nullptr };
		public:
			MethodMapContains(MinitScript* minitScript):
				MinitScript::Method(
					{
						{ .type = MinitScript::TYPE_MAP, .name = "map", .optional = false, .reference = false, .nullable = false },
						{ .type = MinitScript::TYPE_STRING, .name = "key", .optional = false, .reference = false, .nullable = false }
					},
					MinitScript::TYPE_BOOLEAN
				),
				minitScript(minitScript) {}
			const string getMethodName() override {
				return "Map::contains";
			}
			void executeMethod(span<MinitScript::Variable>& arguments, MinitScript::Variable& returnValue, const MinitScript::SubStatement& subStatement) override {
				string key;
				if (arguments.size() == 2 &&
					arguments[0].getType() == MinitScript::TYPE_MAP &&
					MinitScript::getStringValue(arguments, 1, key) == true) {
					returnValue.setValue(arguments[0].hasMapEntry(key));
				} else {
					MINITSCRIPT_METHODUSAGE_COMPLAIN(getMethodName());
				}
			}
		};
		minitScript->registerMethod(new MethodMapContains(minitScript));
	}
	{
		//
		class MethodMapGet: public MinitScript::Method {
		private:
			MinitScript* minitScript { nullptr };
		public:
			MethodMapGet(MinitScript* minitScript):
				MinitScript::Method(
					{
						{ .type = MinitScript::TYPE_MAP, .name = "map", .optional = false, .reference = false, .nullable = false },
						{ .type = MinitScript::TYPE_STRING, .name = "key", .optional = false, .reference = false, .nullable = false }
					},
					MinitScript::TYPE_PSEUDO_MIXED
				),
				minitScript(minitScript) {}
			const string getMethodName() override {
				return "Map::get";
			}
			void executeMethod(span<MinitScript::Variable>& arguments, MinitScript::Variable& returnValue, const MinitScript::SubStatement& subStatement) override {
				string key;
				if (arguments.size() == 2 &&
					arguments[0].getType() == MinitScript::TYPE_MAP &&
					MinitScript::getStringValue(arguments, 1, key) == true) {
					returnValue.setValue(arguments[0].getMapEntry(key));
				} else {
					MINITSCRIPT_METHODUSAGE_COMPLAIN(getMethodName());
				}
			}
		};
		minitScript->registerMethod(new MethodMapGet(minitScript));
	}
	{
		//
		class MethodMapGetReference: public MinitScript::Method {
		private:
			MinitScript* minitScript { nullptr };
		public:
			MethodMapGetReference(MinitScript* minitScript):
				MinitScript::Method(
					{
						{ .type = MinitScript::TYPE_MAP, .name = "map", .optional = false, .reference = false, .nullable = false },
						{ .type = MinitScript::TYPE_STRING, .name = "key", .optional = false, .reference = false, .nullable = false }
					},
					MinitScript::TYPE_PSEUDO_MIXED
				),
				minitScript(minitScript) {}
			const string getMethodName() override {
				return "Map::getReference";
			}
			void executeMethod(span<MinitScript::Variable>& arguments, MinitScript::Variable& returnValue, const MinitScript::SubStatement& subStatement) override {
				string key;
				if (arguments.size() == 2 &&
					arguments[0].getType() == MinitScript::TYPE_MAP &&
					MinitScript::getStringValue(arguments, 1, key) == true) {
					auto mapEntryPtr = arguments[0].getMapEntryPtr(key);
					if (mapEntryPtr != nullptr) returnValue = MinitScript::Variable::createReferenceVariable(mapEntryPtr);
				} else {
					MINITSCRIPT_METHODUSAGE_COMPLAIN(getMethodName());
				}
			}
			virtual bool isPrivate() const override {
				return true;
			}
		};
		minitScript->registerMethod(new MethodMapGetReference(minitScript));
	}
	{
		//
		class MethodMapRemove: public MinitScript::Method {
		private:
			MinitScript* minitScript { nullptr };
		public:
			MethodMapRemove(MinitScript* minitScript):
				MinitScript::Method(
					{
						{ .type = MinitScript::TYPE_MAP, .name = "map", .optional = false, .reference = true, .nullable = false },
						{ .type = MinitScript::TYPE_STRING, .name = "key", .optional = false, .reference = false, .nullable = false }
					},
					MinitScript::TYPE_NULL
				),
				minitScript(minitScript) {}
			const string getMethodName() override {
				return "Map::remove";
			}
			void executeMethod(span<MinitScript::Variable>& arguments, MinitScript::Variable& returnValue, const MinitScript::SubStatement& subStatement) override {
				string key;
				if (arguments.size() == 2 &&
					arguments[0].getType() == MinitScript::TYPE_MAP &&
					MinitScript::getStringValue(arguments, 1, key) == true) {
					arguments[0].removeMapEntry(key);
				} else {
					MINITSCRIPT_METHODUSAGE_COMPLAIN(getMethodName());
				}
			}
		};
		minitScript->registerMethod(new MethodMapRemove(minitScript));
	}
	{
		//
		class MethodMapGetKeys: public MinitScript::Method {
		private:
			MinitScript* minitScript { nullptr };
		public:
			MethodMapGetKeys(MinitScript* minitScript):
				MinitScript::Method(
					{
						{ .type = MinitScript::TYPE_MAP, .name = "map", .optional = false, .reference = false, .nullable = false },
					},
					MinitScript::TYPE_ARRAY
				),
				minitScript(minitScript) {}
			const string getMethodName() override {
				return "Map::getKeys";
			}
			void executeMethod(span<MinitScript::Variable>& arguments, MinitScript::Variable& returnValue, const MinitScript::SubStatement& subStatement) override {
				if (arguments.size() == 1 &&
					arguments[0].getType() == MinitScript::TYPE_MAP) {
					auto keys = arguments[0].getMapKeys();
					returnValue.setType(MinitScript::TYPE_ARRAY);
					for (const auto& key: keys) {
						returnValue.pushArrayEntry(key);
					}
				} else {
					MINITSCRIPT_METHODUSAGE_COMPLAIN(getMethodName());
				}
			}
		};
		minitScript->registerMethod(new MethodMapGetKeys(minitScript));
	}
	{
		//
		class MethodMapGetValues: public MinitScript::Method {
		private:
			MinitScript* minitScript { nullptr };
		public:
			MethodMapGetValues(MinitScript* minitScript):
				MinitScript::Method(
					{
						{ .type = MinitScript::TYPE_MAP, .name = "map", .optional = false, .reference = false, .nullable = false },
					},
					MinitScript::TYPE_ARRAY
				),
				minitScript(minitScript) {}
			const string getMethodName() override {
				return "Map::getValues";
			}
			void executeMethod(span<MinitScript::Variable>& arguments, MinitScript::Variable& returnValue, const MinitScript::SubStatement& subStatement) override {
				if (arguments.size() == 1 &&
					arguments[0].getType() == MinitScript::TYPE_MAP) {
					auto values = arguments[0].getMapValues();
					returnValue.setType(MinitScript::TYPE_ARRAY);
					for (const auto value: values) {
						returnValue.pushArrayEntry(*value);
					}
				} else {
					MINITSCRIPT_METHODUSAGE_COMPLAIN(getMethodName());
				}
			}
		};
		minitScript->registerMethod(new MethodMapGetValues(minitScript));
	}
	{
		//
		class MethodMapClear: public MinitScript::Method {
		private:
			MinitScript* minitScript { nullptr };
		public:
			MethodMapClear(MinitScript* minitScript):
				MinitScript::Method(
					{
						{ .type = MinitScript::TYPE_MAP, .name = "map", .optional = false, .reference = true, .nullable = false }
					},
					MinitScript::TYPE_NULL
				),
				minitScript(minitScript) {}
			const string getMethodName() override {
				return "Map::clear";
			}
			void executeMethod(span<MinitScript::Variable>& arguments, MinitScript::Variable& returnValue, const MinitScript::SubStatement& subStatement) override {
				if (arguments.size() == 1 &&
					arguments[0].getType() == MinitScript::TYPE_MAP) {
					arguments[0].clearMap();
				} else {
					MINITSCRIPT_METHODUSAGE_COMPLAIN(getMethodName());
				}
			}
		};
		minitScript->registerMethod(new MethodMapClear(minitScript));
	}
	{
		//
		class MethodMapForEach: public MinitScript::Method {
		private:
			MinitScript* minitScript { nullptr };
		public:
			MethodMapForEach(MinitScript* minitScript):
				MinitScript::Method(
					{
						{ .type = MinitScript::TYPE_MAP, .name = "map", .optional = false, .reference = false, .nullable = false },
						{ .type = MinitScript::TYPE_FUNCTION_ASSIGNMENT, .name = "callbackFunction", .optional = false, .reference = false, .nullable = false },
						{ .type = MinitScript::TYPE_PSEUDO_MIXED, .name = "cookie", .optional = true, .reference = true, .nullable = false }
					},
					MinitScript::TYPE_NULL
				),
				minitScript(minitScript) {}
			const string getMethodName() override {
				return "Map::forEach";
			}
			void executeMethod(span<MinitScript::Variable>& arguments, MinitScript::Variable& returnValue, const MinitScript::SubStatement& subStatement) override {
				string callbackFunction;
				int callbackFunctionScriptIdx;
				if ((arguments.size() == 2 || arguments.size() == 3) &&
					arguments[0].getType() == MinitScript::TYPE_MAP &&
					MinitScript::getFunctionValue(arguments, 1, callbackFunction, callbackFunctionScriptIdx) == true) {
					auto mapPtr = arguments[0].getMapPointer();
					if (mapPtr != nullptr) {
						if (callbackFunction.empty() == false && callbackFunctionScriptIdx == MinitScript::SCRIPTIDX_NONE) {
							callbackFunctionScriptIdx = minitScript->getFunctionScriptIdx(callbackFunction);
						}
						if (callbackFunctionScriptIdx == MinitScript::SCRIPTIDX_NONE) {
							MINITSCRIPT_METHODUSAGE_COMPLAINM(getMethodName(), "Function not found: " + callbackFunction);
						} else {
							for (const auto& [mapKey, mapValue]: *mapPtr) {
								vector<MinitScript::Variable> functionArguments { MinitScript::Variable(mapKey), MinitScript::Variable::createReferenceVariable(mapValue) };
								if (arguments.size() == 3) functionArguments.push_back(arguments[2]);
								span functionArgumentsSpan(functionArguments);
								MinitScript::Variable functionReturnValue;
								minitScript->call(callbackFunctionScriptIdx, functionArgumentsSpan, functionReturnValue);
								// exit condition
								bool result = false;
								functionReturnValue.getBooleanValue(result, false);
								if (result == true) break;
							}
						}
					}
				} else {
					MINITSCRIPT_METHODUSAGE_COMPLAIN(getMethodName());
				}
			}
		};
		minitScript->registerMethod(new MethodMapForEach(minitScript));
	}
}
