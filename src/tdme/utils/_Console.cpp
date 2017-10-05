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

void _Console::println(int8_t value)
{
	mutex.lock();
	wcout << value << endl;
	mutex.unlock();
}

void _Console::println(int16_t value)
{
	mutex.lock();
	wcout << value << endl;
	mutex.unlock();
}

void _Console::println(int32_t value)
{
	mutex.lock();
	wcout << value << endl;
	mutex.unlock();
}

void _Console::println(int64_t value)
{
	mutex.lock();
	wcout << value << endl;
	mutex.unlock();
}

void _Console::println(float value)
{
	mutex.lock();
	wcout << value << endl;
	mutex.unlock();
}

void _Console::println(double value)
{
	mutex.lock();
	wcout << value << endl;
	mutex.unlock();
}

void _Console::println(bool value)
{
	mutex.lock();
	wcout << value << endl;
	mutex.unlock();
}

void _Console::println(char16_t value)
{
	mutex.lock();
	wcout << value << endl;
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

void _Console::print(int8_t value)
{
	mutex.lock();
	wcout << value;
	mutex.unlock();
}

void _Console::print(int16_t value)
{
	mutex.lock();
	wcout << value;
	mutex.unlock();
}

void _Console::print(int32_t value)
{
	mutex.lock();
	wcout << value;
	mutex.unlock();
}

void _Console::print(int64_t value)
{
	mutex.lock();
	wcout << value;
	mutex.unlock();
}

void _Console::print(float value)
{
	mutex.lock();
	wcout << value;
	mutex.unlock();
}

void _Console::print(double value)
{
	mutex.lock();
	wcout << value;
	mutex.unlock();
}

void _Console::print(bool value)
{
	mutex.lock();
	wcout << value;
	mutex.unlock();
}

void _Console::print(char16_t value)
{
	mutex.lock();
	wcout << value;
	mutex.unlock();
}

void _Console::println()
{
	mutex.lock();
	wcout << endl;
	mutex.unlock();
}

