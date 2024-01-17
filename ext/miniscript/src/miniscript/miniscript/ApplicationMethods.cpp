#include <array>
#include <cstdio>
#include <cstdlib>
#include <span>
#include <memory>

#include <miniscript/miniscript.h>
#include <miniscript/miniscript/ApplicationMethods.h>
#include <miniscript/miniscript/MiniScript.h>
#include <miniscript/utilities/Console.h>
#include <miniscript/utilities/StringTools.h>

using std::array;
using std::span;
using std::shared_ptr;

using miniscript::miniscript::ApplicationMethods;

using miniscript::miniscript::MiniScript;

using _Console = miniscript::utilities::Console;
using _StringTools = miniscript::utilities::StringTools;

void ApplicationMethods::registerConstants(MiniScript* miniScript) {
	miniScript->setConstant("$APPLICATION::EXITCODE_SUCCESS", static_cast<int64_t>(EXIT_SUCCESS));
	miniScript->setConstant("$APPLICATION::EXITCODE_FAILURE", static_cast<int64_t>(EXIT_FAILURE));
	//
	#if defined(__FreeBSD__)
		miniScript->setConstant("$APPLICATION::OS", string("FreeBSD"));
	#elif defined(__HAIKU__)
		miniScript->setConstant("$APPLICATION::OS", string("Haiku"));
	#elif defined(__linux__)
		miniScript->setConstant("$APPLICATION::OS", string("Linux"));
	#elif defined(__APPLE__)
		miniScript->setConstant("$APPLICATION::OS", string("MacOSX"));
	#elif defined(__NetBSD__)
		miniScript->setConstant("$APPLICATION::OS", string("NetBSD"));
	#elif defined(__OpenBSD__)
		miniScript->setConstant("$APPLICATION::OS", string("OpenBSD"));
	#elif defined(_MSC_VER)
		miniScript->setConstant("$APPLICATION::OS", string("Windows-MSC"));
	#elif defined(_WIN32)
		miniScript->setConstant("$APPLICATION::OS", string("Windows-MINGW"));
	#else
		miniScript->setConstant("$APPLICATION::OS", string("Unknown"));
	#endif
	#if defined(__amd64__) || defined(_M_X64)
		miniScript->setConstant("$APPLICATION::CPU", string("X64"));
	#elif defined(__ia64__) || defined(_M_IA64)
		miniScript->setConstant("$APPLICATION::CPU", string("IA64"));
	#elif defined(__aarch64__)
		miniScript->setConstant("$APPLICATION::CPU", string("ARM64"));
	#elif defined(__arm__) || defined(_M_ARM)
		miniScript->setConstant("$APPLICATION::CPU", string("ARM"));
	#elif defined(__powerpc64__)
		miniScript->setConstant("$APPLICATION::CPU", string("PPC64"));
	#elif defined(__powerpc__)
		miniScript->setConstant("$APPLICATION::CPU", string("PPC"));
	#else
		miniScript->setConstant("$APPLICATION::CPU", string("Unknown"));
	#endif
}

const string ApplicationMethods::execute(const string& command) {
	// see: https://stackoverflow.com/questions/478898/how-to-execute-a-command-and-get-output-of-command-within-c-using-posix
	array<char, 128> buffer;
	string result;
	#if defined(_MSC_VER)
		shared_ptr<FILE> pipe(_popen(command.c_str(), "r"), _pclose);
	#else
		shared_ptr<FILE> pipe(popen(command.c_str(), "r"), pclose);
	#endif
	if (!pipe) throw std::runtime_error("popen() failed!");
	while (!feof(pipe.get())) {
		if (fgets(buffer.data(), buffer.size(), pipe.get()) != nullptr)
			result += buffer.data();
	}
	return result;
}

void ApplicationMethods::registerMethods(MiniScript* miniScript) {
	// application
	{
		//
		class MethodApplicationExecute: public MiniScript::Method {
		private:
			MiniScript* miniScript { nullptr };
		public:
			MethodApplicationExecute(MiniScript* miniScript):
				MiniScript::Method(
					{
						{ .type = MiniScript::TYPE_STRING, .name = "command", .optional = false, .reference = false, .nullable = false },
					},
					MiniScript::TYPE_STRING
				),
				miniScript(miniScript) {}
			const string getMethodName() override {
				return "application.execute";
			}
			void executeMethod(span<MiniScript::Variable>& arguments, MiniScript::Variable& returnValue, const MiniScript::Statement& statement) override {
				string command;
				if (MiniScript::getStringValue(arguments, 0, command, false) == true) {
					returnValue.setValue(ApplicationMethods::execute(command));
				} else {
					_Console::println(getMethodName() + "(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation(getMethodName()));
					miniScript->startErrorScript();
				}
			}
		};
		miniScript->registerMethod(new MethodApplicationExecute(miniScript));
	}
	//
	if (miniScript->getContext() != nullptr) {
		//
		{
			//
			class MethodApplicationGetArguments: public MiniScript::Method {
			private:
				MiniScript* miniScript { nullptr };
			public:
				MethodApplicationGetArguments(MiniScript* miniScript):
					MiniScript::Method({}, MiniScript::TYPE_ARRAY),
					miniScript(miniScript) {}
				const string getMethodName() override {
					return "application.getArguments";
				}
				void executeMethod(span<MiniScript::Variable>& arguments, MiniScript::Variable& returnValue, const MiniScript::Statement& statement) override {
					returnValue.setType(MiniScript::TYPE_ARRAY);
					for (const auto& argumentValue: miniScript->getContext()->getArgumentValues()) {
						returnValue.pushArrayEntry(MiniScript::Variable(argumentValue));
					}
				}
			};
			miniScript->registerMethod(new MethodApplicationGetArguments(miniScript));
		}
		{
			//
			class MethodApplicationExit: public MiniScript::Method {
			private:
				MiniScript* miniScript { nullptr };
			public:
				MethodApplicationExit(MiniScript* miniScript):
					MiniScript::Method(
						{
							{ .type = MiniScript::TYPE_INTEGER, .name = "exitCode", .optional = true, .reference = false, .nullable = false },
						}
					),
					miniScript(miniScript) {}
				const string getMethodName() override {
					return "application.exit";
				}
				void executeMethod(span<MiniScript::Variable>& arguments, MiniScript::Variable& returnValue, const MiniScript::Statement& statement) override {
					int64_t exitCode = 0ll;
					if (MiniScript::getIntegerValue(arguments, 0, exitCode, true) == true) {
						miniScript->getContext()->setExitCode(static_cast<int>(exitCode));
						miniScript->stopScriptExecution();
						miniScript->stopRunning();
					} else {
						_Console::println(getMethodName() + "(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation(getMethodName()));
						miniScript->startErrorScript();
					}
				}
			};
			miniScript->registerMethod(new MethodApplicationExit(miniScript));
		}
	}
}
