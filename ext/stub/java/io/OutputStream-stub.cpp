// Generated from /Library/Java/JavaVirtualMachines/1.6.0.jdk/Contents/Classes/classes.jar
#include <java/io/OutputStream.h>

using java::io::OutputStream;
extern void unimplemented_(const char16_t* name);
java::io::OutputStream::OutputStream(const ::default_init_tag&)
	: super(*static_cast< ::default_init_tag* >(0))
{
	clinit();
}

java::io::OutputStream::OutputStream()
	: OutputStream(*static_cast< ::default_init_tag* >(0))
{
	ctor();
}


void OutputStream::ctor()
{ /* stub */
	/* super::ctor(); */
	unimplemented_(u"void OutputStream::ctor()");
}

void OutputStream::close()
{ /* stub */
	unimplemented_(u"void OutputStream::close()");
}

void OutputStream::flush()
{ /* stub */
	unimplemented_(u"void OutputStream::flush()");
}

void OutputStream::write(int8_tArray* arg0)
{ /* stub */
	unimplemented_(u"void OutputStream::write(int8_tArray* arg0)");
}

void OutputStream::write(int8_tArray* arg0, int32_t arg1, int32_t arg2)
{ /* stub */
	unimplemented_(u"void OutputStream::write(int8_tArray* arg0, int32_t arg1, int32_t arg2)");
}

extern java::lang::Class* class_(const char16_t* c, int n);

java::lang::Class* OutputStream::class_()
{
    static ::java::lang::Class* c = ::class_(u"java.io.OutputStream", 20);
    return c;
}

java::lang::Class* OutputStream::getClass0()
{
	return class_();
}

