// Generated from /Library/Java/JavaVirtualMachines/1.6.0.jdk/Contents/Classes/classes.jar
#include <java/nio/ByteBuffer.h>

using java::nio::ByteBuffer;
extern void unimplemented_(const char16_t* name);
java::nio::ByteBuffer::ByteBuffer(const ::default_init_tag&)
	: super(*static_cast< ::default_init_tag* >(0))
{
	clinit();
}

java::nio::ByteBuffer::ByteBuffer(int32_t arg0, int32_t arg1, int32_t arg2, int32_t arg3)
	: ByteBuffer(*static_cast< ::default_init_tag* >(0))
{
	ctor(arg0, arg1, arg2, arg3);
}

java::nio::ByteBuffer::ByteBuffer(int32_t arg0, int32_t arg1, int32_t arg2, int32_t arg3, int8_tArray* arg4, int32_t arg5)
	: ByteBuffer(*static_cast< ::default_init_tag* >(0))
{
	ctor(arg0, arg1, arg2, arg3, arg4, arg5);
}


void ByteBuffer::ctor(int32_t arg0, int32_t arg1, int32_t arg2, int32_t arg3)
{ /* stub */
	/* super::ctor(); */
	unimplemented_(u"void ByteBuffer::ctor(int32_t arg0, int32_t arg1, int32_t arg2, int32_t arg3)");
}

void ByteBuffer::ctor(int32_t arg0, int32_t arg1, int32_t arg2, int32_t arg3, int8_tArray* arg4, int32_t arg5)
{ /* stub */
	/* super::ctor(); */
	unimplemented_(u"void ByteBuffer::ctor(int32_t arg0, int32_t arg1, int32_t arg2, int32_t arg3, int8_tArray* arg4, int32_t arg5)");
}

ByteBuffer* ByteBuffer::allocate(int32_t arg0)
{ /* stub */
	clinit();
	unimplemented_(u"ByteBuffer* ByteBuffer::allocate(int32_t arg0)");
	return 0;
}

ByteBuffer* ByteBuffer::allocateDirect(int32_t arg0)
{ /* stub */
	clinit();
	unimplemented_(u"ByteBuffer* ByteBuffer::allocateDirect(int32_t arg0)");
	return 0;
}

int8_tArray* ByteBuffer::array()
{ /* stub */
	unimplemented_(u"int8_tArray* ByteBuffer::array()");
	return 0;
}

int32_t ByteBuffer::arrayOffset()
{ /* stub */
	unimplemented_(u"int32_t ByteBuffer::arrayOffset()");
	return 0;
}

int32_t ByteBuffer::compareTo(ByteBuffer* arg0)
{ /* stub */
	unimplemented_(u"int32_t ByteBuffer::compareTo(ByteBuffer* arg0)");
	return 0;
}

int32_t ByteBuffer::compareTo(Object* o)
{ 
	return compareTo(dynamic_cast< ByteBuffer* >(o));
}

bool ByteBuffer::equals(Object* arg0)
{ /* stub */
	unimplemented_(u"bool ByteBuffer::equals(Object* arg0)");
	return 0;
}

ByteBuffer* ByteBuffer::get(int8_tArray* arg0)
{ /* stub */
	unimplemented_(u"ByteBuffer* ByteBuffer::get(int8_tArray* arg0)");
	return 0;
}

ByteBuffer* ByteBuffer::get(int8_tArray* arg0, int32_t arg1, int32_t arg2)
{ /* stub */
	unimplemented_(u"ByteBuffer* ByteBuffer::get(int8_tArray* arg0, int32_t arg1, int32_t arg2)");
	return 0;
}

bool ByteBuffer::hasArray()
{ /* stub */
	unimplemented_(u"bool ByteBuffer::hasArray()");
	return 0;
}

int32_t ByteBuffer::hashCode()
{ /* stub */
	unimplemented_(u"int32_t ByteBuffer::hashCode()");
	return 0;
}

ByteOrder* ByteBuffer::order()
{ /* stub */
	unimplemented_(u"ByteOrder* ByteBuffer::order()");
	return 0;
}

ByteBuffer* ByteBuffer::order(ByteOrder* arg0)
{ /* stub */
	unimplemented_(u"ByteBuffer* ByteBuffer::order(ByteOrder* arg0)");
	return 0;
}

ByteBuffer* ByteBuffer::put(ByteBuffer* arg0)
{ /* stub */
	unimplemented_(u"ByteBuffer* ByteBuffer::put(ByteBuffer* arg0)");
	return 0;
}

ByteBuffer* ByteBuffer::put(int8_tArray* arg0)
{ /* stub */
	unimplemented_(u"ByteBuffer* ByteBuffer::put(int8_tArray* arg0)");
	return 0;
}

ByteBuffer* ByteBuffer::put(int8_tArray* arg0, int32_t arg1, int32_t arg2)
{ /* stub */
	unimplemented_(u"ByteBuffer* ByteBuffer::put(int8_tArray* arg0, int32_t arg1, int32_t arg2)");
	return 0;
}

String* ByteBuffer::toString()
{ /* stub */
	unimplemented_(u"String* ByteBuffer::toString()");
	return 0;
}

ByteBuffer* ByteBuffer::wrap(int8_tArray* arg0)
{ /* stub */
	clinit();
	unimplemented_(u"ByteBuffer* ByteBuffer::wrap(int8_tArray* arg0)");
	return 0;
}

ByteBuffer* ByteBuffer::wrap(int8_tArray* arg0, int32_t arg1, int32_t arg2)
{ /* stub */
	clinit();
	unimplemented_(u"ByteBuffer* ByteBuffer::wrap(int8_tArray* arg0, int32_t arg1, int32_t arg2)");
	return 0;
}

extern java::lang::Class* class_(const char16_t* c, int n);

java::lang::Class* ByteBuffer::class_()
{
    static ::java::lang::Class* c = ::class_(u"java.nio.ByteBuffer", 19);
    return c;
}

java::lang::Class* ByteBuffer::getClass0()
{
	return class_();
}

