#include <span>

#include <miniscript/miniscript/SetMethods.h>

#include <miniscript/miniscript.h>
#include <miniscript/miniscript/MiniScript.h>
#include <miniscript/utilities/Console.h>

using std::span;

using miniscript::miniscript::SetMethods;

using miniscript::miniscript::MiniScript;

using _Console = miniscript::utilities::Console;

void SetMethods::registerConstants(MiniScript* miniScript) {
}

void SetMethods::registerMethods(MiniScript* miniScript) {
	// sets
	{
		//
		class MethodSet: public MiniScript::Method {
		private:
			MiniScript* miniScript { nullptr };
		public:
			MethodSet(MiniScript* miniScript):
				MiniScript::Method(
					{},
					MiniScript::TYPE_SET
				),
				miniScript(miniScript) {}
			const string getMethodName() override {
				return "Set";
			}
			void executeMethod(span<MiniScript::Variable>& arguments, MiniScript::Variable& returnValue, const MiniScript::Statement& statement) override {
				returnValue.setType(MiniScript::TYPE_SET);
			}
		};
		miniScript->registerMethod(new MethodSet(miniScript));
	}
	{
		//
		class MethodSetInsert: public MiniScript::Method {
		private:
			MiniScript* miniScript { nullptr };
		public:
			MethodSetInsert(MiniScript* miniScript):
				MiniScript::Method(
					{
						{ .type = MiniScript::TYPE_SET, .name = "set", .optional = false, .reference = true, .nullable = false },
						{ .type = MiniScript::TYPE_STRING, .name = "key", .optional = false, .reference = false, .nullable = false }
					},
					MiniScript::TYPE_NULL
				),
				miniScript(miniScript) {}
			const string getMethodName() override {
				return "Set::insert";
			}
			void executeMethod(span<MiniScript::Variable>& arguments, MiniScript::Variable& returnValue, const MiniScript::Statement& statement) override {
				//
				string key;
				if (arguments.size() != 2 ||
					arguments[0].getType() != MiniScript::TYPE_SET ||
					MiniScript::getStringValue(arguments, 1, key, false) == false) {
					_Console::println(getMethodName() + "(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation(getMethodName()));
					miniScript->startErrorScript();
				} else {
					arguments[0].insertSetKey(key);
				}
			}
		};
		miniScript->registerMethod(new MethodSetInsert(miniScript));
	}
	{
		//
		class MethodSetHas: public MiniScript::Method {
		private:
			MiniScript* miniScript { nullptr };
		public:
			MethodSetHas(MiniScript* miniScript):
				MiniScript::Method(
					{
						{ .type = MiniScript::TYPE_SET, .name = "set", .optional = false, .reference = false, .nullable = false },
						{ .type = MiniScript::TYPE_STRING, .name = "key", .optional = false, .reference = false, .nullable = false }
					},
					MiniScript::TYPE_BOOLEAN
				),
				miniScript(miniScript) {}
			const string getMethodName() override {
				return "Set::has";
			}
			void executeMethod(span<MiniScript::Variable>& arguments, MiniScript::Variable& returnValue, const MiniScript::Statement& statement) override {
				//
				string key;
				if (arguments.size() < 2 ||
					arguments[0].getType() != MiniScript::TYPE_SET ||
					MiniScript::getStringValue(arguments, 1, key, false) == false) {
					_Console::println(getMethodName() + "(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation(getMethodName()));
					miniScript->startErrorScript();
				} else {
					returnValue.setValue(arguments[0].hasSetKey(key));
				}
			}
		};
		miniScript->registerMethod(new MethodSetHas(miniScript));
	}
	{
		//
		class MethodSetRemove: public MiniScript::Method {
		private:
			MiniScript* miniScript { nullptr };
		public:
			MethodSetRemove(MiniScript* miniScript):
				MiniScript::Method(
					{
						{ .type = MiniScript::TYPE_SET, .name = "set", .optional = false, .reference = true, .nullable = false },
						{ .type = MiniScript::TYPE_STRING, .name = "key", .optional = false, .reference = false, .nullable = false }
					},
					MiniScript::TYPE_NULL
				),
				miniScript(miniScript) {}
			const string getMethodName() override {
				return "Set::remove";
			}
			void executeMethod(span<MiniScript::Variable>& arguments, MiniScript::Variable& returnValue, const MiniScript::Statement& statement) override {
				//
				string key;
				if (arguments.size() < 2 ||
					arguments[0].getType() != MiniScript::TYPE_SET ||
					MiniScript::getStringValue(arguments, 1, key, false) == false) {
					_Console::println(getMethodName() + "(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation(getMethodName()));
					miniScript->startErrorScript();
				} else {
					arguments[0].removeSetKey(key);
				}
			}
		};
		miniScript->registerMethod(new MethodSetRemove(miniScript));
	}
	{
		//
		class MethodSetGetKeys: public MiniScript::Method {
		private:
			MiniScript* miniScript { nullptr };
		public:
			MethodSetGetKeys(MiniScript* miniScript):
				MiniScript::Method(
					{
						{ .type = MiniScript::TYPE_SET, .name = "set", .optional = false, .reference = false, .nullable = false },
					},
					MiniScript::TYPE_ARRAY
				),
				miniScript(miniScript) {}
			const string getMethodName() override {
				return "Set::getKeys";
			}
			void executeMethod(span<MiniScript::Variable>& arguments, MiniScript::Variable& returnValue, const MiniScript::Statement& statement) override {
				//
				if (arguments.size() != 1 ||
					arguments[0].getType() != MiniScript::TYPE_SET) {
					_Console::println(getMethodName() + "(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation(getMethodName()));
					miniScript->startErrorScript();
				} else {
					auto keys = arguments[0].getSetKeys();
					returnValue.setType(MiniScript::TYPE_ARRAY);
					for (const auto& key: keys) {
						returnValue.pushArrayEntry(key);
					}
				}
			}
		};
		miniScript->registerMethod(new MethodSetGetKeys(miniScript));
	}
	{
		//
		class MethodSetClear: public MiniScript::Method {
		private:
			MiniScript* miniScript { nullptr };
		public:
			MethodSetClear(MiniScript* miniScript):
				MiniScript::Method(
					{
						{ .type = MiniScript::TYPE_SET, .name = "set", .optional = false, .reference = true, .nullable = false }
					},
					MiniScript::TYPE_NULL
				),
				miniScript(miniScript) {}
			const string getMethodName() override {
				return "Set::clear";
			}
			void executeMethod(span<MiniScript::Variable>& arguments, MiniScript::Variable& returnValue, const MiniScript::Statement& statement) override {
				if ((arguments.size() != 1 || arguments[0].getType() != MiniScript::TYPE_SET)) {
					_Console::println(getMethodName() + "(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation(getMethodName()));
					miniScript->startErrorScript();
				} else {
					arguments[0].clearSet();
				}
			}
		};
		miniScript->registerMethod(new MethodSetClear(miniScript));
	}
	{
		//
		class MethodSetForEach: public MiniScript::Method {
		private:
			MiniScript* miniScript { nullptr };
		public:
			MethodSetForEach(MiniScript* miniScript):
				MiniScript::Method(
					{
						{ .type = MiniScript::TYPE_SET, .name = "set", .optional = false, .reference = false, .nullable = false },
						{ .type = MiniScript::TYPE_FUNCTION_ASSIGNMENT, .name = "function", .optional = false, .reference = false, .nullable = false },
						{ .type = MiniScript::TYPE_PSEUDO_MIXED, .name = "cookie", .optional = true, .reference = true, .nullable = false }
					},
					MiniScript::TYPE_NULL
				),
				miniScript(miniScript) {}
			const string getMethodName() override {
				return "Set::forEach";
			}
			void executeMethod(span<MiniScript::Variable>& arguments, MiniScript::Variable& returnValue, const MiniScript::Statement& statement) override {
				string function;
				if ((arguments.size() != 2 && arguments.size() != 3) ||
					arguments[0].getType() != MiniScript::TYPE_SET ||
					MiniScript::getStringValue(arguments, 1, function, false) == false) {
					_Console::println(getMethodName() + "(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation(getMethodName()));
					miniScript->startErrorScript();
				} else {
					auto setPtr = arguments[0].getSetPointer();
					if (setPtr != nullptr) {
						for (auto setEntry: *setPtr) {
							vector<MiniScript::Variable> functionArguments { MiniScript::Variable(setEntry) };
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
		miniScript->registerMethod(new MethodSetForEach(miniScript));
	}
}
