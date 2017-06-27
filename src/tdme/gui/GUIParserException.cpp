// Generated from /tdme/src/tdme/gui/GUIParserException.java
#include <tdme/gui/GUIParserException.h>

using tdme::gui::GUIParserException;
GUIParserException::GUIParserException(const ::default_init_tag&)
	: super(*static_cast< ::default_init_tag* >(0))
{
	clinit();
}

GUIParserException::GUIParserException(String* message) 
	: GUIParserException(*static_cast< ::default_init_tag* >(0))
{
	ctor(message);
}

void GUIParserException::ctor(String* message)
{
	super::ctor(message);
}

extern java::lang::Class* class_(const char16_t* c, int n);

java::lang::Class* GUIParserException::class_()
{
    static ::java::lang::Class* c = ::class_(u"tdme.gui.GUIParserException", 27);
    return c;
}

java::lang::Class* GUIParserException::getClass0()
{
	return class_();
}

