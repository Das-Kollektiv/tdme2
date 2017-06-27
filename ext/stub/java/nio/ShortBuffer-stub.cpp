// Generated from /Library/Java/JavaVirtualMachines/1.6.0.jdk/Contents/Classes/classes.jar
#include <java/nio/ShortBuffer.h>

using java::nio::ShortBuffer;
extern void unimplemented_(const char16_t* name);
java::nio::ShortBuffer::ShortBuffer(const ::default_init_tag&)
	: super(*static_cast< ::default_init_tag* >(0))
{
	clinit();
}

java::nio::ShortBuffer::ShortBuffer(int32_t arg0, int32_t arg1, int32_t arg2, int32_t arg3)
	: ShortBuffer(*static_cast< ::default_init_tag* >(0))
{
	ctor(arg0, arg1, arg2, arg3);
}

java::nio::ShortBuffer::ShortBuffer(int32_t arg0, int32_t arg1, int32_t arg2, int32_t arg3, int16_tArray* arg4, int32_t arg5)
	: ShortBuffer(*static_cast< ::default_init_tag* >(0))
{
	ctor(arg0, arg1, arg2, arg3, arg4, arg5);
}


void ShortBuffer::ctor(int32_t arg0, int32_t arg1, int32_t arg2, int32_t arg3)
{ /* stub */
	/* super::ctor(); */
	unimplemented_(u"void ShortBuffer::ctor(int32_t arg0, int32_t arg1, int32_t arg2, int32_t arg3)");
}

void ShortBuffer::ctor(int32_t arg0, int32_t arg1, int32_t arg2, int32_t arg3, int16_tArray* arg4, int32_t arg5)
{ /* stub */
	/* super::ctor(); */
	unimplemented_(u"void ShortBuffer::ctor(int32_t arg0, int32_t arg1, int32_t arg2, int32_t arg3, int16_tArray* arg4, int32_t arg5)");
}

ShortBuffer* ShortBuffer::allocate(int32_t arg0)
{ /* stub */
	clinit();
	unimplemented_(u"ShortBuffer* ShortBuffer::allocate(int32_t arg0)");
	return 0;
}

int16_tArray* ShortBuffer::array()
{ /* stub */
	unimplemented_(u"int16_tArray* ShortBuffer::array()");
	return 0;
}

int32_t ShortBuffer::arrayOffset()
{ /* stub */
	unimplemented_(u"int32_t ShortBuffer::arrayOffset()");
	return 0;
}

int32_t ShortBuffer::compareTo(ShortBuffer* arg0)
{ /* stub */
	unimplemented_(u"int32_t ShortBuffer::compareTo(ShortBuffer* arg0)");
	return 0;
}

int32_t ShortBuffer::compareTo(Object* o)
{ 
	return compareTo(dynamic_cast< ShortBuffer* >(o));
}

bool ShortBuffer::equals(Object* arg0)
{ /* stub */
	unimplemented_(u"bool ShortBuffer::equals(Object* arg0)");
	return 0;
}

ShortBuffer* ShortBuffer::get(int16_tArray* arg0)
{ /* stub */
	unimplemented_(u"ShortBuffer* ShortBuffer::get(int16_tArray* arg0)");
	return 0;
}

ShortBuffer* ShortBuffer::get(int16_tArray* arg0, int32_t arg1, int32_t arg2)
{ /* stub */
	unimplemented_(u"ShortBuffer* ShortBuffer::get(int16_tArray* arg0, int32_t arg1, int32_t arg2)");
	return 0;
}

bool ShortBuffer::hasArray()
{ /* stub */
	unimplemented_(u"bool ShortBuffer::hasArray()");
	return 0;
}

int32_t ShortBuffer::hashCode()
{ /* stub */
	unimplemented_(u"int32_t ShortBuffer::hashCode()");
	return 0;
}

ShortBuffer* ShortBuffer::put(ShortBuffer* arg0)
{ /* stub */
	unimplemented_(u"ShortBuffer* ShortBuffer::put(ShortBuffer* arg0)");
	return 0;
}

ShortBuffer* ShortBuffer::put(int16_tArray* arg0)
{ /* stub */
	unimplemented_(u"ShortBuffer* ShortBuffer::put(int16_tArray* arg0)");
	return 0;
}

ShortBuffer* ShortBuffer::put(int16_tArray* arg0, int32_t arg1, int32_t arg2)
{ /* stub */
	unimplemented_(u"ShortBuffer* ShortBuffer::put(int16_tArray* arg0, int32_t arg1, int32_t arg2)");
	return 0;
}

String* ShortBuffer::toString()
{ /* stub */
	unimplemented_(u"String* ShortBuffer::toString()");
	return 0;
}

ShortBuffer* ShortBuffer::wrap(int16_tArray* arg0)
{ /* stub */
	clinit();
	unimplemented_(u"ShortBuffer* ShortBuffer::wrap(int16_tArray* arg0)");
	return 0;
}

ShortBuffer* ShortBuffer::wrap(int16_tArray* arg0, int32_t arg1, int32_t arg2)
{ /* stub */
	clinit();
	unimplemented_(u"ShortBuffer* ShortBuffer::wrap(int16_tArray* arg0, int32_t arg1, int32_t arg2)");
	return 0;
}

extern java::lang::Class* class_(const char16_t* c, int n);

java::lang::Class* ShortBuffer::class_()
{
    static ::java::lang::Class* c = ::class_(u"java.nio.ShortBuffer", 20);
    return c;
}

java::lang::Class* ShortBuffer::getClass0()
{
	return class_();
}

