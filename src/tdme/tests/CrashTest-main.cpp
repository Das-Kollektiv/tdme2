#include <tdme/application/Application.h>
#include <tdme/tdme.h>
#include <tdme/utilities/Console.h>

using tdme::application::Application;
using tdme::utilities::Console;

class CrashTestClass {
public:
	static void crash() {
		char* i = nullptr;
		Console::printLine(string("CrashTestClass::crash(): message: ") + i);
	}
};

static void crashTestFunction() {
	CrashTestClass::crash();
}

int main(int argc, char** argv) {
	Application::installExceptionHandler();
	Console::printLine("CrashTest: init");
	crashTestFunction();
	Console::printLine("CrashTest: done");
	//
	Console::shutdown();
	return 0;
}
