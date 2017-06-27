// Generated from /tdme/lib/jogl-all.jar
#include <com/jogamp/opengl/GLCapabilities.h>

#include <com/jogamp/nativewindow/CapabilitiesImmutable.h>

using com::jogamp::opengl::GLCapabilities;
using com::jogamp::nativewindow::CapabilitiesImmutable;

extern void unimplemented_(const char16_t* name);
com::jogamp::opengl::GLCapabilities::GLCapabilities(const ::default_init_tag&)
	: super(*static_cast< ::default_init_tag* >(0))
{
	clinit();
}

com::jogamp::opengl::GLCapabilities::GLCapabilities(GLProfile* arg0)
	: GLCapabilities(*static_cast< ::default_init_tag* >(0))
{
	ctor(arg0);
}


void GLCapabilities::ctor(GLProfile* arg0)
{ /* stub */
	/* super::ctor(); */
	unimplemented_(u"void GLCapabilities::ctor(GLProfile* arg0)");
}

Object* GLCapabilities::clone()
{ /* stub */
	unimplemented_(u"Object* GLCapabilities::clone()");
	return 0;
}

Object* GLCapabilities::cloneMutable()
{ /* stub */
	unimplemented_(u"Object* GLCapabilities::cloneMutable()");
	return 0;
}

int32_t GLCapabilities::compareTo(CapabilitiesImmutable* arg0)
{ /* stub */
	unimplemented_(u"int32_t GLCapabilities::compareTo(CapabilitiesImmutable* arg0)");
	return 0;
}

int32_t GLCapabilities::compareTo(Object* o)
{ 
	return compareTo(dynamic_cast< CapabilitiesImmutable* >(o));
}

GLCapabilities* GLCapabilities::copyFrom(GLCapabilitiesImmutable* arg0)
{ /* stub */
	unimplemented_(u"GLCapabilities* GLCapabilities::copyFrom(GLCapabilitiesImmutable* arg0)");
	return 0;
}

bool GLCapabilities::equals(Object* arg0)
{ /* stub */
	unimplemented_(u"bool GLCapabilities::equals(Object* arg0)");
	return 0;
}

int32_t GLCapabilities::getAccumAlphaBits()
{ /* stub */
return accumAlphaBits ; /* getter */
}

int32_t GLCapabilities::getAccumBlueBits()
{ /* stub */
return accumBlueBits ; /* getter */
}

int32_t GLCapabilities::getAccumGreenBits()
{ /* stub */
return accumGreenBits ; /* getter */
}

int32_t GLCapabilities::getAccumRedBits()
{ /* stub */
return accumRedBits ; /* getter */
}

int32_t GLCapabilities::getDepthBits()
{ /* stub */
return depthBits ; /* getter */
}

bool GLCapabilities::getDoubleBuffered()
{ /* stub */
return doubleBuffered ; /* getter */
}

GLProfile* GLCapabilities::getGLProfile()
{ /* stub */
	unimplemented_(u"GLProfile* GLCapabilities::getGLProfile()");
	return 0;
}

bool GLCapabilities::getHardwareAccelerated()
{ /* stub */
return hardwareAccelerated ; /* getter */
}

int32_t GLCapabilities::getNumSamples()
{ /* stub */
return numSamples ; /* getter */
}

bool GLCapabilities::getSampleBuffers()
{ /* stub */
return sampleBuffers ; /* getter */
}

String* GLCapabilities::getSampleExtension()
{ /* stub */
return sampleExtension ; /* getter */
}

int32_t GLCapabilities::getStencilBits()
{ /* stub */
return stencilBits ; /* getter */
}

bool GLCapabilities::getStereo()
{ /* stub */
return stereo ; /* getter */
}

int32_t GLCapabilities::hashCode()
{ /* stub */
	unimplemented_(u"int32_t GLCapabilities::hashCode()");
	return 0;
}

bool GLCapabilities::isFBO()
{ /* stub */
	unimplemented_(u"bool GLCapabilities::isFBO()");
	return 0;
}

bool GLCapabilities::isPBuffer()
{ /* stub */
	unimplemented_(u"bool GLCapabilities::isPBuffer()");
	return 0;
}

void GLCapabilities::setAccumAlphaBits(int32_t arg0)
{ /* stub */
	this->accumAlphaBits = arg0; /* setter */
}

void GLCapabilities::setAccumBlueBits(int32_t arg0)
{ /* stub */
	this->accumBlueBits = arg0; /* setter */
}

void GLCapabilities::setAccumGreenBits(int32_t arg0)
{ /* stub */
	this->accumGreenBits = arg0; /* setter */
}

void GLCapabilities::setAccumRedBits(int32_t arg0)
{ /* stub */
	this->accumRedBits = arg0; /* setter */
}

void GLCapabilities::setDepthBits(int32_t arg0)
{ /* stub */
	this->depthBits = arg0; /* setter */
}

void GLCapabilities::setDoubleBuffered(bool arg0)
{ /* stub */
	this->doubleBuffered = arg0; /* setter */
}

void GLCapabilities::setFBO(bool arg0)
{ /* stub */
	unimplemented_(u"void GLCapabilities::setFBO(bool arg0)");
}

void GLCapabilities::setGLProfile(GLProfile* arg0)
{ /* stub */
	unimplemented_(u"void GLCapabilities::setGLProfile(GLProfile* arg0)");
}

void GLCapabilities::setHardwareAccelerated(bool arg0)
{ /* stub */
	this->hardwareAccelerated = arg0; /* setter */
}

void GLCapabilities::setNumSamples(int32_t arg0)
{ /* stub */
	this->numSamples = arg0; /* setter */
}

void GLCapabilities::setPBuffer(bool arg0)
{ /* stub */
	unimplemented_(u"void GLCapabilities::setPBuffer(bool arg0)");
}

void GLCapabilities::setSampleBuffers(bool arg0)
{ /* stub */
	this->sampleBuffers = arg0; /* setter */
}

void GLCapabilities::setSampleExtension(String* arg0)
{ /* stub */
	this->sampleExtension = arg0; /* setter */
}

void GLCapabilities::setStencilBits(int32_t arg0)
{ /* stub */
	this->stencilBits = arg0; /* setter */
}

void GLCapabilities::setStereo(bool arg0)
{ /* stub */
	this->stereo = arg0; /* setter */
}

String* GLCapabilities::toString()
{ /* stub */
	unimplemented_(u"String* GLCapabilities::toString()");
	return 0;
}

StringBuilder* GLCapabilities::toString(StringBuilder* arg0)
{ /* stub */
	unimplemented_(u"StringBuilder* GLCapabilities::toString(StringBuilder* arg0)");
	return 0;
}

extern java::lang::Class* class_(const char16_t* c, int n);

java::lang::Class* GLCapabilities::class_()
{
    static ::java::lang::Class* c = ::class_(u"com.jogamp.opengl.GLCapabilities", 32);
    return c;
}

int32_t GLCapabilities::getAlphaBits()
{
	return Capabilities::getAlphaBits();
}

int32_t GLCapabilities::getBlueBits()
{
	return Capabilities::getBlueBits();
}

int32_t GLCapabilities::getGreenBits()
{
	return Capabilities::getGreenBits();
}

int32_t GLCapabilities::getRedBits()
{
	return Capabilities::getRedBits();
}

int32_t GLCapabilities::getTransparentAlphaValue()
{
	return Capabilities::getTransparentAlphaValue();
}

int32_t GLCapabilities::getTransparentBlueValue()
{
	return Capabilities::getTransparentBlueValue();
}

int32_t GLCapabilities::getTransparentGreenValue()
{
	return Capabilities::getTransparentGreenValue();
}

int32_t GLCapabilities::getTransparentRedValue()
{
	return Capabilities::getTransparentRedValue();
}

bool GLCapabilities::isBackgroundOpaque()
{
	return Capabilities::isBackgroundOpaque();
}

bool GLCapabilities::isBitmap()
{
	return Capabilities::isBitmap();
}

bool GLCapabilities::isOnscreen()
{
	return Capabilities::isOnscreen();
}

int32_t GLCapabilities::getVisualID(VisualIDHolder_VIDType* arg0)
{
	return Capabilities::getVisualID(arg0);
}

Capabilities* GLCapabilities::copyFrom(CapabilitiesImmutable* arg0)
{
	return super::copyFrom(arg0);
}

StringBuilder* GLCapabilities::toString(StringBuilder* arg0, bool arg1)
{
	return super::toString(arg0, arg1);
}

java::lang::Class* GLCapabilities::getClass0()
{
	return class_();
}

