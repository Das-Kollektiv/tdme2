#include <span>

#include <minitscript/minitscript.h>
#include <minitscript/minitscript/ArrayMethods.h>
#include <minitscript/minitscript/MinitScript.h>
#include <minitscript/utilities/Console.h>

using std::span;

using minitscript::minitscript::ArrayMethods;

using minitscript::minitscript::MinitScript;

using _Console = minitscript::utilities::Console;

void ArrayMethods::registerConstants(MinitScript* minitScript) {
}

void ArrayMethods::registerMethods(MinitScript* minitScript) {
	// array methods
	{
		//
		class MethodArray: public MinitScript::Method {
		private:
			MinitScript* minitScript { nullptr };
		public:
			MethodArray(MinitScript* minitScript):
				MinitScript::Method(
					{},
					MinitScript::TYPE_ARRAY
				),
				minitScript(minitScript) {}
			const string getMethodName() override {
				return "Array";
			}
			bool isVariadic() const override {
				return true;
			}
			void executeMethod(span<MinitScript::Variable>& arguments, MinitScript::Variable& returnValue, const MinitScript::SubStatement& subStatement) override {
				returnValue.setType(MinitScript::TYPE_ARRAY);
				for (const auto& argument: arguments) {
					returnValue.pushArrayEntry(MinitScript::Variable::createNonReferenceVariable(&argument));
				}
			}
		};
		minitScript->registerMethod(new MethodArray(minitScript));
	}
	{
		//
		class MethodArrayGetSize: public MinitScript::Method {
		private:
			MinitScript* minitScript { nullptr };
		public:
			MethodArrayGetSize(MinitScript* minitScript):
				MinitScript::Method(
					{
						{ .type = MinitScript::TYPE_ARRAY, .name = "array", .optional = false, .reference = false, .nullable = false }
					},
					MinitScript::TYPE_INTEGER
				),
				minitScript(minitScript) {}
			const string getMethodName() override {
				return "Array::getSize";
			}
			void executeMethod(span<MinitScript::Variable>& arguments, MinitScript::Variable& returnValue, const MinitScript::SubStatement& subStatement) override {
				if (arguments.size() == 1 &&
					arguments[0].getType() == MinitScript::TYPE_ARRAY) {
					returnValue.setValue(static_cast<int64_t>(arguments[0].getArraySize()));
				} else {
					MINITSCRIPT_METHODUSAGE_COMPLAIN(getMethodName());
				}
			}
		};
		minitScript->registerMethod(new MethodArrayGetSize(minitScript));
	}
	{
		//
		class MethodArrayIsEmpty: public MinitScript::Method {
		private:
			MinitScript* minitScript { nullptr };
		public:
			MethodArrayIsEmpty(MinitScript* minitScript):
				MinitScript::Method(
					{
						{ .type = MinitScript::TYPE_ARRAY, .name = "array", .optional = false, .reference = false, .nullable = false }
					},
					MinitScript::TYPE_BOOLEAN
				),
				minitScript(minitScript) {}
			const string getMethodName() override {
				return "Array::isEmpty";
			}
			void executeMethod(span<MinitScript::Variable>& arguments, MinitScript::Variable& returnValue, const MinitScript::SubStatement& subStatement) override {
				if (arguments.size() == 1 &&
					arguments[0].getType() == MinitScript::TYPE_ARRAY) {
					returnValue.setValue(arguments[0].getArraySize() == 0);
				} else {
					MINITSCRIPT_METHODUSAGE_COMPLAIN(getMethodName());
				}
			}
		};
		minitScript->registerMethod(new MethodArrayIsEmpty(minitScript));
	}
	{
		//
		class MethodArrayPush: public MinitScript::Method {
		private:
			MinitScript* minitScript { nullptr };
		public:
			MethodArrayPush(MinitScript* minitScript):
				MinitScript::Method(
					{
						{ .type = MinitScript::TYPE_ARRAY, .name = "array", .optional = false, .reference = true, .nullable = false }
					},
					MinitScript::TYPE_NULL
				),
				minitScript(minitScript) {}
			const string getMethodName() override {
				return "Array::push";
			}
			bool isVariadic() const override {
				return true;
			}
			void executeMethod(span<MinitScript::Variable>& arguments, MinitScript::Variable& returnValue, const MinitScript::SubStatement& subStatement) override {
				//
				if (arguments.size() > 1 &&
					arguments[0].getType() == MinitScript::TYPE_ARRAY) {
					for (auto i = 1; i < arguments.size(); i++) {
						arguments[0].pushArrayEntry(MinitScript::Variable::createNonReferenceVariable(&arguments[i]));
					}
				} else {
					MINITSCRIPT_METHODUSAGE_COMPLAIN(getMethodName());
				}
			}
		};
		minitScript->registerMethod(new MethodArrayPush(minitScript));
	}
	{
		//
		class MethodArrayGet: public MinitScript::Method {
		private:
			MinitScript* minitScript { nullptr };
		public:
			MethodArrayGet(MinitScript* minitScript):
				MinitScript::Method(
					{
						{ .type = MinitScript::TYPE_ARRAY, .name = "array", .optional = false, .reference = false, .nullable = false },
						{ .type = MinitScript::TYPE_INTEGER, .name = "index", .optional = false, .reference = false, .nullable = false }
					},
					MinitScript::TYPE_PSEUDO_MIXED
				),
				minitScript(minitScript) {}
			const string getMethodName() override {
				return "Array::get";
			}
			void executeMethod(span<MinitScript::Variable>& arguments, MinitScript::Variable& returnValue, const MinitScript::SubStatement& subStatement) override {
				int64_t index;
				if (arguments.size() == 2 &&
					arguments[0].getType() == MinitScript::TYPE_ARRAY &&
					MinitScript::getIntegerValue(arguments, 1, index) == true) {
					returnValue.setValue(arguments[0].getArrayEntry(index));
				} else {
					MINITSCRIPT_METHODUSAGE_COMPLAIN(getMethodName());
				}
			}
		};
		minitScript->registerMethod(new MethodArrayGet(minitScript));
	}
	{
		//
		class MethodArraySet: public MinitScript::Method {
		private:
			MinitScript* minitScript { nullptr };
		public:
			MethodArraySet(MinitScript* minitScript):
				MinitScript::Method(
					{
						{ .type = MinitScript::TYPE_ARRAY, .name = "array", .optional = false, .reference = true, .nullable = false },
						{ .type = MinitScript::TYPE_INTEGER, .name = "index", .optional = false, .reference = false, .nullable = false },
						{ .type = MinitScript::TYPE_PSEUDO_MIXED, .name = "value", .optional = false, .reference = false, .nullable = false }
					},
					MinitScript::TYPE_NULL
				),
				minitScript(minitScript) {}
			const string getMethodName() override {
				return "Array::set";
			}
			void executeMethod(span<MinitScript::Variable>& arguments, MinitScript::Variable& returnValue, const MinitScript::SubStatement& subStatement) override {
				int64_t index;
				if (arguments.size() == 3 &&
					arguments[0].getType() == MinitScript::TYPE_ARRAY &&
					MinitScript::getIntegerValue(arguments, 1, index) == true) {
					arguments[0].setArrayEntry(index, MinitScript::Variable::createNonReferenceVariable(&arguments[2]));
				} else {
					MINITSCRIPT_METHODUSAGE_COMPLAIN(getMethodName());
				}
			}
		};
		minitScript->registerMethod(new MethodArraySet(minitScript));
	}
	{
		//
		class MethodArrayRemove: public MinitScript::Method {
		private:
			MinitScript* minitScript { nullptr };
		public:
			MethodArrayRemove(MinitScript* minitScript):
				MinitScript::Method(
					{
						{ .type = MinitScript::TYPE_ARRAY, .name = "array", .optional = false, .reference = true, .nullable = false },
						{ .type = MinitScript::TYPE_INTEGER, .name = "index", .optional = false, .reference = false, .nullable = false }
					},
					MinitScript::TYPE_NULL
				),
				minitScript(minitScript) {}
			const string getMethodName() override {
				return "Array::remove";
			}
			void executeMethod(span<MinitScript::Variable>& arguments, MinitScript::Variable& returnValue, const MinitScript::SubStatement& subStatement) override {
				int64_t index;
				if (arguments.size() == 2 &&
					arguments[0].getType() == MinitScript::TYPE_ARRAY &&
					MinitScript::getIntegerValue(arguments, 1, index) == true) {
					arguments[0].removeArrayEntry(index);
					arguments[0].computeArraySubType();
				} else {
					MINITSCRIPT_METHODUSAGE_COMPLAIN(getMethodName());
				}
			}
		};
		minitScript->registerMethod(new MethodArrayRemove(minitScript));
	}
	{
		//
		class MethodArrayRemoveOf: public MinitScript::Method {
		private:
			MinitScript* minitScript { nullptr };
		public:
			MethodArrayRemoveOf(MinitScript* minitScript):
				MinitScript::Method(
					{
						{ .type = MinitScript::TYPE_ARRAY, .name = "array", .optional = false, .reference = true, .nullable = false },
						{ .type = MinitScript::TYPE_STRING, .name = "value", .optional = false, .reference = false, .nullable = false },
						{ .type = MinitScript::TYPE_INTEGER, .name = "beginIndex", .optional = true, .reference = false, .nullable = false },
					},
					MinitScript::TYPE_NULL
				),
				minitScript(minitScript) {}
			const string getMethodName() override {
				return "Array::removeOf";
			}
			void executeMethod(span<MinitScript::Variable>& arguments, MinitScript::Variable& returnValue, const MinitScript::SubStatement& subStatement) override {
				string stringValue;
				int64_t beginIndex = 0;
				if ((arguments.size() == 2 || arguments.size() == 3) &&
					arguments[0].getType() == MinitScript::TYPE_ARRAY &&
					MinitScript::getStringValue(arguments, 1, stringValue) == true &&
					MinitScript::getIntegerValue(arguments, 2, beginIndex, true) == true) {
					auto& array = arguments[0];
					for (auto i = beginIndex; i < array.getArraySize(); i++) {
						auto arrayValue = array.getArrayEntry(i);
						if (arrayValue.getValueAsString() == stringValue) {
							array.removeArrayEntry(i);
							i--;
						}
					}
					arguments[0].computeArraySubType();
				} else {
					MINITSCRIPT_METHODUSAGE_COMPLAIN(getMethodName());
				}
			}
		};
		minitScript->registerMethod(new MethodArrayRemoveOf(minitScript));
	}
	{
		//
		class MethodArrayIndexOf: public MinitScript::Method {
		private:
			MinitScript* minitScript { nullptr };
		public:
			MethodArrayIndexOf(MinitScript* minitScript):
				MinitScript::Method(
					{
						{ .type = MinitScript::TYPE_ARRAY, .name = "array", .optional = false, .reference = false, .nullable = false },
						{ .type = MinitScript::TYPE_STRING, .name = "value", .optional = false, .reference = false, .nullable = false },
						{ .type = MinitScript::TYPE_INTEGER, .name = "beginIndex", .optional = true, .reference = false, .nullable = false },
					},
					MinitScript::TYPE_INTEGER
				),
				minitScript(minitScript) {}
			const string getMethodName() override {
				return "Array::indexOf";
			}
			void executeMethod(span<MinitScript::Variable>& arguments, MinitScript::Variable& returnValue, const MinitScript::SubStatement& subStatement) override {
				string stringValue;
				int64_t beginIndex = 0;
				if ((arguments.size() == 2 || arguments.size() == 3) &&
					arguments[0].getType() == MinitScript::TYPE_ARRAY &&
					MinitScript::getStringValue(arguments, 1, stringValue) == true &&
					MinitScript::getIntegerValue(arguments, 2, beginIndex, true) == true) {
					const auto& array = arguments[0];
					returnValue.setValue(static_cast<int64_t>(-1));
					for (auto i = beginIndex; i < array.getArraySize(); i++) {
						auto arrayValue = array.getArrayEntry(i);
						if (arrayValue.getValueAsString() == stringValue) {
							returnValue.setValue(static_cast<int64_t>(i));
							break;
						}
					}
				} else {
					MINITSCRIPT_METHODUSAGE_COMPLAIN(getMethodName());
				}
			}
		};
		minitScript->registerMethod(new MethodArrayIndexOf(minitScript));
	}
	{
		//
		class MethodArraySortAscending: public MinitScript::Method {
		private:
			MinitScript* minitScript { nullptr };
		public:
			MethodArraySortAscending(MinitScript* minitScript):
				MinitScript::Method(
					{
						{ .type = MinitScript::TYPE_ARRAY, .name = "array", .optional = false, .reference = true, .nullable = false },
					},
					MinitScript::TYPE_NULL
				),
				minitScript(minitScript) {}
			const string getMethodName() override {
				return "Array::sortAscending";
			}
			void executeMethod(span<MinitScript::Variable>& arguments, MinitScript::Variable& returnValue, const MinitScript::SubStatement& subStatement) override {
				if (arguments.size() == 1 &&
					arguments[0].getType() == MinitScript::TYPE_ARRAY) {
					auto arrayPtr = arguments[0].getArrayPointer();
					if (arrayPtr != nullptr) {
						switch (arguments[0].getArraySubType()) {
							case MinitScript::Variable::ARRAY_SUBTYPE_BOOLEAN:
							case MinitScript::Variable::ARRAY_SUBTYPE_INTEGER:
								{
									class SortClass {
									public:
										SortClass() {
										}
										bool operator()(const MinitScript::Variable* a, const MinitScript::Variable* b) const {
											return a->getIntegerValueReference() < b->getIntegerValueReference();
										}
									};
									sort(arrayPtr->begin(), arrayPtr->end(), SortClass());
									break;
								}
							case MinitScript::Variable::ARRAY_SUBTYPE_FLOAT:
								{
									class SortClass {
									public:
										SortClass() {
										}
										bool operator()(const MinitScript::Variable* a, const MinitScript::Variable* b) const {
											auto _a = 0.0f;
											auto _b = 0.0f;
											a->getFloatValue(_a, true);
											b->getFloatValue(_b, true);
											return _a < _b;
										}
									};
									sort(arrayPtr->begin(), arrayPtr->end(), SortClass());
									break;
								}
							case MinitScript::Variable::ARRAY_SUBTYPE_MIXED:
								{
									class SortClass {
									public:
										SortClass() {
										}
										bool operator()(const MinitScript::Variable* a, const MinitScript::Variable* b) const {
											return a->getValueAsString() < b->getValueAsString();
										}
									};
									sort(arrayPtr->begin(), arrayPtr->end(), SortClass());
									break;
								}
						}
					}
				} else {
					MINITSCRIPT_METHODUSAGE_COMPLAIN(getMethodName());
				}
			}
		};
		minitScript->registerMethod(new MethodArraySortAscending(minitScript));
	}
	{
		//
		class MethodArraySortDescending: public MinitScript::Method {
		private:
			MinitScript* minitScript { nullptr };
		public:
			MethodArraySortDescending(MinitScript* minitScript):
				MinitScript::Method(
					{
						{ .type = MinitScript::TYPE_ARRAY, .name = "array", .optional = false, .reference = true, .nullable = false },
					},
					MinitScript::TYPE_NULL
				),
				minitScript(minitScript) {}
			const string getMethodName() override {
				return "Array::sortDescending";
			}
			void executeMethod(span<MinitScript::Variable>& arguments, MinitScript::Variable& returnValue, const MinitScript::SubStatement& subStatement) override {
				if (arguments.size() == 1 &&
					arguments[0].getType() == MinitScript::TYPE_ARRAY) {
					auto arrayPtr = arguments[0].getArrayPointer();
					if (arrayPtr != nullptr) {
						switch (arguments[0].getArraySubType()) {
							case MinitScript::Variable::ARRAY_SUBTYPE_BOOLEAN:
							case MinitScript::Variable::ARRAY_SUBTYPE_INTEGER:
								{
									class SortClass {
									public:
										SortClass() {
										}
										bool operator()(const MinitScript::Variable* a, const MinitScript::Variable* b) const {
											return a->getIntegerValueReference() > b->getIntegerValueReference();
										}
									};
									sort(arrayPtr->begin(), arrayPtr->end(), SortClass());
									break;
								}
							case MinitScript::Variable::ARRAY_SUBTYPE_FLOAT:
								{
									class SortClass {
									public:
										SortClass() {
										}
										bool operator()(const MinitScript::Variable* a, const MinitScript::Variable* b) const {
											auto _a = 0.0f;
											auto _b = 0.0f;
											a->getFloatValue(_a, true);
											b->getFloatValue(_b, true);
											return _a > _b;
										}
									};
									sort(arrayPtr->begin(), arrayPtr->end(), SortClass());
									break;
								}
							case MinitScript::Variable::ARRAY_SUBTYPE_MIXED:
								{
									class SortClass {
									public:
										SortClass() {
										}
										bool operator()(const MinitScript::Variable* a, const MinitScript::Variable* b) const {
											return a->getValueAsString() > b->getValueAsString();
										}
									};
									sort(arrayPtr->begin(), arrayPtr->end(), SortClass());
									break;
								}
						}
					}
				} else {
					MINITSCRIPT_METHODUSAGE_COMPLAIN(getMethodName());
				}
			}
		};
		minitScript->registerMethod(new MethodArraySortDescending(minitScript));
	}
	{
		//
		class MethodArraySort: public MinitScript::Method {
		private:
			MinitScript* minitScript { nullptr };
		public:
			MethodArraySort(MinitScript* minitScript):
				MinitScript::Method(
					{
						{ .type = MinitScript::TYPE_ARRAY, .name = "array", .optional = false, .reference = true, .nullable = false },
						{ .type = MinitScript::TYPE_FUNCTION_ASSIGNMENT, .name = "sortFunction", .optional = false, .reference = false, .nullable = false },
					},
					MinitScript::TYPE_NULL
				),
				minitScript(minitScript) {}
			const string getMethodName() override {
				return "Array::sort";
			}
			void executeMethod(span<MinitScript::Variable>& arguments, MinitScript::Variable& returnValue, const MinitScript::SubStatement& subStatement) override {
				string sortFunction;
				int sortFunctionScriptIdx;
				if (arguments.size() == 2 &&
					arguments[0].getType() == MinitScript::TYPE_ARRAY &&
					MinitScript::getFunctionValue(arguments, 1, sortFunction, sortFunctionScriptIdx) == true) {
					auto arrayPtr = arguments[0].getArrayPointer();
					if (arrayPtr != nullptr) {
						if (sortFunction.empty() == false && sortFunctionScriptIdx == MinitScript::SCRIPTIDX_NONE) {
							sortFunctionScriptIdx = minitScript->getFunctionScriptIdx(sortFunction);
						}
						if (sortFunctionScriptIdx == MinitScript::SCRIPTIDX_NONE) {
							MINITSCRIPT_METHODUSAGE_COMPLAINM(getMethodName(), "Function not found: " + sortFunction);
						} else {
							class SortClass {
								private:
									MinitScript* minitScript;
									int sortFunctionScriptIdx;
								public:
									SortClass(MinitScript* minitScript, int sortFunctionScriptIdx): minitScript(minitScript), sortFunctionScriptIdx(sortFunctionScriptIdx) {
									}
									bool operator()(const MinitScript::Variable* a, const MinitScript::Variable* b) const {
										vector<MinitScript::Variable> sortArguments { MinitScript::Variable::createReferenceVariable(a), MinitScript::Variable::createReferenceVariable(b) };
										span sortArgumentsSpan(sortArguments);
										MinitScript::Variable sortReturnValue;
										minitScript->call(sortFunctionScriptIdx, sortArgumentsSpan, sortReturnValue);
										bool result = false;
										sortReturnValue.getBooleanValue(result, false);
										return result;
									}
							};
							sort(arrayPtr->begin(), arrayPtr->end(), SortClass(minitScript, sortFunctionScriptIdx));
						}
					}
				} else {
					MINITSCRIPT_METHODUSAGE_COMPLAIN(getMethodName());
				}
			}
		};
		minitScript->registerMethod(new MethodArraySort(minitScript));
	}
	{
		//
		class MethodArrayReverse: public MinitScript::Method {
		private:
			MinitScript* minitScript { nullptr };
		public:
			MethodArrayReverse(MinitScript* minitScript):
				MinitScript::Method(
					{
						{ .type = MinitScript::TYPE_ARRAY, .name = "array", .optional = false, .reference = true, .nullable = false }
					},
					MinitScript::TYPE_NULL
				),
				minitScript(minitScript) {}
			const string getMethodName() override {
				return "Array::reverse";
			}
			void executeMethod(span<MinitScript::Variable>& arguments, MinitScript::Variable& returnValue, const MinitScript::SubStatement& subStatement) override {
				if (arguments.size() == 1 &&
					arguments[0].getType() == MinitScript::TYPE_ARRAY) {
					auto arrayPtr = arguments[0].getArrayPointer();
					if (arrayPtr != nullptr) {
						reverse(arrayPtr->begin(), arrayPtr->end());
					}
				} else {
					MINITSCRIPT_METHODUSAGE_COMPLAIN(getMethodName());
				}
			}
		};
		minitScript->registerMethod(new MethodArrayReverse(minitScript));
	}
	{
		//
		class MethodArrayClear: public MinitScript::Method {
		private:
			MinitScript* minitScript { nullptr };
		public:
			MethodArrayClear(MinitScript* minitScript):
				MinitScript::Method(
					{
						{ .type = MinitScript::TYPE_ARRAY, .name = "array", .optional = false, .reference = true, .nullable = false }
					},
					MinitScript::TYPE_NULL
				),
				minitScript(minitScript) {}
			const string getMethodName() override {
				return "Array::clear";
			}
			void executeMethod(span<MinitScript::Variable>& arguments, MinitScript::Variable& returnValue, const MinitScript::SubStatement& subStatement) override {
				if (arguments.size() == 1 &&
					arguments[0].getType() == MinitScript::TYPE_ARRAY) {
					arguments[0].clearArray();
				} else {
					MINITSCRIPT_METHODUSAGE_COMPLAIN(getMethodName());
				}
			}
		};
		minitScript->registerMethod(new MethodArrayClear(minitScript));
	}
	{
		//
		class MethodArrayForEach: public MinitScript::Method {
		private:
			MinitScript* minitScript { nullptr };
		public:
			MethodArrayForEach(MinitScript* minitScript):
				MinitScript::Method(
					{
						{ .type = MinitScript::TYPE_ARRAY, .name = "array", .optional = false, .reference = false, .nullable = false },
						{ .type = MinitScript::TYPE_FUNCTION_ASSIGNMENT, .name = "callbackFunction", .optional = false, .reference = false, .nullable = false },
						{ .type = MinitScript::TYPE_PSEUDO_MIXED, .name = "cookie", .optional = true, .reference = true, .nullable = false }
					},
					MinitScript::TYPE_NULL
				),
				minitScript(minitScript) {}
			const string getMethodName() override {
				return "Array::forEach";
			}
			void executeMethod(span<MinitScript::Variable>& arguments, MinitScript::Variable& returnValue, const MinitScript::SubStatement& subStatement) override {
				string callbackFunction;
				int callbackFunctionScriptIdx;
				if ((arguments.size() == 2 || arguments.size() == 3) &&
					arguments[0].getType() == MinitScript::TYPE_ARRAY &&
					MinitScript::getFunctionValue(arguments, 1, callbackFunction, callbackFunctionScriptIdx) == true) {
					auto arrayPtr = arguments[0].getArrayPointer();
					if (arrayPtr != nullptr) {
						if (callbackFunction.empty() == false && callbackFunctionScriptIdx == MinitScript::SCRIPTIDX_NONE) {
							callbackFunctionScriptIdx = minitScript->getFunctionScriptIdx(callbackFunction);
						}
						if (callbackFunctionScriptIdx == MinitScript::SCRIPTIDX_NONE) {
							MINITSCRIPT_METHODUSAGE_COMPLAINM(getMethodName(), "Function not found: " + callbackFunction);
						} else {
							for (auto arrayEntry: *arrayPtr) {
								vector<MinitScript::Variable> functionArguments { MinitScript::Variable::createReferenceVariable(arrayEntry) };
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
		minitScript->registerMethod(new MethodArrayForEach(minitScript));
	}
	{
		//
		class MethodArrayForRange: public MinitScript::Method {
		private:
			MinitScript* minitScript { nullptr };
		public:
			MethodArrayForRange(MinitScript* minitScript):
				MinitScript::Method(
					{
						{ .type = MinitScript::TYPE_ARRAY, .name = "array", .optional = false, .reference = false, .nullable = false },
						{ .type = MinitScript::TYPE_FUNCTION_ASSIGNMENT, .name = "callbackFunction", .optional = false, .reference = false, .nullable = false },
						{ .type = MinitScript::TYPE_INTEGER, .name = "beginIndex", .optional = false, .reference = false, .nullable = false },
						{ .type = MinitScript::TYPE_INTEGER, .name = "count", .optional = true, .reference = false, .nullable = false },
						{ .type = MinitScript::TYPE_INTEGER, .name = "step", .optional = true, .reference = false, .nullable = false },
						{ .type = MinitScript::TYPE_PSEUDO_MIXED, .name = "cookie", .optional = true, .reference = true, .nullable = false }
					},
					MinitScript::TYPE_NULL
				),
				minitScript(minitScript) {}
			const string getMethodName() override {
				return "Array::forRange";
			}
			void executeMethod(span<MinitScript::Variable>& arguments, MinitScript::Variable& returnValue, const MinitScript::SubStatement& subStatement) override {
				string callbackFunction;
				int callbackFunctionScriptIdx;
				int64_t beginIndex;
				int64_t count = -1ll;
				int64_t step = 1ll;
				if ((arguments.size() == 3 || arguments.size() == 4 || arguments.size() == 5 || arguments.size() == 6) &&
					arguments[0].getType() == MinitScript::TYPE_ARRAY &&
					MinitScript::getFunctionValue(arguments, 1, callbackFunction, callbackFunctionScriptIdx) == true &&
					MinitScript::getIntegerValue(arguments, 2, beginIndex, true) == true &&
					MinitScript::getIntegerValue(arguments, 3, count, true) == true &&
					MinitScript::getIntegerValue(arguments, 4, step, true) == true) {
					auto arrayPtr = arguments[0].getArrayPointer();
					if (arrayPtr != nullptr) {
						if (callbackFunction.empty() == false && callbackFunctionScriptIdx == MinitScript::SCRIPTIDX_NONE) {
							callbackFunctionScriptIdx = minitScript->getFunctionScriptIdx(callbackFunction);
						}
						if (callbackFunctionScriptIdx == MinitScript::SCRIPTIDX_NONE) {
							MINITSCRIPT_METHODUSAGE_COMPLAINM(getMethodName(), "Function not found: " + callbackFunction);
						} else {
							auto counter = 0;
							for (auto i = beginIndex; i >= 0 && counter < count && i < arrayPtr->size(); i+= step) {
								auto arrayEntry = (*arrayPtr)[i];
								vector<MinitScript::Variable> functionArguments { MinitScript::Variable::createReferenceVariable(arrayEntry) };
								if (arguments.size() == 6) functionArguments.push_back(arguments[5]);
								span functionArgumentsSpan(functionArguments);
								MinitScript::Variable functionReturnValue;
								minitScript->call(callbackFunctionScriptIdx, functionArgumentsSpan, functionReturnValue);
								// exit condition
								bool result = false;
								functionReturnValue.getBooleanValue(result, false);
								if (result == true) break;
								//
								counter++;
							}
						}
					}
				} else {
					MINITSCRIPT_METHODUSAGE_COMPLAIN(getMethodName());
				}
			}
		};
		minitScript->registerMethod(new MethodArrayForRange(minitScript));
	}
	{
		//
		class MethodArrayContains: public MinitScript::Method {
		private:
			MinitScript* minitScript { nullptr };
		public:
			MethodArrayContains(MinitScript* minitScript):
				MinitScript::Method(
					{
						{ .type = MinitScript::TYPE_ARRAY, .name = "array", .optional = false, .reference = false, .nullable = false },
						{ .type = MinitScript::TYPE_PSEUDO_MIXED, .name = "value", .optional = false, .reference = false, .nullable = false },
					},
					MinitScript::TYPE_BOOLEAN
				),
				minitScript(minitScript) {}
			const string getMethodName() override {
				return "Array::contains";
			}
			void executeMethod(span<MinitScript::Variable>& arguments, MinitScript::Variable& returnValue, const MinitScript::SubStatement& subStatement) override {
				string stringValue;
				if ((arguments.size() == 2) &&
					arguments[0].getType() == MinitScript::TYPE_ARRAY &&
					MinitScript::getStringValue(arguments, 1, stringValue) == true) {
					const auto& array = arguments[0];
					returnValue.setValue(false);
					for (auto i = 0; i < array.getArraySize(); i++) {
						auto arrayValue = array.getArrayEntry(i);
						if (arrayValue.getValueAsString() == stringValue) {
							returnValue.setValue(true);
							break;
						}
					}
				} else {
					MINITSCRIPT_METHODUSAGE_COMPLAIN(getMethodName());
				}
			}
		};
		minitScript->registerMethod(new MethodArrayContains(minitScript));
	}
}
