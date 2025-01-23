#if defined(__FreeBSD__) || defined(__linux__) || defined(__NetBSD__) || defined(__OpenBSD__)
	#include <spawn.h>
	#include <sys/types.h>
	#include <sys/wait.h>

	#include <cstring>
#endif

#include <array>
#include <cstdio>
#include <cstdlib>
#include <memory>
#include <span>
#include <string>
#include <vector>

#include <minitscript/minitscript.h>
#include <minitscript/minitscript/ApplicationMethods.h>
#include <minitscript/minitscript/MinitScript.h>
#include <minitscript/os/filesystem/FileSystem.h>
#include <minitscript/os/threading/Mutex.h>
#include <minitscript/os/threading/Thread.h>
#include <minitscript/utilities/Console.h>
#include <minitscript/utilities/Exception.h>
#include <minitscript/utilities/StringTools.h>

using std::array;
using std::make_unique;
using std::span;
using std::shared_ptr;
using std::string;
using std::to_string;
using std::unique_ptr;
using std::vector;

using minitscript::minitscript::ApplicationMethods;

using minitscript::minitscript::MinitScript;

using _Console = minitscript::utilities::Console;
using _Exception = minitscript::utilities::Exception;
using _FileSystem = minitscript::os::filesystem::FileSystem;
using _Mutex = minitscript::os::threading::Mutex;
using _StringTools = minitscript::utilities::StringTools;
using _Thread = minitscript::os::threading::Thread;

extern char **environ;

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
	#if defined(_MSC_VER)
		_command = "chcp 65001 > nul && " + _command
	#endif
	auto _exitCode = EXIT_FAILURE;
	// error stream
	string errorFile;
	if (error != nullptr) {
		#if defined(__MINGW32__) || defined(__MINGW64__)
			errorFile = string() + "." + tmpnam(nullptr);
		#else
			errorFile = tmpnam(nullptr);
		#endif
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
		while (fgets(buffer.data(), buffer.size(), pipe) != nullptr) {
			result += buffer.data();
		}
	} catch (_Exception& exception) {
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
			*error = _FileSystem::getContentAsString(
				_FileSystem::getPathName(errorFile),
				_FileSystem::getFileName(errorFile)
			);
			_FileSystem::removeFile(
				_FileSystem::getPathName(errorFile),
				_FileSystem::getFileName(errorFile)
			);
		} catch (_Exception& exception) {
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
	{
		//
		class MethodApplicationExecuteMultiple: public MinitScript::Method {
		private:
			MinitScript* minitScript { nullptr };
		public:
			MethodApplicationExecuteMultiple(MinitScript* minitScript):
				MinitScript::Method(
					{
						{ .type = MinitScript::TYPE_ARRAY, .name = "commands", .optional = false, .reference = false, .nullable = false },
						{ .type = MinitScript::TYPE_INTEGER, .name = "concurrency", .optional = true, .reference = false, .nullable = false }
					},
					MinitScript::TYPE_BOOLEAN
				),
				minitScript(minitScript) {}
			const string getMethodName() override {
				return "application.executeMultiple";
			}
			void executeMethod(span<MinitScript::Variable>& arguments, MinitScript::Variable& returnValue, const MinitScript::SubStatement& subStatement) override {
				string command;
				int64_t concurrency = 1;
				if ((arguments.size() == 1 || arguments.size() == 2) &&
					arguments[0].getType() == MinitScript::TYPE_ARRAY &&
					MinitScript::getIntegerValue(arguments, 1, concurrency, true) == true) {
					// collect commands
					vector<string> commands;
					auto arrayPtr = arguments[0].getArrayPointer();
					if (arrayPtr != nullptr) {
						for (auto arrayEntry: *arrayPtr) commands.push_back(arrayEntry->getValueAsString());
					}
					/**
					 * Execution commands container
					 */
					class ExecutionCommands {
						private:
							_Mutex mutex;
							const vector<string>& commands;
							int commandIdx { 0 };
						public:
							/**
							 * Constructor
							 * @param commands commands
							 */
							ExecutionCommands(const vector<string>& commands): mutex("cmdlist-mutex"), commands(commands) {
							}
							/**
							 * @return returns left command
							 */
							bool getCommand(string& command) {
								mutex.lock();
								if (commandIdx >= commands.size()) {
									mutex.unlock();
									return false;
								}
								command = commands[commandIdx++];
								mutex.unlock();
								return true;
							}
							/**
							 * Stop delivering commands
							 */
							void stop() {
								mutex.lock();
								commandIdx = commands.size();
								mutex.unlock();
							}
					};
					/**
					 * Execution thread
					 */
					class ExecutionThread: public _Thread {
						private:
							int idx;
							ExecutionCommands* executionCommands;
							bool failure { false };
						public:
							/**
							 * Constructor
							 * @param idx thread index
							 * @param executionCommands excecution commands
							 */
							ExecutionThread(int idx, ExecutionCommands* executionCommands): _Thread("execution-thread"), idx(idx), executionCommands(executionCommands) {
							}
							/**
							 * @returns returns if an error has occurred
							 */
							inline bool hadFailure() {
								return failure;
							}
							/**
							 * Run
							 */
							void run() {
								string command;
								while (executionCommands->getCommand(command) == true) {
									_Console::printLine("[" + to_string(idx) + "]: " + command);
									#if defined(__FreeBSD__) || defined(__linux__) || defined(__NetBSD__) || defined(__OpenBSD__)
										//
										pid_t pid;
										auto commandC = new char[command.size() + 1];
										strcpy(commandC, command.c_str());
										char *argv[] = {"/bin/sh", "-c", commandC, nullptr};
										//
										auto exitCode = EXIT_FAILURE;
										auto status = posix_spawn(&pid, "/bin/sh", nullptr, nullptr, argv, ::environ);
										if (status == 0) {
											do {
												if (waitpid(pid, &status, 0) != -1) {
													exitCode = WEXITSTATUS(status);
												} else {
													break;
												}
											} while (WIFEXITED(status) == 0 && WIFSIGNALED(status) == 0);
										}
										delete [] commandC;
									#else
										int exitCode;
										string error;
										_Console::printLine("[" + to_string(idx) + "]: " + command);
										auto result = ApplicationMethods::execute(command, &exitCode, &error);
										if (result.empty() == false)_Console::printLine(result);
										if (error.empty() == false) _Console::printLine(error);
									#endif
									//
									if (exitCode != EXIT_SUCCESS) {
										executionCommands->stop();
										failure = true;
									}
								}
							}
					};
					// execute
					ExecutionCommands executionCommands(commands);
					vector<unique_ptr<ExecutionThread>> executionThreads;
					executionThreads.resize(concurrency);
					for (auto i = 0; i < concurrency; i++) executionThreads[i] = make_unique<ExecutionThread>(i, &executionCommands);
					for (auto i = 0; i < concurrency; i++) executionThreads[i]->start();
					for (auto i = 0; i < concurrency; i++) executionThreads[i]->join();
					// failure
					auto success = true;
					for (auto i = 0; i < concurrency; i++) {
						if (executionThreads[i]->hadFailure() == true) success = false;
					}
					returnValue.setValue(success);
					//
				} else {
					MINITSCRIPT_METHODUSAGE_COMPLAIN(getMethodName());
				}
			}
		};
		minitScript->registerMethod(new MethodApplicationExecuteMultiple(minitScript));
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
