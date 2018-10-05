#include <tdme/tests/CrashTest.h>

#include <tdme/application/Application.h>
#include <tdme/utils/Console.h>

using tdme::tests::CrashTest;

using tdme::application::Application;
using tdme::utils::Console;

class XXX {
public:
	static void xxxTest() {
		char* i = nullptr;
		Console::println(string("CrashTest::main(): message: ") + i);
	}
};

void test() {
	XXX::xxxTest();
}

void CrashTest::main()
{
	Application::installExceptionHandler();
	Console::println("CrashTest::main(): init");
	test();
	Console::println("CrashTest::main(): done");
}
