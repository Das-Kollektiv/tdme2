#include <span>

#include <memory>

#include <minitscript/minitscript.h>
#include <minitscript/minitscript/ContextMethods.h>
#include <minitscript/minitscript/MinitScript.h>
#include <minitscript/utilities/Console.h>

using std::span;
using std::unique_ptr;

using minitscript::minitscript::ContextMethods;

using minitscript::minitscript::MinitScript;

using _Console = minitscript::utilities::Console;

void ContextMethods::registerConstants(MinitScript* minitScript) {
}

void ContextMethods::registerMethods(MinitScript* minitScript) {
	if (minitScript->getContext() == nullptr) return;
	{
		//
		class MethodContextScriptHasCallable: public MinitScript::Method {
		private:
			MinitScript* minitScript { nullptr };
		public:
			MethodContextScriptHasCallable(MinitScript* minitScript):
				MinitScript::Method(
					{
						{ .type = MinitScript::TYPE_STRING, .name = "scriptId", .optional = false, .reference = false, .nullable = false },
						{ .type = MinitScript::TYPE_STRING, .name = "callable", .optional = false, .reference = false, .nullable = false }
					},
					MinitScript::TYPE_BOOLEAN
				),
				minitScript(minitScript) {}
			const string getMethodName() override {
				return "context.script.hasCallable";
			}
			void executeMethod(span<MinitScript::Variable>& arguments, MinitScript::Variable& returnValue, const MinitScript::SubStatement& subStatement) override {
				string scriptId;
				string callable;
				if (arguments.size() == 2 &&
					MinitScript::getStringValue(arguments, 0, scriptId) == true &&
					MinitScript::getStringValue(arguments, 1, callable) == true) {
					auto script = minitScript->getContext()->getScript(scriptId);
					if (script == nullptr) {
						returnValue.setValue(false);
					} else {
						auto scriptIdx = script->getFunctionScriptIdx(callable);
						if (scriptIdx == MinitScript::SCRIPTIDX_NONE || script->getScripts()[scriptIdx].callable == false) {
							returnValue.setValue(false);
						} else {
							returnValue.setValue(true);
						}
					}
				} else {
					MINITSCRIPT_METHODUSAGE_COMPLAIN(getMethodName());
				}
			}
		};
		minitScript->registerMethod(new MethodContextScriptHasCallable(minitScript));
	}
	{
		//
		class MethodContextScriptCall: public MinitScript::Method {
		private:
			MinitScript* minitScript { nullptr };
		public:
			MethodContextScriptCall(MinitScript* minitScript):
				Method(
					{
						{ .type = MinitScript::TYPE_STRING, .name = "scriptId", .optional = false, .reference = false, .nullable = false },
						{ .type = MinitScript::TYPE_STRING, .name = "callable", .optional = false, .reference = false, .nullable = false }
					},
					MinitScript::TYPE_PSEUDO_MIXED
				),
				minitScript(minitScript) {}
			const string getMethodName() override {
				return "context.script.call";
			}
			void executeMethod(span<MinitScript::Variable>& arguments, MinitScript::Variable& returnValue, const MinitScript::SubStatement& subStatement) override {
				string scriptId;
				string callable;
				if (arguments.size() >= 2 &&
					MinitScript::getStringValue(arguments, 0, scriptId) == true &&
					MinitScript::getStringValue(arguments, 1, callable) == true) {
					auto script = dynamic_cast<MinitScript*>(minitScript->getContext()->getScript(scriptId));
					if (script == nullptr) {
						MINITSCRIPT_METHODUSAGE_COMPLAINM(getMethodName(), "No script with given id: " + scriptId);
					} else {
						auto scriptIdx = script->getFunctionScriptIdx(callable);
						if (scriptIdx == MinitScript::SCRIPTIDX_NONE || script->getScripts()[scriptIdx].callable == false) {
							MINITSCRIPT_METHODUSAGE_COMPLAINM(getMethodName(), "Callable not found: " + callable);
						} else {
							minitScript->getContext()->push(script);
							#if defined (__clang__)
								// Clang currently does not support initializing span using begin and end iterators,
								vector<MinitScript::Variable> callArguments(arguments.size() - 2);
								for (auto i = 2; i < arguments.size(); i++) callArguments[i - 2] = move(arguments[i]);
								// call
								span callArgumentsSpan(callArguments);
								script->call(scriptIdx, callArgumentsSpan, returnValue);
								// move back arguments
								for (auto i = 2; i < arguments.size(); i++) arguments[i] = move(callArguments[i - 2]);
							#else
								span callArgumentsSpan(arguments.begin() + 2, arguments.end());
								script->call(scriptIdx, callArgumentsSpan, returnValue);
							#endif
							minitScript->getContext()->pop();
						}
					}
				} else {
					MINITSCRIPT_METHODUSAGE_COMPLAIN(getMethodName());
				}
			}
			bool isVariadic() const override {
				return true;
			}
		};
		minitScript->registerMethod(new MethodContextScriptCall(minitScript));
	}
	{
		//
		class MethodContextScriptLoadScript: public MinitScript::Method {
		private:
			MinitScript* minitScript { nullptr };
		public:
			MethodContextScriptLoadScript(MinitScript* minitScript):
				MinitScript::Method(
					{
						{ .type = MinitScript::TYPE_STRING, .name = "scriptId", .optional = false, .reference = false, .nullable = false },
						{ .type = MinitScript::TYPE_STRING, .name = "pathName", .optional = false, .reference = false, .nullable = false },
						{ .type = MinitScript::TYPE_STRING, .name = "fileName", .optional = false, .reference = false, .nullable = false },
						{ .type = MinitScript::TYPE_BOOLEAN, .name = "verbose", .optional = true, .reference = false, .nullable = false },
					},
					MinitScript::TYPE_NULL
				),
				minitScript(minitScript) {}
			const string getMethodName() override {
				return "context.script.loadScript";
			}
			void executeMethod(span<MinitScript::Variable>& arguments, MinitScript::Variable& returnValue, const MinitScript::SubStatement& subStatement) override {
				string scriptId;
				string pathName;
				string fileName;
				bool verbose = false;
				if ((arguments.size() == 3 || arguments.size() == 4) &&
					MinitScript::getStringValue(arguments, 0, scriptId) == true &&
					MinitScript::getStringValue(arguments, 1, pathName) == true &&
					MinitScript::getStringValue(arguments, 2, fileName) == true &&
					MinitScript::getBooleanValue(arguments, 3, verbose, true) == true) {
					unique_ptr<MinitScript> script;
					// try to load from (native) library
					if (minitScript->getLibrary() != nullptr) {
						script = unique_ptr<MinitScript>(
							minitScript->getLibrary()->loadScript(
								pathName,
								fileName
							)
						);
					}
					// no native script?
					if (script == nullptr) {
						// yarrrr, parse ordinary script
						script = make_unique<MinitScript>();
						script->setContext(minitScript->getContext());
						script->parseScript(
							pathName,
							fileName
						);
					}
					if (script != nullptr) {
						// verbose
						if (verbose == true) _Console::printLine(script->getInformation());
						//
						if (script->isValid() == false) {
							_Console::printLine("Script not valid.");
						} else {
							minitScript->getContext()->addScript(scriptId, script.release());
						}
					}
				} else {
					MINITSCRIPT_METHODUSAGE_COMPLAIN(getMethodName());
				}
			}
		};
		minitScript->registerMethod(new MethodContextScriptLoadScript(minitScript));
	}
	{
		//
		class MethodContextScriptRemoveScript: public MinitScript::Method {
		private:
			MinitScript* minitScript { nullptr };
		public:
			MethodContextScriptRemoveScript(MinitScript* minitScript):
				MinitScript::Method(
					{
						{ .type = MinitScript::TYPE_STRING, .name = "scriptId", .optional = false, .reference = false, .nullable = false }
					},
					MinitScript::TYPE_NULL
				),
				minitScript(minitScript) {}
			const string getMethodName() override {
				return "context.script.removeScript";
			}
			void executeMethod(span<MinitScript::Variable>& arguments, MinitScript::Variable& returnValue, const MinitScript::SubStatement& subStatement) override {
				string scriptId;
				if (arguments.size() == 1 &&
					MinitScript::getStringValue(arguments, 0, scriptId) == true) {
					minitScript->getContext()->removeScript(scriptId);
				} else {
					MINITSCRIPT_METHODUSAGE_COMPLAIN(getMethodName());
				}
			}
		};
		minitScript->registerMethod(new MethodContextScriptRemoveScript(minitScript));
	}
	{
		//
		class MethodContextScriptGetScriptIds: public MinitScript::Method {
		private:
			MinitScript* minitScript { nullptr };
		public:
			MethodContextScriptGetScriptIds(MinitScript* minitScript):
				MinitScript::Method({}, MinitScript::TYPE_ARRAY),
				minitScript(minitScript) {}
			const string getMethodName() override {
				return "context.script.getScriptIds";
			}
			void executeMethod(span<MinitScript::Variable>& arguments, MinitScript::Variable& returnValue, const MinitScript::SubStatement& subStatement) override {
				if (arguments.size() == 0) {
					auto scriptIds = minitScript->getContext()->getScriptIds();
					returnValue.setType(MinitScript::TYPE_ARRAY);
					for (const auto& scriptId: scriptIds) returnValue.pushArrayEntry(scriptId);
				} else {
					MINITSCRIPT_METHODUSAGE_COMPLAIN(getMethodName());
				}
			}
		};
		minitScript->registerMethod(new MethodContextScriptGetScriptIds(minitScript));
	}
}
