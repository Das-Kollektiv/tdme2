#include <span>

#include <tdme/tdme.h>
#include <tdme/utilities/MiniScript.h>
#include <tdme/utilities/MiniScriptSet.h>

using std::span;

using tdme::utilities::MiniScriptSet;

using tdme::utilities::MiniScript;

void MiniScriptSet::registerMethods(MiniScript* miniScript) {
	// sets
	{
		//
		class ScriptMethodSet: public MiniScript::ScriptMethod {
		private:
			MiniScript* miniScript { nullptr };
		public:
			ScriptMethodSet(MiniScript* miniScript):
				MiniScript::ScriptMethod(
					{},
					MiniScript::TYPE_SET
				),
				miniScript(miniScript) {}
			const string getMethodName() override {
				return "set";
			}
			void executeMethod(span<MiniScript::ScriptVariable>& argumentValues, MiniScript::ScriptVariable& returnValue, const MiniScript::ScriptStatement& statement) override {
				returnValue.setType(MiniScript::TYPE_SET);
			}
		};
		miniScript->registerMethod(new ScriptMethodSet(miniScript));
	}
	{
		//
		class ScriptMethodSetInsert: public MiniScript::ScriptMethod {
		private:
			MiniScript* miniScript { nullptr };
		public:
			ScriptMethodSetInsert(MiniScript* miniScript):
				MiniScript::ScriptMethod(
					{
						{ .type = MiniScript::TYPE_SET, .name = "set", .optional = false, .reference = true, .nullable = false },
						{ .type = MiniScript::TYPE_STRING, .name = "key", .optional = false, .reference = false, .nullable = false }
					},
					MiniScript::TYPE_NULL
				),
				miniScript(miniScript) {}
			const string getMethodName() override {
				return "set.insert";
			}
			void executeMethod(span<MiniScript::ScriptVariable>& argumentValues, MiniScript::ScriptVariable& returnValue, const MiniScript::ScriptStatement& statement) override {
				//
				string key;
				if (argumentValues.size() != 2 ||
					argumentValues[0].getType() != MiniScript::TYPE_SET ||
					MiniScript::getStringValue(argumentValues, 1, key, false) == false) {
					Console::println(getMethodName() + "(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation(getMethodName()));
					miniScript->startErrorScript();
				} else {
					argumentValues[0].insertSetKey(key);
				}
			}
		};
		miniScript->registerMethod(new ScriptMethodSetInsert(miniScript));
	}
	{
		//
		class ScriptMethodSetHas: public MiniScript::ScriptMethod {
		private:
			MiniScript* miniScript { nullptr };
		public:
			ScriptMethodSetHas(MiniScript* miniScript):
				MiniScript::ScriptMethod(
					{
						{ .type = MiniScript::TYPE_SET, .name = "set", .optional = false, .reference = false, .nullable = false },
						{ .type = MiniScript::TYPE_STRING, .name = "key", .optional = false, .reference = false, .nullable = false }
					},
					MiniScript::TYPE_BOOLEAN
				),
				miniScript(miniScript) {}
			const string getMethodName() override {
				return "set.has";
			}
			void executeMethod(span<MiniScript::ScriptVariable>& argumentValues, MiniScript::ScriptVariable& returnValue, const MiniScript::ScriptStatement& statement) override {
				//
				string key;
				if (argumentValues.size() < 2 ||
					argumentValues[0].getType() != MiniScript::TYPE_SET ||
					MiniScript::getStringValue(argumentValues, 1, key, false) == false) {
					Console::println(getMethodName() + "(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation(getMethodName()));
					miniScript->startErrorScript();
				} else {
					returnValue.setValue(argumentValues[0].hasSetKey(key));
				}
			}
		};
		miniScript->registerMethod(new ScriptMethodSetHas(miniScript));
	}
	{
		//
		class ScriptMethodSetRemove: public MiniScript::ScriptMethod {
		private:
			MiniScript* miniScript { nullptr };
		public:
			ScriptMethodSetRemove(MiniScript* miniScript):
				MiniScript::ScriptMethod(
					{
						{ .type = MiniScript::TYPE_SET, .name = "set", .optional = false, .reference = true, .nullable = false },
						{ .type = MiniScript::TYPE_STRING, .name = "key", .optional = false, .reference = false, .nullable = false }
					},
					MiniScript::TYPE_NULL
				),
				miniScript(miniScript) {}
			const string getMethodName() override {
				return "set.remove";
			}
			void executeMethod(span<MiniScript::ScriptVariable>& argumentValues, MiniScript::ScriptVariable& returnValue, const MiniScript::ScriptStatement& statement) override {
				//
				string key;
				if (argumentValues.size() < 2 ||
					argumentValues[0].getType() != MiniScript::TYPE_SET ||
					MiniScript::getStringValue(argumentValues, 1, key, false) == false) {
					Console::println(getMethodName() + "(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation(getMethodName()));
					miniScript->startErrorScript();
				} else {
					argumentValues[0].removeSetKey(key);
				}
			}
		};
		miniScript->registerMethod(new ScriptMethodSetRemove(miniScript));
	}
	{
		//
		class ScriptMethodSetGetKeys: public MiniScript::ScriptMethod {
		private:
			MiniScript* miniScript { nullptr };
		public:
			ScriptMethodSetGetKeys(MiniScript* miniScript):
				MiniScript::ScriptMethod(
					{
						{ .type = MiniScript::TYPE_SET, .name = "set", .optional = false, .reference = false, .nullable = false },
					},
					MiniScript::TYPE_ARRAY
				),
				miniScript(miniScript) {}
			const string getMethodName() override {
				return "set.getKeys";
			}
			void executeMethod(span<MiniScript::ScriptVariable>& argumentValues, MiniScript::ScriptVariable& returnValue, const MiniScript::ScriptStatement& statement) override {
				//
				if (argumentValues.size() != 1 ||
					argumentValues[0].getType() != MiniScript::TYPE_SET) {
					Console::println(getMethodName() + "(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation(getMethodName()));
					miniScript->startErrorScript();
				} else {
					auto keys = argumentValues[0].getSetKeys();
					returnValue.setType(MiniScript::TYPE_ARRAY);
					for (const auto& key: keys) {
						returnValue.pushArrayEntry(key);
					}
				}
			}
		};
		miniScript->registerMethod(new ScriptMethodSetGetKeys(miniScript));
	}
}
