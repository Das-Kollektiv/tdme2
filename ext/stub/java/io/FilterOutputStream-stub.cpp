// Generated from /Library/Java/JavaVirtualMachines/1.6.0.jdk/Contents/Classes/classes.jar
#include <java/io/FilterOutputStream.h>

using java::io::FilterOutputStream;
extern void unimplemented_(const char16_t* name);
java::io::FilterOutputStream::FilterOutputStream(const ::default_init_tag&)
	: super(*static_cast< ::default_init_tag* >(0))
{
	clinit();
}

java::io::FilterOutputStream::FilterOutputStream(OutputStream* arg0)
	: FilterOutputStream(*static_cast< ::default_init_tag* >(0))
{
	ctor(arg0);
}


void FilterOutputStream::ctor(OutputStream* arg0)
{ /* stub */
	/* super::ctor(); */
	unimplemented_(u"void FilterOutputStream::ctor(OutputStream* arg0)");
}

void FilterOutputStream::close()
{ /* stub */
	unimplemented_(u"void FilterOutputStream::close()");
}

void FilterOutputStream::flush()
{ /* stub */
	unimplemented_(u"void FilterOutputStream::flush()");
}

void FilterOutputStream::write(int32_t arg0)
{ /* stub */
	unimplemented_(u"void FilterOutputStream::write(int32_t arg0)");
}

void FilterOutputStream::write(int8_tArray* arg0)
{ /* stub */
	unimplemented_(u"void FilterOutputStream::write(int8_tArray* arg0)");
}

void FilterOutputStream::write(int8_tArray* arg0, int32_t arg1, int32_t arg2)
{ /* stub */
	unimplemented_(u"void FilterOutputStream::write(int8_tArray* arg0, int32_t arg1, int32_t arg2)");
}

extern java::lang::Class* class_(const char16_t* c, int n);

java::lang::Class* FilterOutputStream::class_()
{
    static ::java::lang::Class* c = ::class_(u"java.io.FilterOutputStream", 26);
    return c;
}

java::lang::Class* FilterOutputStream::getClass0()
{
	return class_();
}

