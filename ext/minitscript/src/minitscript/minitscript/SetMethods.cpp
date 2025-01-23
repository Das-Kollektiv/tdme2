#include <span>

#include <minitscript/minitscript/SetMethods.h>

#include <minitscript/minitscript.h>
#include <minitscript/minitscript/MinitScript.h>
#include <minitscript/utilities/Console.h>

using std::span;

using minitscript::minitscript::SetMethods;

using minitscript::minitscript::MinitScript;

using _Console = minitscript::utilities::Console;

void SetMethods::registerConstants(MinitScript* minitScript) {
}

void SetMethods::registerMethods(MinitScript* minitScript) {
	// sets
	{
		//
		class MethodSet: public MinitScript::Method {
		private:
			MinitScript* minitScript { nullptr };
		public:
			MethodSet(MinitScript* minitScript):
				MinitScript::Method(
					{},
					MinitScript::TYPE_SET
				),
				minitScript(minitScript) {}
			const string getMethodName() override {
				return "Set";
			}
			void executeMethod(span<MinitScript::Variable>& arguments, MinitScript::Variable& returnValue, const MinitScript::SubStatement& subStatement) override {
				if (arguments.size() == 0) {
					returnValue.setType(MinitScript::TYPE_SET);
				} else {
					MINITSCRIPT_METHODUSAGE_COMPLAIN(getMethodName());
				}
			}
		};
		minitScript->registerMethod(new MethodSet(minitScript));
	}
	{
		//
		class MethodSetGetSize: public MinitScript::Method {
		private:
			MinitScript* minitScript { nullptr };
		public:
			MethodSetGetSize(MinitScript* minitScript):
				MinitScript::Method(
					{
						{ .type = MinitScript::TYPE_SET, .name = "set", .optional = false, .reference = false, .nullable = false }
					},
					MinitScript::TYPE_INTEGER
				),
				minitScript(minitScript) {}
			const string getMethodName() override {
				return "Set::getSize";
			}
			void executeMethod(span<MinitScript::Variable>& arguments, MinitScript::Variable& returnValue, const MinitScript::SubStatement& subStatement) override {
				if (arguments.size() == 1 &&
					arguments[0].getType() == MinitScript::TYPE_SET) {
					returnValue.setValue(static_cast<int64_t>(arguments[0].getSetSize()));
				} else {
					MINITSCRIPT_METHODUSAGE_COMPLAIN(getMethodName());
				}
			}
		};
		minitScript->registerMethod(new MethodSetGetSize(minitScript));
	}
	{
		//
		class MethodSetIsEmpty: public MinitScript::Method {
		private:
			MinitScript* minitScript { nullptr };
		public:
			MethodSetIsEmpty(MinitScript* minitScript):
				MinitScript::Method(
					{
						{ .type = MinitScript::TYPE_SET, .name = "set", .optional = false, .reference = false, .nullable = false }
					},
					MinitScript::TYPE_BOOLEAN
				),
				minitScript(minitScript) {}
			const string getMethodName() override {
				return "Set::isEmpty";
			}
			void executeMethod(span<MinitScript::Variable>& arguments, MinitScript::Variable& returnValue, const MinitScript::SubStatement& subStatement) override {
				if (arguments.size() == 1 &&
					arguments[0].getType() != MinitScript::TYPE_SET) {
					returnValue.setValue(arguments[0].getSetSize() == 0);
				} else {
					MINITSCRIPT_METHODUSAGE_COMPLAIN(getMethodName());
				}
			}
		};
		minitScript->registerMethod(new MethodSetIsEmpty(minitScript));
	}
	{
		//
		class MethodSetInsert: public MinitScript::Method {
		private:
			MinitScript* minitScript { nullptr };
		public:
			MethodSetInsert(MinitScript* minitScript):
				MinitScript::Method(
					{
						{ .type = MinitScript::TYPE_SET, .name = "set", .optional = false, .reference = true, .nullable = false },
						{ .type = MinitScript::TYPE_STRING, .name = "key", .optional = false, .reference = false, .nullable = false }
					},
					MinitScript::TYPE_NULL
				),
				minitScript(minitScript) {}
			const string getMethodName() override {
				return "Set::insert";
			}
			void executeMethod(span<MinitScript::Variable>& arguments, MinitScript::Variable& returnValue, const MinitScript::SubStatement& subStatement) override {
				string key;
				if (arguments.size() == 2 &&
					arguments[0].getType() == MinitScript::TYPE_SET &&
					MinitScript::getStringValue(arguments, 1, key) == true) {
					arguments[0].insertSetKey(key);
				} else {
					MINITSCRIPT_METHODUSAGE_COMPLAIN(getMethodName());
				}
			}
		};
		minitScript->registerMethod(new MethodSetInsert(minitScript));
	}
	{
		//
		class MethodSetContains: public MinitScript::Method {
		private:
			MinitScript* minitScript { nullptr };
		public:
			MethodSetContains(MinitScript* minitScript):
				MinitScript::Method(
					{
						{ .type = MinitScript::TYPE_SET, .name = "set", .optional = false, .reference = false, .nullable = false },
						{ .type = MinitScript::TYPE_STRING, .name = "key", .optional = false, .reference = false, .nullable = false }
					},
					MinitScript::TYPE_BOOLEAN
				),
				minitScript(minitScript) {}
			const string getMethodName() override {
				return "Set::contains";
			}
			void executeMethod(span<MinitScript::Variable>& arguments, MinitScript::Variable& returnValue, const MinitScript::SubStatement& subStatement) override {
				string key;
				if (arguments.size() == 2 &&
					arguments[0].getType() == MinitScript::TYPE_SET &&
					MinitScript::getStringValue(arguments, 1, key) == true) {
					returnValue.setValue(arguments[0].hasSetKey(key));
				} else {
					MINITSCRIPT_METHODUSAGE_COMPLAIN(getMethodName());
				}
			}
		};
		minitScript->registerMethod(new MethodSetContains(minitScript));
	}
	{
		//
		class MethodSetRemove: public MinitScript::Method {
		private:
			MinitScript* minitScript { nullptr };
		public:
			MethodSetRemove(MinitScript* minitScript):
				MinitScript::Method(
					{
						{ .type = MinitScript::TYPE_SET, .name = "set", .optional = false, .reference = true, .nullable = false },
						{ .type = MinitScript::TYPE_STRING, .name = "key", .optional = false, .reference = false, .nullable = false }
					},
					MinitScript::TYPE_NULL
				),
				minitScript(minitScript) {}
			const string getMethodName() override {
				return "Set::remove";
			}
			void executeMethod(span<MinitScript::Variable>& arguments, MinitScript::Variable& returnValue, const MinitScript::SubStatement& subStatement) override {
				string key;
				if (arguments.size() == 2 &&
					arguments[0].getType() == MinitScript::TYPE_SET &&
					MinitScript::getStringValue(arguments, 1, key) == true) {
					arguments[0].removeSetKey(key);
				} else {
					MINITSCRIPT_METHODUSAGE_COMPLAIN(getMethodName());
				}
			}
		};
		minitScript->registerMethod(new MethodSetRemove(minitScript));
	}
	{
		//
		class MethodSetGetKeys: public MinitScript::Method {
		private:
			MinitScript* minitScript { nullptr };
		public:
			MethodSetGetKeys(MinitScript* minitScript):
				MinitScript::Method(
					{
						{ .type = MinitScript::TYPE_SET, .name = "set", .optional = false, .reference = false, .nullable = false },
					},
					MinitScript::TYPE_ARRAY
				),
				minitScript(minitScript) {}
			const string getMethodName() override {
				return "Set::getKeys";
			}
			void executeMethod(span<MinitScript::Variable>& arguments, MinitScript::Variable& returnValue, const MinitScript::SubStatement& subStatement) override {
				//
				if (arguments.size() == 1 &&
					arguments[0].getType() == MinitScript::TYPE_SET) {
					auto keys = arguments[0].getSetKeys();
					returnValue.setType(MinitScript::TYPE_ARRAY);
					for (const auto& key: keys) {
						returnValue.pushArrayEntry(key);
					}
				} else {
					MINITSCRIPT_METHODUSAGE_COMPLAIN(getMethodName());
				}
			}
		};
		minitScript->registerMethod(new MethodSetGetKeys(minitScript));
	}
	{
		//
		class MethodSetClear: public MinitScript::Method {
		private:
			MinitScript* minitScript { nullptr };
		public:
			MethodSetClear(MinitScript* minitScript):
				MinitScript::Method(
					{
						{ .type = MinitScript::TYPE_SET, .name = "set", .optional = false, .reference = true, .nullable = false }
					},
					MinitScript::TYPE_NULL
				),
				minitScript(minitScript) {}
			const string getMethodName() override {
				return "Set::clear";
			}
			void executeMethod(span<MinitScript::Variable>& arguments, MinitScript::Variable& returnValue, const MinitScript::SubStatement& subStatement) override {
				if (arguments.size() == 1 &&
					arguments[0].getType() == MinitScript::TYPE_SET) {
					arguments[0].clearSet();
				} else {
					MINITSCRIPT_METHODUSAGE_COMPLAIN(getMethodName());
				}
			}
		};
		minitScript->registerMethod(new MethodSetClear(minitScript));
	}
	{
		//
		class MethodSetForEach: public MinitScript::Method {
		private:
			MinitScript* minitScript { nullptr };
		public:
			MethodSetForEach(MinitScript* minitScript):
				MinitScript::Method(
					{
						{ .type = MinitScript::TYPE_SET, .name = "set", .optional = false, .reference = false, .nullable = false },
						{ .type = MinitScript::TYPE_FUNCTION_ASSIGNMENT, .name = "callbackFunction", .optional = false, .reference = false, .nullable = false },
						{ .type = MinitScript::TYPE_PSEUDO_MIXED, .name = "cookie", .optional = true, .reference = true, .nullable = false }
					},
					MinitScript::TYPE_NULL
				),
				minitScript(minitScript) {}
			const string getMethodName() override {
				return "Set::forEach";
			}
			void executeMethod(span<MinitScript::Variable>& arguments, MinitScript::Variable& returnValue, const MinitScript::SubStatement& subStatement) override {
				string callbackFunction;
				int callbackFunctionScriptIdx;
				if ((arguments.size() == 2 || arguments.size() == 3) &&
					arguments[0].getType() == MinitScript::TYPE_SET &&
					MinitScript::getFunctionValue(arguments, 1, callbackFunction, callbackFunctionScriptIdx) == true) {
					auto setPtr = arguments[0].getSetPointer();
					if (setPtr != nullptr) {
						if (callbackFunction.empty() == false && callbackFunctionScriptIdx == MinitScript::SCRIPTIDX_NONE) {
							callbackFunctionScriptIdx = minitScript->getFunctionScriptIdx(callbackFunction);
						}
						if (callbackFunctionScriptIdx == MinitScript::SCRIPTIDX_NONE) {
							MINITSCRIPT_METHODUSAGE_COMPLAINM(getMethodName(), "Function not found: " + callbackFunction);
						} else {
							for (auto setEntry: *setPtr) {
								vector<MinitScript::Variable> functionArguments { MinitScript::Variable(setEntry) };
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
		minitScript->registerMethod(new MethodSetForEach(minitScript));
	}
	{
		//
		class MethodSetConcatenate: public MinitScript::Method {
		private:
			MinitScript* minitScript { nullptr };
		public:
			MethodSetConcatenate(MinitScript* minitScript):
				MinitScript::Method(
					{
						{ .type = MinitScript::TYPE_SET, .name = "set", .optional = false, .reference = false, .nullable = false },
						{ .type = MinitScript::TYPE_STRING, .name = "separator", .optional = false, .reference = false, .nullable = false },
					},
					MinitScript::TYPE_STRING
				),
				minitScript(minitScript) {}
			const string getMethodName() override {
				return "Set::concatenate";
			}
			void executeMethod(span<MinitScript::Variable>& arguments, MinitScript::Variable& returnValue, const MinitScript::SubStatement& subStatement) override {
				string separator;
				if ((arguments.size() == 2) &&
					arguments[0].getType() == MinitScript::TYPE_SET &&
					MinitScript::getStringValue(arguments, 1, separator) == true) {
					//
					string result;
					auto setPtr = arguments[0].getSetPointer();
					if (setPtr != nullptr) {
						for (auto setKey: *setPtr) {
							if (result.empty() == false) result+= separator;
							result+= setKey;
						}
					}
					returnValue.setValue(result);
				} else {
					MINITSCRIPT_METHODUSAGE_COMPLAIN(getMethodName());
				}
			}
		};
		minitScript->registerMethod(new MethodSetConcatenate(minitScript));
	}
}
