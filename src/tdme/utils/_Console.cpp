#include <iostream>
#include <string>

#include <tdme/utils/_Console.h>

#include <java/lang/Object.h>
#include <tdme/utils/Time.h>
#include <java/lang/String.h>

using namespace std;

using tdme::utils::_Console;
using java::io::PrintStream;
using java::lang::Object;
using tdme::utils::Time;

_Console::_Console(const ::default_init_tag&)
	: super(*static_cast< ::default_init_tag* >(0))
{
	clinit();
}

_Console::_Console()
	: _Console(*static_cast< ::default_init_tag* >(0))
{
	ctor();
}

void _Console::println(const wstring& string)
{
	clinit();
	wcout << string << endl;
}

void _Console::println(const string& string)
{
	clinit();
	cout << string << endl;
}

void _Console::println(Object* object)
{
	clinit();
	wcout << object->toString()->getCPPWString() << endl;
}

void _Console::println(int8_t value)
{
	clinit();
	wcout << value << endl;
}

void _Console::println(int16_t value)
{
	clinit();
	wcout << value << endl;
}

void _Console::println(int32_t value)
{
	clinit();
	wcout << value << endl;
}

void _Console::println(int64_t value)
{
	clinit();
	wcout << value << endl;
}

void _Console::println(float value)
{
	clinit();
	wcout << value << endl;
}

void _Console::println(double value)
{
	clinit();
	wcout << value << endl;
}

void _Console::println(bool value)
{
	clinit();
	wcout << value << endl;
}

void _Console::println(char16_t value)
{
	clinit();
	wcout << value << endl;
}

void _Console::print(const wstring& string)
{
	clinit();
	wcout << string;
}

void _Console::print(const string& string)
{
	clinit();
	cout << string;
}

void _Console::print(Object* object)
{
	clinit();
	wcout << object->toString()->getCPPWString();
}

void _Console::print(int8_t value)
{
	clinit();
	wcout << value;
}

void _Console::print(int16_t value)
{
	clinit();
	wcout << value;
}

void _Console::print(int32_t value)
{
	clinit();
	wcout << value;
}

void _Console::print(int64_t value)
{
	clinit();
	wcout << value;
}

void _Console::print(float value)
{
	clinit();
	wcout << value;
}

void _Console::print(double value)
{
	clinit();
	wcout << value;
}

void _Console::print(bool value)
{
	clinit();
	wcout << value;
}

void _Console::print(char16_t value)
{
	clinit();
	wcout << value;
}

void _Console::println()
{
	clinit();
	wcout << endl;
}

extern java::lang::Class* class_(const char16_t* c, int n);

java::lang::Class* _Console::class_()
{
    static ::java::lang::Class* c = ::class_(u"tdme.utils._Console", 19);
    return c;
}

java::lang::Class* _Console::getClass0()
{
	return class_();
}

