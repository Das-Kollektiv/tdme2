#include <iostream>
#include <span>

#include <miniscript/miniscript.h>
#include <miniscript/miniscript/ConsoleMethods.h>
#include <miniscript/miniscript/MiniScript.h>
#include <miniscript/utilities/Console.h>
#include <miniscript/utilities/ErrorConsole.h>

using std::cin;
using std::getline;
using std::span;

using miniscript::miniscript::ConsoleMethods;

using miniscript::miniscript::MiniScript;

using _Console = miniscript::utilities::Console;
using _ErrorConsole = miniscript::utilities::ErrorConsole;

void ConsoleMethods::registerConstants(MiniScript* miniScript) {
}

void ConsoleMethods::registerMethods(MiniScript* miniScript) {
	// console
	{
		//
		class MethodConsoleDump: public MiniScript::Method {
		private:
			MiniScript* miniScript { nullptr };
		public:
			MethodConsoleDump(MiniScript* miniScript):
				MiniScript::Method(
					{
						{ .type = MiniScript::TYPE_PSEUDO_MIXED, .name = "value", .optional = false, .reference = false, .nullable = false }
					}
				),
				miniScript(miniScript) {}
			const string getMethodName() override {
				return "console.dump";
			}
			void executeMethod(span<MiniScript::Variable>& arguments, MiniScript::Variable& returnValue, const MiniScript::Statement& statement) override {
				if (arguments.size() != 1) {
					_Console::printLine(getMethodName() + "(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation(getMethodName()));
					miniScript->startErrorScript();
				} else {
					_Console::printLine(arguments[0].getValueAsString(true));
				}
			}
		};
		miniScript->registerMethod(new MethodConsoleDump(miniScript));
	}
	{
		//
		class MethodConsolePrint: public MiniScript::Method {
		private:
			MiniScript* miniScript { nullptr };
		public:
			MethodConsolePrint(MiniScript* miniScript): MiniScript::Method(), miniScript(miniScript) {}
			const string getMethodName() override {
				return "console.print";
			}
			void executeMethod(span<MiniScript::Variable>& arguments, MiniScript::Variable& returnValue, const MiniScript::Statement& statement) override {
				for (const auto& argument: arguments) {
					_Console::print(argument.getValueAsString());
				}
			}
			bool isVariadic() const override {
				return true;
			}
		};
		miniScript->registerMethod(new MethodConsolePrint(miniScript));
	}
	{
		//
		class MethodConsolePrintLine: public MiniScript::Method {
		private:
			MiniScript* miniScript { nullptr };
		public:
			MethodConsolePrintLine(MiniScript* miniScript): MiniScript::Method(), miniScript(miniScript) {}
			const string getMethodName() override {
				return "console.printLine";
			}
			void executeMethod(span<MiniScript::Variable>& arguments, MiniScript::Variable& returnValue, const MiniScript::Statement& statement) override {
				for (const auto& argument: arguments) {
					_Console::print(argument.getValueAsString());
				}
				_Console::printLine();
			}
			bool isVariadic() const override {
				return true;
			}
		};
		miniScript->registerMethod(new MethodConsolePrintLine(miniScript));
	}
	{
		//
		class MethodConsoleReadLine: public MiniScript::Method {
		private:
			MiniScript* miniScript { nullptr };
		public:
			MethodConsoleReadLine(MiniScript* miniScript):
				MiniScript::Method({}, MiniScript::TYPE_STRING),
				miniScript(miniScript) {
				//
			}
			const string getMethodName() override {
				return "console.readLine";
			}
			void executeMethod(span<MiniScript::Variable>& arguments, MiniScript::Variable& returnValue, const MiniScript::Statement& statement) override {
				returnValue.setValue(_Console::readLine());
			}
		};
		miniScript->registerMethod(new MethodConsoleReadLine(miniScript));
	}
	{
		//
		class MethodConsoleReadAll: public MiniScript::Method {
		private:
			MiniScript* miniScript { nullptr };
		public:
			MethodConsoleReadAll(MiniScript* miniScript):
				MiniScript::Method({}, MiniScript::TYPE_STRING),
				miniScript(miniScript) {
				//
			}
			const string getMethodName() override {
				return "console.readAll";
			}
			void executeMethod(span<MiniScript::Variable>& arguments, MiniScript::Variable& returnValue, const MiniScript::Statement& statement) override {
				returnValue.setValue(_Console::readAll());
			}
		};
		miniScript->registerMethod(new MethodConsoleReadAll(miniScript));
	}
	{
		//
		class MethodConsoleReadAllAsArray: public MiniScript::Method {
		private:
			MiniScript* miniScript { nullptr };
		public:
			MethodConsoleReadAllAsArray(MiniScript* miniScript):
				MiniScript::Method({}, MiniScript::TYPE_ARRAY),
				miniScript(miniScript) {
				//
			}
			const string getMethodName() override {
				return "console.readAllAsArray";
			}
			void executeMethod(span<MiniScript::Variable>& arguments, MiniScript::Variable& returnValue, const MiniScript::Statement& statement) override {
				returnValue.setType(MiniScript::TYPE_ARRAY);
				const auto input = _Console::readAllAsArray();
				for (const auto& line: input) returnValue.pushArrayEntry(MiniScript::Variable(line));
			}
		};
		miniScript->registerMethod(new MethodConsoleReadAllAsArray(miniScript));
	}
	{
		//
		class MethodConsoleErrorPrint: public MiniScript::Method {
		private:
			MiniScript* miniScript { nullptr };
		public:
			MethodConsoleErrorPrint(MiniScript* miniScript): MiniScript::Method(), miniScript(miniScript) {}
			const string getMethodName() override {
				return "console.error.print";
			}
			void executeMethod(span<MiniScript::Variable>& arguments, MiniScript::Variable& returnValue, const MiniScript::Statement& statement) override {
				for (const auto& argument: arguments) {
					_ErrorConsole::print(argument.getValueAsString());
				}
			}
			bool isVariadic() const override {
				return true;
			}
		};
		miniScript->registerMethod(new MethodConsoleErrorPrint(miniScript));
	}
	{
		//
		class MethodConsoleErrorPrintLine: public MiniScript::Method {
		private:
			MiniScript* miniScript { nullptr };
		public:
			MethodConsoleErrorPrintLine(MiniScript* miniScript): MiniScript::Method(), miniScript(miniScript) {}
			const string getMethodName() override {
				return "console.error.printLine";
			}
			void executeMethod(span<MiniScript::Variable>& arguments, MiniScript::Variable& returnValue, const MiniScript::Statement& statement) override {
				for (const auto& argument: arguments) {
					_ErrorConsole::print(argument.getValueAsString());
				}
				_ErrorConsole::printLine();
			}
			bool isVariadic() const override {
				return true;
			}
		};
		miniScript->registerMethod(new MethodConsoleErrorPrintLine(miniScript));
	}
}

