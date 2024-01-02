#include <span>

#include <miniscript/miniscript.h>
#include <miniscript/miniscript/ArrayMethods.h>
#include <miniscript/miniscript/MiniScript.h>
#include <miniscript/utilities/Console.h>

using std::span;

using miniscript::miniscript::ArrayMethods;

using miniscript::miniscript::MiniScript;

using _Console = miniscript::utilities::Console;

void ArrayMethods::registerConstants(MiniScript* miniScript) {
}

void ArrayMethods::registerMethods(MiniScript* miniScript) {
	// array methods
	{
		//
		class MethodArray: public MiniScript::Method {
		private:
			MiniScript* miniScript { nullptr };
		public:
			MethodArray(MiniScript* miniScript):
				MiniScript::Method(
					{},
					MiniScript::TYPE_ARRAY
				),
				miniScript(miniScript) {}
			const string getMethodName() override {
				return "Array";
			}
			bool isVariadic() const override {
				return true;
			}
			void executeMethod(span<MiniScript::Variable>& arguments, MiniScript::Variable& returnValue, const MiniScript::Statement& statement) override {
				returnValue.setType(MiniScript::TYPE_ARRAY);
				for (const auto& argument: arguments) {
					returnValue.pushArrayEntry(argument);
				}
			}
		};
		miniScript->registerMethod(new MethodArray(miniScript));
	}
	{
		//
		class MethodArrayLength: public MiniScript::Method {
		private:
			MiniScript* miniScript { nullptr };
		public:
			MethodArrayLength(MiniScript* miniScript):
				MiniScript::Method(
					{
						{ .type = MiniScript::TYPE_ARRAY, .name = "array", .optional = false, .reference = false, .nullable = false }
					},
					MiniScript::TYPE_INTEGER
				),
				miniScript(miniScript) {}
			const string getMethodName() override {
				return "Array::length";
			}
			void executeMethod(span<MiniScript::Variable>& arguments, MiniScript::Variable& returnValue, const MiniScript::Statement& statement) override {
				if (arguments.size() != 1 || arguments[0].getType() != MiniScript::TYPE_ARRAY) {
					_Console::println(getMethodName() + "(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation(getMethodName()));
					miniScript->startErrorScript();
				} else {
					returnValue.setValue(static_cast<int64_t>(arguments[0].getArraySize()));
				}
			}
		};
		miniScript->registerMethod(new MethodArrayLength(miniScript));
	}
	{
		//
		class MethodArrayPush: public MiniScript::Method {
		private:
			MiniScript* miniScript { nullptr };
		public:
			MethodArrayPush(MiniScript* miniScript):
				MiniScript::Method(
					{
						{ .type = MiniScript::TYPE_ARRAY, .name = "array", .optional = false, .reference = true, .nullable = false }
					},
					MiniScript::TYPE_NULL
				),
				miniScript(miniScript) {}
			const string getMethodName() override {
				return "Array::push";
			}
			bool isVariadic() const override {
				return true;
			}
			void executeMethod(span<MiniScript::Variable>& arguments, MiniScript::Variable& returnValue, const MiniScript::Statement& statement) override {
				//
				if (arguments.size() < 1 || arguments[0].getType() != MiniScript::TYPE_ARRAY) {
					_Console::println(getMethodName() + "(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation(getMethodName()));
					miniScript->startErrorScript();
				} else {
					for (auto i = 1; i < arguments.size(); i++) {
						arguments[0].pushArrayEntry(arguments[i]);
					}
				}
			}
		};
		miniScript->registerMethod(new MethodArrayPush(miniScript));
	}
	{
		//
		class MethodArrayGet: public MiniScript::Method {
		private:
			MiniScript* miniScript { nullptr };
		public:
			MethodArrayGet(MiniScript* miniScript):
				MiniScript::Method(
					{
						{ .type = MiniScript::TYPE_ARRAY, .name = "array", .optional = false, .reference = false, .nullable = false },
						{ .type = MiniScript::TYPE_INTEGER, .name = "index", .optional = false, .reference = false, .nullable = false }
					},
					MiniScript::TYPE_PSEUDO_MIXED
				),
				miniScript(miniScript) {}
			const string getMethodName() override {
				return "Array::get";
			}
			void executeMethod(span<MiniScript::Variable>& arguments, MiniScript::Variable& returnValue, const MiniScript::Statement& statement) override {
				int64_t index;
				if ((arguments.size() <= 1 || arguments[0].getType() != MiniScript::TYPE_ARRAY) ||
					MiniScript::getIntegerValue(arguments, 1, index, false) == false) {
					_Console::println(getMethodName() + "(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation(getMethodName()));
					miniScript->startErrorScript();
				} else {
					returnValue = arguments[0].getArrayEntry(index);
				}
			}
		};
		miniScript->registerMethod(new MethodArrayGet(miniScript));
	}
	{
		//
		class MethodArraySet: public MiniScript::Method {
		private:
			MiniScript* miniScript { nullptr };
		public:
			MethodArraySet(MiniScript* miniScript):
				MiniScript::Method(
					{
						{ .type = MiniScript::TYPE_ARRAY, .name = "array", .optional = false, .reference = true, .nullable = false },
						{ .type = MiniScript::TYPE_INTEGER, .name = "index", .optional = false, .reference = false, .nullable = false },
						{ .type = MiniScript::TYPE_PSEUDO_MIXED, .name = "value", .optional = false, .reference = false, .nullable = false }
					},
					MiniScript::TYPE_NULL
				),
				miniScript(miniScript) {}
			const string getMethodName() override {
				return "Array::set";
			}
			void executeMethod(span<MiniScript::Variable>& arguments, MiniScript::Variable& returnValue, const MiniScript::Statement& statement) override {
				int64_t index;
				if ((arguments.size() <= 2 || arguments[0].getType() != MiniScript::TYPE_ARRAY) ||
					MiniScript::getIntegerValue(arguments, 1, index, false) == false) {
					_Console::println(getMethodName() + "(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation(getMethodName()));
					miniScript->startErrorScript();
				} else {
					arguments[0].setArrayEntry(index, arguments[2]);
				}
			}
		};
		miniScript->registerMethod(new MethodArraySet(miniScript));
	}
	{
		//
		class MethodArrayRemove: public MiniScript::Method {
		private:
			MiniScript* miniScript { nullptr };
		public:
			MethodArrayRemove(MiniScript* miniScript):
				MiniScript::Method(
					{
						{ .type = MiniScript::TYPE_ARRAY, .name = "array", .optional = false, .reference = true, .nullable = false },
						{ .type = MiniScript::TYPE_INTEGER, .name = "index", .optional = false, .reference = false, .nullable = false }
					},
					MiniScript::TYPE_NULL
				),
				miniScript(miniScript) {}
			const string getMethodName() override {
				return "Array::remove";
			}
			void executeMethod(span<MiniScript::Variable>& arguments, MiniScript::Variable& returnValue, const MiniScript::Statement& statement) override {
				int64_t index;
				if ((arguments.size() < 2 || arguments[0].getType() != MiniScript::TYPE_ARRAY) ||
					MiniScript::getIntegerValue(arguments, 1, index, false) == false) {
					_Console::println(getMethodName() + "(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation(getMethodName()));
					miniScript->startErrorScript();
				} else {
					arguments[0].removeArrayEntry(index);
				}
			}
		};
		miniScript->registerMethod(new MethodArrayRemove(miniScript));
	}
	{
		//
		class MethodArrayRemoveOf: public MiniScript::Method {
		private:
			MiniScript* miniScript { nullptr };
		public:
			MethodArrayRemoveOf(MiniScript* miniScript):
				MiniScript::Method(
					{
						{ .type = MiniScript::TYPE_ARRAY, .name = "array", .optional = false, .reference = true, .nullable = false },
						{ .type = MiniScript::TYPE_STRING, .name = "value", .optional = false, .reference = false, .nullable = false },
						{ .type = MiniScript::TYPE_INTEGER, .name = "beginIndex", .optional = true, .reference = false, .nullable = false },
					},
					MiniScript::TYPE_NULL
				),
				miniScript(miniScript) {}
			const string getMethodName() override {
				return "Array::removeOf";
			}
			void executeMethod(span<MiniScript::Variable>& arguments, MiniScript::Variable& returnValue, const MiniScript::Statement& statement) override {
				string stringValue;
				int64_t beginIndex = 0;
				if (arguments.size() < 2 ||
					arguments[0].getType() != MiniScript::TYPE_ARRAY ||
					MiniScript::getStringValue(arguments, 1, stringValue, false) == false ||
					MiniScript::getIntegerValue(arguments, 2, beginIndex, true) == false) {
					_Console::println(getMethodName() + "(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation(getMethodName()));
					miniScript->startErrorScript();
				} else {
					auto& array = arguments[0];
					for (auto i = beginIndex; i < array.getArraySize(); i++) {
						auto arrayValue = array.getArrayEntry(i);
						if (arrayValue.getValueAsString() == stringValue) {
							array.removeArrayEntry(i);
							i--;
						}
					}
				}
			}
		};
		miniScript->registerMethod(new MethodArrayRemoveOf(miniScript));
	}
	{
		//
		class MethodArrayIndexOf: public MiniScript::Method {
		private:
			MiniScript* miniScript { nullptr };
		public:
			MethodArrayIndexOf(MiniScript* miniScript):
				MiniScript::Method(
					{
						{ .type = MiniScript::TYPE_ARRAY, .name = "array", .optional = false, .reference = false, .nullable = false },
						{ .type = MiniScript::TYPE_STRING, .name = "value", .optional = false, .reference = false, .nullable = false },
						{ .type = MiniScript::TYPE_INTEGER, .name = "beginIndex", .optional = true, .reference = false, .nullable = false },
					},
					MiniScript::TYPE_INTEGER
				),
				miniScript(miniScript) {}
			const string getMethodName() override {
				return "Array::indexOf";
			}
			void executeMethod(span<MiniScript::Variable>& arguments, MiniScript::Variable& returnValue, const MiniScript::Statement& statement) override {
				string stringValue;
				int64_t beginIndex = 0;
				if (arguments.size() < 2 ||
					arguments[0].getType() != MiniScript::TYPE_ARRAY ||
					MiniScript::getStringValue(arguments, 1, stringValue, false) == false ||
					MiniScript::getIntegerValue(arguments, 2, beginIndex, true) == false) {
					_Console::println(getMethodName() + "(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation(getMethodName()));
					miniScript->startErrorScript();
				} else {
					const auto& array = arguments[0];
					returnValue.setValue(static_cast<int64_t>(-1));
					for (auto i = beginIndex; i < array.getArraySize(); i++) {
						auto arrayValue = array.getArrayEntry(i);
						if (arrayValue.getValueAsString() == stringValue) {
							returnValue.setValue(static_cast<int64_t>(i));
							break;
						}
					}
				}
			}
		};
		miniScript->registerMethod(new MethodArrayIndexOf(miniScript));
	}
	{
		//
		class MethodArraySort: public MiniScript::Method {
		private:
			MiniScript* miniScript { nullptr };
		public:
			MethodArraySort(MiniScript* miniScript):
				MiniScript::Method(
					{
						{ .type = MiniScript::TYPE_ARRAY, .name = "array", .optional = false, .reference = true, .nullable = false },
						{ .type = MiniScript::TYPE_FUNCTION_ASSIGNMENT, .name = "function", .optional = false, .reference = false, .nullable = false },
					},
					MiniScript::TYPE_NULL
				),
				miniScript(miniScript) {}
			const string getMethodName() override {
				return "Array::sort";
			}
			void executeMethod(span<MiniScript::Variable>& arguments, MiniScript::Variable& returnValue, const MiniScript::Statement& statement) override {
				string function;
				if (arguments.size() != 2 ||
					arguments[0].getType() != MiniScript::TYPE_ARRAY ||
					MiniScript::getStringValue(arguments, 1, function, false) == false) {
					_Console::println(getMethodName() + "(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation(getMethodName()));
					miniScript->startErrorScript();
				} else {
					//
					auto arrayPtr = arguments[0].getArrayPointer();
					if (arrayPtr != nullptr) {
						class SortClass {
							private:
								MiniScript* miniScript;
								const string& function;
							public:
								SortClass(MiniScript* miniScript, const string& function): miniScript(miniScript), function(function) {
								}
								bool operator()(const MiniScript::Variable* a, const MiniScript::Variable* b) const {
									vector<MiniScript::Variable> sortArguments { MiniScript::Variable::createReferenceVariable(a), MiniScript::Variable::createReferenceVariable(b) };
									span sortArgumentsSpan(sortArguments);
									MiniScript::Variable sortReturnValue;
									miniScript->call(function, sortArgumentsSpan, sortReturnValue);
									bool result = false;
									sortReturnValue.getBooleanValue(result, false);
									return result;
								}
						};
						sort(arrayPtr->begin(), arrayPtr->end(), SortClass(miniScript, function));
					}
				}
			}
		};
		miniScript->registerMethod(new MethodArraySort(miniScript));
	}
	{
		//
		class MethodArrayReverse: public MiniScript::Method {
		private:
			MiniScript* miniScript { nullptr };
		public:
			MethodArrayReverse(MiniScript* miniScript):
				MiniScript::Method(
					{
						{ .type = MiniScript::TYPE_ARRAY, .name = "array", .optional = false, .reference = true, .nullable = false }
					},
					MiniScript::TYPE_NULL
				),
				miniScript(miniScript) {}
			const string getMethodName() override {
				return "Array::reverse";
			}
			void executeMethod(span<MiniScript::Variable>& arguments, MiniScript::Variable& returnValue, const MiniScript::Statement& statement) override {
				if (arguments.size() != 1 ||
					arguments[0].getType() != MiniScript::TYPE_ARRAY) {
					_Console::println(getMethodName() + "(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation(getMethodName()));
					miniScript->startErrorScript();
				} else {
					//
					auto arrayPtr = arguments[0].getArrayPointer();
					if (arrayPtr != nullptr) {
						reverse(arrayPtr->begin(), arrayPtr->end());
					}
				}
			}
		};
		miniScript->registerMethod(new MethodArrayReverse(miniScript));
	}
	{
		//
		class MethodArrayClear: public MiniScript::Method {
		private:
			MiniScript* miniScript { nullptr };
		public:
			MethodArrayClear(MiniScript* miniScript):
				MiniScript::Method(
					{
						{ .type = MiniScript::TYPE_ARRAY, .name = "array", .optional = false, .reference = true, .nullable = false }
					},
					MiniScript::TYPE_NULL
				),
				miniScript(miniScript) {}
			const string getMethodName() override {
				return "Array::clear";
			}
			void executeMethod(span<MiniScript::Variable>& arguments, MiniScript::Variable& returnValue, const MiniScript::Statement& statement) override {
				if (arguments.size() != 1 || arguments[0].getType() != MiniScript::TYPE_ARRAY) {
					_Console::println(getMethodName() + "(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation(getMethodName()));
					miniScript->startErrorScript();
				} else {
					arguments[0].clearArray();
				}
			}
		};
		miniScript->registerMethod(new MethodArrayClear(miniScript));
	}
	{
		//
		class MethodArrayForEach: public MiniScript::Method {
		private:
			MiniScript* miniScript { nullptr };
		public:
			MethodArrayForEach(MiniScript* miniScript):
				MiniScript::Method(
					{
						{ .type = MiniScript::TYPE_ARRAY, .name = "array", .optional = false, .reference = false, .nullable = false },
						{ .type = MiniScript::TYPE_FUNCTION_ASSIGNMENT, .name = "function", .optional = false, .reference = false, .nullable = false },
						{ .type = MiniScript::TYPE_PSEUDO_MIXED, .name = "cookie", .optional = true, .reference = true, .nullable = false }
					},
					MiniScript::TYPE_NULL
				),
				miniScript(miniScript) {}
			const string getMethodName() override {
				return "Array::forEach";
			}
			void executeMethod(span<MiniScript::Variable>& arguments, MiniScript::Variable& returnValue, const MiniScript::Statement& statement) override {
				string function;
				if ((arguments.size() != 2 && arguments.size() != 3) ||
					arguments[0].getType() != MiniScript::TYPE_ARRAY ||
					MiniScript::getStringValue(arguments, 1, function, false) == false) {
					_Console::println(getMethodName() + "(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation(getMethodName()));
					miniScript->startErrorScript();
				} else {
					auto arrayPtr = arguments[0].getArrayPointer();
					if (arrayPtr != nullptr) {
						for (auto arrayEntry: *arrayPtr) {
							vector<MiniScript::Variable> functionArguments { MiniScript::Variable::createReferenceVariable(arrayEntry) };
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
		miniScript->registerMethod(new MethodArrayForEach(miniScript));
	}
	{
		//
		class MethodArrayForRange: public MiniScript::Method {
		private:
			MiniScript* miniScript { nullptr };
		public:
			MethodArrayForRange(MiniScript* miniScript):
				MiniScript::Method(
					{
						{ .type = MiniScript::TYPE_ARRAY, .name = "array", .optional = false, .reference = false, .nullable = false },
						{ .type = MiniScript::TYPE_FUNCTION_ASSIGNMENT, .name = "function", .optional = false, .reference = false, .nullable = false },
						{ .type = MiniScript::TYPE_INTEGER, .name = "beginIndex", .optional = false, .reference = false, .nullable = false },
						{ .type = MiniScript::TYPE_INTEGER, .name = "count", .optional = true, .reference = false, .nullable = false },
						{ .type = MiniScript::TYPE_INTEGER, .name = "step", .optional = true, .reference = false, .nullable = false },
						{ .type = MiniScript::TYPE_PSEUDO_MIXED, .name = "cookie", .optional = true, .reference = true, .nullable = false }
					},
					MiniScript::TYPE_NULL
				),
				miniScript(miniScript) {}
			const string getMethodName() override {
				return "Array::forRange";
			}
			void executeMethod(span<MiniScript::Variable>& arguments, MiniScript::Variable& returnValue, const MiniScript::Statement& statement) override {
				string function;
				int64_t beginIndex;
				int64_t count = -1ll;
				int64_t step = 1ll;
				if (arguments.size() < 3 ||
					arguments.size() > 6 ||
					arguments[0].getType() != MiniScript::TYPE_ARRAY ||
					MiniScript::getStringValue(arguments, 1, function, false) == false ||
					MiniScript::getIntegerValue(arguments, 2, beginIndex, true) == false ||
					MiniScript::getIntegerValue(arguments, 3, count, true) == false ||
					MiniScript::getIntegerValue(arguments, 4, step, true) == false) {
					_Console::println(getMethodName() + "(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation(getMethodName()));
					miniScript->startErrorScript();
				} else {
					auto arrayPtr = arguments[0].getArrayPointer();
					if (arrayPtr != nullptr) {
						auto counter = 0;
						for (auto i = beginIndex; i >= 0 && counter < count && i < arrayPtr->size(); i+= step) {
							auto arrayEntry = (*arrayPtr)[i];
							vector<MiniScript::Variable> functionArguments { MiniScript::Variable::createReferenceVariable(arrayEntry) };
							if (arguments.size() == 6) functionArguments.push_back(arguments[5]);
							span functionArgumentsSpan(functionArguments);
							MiniScript::Variable functionReturnValue;
							miniScript->call(function, functionArgumentsSpan, functionReturnValue);
							// exit condition
							bool result = false;
							functionReturnValue.getBooleanValue(result, false);
							if (result == true) break;
							//
							counter++;
						}
					}
				}
			}
		};
		miniScript->registerMethod(new MethodArrayForRange(miniScript));
	}
}
