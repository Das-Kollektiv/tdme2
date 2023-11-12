#include <span>

#include <tdme/tdme.h>
#include <tdme/utilities/MiniScript.h>
#include <tdme/utilities/MiniScriptArray.h>

using std::span;

using tdme::utilities::MiniScriptArray;

using tdme::utilities::MiniScript;

void MiniScriptArray::registerMethods(MiniScript* miniScript) {
	// array methods
	{
		//
		class ScriptMethodArray: public MiniScript::ScriptMethod {
		private:
			MiniScript* miniScript { nullptr };
		public:
			ScriptMethodArray(MiniScript* miniScript):
				MiniScript::ScriptMethod(
					{},
					MiniScript::ScriptVariableType::TYPE_ARRAY
				),
				miniScript(miniScript) {}
			const string getMethodName() override {
				return "array";
			}
			bool isVariadic() const override {
				return true;
			}
			void executeMethod(span<MiniScript::ScriptVariable>& argumentValues, MiniScript::ScriptVariable& returnValue, const MiniScript::ScriptStatement& statement) override {
				returnValue.setType(MiniScript::TYPE_ARRAY);
				for (const auto& argumentValue: argumentValues) {
					returnValue.pushArrayEntry(argumentValue);
				}
			}
		};
		miniScript->registerMethod(new ScriptMethodArray(miniScript));
	}
	{
		//
		class ScriptMethodArrayLength: public MiniScript::ScriptMethod {
		private:
			MiniScript* miniScript { nullptr };
		public:
			ScriptMethodArrayLength(MiniScript* miniScript):
				MiniScript::ScriptMethod(
					{
						{ .type = MiniScript::ScriptVariableType::TYPE_ARRAY, .name = "array", .optional = false, .reference = false, .nullable = false }
					},
					MiniScript::ScriptVariableType::TYPE_INTEGER
				),
				miniScript(miniScript) {}
			const string getMethodName() override {
				return "array.length";
			}
			void executeMethod(span<MiniScript::ScriptVariable>& argumentValues, MiniScript::ScriptVariable& returnValue, const MiniScript::ScriptStatement& statement) override {
				if (argumentValues.size() != 1 || argumentValues[0].getType() != MiniScript::ScriptVariableType::TYPE_ARRAY) {
					Console::println(getMethodName() + "(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation(getMethodName()));
					miniScript->startErrorScript();
				} else {
					returnValue.setValue(static_cast<int64_t>(argumentValues[0].getArraySize()));
				}
			}
		};
		miniScript->registerMethod(new ScriptMethodArrayLength(miniScript));
	}
	{
		//
		class ScriptMethodArrayPush: public MiniScript::ScriptMethod {
		private:
			MiniScript* miniScript { nullptr };
		public:
			ScriptMethodArrayPush(MiniScript* miniScript):
				MiniScript::ScriptMethod(
					{
						{ .type = MiniScript::ScriptVariableType::TYPE_ARRAY, .name = "array", .optional = false, .reference = true, .nullable = false }
					},
					MiniScript::ScriptVariableType::TYPE_NULL
				),
				miniScript(miniScript) {}
			const string getMethodName() override {
				return "array.push";
			}
			bool isVariadic() const override {
				return true;
			}
			void executeMethod(span<MiniScript::ScriptVariable>& argumentValues, MiniScript::ScriptVariable& returnValue, const MiniScript::ScriptStatement& statement) override {
				//
				if (argumentValues.size() < 1 || argumentValues[0].getType() != MiniScript::ScriptVariableType::TYPE_ARRAY) {
					Console::println(getMethodName() + "(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation(getMethodName()));
					miniScript->startErrorScript();
				} else {
					for (auto i = 1; i < argumentValues.size(); i++) {
						argumentValues[0].pushArrayEntry(argumentValues[i]);
					}
				}
			}
		};
		miniScript->registerMethod(new ScriptMethodArrayPush(miniScript));
	}
	{
		//
		class ScriptMethodArrayGet: public MiniScript::ScriptMethod {
		private:
			MiniScript* miniScript { nullptr };
		public:
			ScriptMethodArrayGet(MiniScript* miniScript):
				MiniScript::ScriptMethod(
					{
						{ .type = MiniScript::ScriptVariableType::TYPE_ARRAY, .name = "array", .optional = false, .reference = false, .nullable = false },
						{ .type = MiniScript::ScriptVariableType::TYPE_INTEGER, .name = "index", .optional = false, .reference = false, .nullable = false }
					},
					MiniScript::ScriptVariableType::TYPE_PSEUDO_MIXED
				),
				miniScript(miniScript) {}
			const string getMethodName() override {
				return "array.get";
			}
			void executeMethod(span<MiniScript::ScriptVariable>& argumentValues, MiniScript::ScriptVariable& returnValue, const MiniScript::ScriptStatement& statement) override {
				int64_t index;
				if ((argumentValues.size() <= 1 || argumentValues[0].getType() != MiniScript::ScriptVariableType::TYPE_ARRAY) ||
					MiniScript::getIntegerValue(argumentValues, 1, index, false) == false) {
					Console::println(getMethodName() + "(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation(getMethodName()));
					miniScript->startErrorScript();
				} else {
					returnValue = argumentValues[0].getArrayEntry(index);
				}
			}
		};
		miniScript->registerMethod(new ScriptMethodArrayGet(miniScript));
	}
	{
		//
		class ScriptMethodArraySet: public MiniScript::ScriptMethod {
		private:
			MiniScript* miniScript { nullptr };
		public:
			ScriptMethodArraySet(MiniScript* miniScript):
				MiniScript::ScriptMethod(
					{
						{ .type = MiniScript::ScriptVariableType::TYPE_ARRAY, .name = "array", .optional = false, .reference = true, .nullable = false },
						{ .type = MiniScript::ScriptVariableType::TYPE_INTEGER, .name = "index", .optional = false, .reference = false, .nullable = false },
						{ .type = MiniScript::ScriptVariableType::TYPE_PSEUDO_MIXED, .name = "value", .optional = false, .reference = false, .nullable = false }
					},
					MiniScript::ScriptVariableType::TYPE_NULL
				),
				miniScript(miniScript) {}
			const string getMethodName() override {
				return "array.set";
			}
			void executeMethod(span<MiniScript::ScriptVariable>& argumentValues, MiniScript::ScriptVariable& returnValue, const MiniScript::ScriptStatement& statement) override {
				int64_t index;
				if ((argumentValues.size() <= 2 || argumentValues[0].getType() != MiniScript::ScriptVariableType::TYPE_ARRAY) ||
					MiniScript::getIntegerValue(argumentValues, 1, index, false) == false) {
					Console::println(getMethodName() + "(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation(getMethodName()));
					miniScript->startErrorScript();
				} else {
					argumentValues[0].setArrayEntry(index, argumentValues[2]);
				}
			}
		};
		miniScript->registerMethod(new ScriptMethodArraySet(miniScript));
	}
	{
		//
		class ScriptMethodArrayRemove: public MiniScript::ScriptMethod {
		private:
			MiniScript* miniScript { nullptr };
		public:
			ScriptMethodArrayRemove(MiniScript* miniScript):
				MiniScript::ScriptMethod(
					{
						{ .type = MiniScript::ScriptVariableType::TYPE_ARRAY, .name = "array", .optional = false, .reference = true, .nullable = false },
						{ .type = MiniScript::ScriptVariableType::TYPE_INTEGER, .name = "index", .optional = false, .reference = false, .nullable = false }
					},
					MiniScript::ScriptVariableType::TYPE_NULL
				),
				miniScript(miniScript) {}
			const string getMethodName() override {
				return "array.remove";
			}
			void executeMethod(span<MiniScript::ScriptVariable>& argumentValues, MiniScript::ScriptVariable& returnValue, const MiniScript::ScriptStatement& statement) override {
				int64_t index;
				if ((argumentValues.size() < 2 || argumentValues[0].getType() != MiniScript::ScriptVariableType::TYPE_ARRAY) ||
					MiniScript::getIntegerValue(argumentValues, 1, index, false) == false) {
					Console::println(getMethodName() + "(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation(getMethodName()));
					miniScript->startErrorScript();
				} else {
					argumentValues[0].removeArrayEntry(index);
				}
			}
		};
		miniScript->registerMethod(new ScriptMethodArrayRemove(miniScript));
	}
	{
		//
		class ScriptMethodArrayRemoveOf: public MiniScript::ScriptMethod {
		private:
			MiniScript* miniScript { nullptr };
		public:
			ScriptMethodArrayRemoveOf(MiniScript* miniScript):
				MiniScript::ScriptMethod(
					{
						{ .type = MiniScript::ScriptVariableType::TYPE_ARRAY, .name = "array", .optional = false, .reference = true, .nullable = false },
						{ .type = MiniScript::ScriptVariableType::TYPE_STRING, .name = "value", .optional = false, .reference = false, .nullable = false },
						{ .type = MiniScript::ScriptVariableType::TYPE_INTEGER, .name = "beginIndex", .optional = true, .reference = false, .nullable = false },
					},
					MiniScript::ScriptVariableType::TYPE_NULL
				),
				miniScript(miniScript) {}
			const string getMethodName() override {
				return "array.removeOf";
			}
			void executeMethod(span<MiniScript::ScriptVariable>& argumentValues, MiniScript::ScriptVariable& returnValue, const MiniScript::ScriptStatement& statement) override {
				string stringValue;
				int64_t beginIndex = 0;
				if (argumentValues.size() < 2 ||
					argumentValues[0].getType() != MiniScript::ScriptVariableType::TYPE_ARRAY ||
					MiniScript::getStringValue(argumentValues, 1, stringValue, false) == false ||
					MiniScript::getIntegerValue(argumentValues, 2, beginIndex, true) == false) {
					Console::println(getMethodName() + "(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation(getMethodName()));
					miniScript->startErrorScript();
				} else {
					auto& array = argumentValues[0];
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
		miniScript->registerMethod(new ScriptMethodArrayRemoveOf(miniScript));
	}
	{
		//
		class ScriptMethodArrayIndexOf: public MiniScript::ScriptMethod {
		private:
			MiniScript* miniScript { nullptr };
		public:
			ScriptMethodArrayIndexOf(MiniScript* miniScript):
				MiniScript::ScriptMethod(
					{
						{ .type = MiniScript::ScriptVariableType::TYPE_ARRAY, .name = "array", .optional = false, .reference = false, .nullable = false },
						{ .type = MiniScript::ScriptVariableType::TYPE_STRING, .name = "value", .optional = false, .reference = false, .nullable = false },
						{ .type = MiniScript::ScriptVariableType::TYPE_INTEGER, .name = "beginIndex", .optional = true, .reference = false, .nullable = false },
					},
					MiniScript::ScriptVariableType::TYPE_INTEGER
				),
				miniScript(miniScript) {}
			const string getMethodName() override {
				return "array.indexOf";
			}
			void executeMethod(span<MiniScript::ScriptVariable>& argumentValues, MiniScript::ScriptVariable& returnValue, const MiniScript::ScriptStatement& statement) override {
				string stringValue;
				int64_t beginIndex = 0;
				if (argumentValues.size() < 2 ||
					argumentValues[0].getType() != MiniScript::ScriptVariableType::TYPE_ARRAY ||
					MiniScript::getStringValue(argumentValues, 1, stringValue, false) == false ||
					MiniScript::getIntegerValue(argumentValues, 2, beginIndex, true) == false) {
					Console::println(getMethodName() + "(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation(getMethodName()));
					miniScript->startErrorScript();
				} else {
					const auto& array = argumentValues[0];
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
		miniScript->registerMethod(new ScriptMethodArrayIndexOf(miniScript));
	}
	{
		//
		class ScriptMethodArraySort: public MiniScript::ScriptMethod {
		private:
			MiniScript* miniScript { nullptr };
		public:
			ScriptMethodArraySort(MiniScript* miniScript):
				MiniScript::ScriptMethod(
					{
						{ .type = MiniScript::ScriptVariableType::TYPE_ARRAY, .name = "array", .optional = false, .reference = true, .nullable = false },
						{ .type = MiniScript::ScriptVariableType::TYPE_STRING, .name = "function", .optional = false, .reference = false, .nullable = false },
					},
					MiniScript::ScriptVariableType::TYPE_NULL
				),
				miniScript(miniScript) {}
			const string getMethodName() override {
				return "array.sort";
			}
			void executeMethod(span<MiniScript::ScriptVariable>& argumentValues, MiniScript::ScriptVariable& returnValue, const MiniScript::ScriptStatement& statement) override {
				string function;
				if (argumentValues.size() != 2 ||
					argumentValues[0].getType() != MiniScript::ScriptVariableType::TYPE_ARRAY ||
					MiniScript::getStringValue(argumentValues, 1, function, false) == false) {
					Console::println(getMethodName() + "(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation(getMethodName()));
					miniScript->startErrorScript();
				} else {
					//
					auto arrayPtr = argumentValues[0].getArrayPointer();
					if (arrayPtr != nullptr) {
						class SortClass {
							private:
								MiniScript* miniScript;
								const string& function;
							public:
								SortClass(MiniScript* miniScript, const string& function): miniScript(miniScript), function(function) {
								}
								bool operator()(const MiniScript::MiniScript::ScriptVariable* a, const MiniScript::MiniScript::ScriptVariable* b) const {
									vector<MiniScript::MiniScript::ScriptVariable> sortArgumentValues { *a, *b };
									span sortArgumentValuesSpan(sortArgumentValues);
									MiniScript::MiniScript::ScriptVariable sortReturnValue;
									miniScript->call(function, sortArgumentValuesSpan, sortReturnValue);
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
		miniScript->registerMethod(new ScriptMethodArraySort(miniScript));
	}
	{
		//
		class ScriptMethodArrayReverse: public MiniScript::ScriptMethod {
		private:
			MiniScript* miniScript { nullptr };
		public:
			ScriptMethodArrayReverse(MiniScript* miniScript):
				MiniScript::ScriptMethod(
					{
						{ .type = MiniScript::ScriptVariableType::TYPE_ARRAY, .name = "array", .optional = false, .reference = true, .nullable = false }
					},
					MiniScript::ScriptVariableType::TYPE_NULL
				),
				miniScript(miniScript) {}
			const string getMethodName() override {
				return "array.reverse";
			}
			void executeMethod(span<MiniScript::ScriptVariable>& argumentValues, MiniScript::ScriptVariable& returnValue, const MiniScript::ScriptStatement& statement) override {
				if (argumentValues.size() != 1 ||
					argumentValues[0].getType() != MiniScript::ScriptVariableType::TYPE_ARRAY) {
					Console::println(getMethodName() + "(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation(getMethodName()));
					miniScript->startErrorScript();
				} else {
					//
					auto arrayPtr = argumentValues[0].getArrayPointer();
					if (arrayPtr != nullptr) {
						reverse(arrayPtr->begin(), arrayPtr->end());
					}
				}
			}
		};
		miniScript->registerMethod(new ScriptMethodArrayReverse(miniScript));
	}
}
