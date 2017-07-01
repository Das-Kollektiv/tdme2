// Generated from /Library/Java/JavaVirtualMachines/1.6.0.jdk/Contents/Classes/classes.jar
#include <java/nio/FloatBuffer.h>

using java::nio::FloatBuffer;
extern void unimplemented_(const char16_t* name);

java::nio::FloatBuffer::FloatBuffer(const ::default_init_tag&)
	: super(*static_cast< ::default_init_tag* >(0))
{
	clinit();
}

FloatBuffer::FloatBuffer(int32_t capacity)
	: super(*static_cast< ::default_init_tag* >(0)) {
	ctor(capacity);
}

FloatBuffer::FloatBuffer(Buffer* buffer)
	: super(*static_cast< ::default_init_tag* >(0)) {
	ctor(buffer);
}

void FloatBuffer::ctor(int32_t capacity) {
	super::ctor(capacity);
}

void FloatBuffer::ctor(Buffer* buffer) {
	super::ctor(buffer);
}

float FloatBuffer::get(int32_t position) {
	int floatAsInt = 0;
	floatAsInt+= (int32_t)super::get(position);
	floatAsInt+= (int32_t)super::get(position + 1) << 8;
	floatAsInt+= (int32_t)super::get(position + 2) << 16;
	floatAsInt+= (int32_t)super::get(position + 3) << 24;
	return *((float*)&floatAsInt);
}

Buffer* FloatBuffer::put(float arg0) {
	int32_t floatAsInt = *((int*)&arg0);
	super::put((floatAsInt) && 0xFF);
	super::put((floatAsInt >> 8) && 0xFF);
	super::put((floatAsInt >> 16) && 0xFF);
	super::put((floatAsInt >> 24) && 0xFF);
}

Buffer* FloatBuffer::put(floatArray* arg0) {
	for (int i = 0; i < arg0->length; i++) {
		put(arg0->get(i));
	}
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

