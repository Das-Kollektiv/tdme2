// Generated from /tdme/lib/jogl-all.jar
#include <com/jogamp/nativewindow/Capabilities.h>

#include <com/jogamp/nativewindow/CapabilitiesImmutable.h>

using com::jogamp::nativewindow::Capabilities;
using com::jogamp::nativewindow::CapabilitiesImmutable;

extern void unimplemented_(const char16_t* name);
com::jogamp::nativewindow::Capabilities::Capabilities(const ::default_init_tag&)
	: super(*static_cast< ::default_init_tag* >(0))
{
	clinit();
}

com::jogamp::nativewindow::Capabilities::Capabilities()
	: Capabilities(*static_cast< ::default_init_tag* >(0))
{
	ctor();
}

String* com::jogamp::nativewindow::Capabilities::CSEP;
String* com::jogamp::nativewindow::Capabilities::ESEP;
String* com::jogamp::nativewindow::Capabilities::na_str;

void Capabilities::ctor()
{ /* stub */
	/* super::ctor(); */
	unimplemented_(u"void Capabilities::ctor()");
}

Object* Capabilities::clone()
{ /* stub */
	unimplemented_(u"Object* Capabilities::clone()");
	return 0;
}

Object* Capabilities::cloneMutable()
{ /* stub */
	unimplemented_(u"Object* Capabilities::cloneMutable()");
	return 0;
}

int32_t Capabilities::compareTo(CapabilitiesImmutable* arg0)
{ /* stub */
	unimplemented_(u"int32_t Capabilities::compareTo(CapabilitiesImmutable* arg0)");
	return 0;
}

int32_t Capabilities::compareTo(Object* o)
{ 
	return compareTo(dynamic_cast< CapabilitiesImmutable* >(o));
}

Capabilities* Capabilities::copyFrom(CapabilitiesImmutable* arg0)
{ /* stub */
	unimplemented_(u"Capabilities* Capabilities::copyFrom(CapabilitiesImmutable* arg0)");
	return 0;
}

bool Capabilities::equals(Object* arg0)
{ /* stub */
	unimplemented_(u"bool Capabilities::equals(Object* arg0)");
	return 0;
}

int32_t Capabilities::getAlphaBits()
{ /* stub */
return alphaBits ; /* getter */
}

int32_t Capabilities::getBlueBits()
{ /* stub */
return blueBits ; /* getter */
}

int32_t Capabilities::getGreenBits()
{ /* stub */
return greenBits ; /* getter */
}

int32_t Capabilities::getRedBits()
{ /* stub */
return redBits ; /* getter */
}

int32_t Capabilities::getTransparentAlphaValue()
{ /* stub */
	unimplemented_(u"int32_t Capabilities::getTransparentAlphaValue()");
	return 0;
}

int32_t Capabilities::getTransparentBlueValue()
{ /* stub */
	unimplemented_(u"int32_t Capabilities::getTransparentBlueValue()");
	return 0;
}

int32_t Capabilities::getTransparentGreenValue()
{ /* stub */
	unimplemented_(u"int32_t Capabilities::getTransparentGreenValue()");
	return 0;
}

int32_t Capabilities::getTransparentRedValue()
{ /* stub */
	unimplemented_(u"int32_t Capabilities::getTransparentRedValue()");
	return 0;
}

int32_t Capabilities::getVisualID(VisualIDHolder_VIDType* arg0)
{ /* stub */
	unimplemented_(u"int32_t Capabilities::getVisualID(VisualIDHolder_VIDType* arg0)");
	return 0;
}

int32_t Capabilities::hashCode()
{ /* stub */
	unimplemented_(u"int32_t Capabilities::hashCode()");
	return 0;
}

bool Capabilities::isBackgroundOpaque()
{ /* stub */
	unimplemented_(u"bool Capabilities::isBackgroundOpaque()");
	return 0;
}

bool Capabilities::isBitmap()
{ /* stub */
	unimplemented_(u"bool Capabilities::isBitmap()");
	return 0;
}

bool Capabilities::isOnscreen()
{ /* stub */
	unimplemented_(u"bool Capabilities::isOnscreen()");
	return 0;
}

StringBuilder* Capabilities::onoffScreenToString(StringBuilder* arg0)
{ /* stub */
	unimplemented_(u"StringBuilder* Capabilities::onoffScreenToString(StringBuilder* arg0)");
	return 0;
}

void Capabilities::setAlphaBits(int32_t arg0)
{ /* stub */
	this->alphaBits = arg0; /* setter */
}

void Capabilities::setBackgroundOpaque(bool arg0)
{ /* stub */
	this->backgroundOpaque = arg0; /* setter */
}

void Capabilities::setBitmap(bool arg0)
{ /* stub */
	unimplemented_(u"void Capabilities::setBitmap(bool arg0)");
}

void Capabilities::setBlueBits(int32_t arg0)
{ /* stub */
	this->blueBits = arg0; /* setter */
}

void Capabilities::setGreenBits(int32_t arg0)
{ /* stub */
	this->greenBits = arg0; /* setter */
}

void Capabilities::setOnscreen(bool arg0)
{ /* stub */
	this->onscreen = arg0; /* setter */
}

void Capabilities::setRedBits(int32_t arg0)
{ /* stub */
	this->redBits = arg0; /* setter */
}

void Capabilities::setTransparentAlphaValue(int32_t arg0)
{ /* stub */
	unimplemented_(u"void Capabilities::setTransparentAlphaValue(int32_t arg0)");
}

void Capabilities::setTransparentBlueValue(int32_t arg0)
{ /* stub */
	unimplemented_(u"void Capabilities::setTransparentBlueValue(int32_t arg0)");
}

void Capabilities::setTransparentGreenValue(int32_t arg0)
{ /* stub */
	unimplemented_(u"void Capabilities::setTransparentGreenValue(int32_t arg0)");
}

void Capabilities::setTransparentRedValue(int32_t arg0)
{ /* stub */
	unimplemented_(u"void Capabilities::setTransparentRedValue(int32_t arg0)");
}

String* Capabilities::toHexString(int32_t arg0)
{ /* stub */
	unimplemented_(u"String* Capabilities::toHexString(int32_t arg0)");
	return 0;
}

String* Capabilities::toString()
{ /* stub */
	unimplemented_(u"String* Capabilities::toString()");
	return 0;
}

StringBuilder* Capabilities::toString(StringBuilder* arg0)
{ /* stub */
	unimplemented_(u"StringBuilder* Capabilities::toString(StringBuilder* arg0)");
	return 0;
}

StringBuilder* Capabilities::toString(StringBuilder* arg0, bool arg1)
{ /* stub */
	unimplemented_(u"StringBuilder* Capabilities::toString(StringBuilder* arg0, bool arg1)");
	return 0;
}

extern java::lang::Class* class_(const char16_t* c, int n);

java::lang::Class* Capabilities::class_()
{
    static ::java::lang::Class* c = ::class_(u"com.jogamp.nativewindow.Capabilities", 36);
    return c;
}

java::lang::Class* Capabilities::getClass0()
{
	return class_();
}

