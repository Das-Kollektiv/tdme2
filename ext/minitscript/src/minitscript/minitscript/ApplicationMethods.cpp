#include <array>
#include <cstdio>
#include <cstdlib>
#include <span>
#include <memory>

#include <minitscript/minitscript.h>
#include <minitscript/minitscript/ApplicationMethods.h>
#include <minitscript/minitscript/MinitScript.h>
#include <minitscript/os/filesystem/FileSystem.h>
#include <minitscript/utilities/Console.h>
#include <minitscript/utilities/Exception.h>
#include <minitscript/utilities/StringTools.h>

using std::array;
using std::span;
using std::shared_ptr;

using minitscript::minitscript::ApplicationMethods;

using minitscript::minitscript::MinitScript;
using minitscript::os::filesystem::FileSystem;
using minitscript::utilities::Exception;

using _Console = minitscript::utilities::Console;
using _StringTools = minitscript::utilities::StringTools;

void ApplicationMethods::registerConstants(MinitScript* minitScript) {
	minitScript->setConstant("$application::EXITCODE_SUCCESS", MinitScript::Variable(static_cast<int64_t>(EXIT_SUCCESS)));
	minitScript->setConstant("$application::EXITCODE_FAILURE", MinitScript::Variable(static_cast<int64_t>(EXIT_FAILURE)));
	//
	#if defined(__FreeBSD__)
		minitScript->setConstant("$application::OS", string("FreeBSD"));
	#elif defined(__HAIKU__)
		minitScript->setConstant("$application::OS", string("Haiku"));
	#elif defined(__linux__)
		minitScript->setConstant("$application::OS", string("Linux"));
	#elif defined(__APPLE__)
		minitScript->setConstant("$application::OS", string("MacOSX"));
	#elif defined(__NetBSD__)
		minitScript->setConstant("$application::OS", string("NetBSD"));
	#elif defined(__OpenBSD__)
		minitScript->setConstant("$application::OS", string("OpenBSD"));
	#elif defined(_MSC_VER)
		minitScript->setConstant("$application::OS", string("Windows-MSC"));
	#elif defined(_WIN32)
		minitScript->setConstant("$application::OS", string("Windows-MINGW"));
	#else
		minitScript->setConstant("$application::OS", string("Unknown"));
	#endif
	#if defined(__i386__) || defined(_M_IX86)
		minitScript->setConstant("$application::CPU", string("X86"));
	#elif defined(__amd64__) || defined(_M_X64)
		minitScript->setConstant("$application::CPU", string("X64"));
	#elif defined(__ia64__) || defined(_M_IA64)
		minitScript->setConstant("$application::CPU", string("IA64"));
	#elif defined(__aarch64__) || defined(_M_ARM64)
		minitScript->setConstant("$application::CPU", string("ARM64"));
	#elif defined(__arm__) || defined(_M_ARM)
		minitScript->setConstant("$application::CPU", string("ARM"));
	#elif defined(__riscv)
		#if __riscv_xlen == 64
			minitScript->setConstant("$application::CPU", string("RISCV64"));
		#else
			minitScript->setConstant("$application::CPU", string("RISCV"));
		#endif
	#elif defined(__powerpc64__)
		minitScript->setConstant("$application::CPU", string("PPC64"));
	#elif defined(__powerpc__)
		minitScript->setConstant("$application::CPU", string("PPC"));
	#else
		minitScript->setConstant("$application::CPU", string("Unknown"));
	#endif
}

const string ApplicationMethods::execute(const string& command, int* exitCode, string* error) {
	string result;
	auto _command = command;
	auto _exitCode = EXIT_FAILURE;
	// error stream
	string errorFile;
	if (error != nullptr) {
		errorFile = tmpnam(nullptr);
		_command+= " 2>" + errorFile;
	}
	// execute command
	FILE* pipe = nullptr;
	try {
		array<char, 128> buffer;
		#if defined(_MSC_VER)
			pipe = _popen(_command.c_str(), "r");
		#else
			pipe = popen(_command.c_str(), "r");
		#endif
		if (pipe == nullptr) throw std::runtime_error("popen() failed!");
		while (feof(pipe) == false) {
			if (fgets(buffer.data(), buffer.size(), pipe) != nullptr) result += buffer.data();
		}
	} catch (Exception& exception) {
		_Console::printLine("ApplicationMethods::execute(): An error occurred: " + string(exception.what()));
	}
	// get exit code, if we have a pipe
	if (pipe != nullptr) {
		#if defined(_MSC_VER)
			_exitCode = _pclose(pipe);
		#else
			_exitCode = pclose(pipe);
		#endif
	}
	// store it to given exit code int pointer
	if (exitCode != nullptr) *exitCode = _exitCode;
	// store error to given string error pointer
	if (error != nullptr) {
		try {
			*error = FileSystem::getContentAsString(
				FileSystem::getPathName(errorFile),
				FileSystem::getFileName(errorFile)
			);
			FileSystem::removeFile(
				FileSystem::getPathName(errorFile),
				FileSystem::getFileName(errorFile)
			);
		} catch (Exception& exception) {
			_Console::printLine("ApplicationMethods::execute(): An error occurred: " + string(exception.what()));
		}
	}
	// done
	return result;
}

void ApplicationMethods::registerMethods(MinitScript* minitScript) {
	// application
	{
		//
		class MethodApplicationExecute: public MinitScript::Method {
		private:
			MinitScript* minitScript { nullptr };
		public:
			MethodApplicationExecute(MinitScript* minitScript):
				MinitScript::Method(
					{
						{ .type = MinitScript::TYPE_STRING, .name = "command", .optional = false, .reference = false, .nullable = false },
						{ .type = MinitScript::TYPE_INTEGER, .name = "exitCode", .optional = true, .reference = true, .nullable = true },
						{ .type = MinitScript::TYPE_STRING, .name = "error", .optional = true, .reference = true, .nullable = true },
					},
					MinitScript::TYPE_STRING
				),
				minitScript(minitScript) {}
			const string getMethodName() override {
				return "application.execute";
			}
			void executeMethod(span<MinitScript::Variable>& arguments, MinitScript::Variable& returnValue, const MinitScript::SubStatement& subStatement) override {
				string command;
				if ((arguments.size() == 1 || arguments.size() == 2 || arguments.size() == 3) &&
					MinitScript::getStringValue(arguments, 0, command) == true) {
					int exitCode = -1;
					string error;
					int* exitCodePtr = arguments.size() >= 2?&exitCode:nullptr;
					string* errorPtr = arguments.size() >= 3?&error:nullptr;
					returnValue.setValue(ApplicationMethods::execute(command, exitCodePtr, errorPtr));
					if (exitCodePtr != nullptr) arguments[1].setValue(static_cast<int64_t>(exitCode));
					if (errorPtr != nullptr) arguments[2].setValue(error);
				} else {
					MINITSCRIPT_METHODUSAGE_COMPLAIN(getMethodName());
				}
			}
		};
		minitScript->registerMethod(new MethodApplicationExecute(minitScript));
	}
	//
	if (minitScript->getContext() != nullptr) {
		//
		{
			//
			class MethodApplicationGetArguments: public MinitScript::Method {
			private:
				MinitScript* minitScript { nullptr };
			public:
				MethodApplicationGetArguments(MinitScript* minitScript):
					MinitScript::Method({}, MinitScript::TYPE_ARRAY),
					minitScript(minitScript) {}
				const string getMethodName() override {
					return "application.getArguments";
				}
				void executeMethod(span<MinitScript::Variable>& arguments, MinitScript::Variable& returnValue, const MinitScript::SubStatement& subStatement) override {
					if (arguments.size() == 0) {
						returnValue.setType(MinitScript::TYPE_ARRAY);
						for (const auto& argumentValue: minitScript->getContext()->getArgumentValues()) {
							returnValue.pushArrayEntry(MinitScript::Variable(argumentValue));
						}
					} else {
						MINITSCRIPT_METHODUSAGE_COMPLAIN(getMethodName());
					}
				}
			};
			minitScript->registerMethod(new MethodApplicationGetArguments(minitScript));
		}
		{
			//
			class MethodApplicationExit: public MinitScript::Method {
			private:
				MinitScript* minitScript { nullptr };
			public:
				MethodApplicationExit(MinitScript* minitScript):
					MinitScript::Method(
						{
							{ .type = MinitScript::TYPE_INTEGER, .name = "exitCode", .optional = true, .reference = false, .nullable = false },
						}
					),
					minitScript(minitScript) {}
				const string getMethodName() override {
					return "application.exit";
				}
				void executeMethod(span<MinitScript::Variable>& arguments, MinitScript::Variable& returnValue, const MinitScript::SubStatement& subStatement) override {
					int64_t exitCode = 0ll;
					if ((arguments.size() == 0 || arguments.size() == 1) &&
						MinitScript::getIntegerValue(arguments, 0, exitCode, true) == true) {
						minitScript->getContext()->setExitCode(static_cast<int>(exitCode));
						minitScript->stopScriptExecution();
					} else {
						MINITSCRIPT_METHODUSAGE_COMPLAIN(getMethodName());
					}
				}
			};
			minitScript->registerMethod(new MethodApplicationExit(minitScript));
		}
	}
}
