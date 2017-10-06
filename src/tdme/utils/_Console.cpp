#include <iostream>
#include <string>

#include <tdme/utils/_Console.h>
#include <tdme/utils/Time.h>

using namespace std;

using tdme::utils::_Console;
using tdme::utils::Time;

Mutex _Console::mutex(L"console");

void _Console::println(const wstring& string)
{
	mutex.lock();
	wcout << string << endl;
	mutex.unlock();
}

void _Console::println(const string& string)
{
	mutex.lock();
	cout << string << endl;
	mutex.unlock();
}

void _Console::print(const wstring& string)
{
	mutex.lock();
	wcout << string;
	mutex.unlock();
}

void _Console::print(const string& string)
{
	mutex.lock();
	cout << string;
	mutex.unlock();
}

void _Console::println()
{
	mutex.lock();
	wcout << endl;
	mutex.unlock();
}

