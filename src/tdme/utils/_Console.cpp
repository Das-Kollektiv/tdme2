// Generated from /tdme/src/tdme/utils/_Console.java
#include <tdme/utils/_Console.h>

#include <java/io/PrintStream.h>
#include <java/lang/Object.h>
#include <java/lang/System.h>

using tdme::utils::_Console;
using java::io::PrintStream;
using java::lang::Object;
using java::lang::System;

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

void _Console::println(Object* object)
{
	clinit();
	System::out->println(object->toString());
}

void _Console::println(int8_t value)
{
	clinit();
	System::out->println(static_cast< int32_t >(value));
}

void _Console::println(int16_t value)
{
	clinit();
	System::out->println(static_cast< int32_t >(value));
}

void _Console::println(int32_t value)
{
	clinit();
	System::out->println(value);
}

void _Console::println(int64_t value)
{
	clinit();
	System::out->println(value);
}

void _Console::println(float value)
{
	clinit();
	System::out->println(value);
}

void _Console::println(double value)
{
	clinit();
	System::out->println(value);
}

void _Console::println(bool value)
{
	clinit();
	System::out->println(value);
}

void _Console::println(char16_t value)
{
	clinit();
	System::out->println(value);
}

void _Console::print(Object* object)
{
	clinit();
	System::out->print(object->toString());
}

void _Console::print(int8_t value)
{
	clinit();
	System::out->print(static_cast< int32_t >(value));
}

void _Console::print(int16_t value)
{
	clinit();
	System::out->print(static_cast< int32_t >(value));
}

void _Console::print(int32_t value)
{
	clinit();
	System::out->print(value);
}

void _Console::print(int64_t value)
{
	clinit();
	System::out->print(value);
}

void _Console::print(float value)
{
	clinit();
	System::out->print(value);
}

void _Console::print(double value)
{
	clinit();
	System::out->print(value);
}

void _Console::print(bool value)
{
	clinit();
	System::out->print(value);
}

void _Console::print(char16_t value)
{
	clinit();
	System::out->print(value);
}

void _Console::println()
{
	clinit();
	System::out->println();
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

