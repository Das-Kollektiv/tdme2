#include <iostream>
#include <span>

#include <minitscript/minitscript.h>
#include <minitscript/minitscript/ConsoleMethods.h>
#include <minitscript/minitscript/MinitScript.h>
#include <minitscript/utilities/Console.h>
#include <minitscript/utilities/ErrorConsole.h>

using std::cin;
using std::getline;
using std::span;

using minitscript::minitscript::ConsoleMethods;

using minitscript::minitscript::MinitScript;

using _Console = minitscript::utilities::Console;
using _ErrorConsole = minitscript::utilities::ErrorConsole;

void ConsoleMethods::registerConstants(MinitScript* minitScript) {
}

void ConsoleMethods::registerMethods(MinitScript* minitScript) {
	// console
	{
		//
		class MethodConsoleDump: public MinitScript::Method {
		private:
			MinitScript* minitScript { nullptr };
		public:
			MethodConsoleDump(MinitScript* minitScript):
				MinitScript::Method(
					{
						{ .type = MinitScript::TYPE_PSEUDO_MIXED, .name = "value", .optional = false, .reference = false, .nullable = false }
					}
				),
				minitScript(minitScript) {}
			const string getMethodName() override {
				return "console.dump";
			}
			void executeMethod(span<MinitScript::Variable>& arguments, MinitScript::Variable& returnValue, const MinitScript::SubStatement& subStatement) override {
				if (arguments.size() == 1) {
					_Console::printLine(arguments[0].getValueAsString(true));
				} else {
					MINITSCRIPT_METHODUSAGE_COMPLAIN(getMethodName());
				}
			}
		};
		minitScript->registerMethod(new MethodConsoleDump(minitScript));
	}
	{
		//
		class MethodConsolePrint: public MinitScript::Method {
		private:
			MinitScript* minitScript { nullptr };
		public:
			MethodConsolePrint(MinitScript* minitScript): MinitScript::Method(), minitScript(minitScript) {}
			const string getMethodName() override {
				return "console.print";
			}
			void executeMethod(span<MinitScript::Variable>& arguments, MinitScript::Variable& returnValue, const MinitScript::SubStatement& subStatement) override {
				for (const auto& argument: arguments) {
					_Console::print(argument.getValueAsString());
				}
			}
			bool isVariadic() const override {
				return true;
			}
		};
		minitScript->registerMethod(new MethodConsolePrint(minitScript));
	}
	{
		//
		class MethodConsolePrintLine: public MinitScript::Method {
		private:
			MinitScript* minitScript { nullptr };
		public:
			MethodConsolePrintLine(MinitScript* minitScript): MinitScript::Method(), minitScript(minitScript) {}
			const string getMethodName() override {
				return "console.printLine";
			}
			void executeMethod(span<MinitScript::Variable>& arguments, MinitScript::Variable& returnValue, const MinitScript::SubStatement& subStatement) override {
				for (const auto& argument: arguments) {
					_Console::print(argument.getValueAsString());
				}
				_Console::printLine();
			}
			bool isVariadic() const override {
				return true;
			}
		};
		minitScript->registerMethod(new MethodConsolePrintLine(minitScript));
	}
	{
		//
		class MethodConsoleReadLine: public MinitScript::Method {
		private:
			MinitScript* minitScript { nullptr };
		public:
			MethodConsoleReadLine(MinitScript* minitScript):
				MinitScript::Method({}, MinitScript::TYPE_STRING),
				minitScript(minitScript) {
				//
			}
			const string getMethodName() override {
				return "console.readLine";
			}
			void executeMethod(span<MinitScript::Variable>& arguments, MinitScript::Variable& returnValue, const MinitScript::SubStatement& subStatement) override {
				if (arguments.size() == 0) {
					returnValue.setValue(_Console::readLine());
				} else {
					MINITSCRIPT_METHODUSAGE_COMPLAIN(getMethodName());
				}
			}
		};
		minitScript->registerMethod(new MethodConsoleReadLine(minitScript));
	}
	{
		//
		class MethodConsoleReadAll: public MinitScript::Method {
		private:
			MinitScript* minitScript { nullptr };
		public:
			MethodConsoleReadAll(MinitScript* minitScript):
				MinitScript::Method({}, MinitScript::TYPE_STRING),
				minitScript(minitScript) {
				//
			}
			const string getMethodName() override {
				return "console.readAll";
			}
			void executeMethod(span<MinitScript::Variable>& arguments, MinitScript::Variable& returnValue, const MinitScript::SubStatement& subStatement) override {
				if (arguments.size() == 0) {
					returnValue.setValue(_Console::readAll());
				} else {
					MINITSCRIPT_METHODUSAGE_COMPLAIN(getMethodName());
				}
			}
		};
		minitScript->registerMethod(new MethodConsoleReadAll(minitScript));
	}
	{
		//
		class MethodConsoleReadAllAsArray: public MinitScript::Method {
		private:
			MinitScript* minitScript { nullptr };
		public:
			MethodConsoleReadAllAsArray(MinitScript* minitScript):
				MinitScript::Method({}, MinitScript::TYPE_ARRAY),
				minitScript(minitScript) {
				//
			}
			const string getMethodName() override {
				return "console.readAllAsArray";
			}
			void executeMethod(span<MinitScript::Variable>& arguments, MinitScript::Variable& returnValue, const MinitScript::SubStatement& subStatement) override {
				if (arguments.size() == 0) {
					returnValue.setType(MinitScript::TYPE_ARRAY);
					const auto input = _Console::readAllAsArray();
					for (const auto& line: input) returnValue.pushArrayEntry(MinitScript::Variable(line));
				} else {
					MINITSCRIPT_METHODUSAGE_COMPLAIN(getMethodName());
				}
			}
		};
		minitScript->registerMethod(new MethodConsoleReadAllAsArray(minitScript));
	}
	{
		//
		class MethodConsoleErrorPrint: public MinitScript::Method {
		private:
			MinitScript* minitScript { nullptr };
		public:
			MethodConsoleErrorPrint(MinitScript* minitScript): MinitScript::Method(), minitScript(minitScript) {}
			const string getMethodName() override {
				return "console.error.print";
			}
			void executeMethod(span<MinitScript::Variable>& arguments, MinitScript::Variable& returnValue, const MinitScript::SubStatement& subStatement) override {
				for (const auto& argument: arguments) {
					_ErrorConsole::print(argument.getValueAsString());
				}
			}
			bool isVariadic() const override {
				return true;
			}
		};
		minitScript->registerMethod(new MethodConsoleErrorPrint(minitScript));
	}
	{
		//
		class MethodConsoleErrorPrintLine: public MinitScript::Method {
		private:
			MinitScript* minitScript { nullptr };
		public:
			MethodConsoleErrorPrintLine(MinitScript* minitScript): MinitScript::Method(), minitScript(minitScript) {}
			const string getMethodName() override {
				return "console.error.printLine";
			}
			void executeMethod(span<MinitScript::Variable>& arguments, MinitScript::Variable& returnValue, const MinitScript::SubStatement& subStatement) override {
				for (const auto& argument: arguments) {
					_ErrorConsole::print(argument.getValueAsString());
				}
				_ErrorConsole::printLine();
			}
			bool isVariadic() const override {
				return true;
			}
		};
		minitScript->registerMethod(new MethodConsoleErrorPrintLine(minitScript));
	}
}
