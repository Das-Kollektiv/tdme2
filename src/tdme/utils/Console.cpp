#include <iostream>
#include <string>

#include <tdme/utils/Console.h>
#include <tdme/utils/Time.h>

using namespace std;

using tdme::utils::Console;
using tdme::utils::Time;

Mutex Console::mutex(L"console");

void Console::println(const wstring& string)
{
	mutex.lock();
	wcout << string << endl;
	mutex.unlock();
}

void Console::println(const string& string)
{
	mutex.lock();
	cout << string << endl;
	mutex.unlock();
}

void Console::print(const wstring& string)
{
	mutex.lock();
	wcout << string;
	mutex.unlock();
}

void Console::print(const string& string)
{
	mutex.lock();
	cout << string;
	mutex.unlock();
}

void Console::println()
{
	mutex.lock();
	wcout << endl;
	mutex.unlock();
}

