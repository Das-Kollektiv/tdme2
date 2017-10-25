#include <iostream>
#include <string>

#include <tdme/utils/Console.h>
#include <tdme/utils/Time.h>

using namespace std;

using tdme::utils::Console;
using tdme::utils::Time;

Mutex Console::mutex("console");

void Console::println(const string& str)
{
	mutex.lock();
	cout << str << endl;
	mutex.unlock();
}

void Console::print(const string& str)
{
	mutex.lock();
	cout << str;
	mutex.unlock();
}

void Console::println()
{
	mutex.lock();
	cout << endl;
	mutex.unlock();
}

