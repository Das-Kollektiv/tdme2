#include <array>
#include <cstdio>
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
using miniscript::utilities::Console;
using miniscript::utilities::StringTools;

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
		class ScriptMethodApplicationExecute: public MiniScript::ScriptMethod {
		private:
			MiniScript* miniScript { nullptr };
		public:
			ScriptMethodApplicationExecute(MiniScript* miniScript):
				MiniScript::ScriptMethod(
					{
						{ .type = MiniScript::TYPE_STRING, .name = "command", .optional = false, .reference = false, .nullable = false },
					},
					MiniScript::TYPE_STRING
				),
				miniScript(miniScript) {}
			const string getMethodName() override {
				return "application.execute";
			}
			void executeMethod(span<MiniScript::ScriptVariable>& argumentValues, MiniScript::ScriptVariable& returnValue, const MiniScript::ScriptStatement& statement) override {
				string command;
				if (MiniScript::getStringValue(argumentValues, 0, command, false) == true) {
					returnValue.setValue(ApplicationMethods::execute(command));
				} else {
					Console::println(getMethodName() + "(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation(getMethodName()));
					miniScript->startErrorScript();
				}
			}
		};
		miniScript->registerMethod(new ScriptMethodApplicationExecute(miniScript));
	}
}
