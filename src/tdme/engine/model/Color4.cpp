// Generated from /tdme/src/tdme/engine/model/Color4.java
#include <tdme/engine/model/Color4.h>

#include <tdme/engine/model/Color4Base.h>

using tdme::engine::model::Color4;
using tdme::engine::model::Color4Base;

Color4::Color4(const ::default_init_tag&)
	: super(*static_cast< ::default_init_tag* >(0))
{
	clinit();
}

Color4::Color4() 
	: Color4(*static_cast< ::default_init_tag* >(0))
{
	ctor();
}

Color4::Color4(Color4* color) 
	: Color4(*static_cast< ::default_init_tag* >(0))
{
	ctor(color);
}

Color4::Color4(float r, float g, float b, float a) 
	: Color4(*static_cast< ::default_init_tag* >(0))
{
	ctor(r,g,b,a);
}

Color4::Color4(floatArray* color) 
	: Color4(*static_cast< ::default_init_tag* >(0))
{
	ctor(color);
}

void Color4::ctor()
{
	super::ctor();
}

void Color4::ctor(Color4* color)
{
	super::ctor(static_cast< Color4Base* >(color));
}

void Color4::ctor(float r, float g, float b, float a)
{
	super::ctor(r, g, b, a);
}

void Color4::ctor(floatArray* color)
{
	super::ctor(color);
}

extern java::lang::Class* class_(const char16_t* c, int n);

java::lang::Class* Color4::class_()
{
    static ::java::lang::Class* c = ::class_(u"tdme.engine.model.Color4", 24);
    return c;
}

java::lang::Class* Color4::getClass0()
{
	return class_();
}

