#include <tdme/tdme.h>
#include <tdme/application/Application.h>
#include <tdme/utilities/Console.h>

using tdme::application::Application;
using tdme::utilities::Console;

class CrashTestClass {
public:
	static void crash() {
		char* i = nullptr;
		Console::println(string("CrashTestClass::crash(): message: ") + i);
	}
};

static void crashTestFunction() {
	CrashTestClass::crash();
}

int main(int argc, char** argv) {
	Application::installExceptionHandler();
	Console::println("CrashTest: init");
	crashTestFunction();
	Console::println("CrashTest: done");
	//
	Console::shutdown();
	return 0;
}
