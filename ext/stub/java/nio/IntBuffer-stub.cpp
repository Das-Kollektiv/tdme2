// Generated from /Library/Java/JavaVirtualMachines/1.6.0.jdk/Contents/Classes/classes.jar
#include <java/nio/IntBuffer.h>

using java::nio::IntBuffer;
extern void unimplemented_(const char16_t* name);
java::nio::IntBuffer::IntBuffer(const ::default_init_tag&)
	: super(*static_cast< ::default_init_tag* >(0))
{
	clinit();
}

java::nio::IntBuffer::IntBuffer(int32_t arg0, int32_t arg1, int32_t arg2, int32_t arg3)
	: IntBuffer(*static_cast< ::default_init_tag* >(0))
{
	ctor(arg0, arg1, arg2, arg3);
}

java::nio::IntBuffer::IntBuffer(int32_t arg0, int32_t arg1, int32_t arg2, int32_t arg3, int32_tArray* arg4, int32_t arg5)
	: IntBuffer(*static_cast< ::default_init_tag* >(0))
{
	ctor(arg0, arg1, arg2, arg3, arg4, arg5);
}


void IntBuffer::ctor(int32_t arg0, int32_t arg1, int32_t arg2, int32_t arg3)
{ /* stub */
	/* super::ctor(); */
	unimplemented_(u"void IntBuffer::ctor(int32_t arg0, int32_t arg1, int32_t arg2, int32_t arg3)");
}

void IntBuffer::ctor(int32_t arg0, int32_t arg1, int32_t arg2, int32_t arg3, int32_tArray* arg4, int32_t arg5)
{ /* stub */
	/* super::ctor(); */
	unimplemented_(u"void IntBuffer::ctor(int32_t arg0, int32_t arg1, int32_t arg2, int32_t arg3, int32_tArray* arg4, int32_t arg5)");
}

IntBuffer* IntBuffer::allocate(int32_t arg0)
{ /* stub */
	clinit();
	unimplemented_(u"IntBuffer* IntBuffer::allocate(int32_t arg0)");
	return 0;
}

int32_tArray* IntBuffer::array()
{ /* stub */
	unimplemented_(u"int32_tArray* IntBuffer::array()");
	return 0;
}

int32_t IntBuffer::arrayOffset()
{ /* stub */
	unimplemented_(u"int32_t IntBuffer::arrayOffset()");
	return 0;
}

int32_t IntBuffer::compareTo(IntBuffer* arg0)
{ /* stub */
	unimplemented_(u"int32_t IntBuffer::compareTo(IntBuffer* arg0)");
	return 0;
}

int32_t IntBuffer::compareTo(Object* o)
{ 
	return compareTo(dynamic_cast< IntBuffer* >(o));
}

bool IntBuffer::equals(Object* arg0)
{ /* stub */
	unimplemented_(u"bool IntBuffer::equals(Object* arg0)");
	return 0;
}

IntBuffer* IntBuffer::get(int32_tArray* arg0)
{ /* stub */
	unimplemented_(u"IntBuffer* IntBuffer::get(int32_tArray* arg0)");
	return 0;
}

IntBuffer* IntBuffer::get(int32_tArray* arg0, int32_t arg1, int32_t arg2)
{ /* stub */
	unimplemented_(u"IntBuffer* IntBuffer::get(int32_tArray* arg0, int32_t arg1, int32_t arg2)");
	return 0;
}

bool IntBuffer::hasArray()
{ /* stub */
	unimplemented_(u"bool IntBuffer::hasArray()");
	return 0;
}

int32_t IntBuffer::hashCode()
{ /* stub */
	unimplemented_(u"int32_t IntBuffer::hashCode()");
	return 0;
}

IntBuffer* IntBuffer::put(IntBuffer* arg0)
{ /* stub */
	unimplemented_(u"IntBuffer* IntBuffer::put(IntBuffer* arg0)");
	return 0;
}

IntBuffer* IntBuffer::put(int32_tArray* arg0)
{ /* stub */
	unimplemented_(u"IntBuffer* IntBuffer::put(int32_tArray* arg0)");
	return 0;
}

IntBuffer* IntBuffer::put(int32_tArray* arg0, int32_t arg1, int32_t arg2)
{ /* stub */
	unimplemented_(u"IntBuffer* IntBuffer::put(int32_tArray* arg0, int32_t arg1, int32_t arg2)");
	return 0;
}

String* IntBuffer::toString()
{ /* stub */
	unimplemented_(u"String* IntBuffer::toString()");
	return 0;
}

IntBuffer* IntBuffer::wrap(int32_tArray* arg0)
{ /* stub */
	clinit();
	unimplemented_(u"IntBuffer* IntBuffer::wrap(int32_tArray* arg0)");
	return 0;
}

IntBuffer* IntBuffer::wrap(int32_tArray* arg0, int32_t arg1, int32_t arg2)
{ /* stub */
	clinit();
	unimplemented_(u"IntBuffer* IntBuffer::wrap(int32_tArray* arg0, int32_t arg1, int32_t arg2)");
	return 0;
}

extern java::lang::Class* class_(const char16_t* c, int n);

java::lang::Class* IntBuffer::class_()
{
    static ::java::lang::Class* c = ::class_(u"java.nio.IntBuffer", 18);
    return c;
}

java::lang::Class* IntBuffer::getClass0()
{
	return class_();
}

