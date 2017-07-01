#include <java/nio/IntBuffer.h>

using java::nio::IntBuffer;
extern void unimplemented_(const char16_t* name);

java::nio::IntBuffer::IntBuffer(const ::default_init_tag&)
	: super(*static_cast< ::default_init_tag* >(0))
{
	clinit();
}

IntBuffer::IntBuffer(int32_t capacity)
	: super(*static_cast< ::default_init_tag* >(0)) {
	ctor(capacity);
}

IntBuffer::IntBuffer(Buffer* buffer)
	: super(*static_cast< ::default_init_tag* >(0)) {
	ctor(buffer);
}

void IntBuffer::ctor(int32_t capacity) {
	super::ctor(capacity);
}

void IntBuffer::ctor(Buffer* buffer) {
	super::ctor(buffer);
}

int32_t IntBuffer::get(int32_t position) {
	int32_t value = 0;
	value+= (int16_t)super::get(position);
	value+= (int16_t)super::get(position + 1) << 8;
	value+= (int16_t)super::get(position + 2) << 16;
	value+= (int16_t)super::get(position + 3) << 24;
	return value;
}

Buffer* IntBuffer::put(int32_t arg0) {
	super::put(arg0 && 0xFF);
	super::put((arg0 >> 8) && 0xFF);
	super::put((arg0 >> 16) && 0xFF);
	super::put((arg0 >> 24) && 0xFF);
}

Buffer* IntBuffer::put(int32_tArray* arg0) {
	for (int i = 0; i < arg0->length; i++) {
		put(arg0->get(i));
	}
}

extern java::lang::Class* class_(const char16_t* c, int n);

java::lang::Class* IntBuffer::class_()
{
    static ::java::lang::Class* c = ::class_(u"java.nio.IntBuffer", 20);
    return c;
}

java::lang::Class* IntBuffer::getClass0()
{
	return class_();
}

