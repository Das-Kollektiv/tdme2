// Generated from /Library/Java/JavaVirtualMachines/1.6.0.jdk/Contents/Classes/classes.jar
#include <java/nio/FloatBuffer.h>

using java::nio::FloatBuffer;
extern void unimplemented_(const char16_t* name);
java::nio::FloatBuffer::FloatBuffer(const ::default_init_tag&)
	: super(*static_cast< ::default_init_tag* >(0))
{
	clinit();
}

java::nio::FloatBuffer::FloatBuffer(int32_t arg0, int32_t arg1, int32_t arg2, int32_t arg3)
	: FloatBuffer(*static_cast< ::default_init_tag* >(0))
{
	ctor(arg0, arg1, arg2, arg3);
}

java::nio::FloatBuffer::FloatBuffer(int32_t arg0, int32_t arg1, int32_t arg2, int32_t arg3, floatArray* arg4, int32_t arg5)
	: FloatBuffer(*static_cast< ::default_init_tag* >(0))
{
	ctor(arg0, arg1, arg2, arg3, arg4, arg5);
}


void FloatBuffer::ctor(int32_t arg0, int32_t arg1, int32_t arg2, int32_t arg3)
{ /* stub */
	/* super::ctor(); */
	unimplemented_(u"void FloatBuffer::ctor(int32_t arg0, int32_t arg1, int32_t arg2, int32_t arg3)");
}

void FloatBuffer::ctor(int32_t arg0, int32_t arg1, int32_t arg2, int32_t arg3, floatArray* arg4, int32_t arg5)
{ /* stub */
	/* super::ctor(); */
	unimplemented_(u"void FloatBuffer::ctor(int32_t arg0, int32_t arg1, int32_t arg2, int32_t arg3, floatArray* arg4, int32_t arg5)");
}

FloatBuffer* FloatBuffer::allocate(int32_t arg0)
{ /* stub */
	clinit();
	unimplemented_(u"FloatBuffer* FloatBuffer::allocate(int32_t arg0)");
	return 0;
}

floatArray* FloatBuffer::array()
{ /* stub */
	unimplemented_(u"floatArray* FloatBuffer::array()");
	return 0;
}

int32_t FloatBuffer::arrayOffset()
{ /* stub */
	unimplemented_(u"int32_t FloatBuffer::arrayOffset()");
	return 0;
}

int32_t FloatBuffer::compareTo(FloatBuffer* arg0)
{ /* stub */
	unimplemented_(u"int32_t FloatBuffer::compareTo(FloatBuffer* arg0)");
	return 0;
}

int32_t FloatBuffer::compareTo(Object* o)
{ 
	return compareTo(dynamic_cast< FloatBuffer* >(o));
}

bool FloatBuffer::equals(Object* arg0)
{ /* stub */
	unimplemented_(u"bool FloatBuffer::equals(Object* arg0)");
	return 0;
}

FloatBuffer* FloatBuffer::get(floatArray* arg0)
{ /* stub */
	unimplemented_(u"FloatBuffer* FloatBuffer::get(floatArray* arg0)");
	return 0;
}

FloatBuffer* FloatBuffer::get(floatArray* arg0, int32_t arg1, int32_t arg2)
{ /* stub */
	unimplemented_(u"FloatBuffer* FloatBuffer::get(floatArray* arg0, int32_t arg1, int32_t arg2)");
	return 0;
}

bool FloatBuffer::hasArray()
{ /* stub */
	unimplemented_(u"bool FloatBuffer::hasArray()");
	return 0;
}

int32_t FloatBuffer::hashCode()
{ /* stub */
	unimplemented_(u"int32_t FloatBuffer::hashCode()");
	return 0;
}

FloatBuffer* FloatBuffer::put(FloatBuffer* arg0)
{ /* stub */
	unimplemented_(u"FloatBuffer* FloatBuffer::put(FloatBuffer* arg0)");
	return 0;
}

FloatBuffer* FloatBuffer::put(floatArray* arg0)
{ /* stub */
	unimplemented_(u"FloatBuffer* FloatBuffer::put(floatArray* arg0)");
	return 0;
}

FloatBuffer* FloatBuffer::put(floatArray* arg0, int32_t arg1, int32_t arg2)
{ /* stub */
	unimplemented_(u"FloatBuffer* FloatBuffer::put(floatArray* arg0, int32_t arg1, int32_t arg2)");
	return 0;
}

String* FloatBuffer::toString()
{ /* stub */
	unimplemented_(u"String* FloatBuffer::toString()");
	return 0;
}

FloatBuffer* FloatBuffer::wrap(floatArray* arg0)
{ /* stub */
	clinit();
	unimplemented_(u"FloatBuffer* FloatBuffer::wrap(floatArray* arg0)");
	return 0;
}

FloatBuffer* FloatBuffer::wrap(floatArray* arg0, int32_t arg1, int32_t arg2)
{ /* stub */
	clinit();
	unimplemented_(u"FloatBuffer* FloatBuffer::wrap(floatArray* arg0, int32_t arg1, int32_t arg2)");
	return 0;
}

extern java::lang::Class* class_(const char16_t* c, int n);

java::lang::Class* FloatBuffer::class_()
{
    static ::java::lang::Class* c = ::class_(u"java.nio.FloatBuffer", 20);
    return c;
}

java::lang::Class* FloatBuffer::getClass0()
{
	return class_();
}

