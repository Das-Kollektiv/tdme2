// Generated from /Library/Java/JavaVirtualMachines/1.6.0.jdk/Contents/Classes/classes.jar
#include <java/nio/ByteBuffer.h>
#include <java/nio/FloatBuffer.h>
#include <java/nio/IntBuffer.h>
#include <java/nio/ShortBuffer.h>

using java::nio::ByteBuffer;
using java::nio::FloatBuffer;
using java::nio::IntBuffer;
using java::nio::ShortBuffer;

extern void unimplemented_(const char16_t* name);

java::nio::ByteBuffer::ByteBuffer(const ::default_init_tag&)
	: super(*static_cast< ::default_init_tag* >(0))
{
	clinit();
}

java::nio::ByteBuffer::ByteBuffer(int32_t arg0)
	: super(*static_cast< ::default_init_tag* >(0))
{
	clinit();
	ctor(arg0);
}

java::nio::ByteBuffer::ByteBuffer(Buffer* arg0)
	: super(*static_cast< ::default_init_tag* >(0))
{
	clinit();
	ctor(arg0);
}

java::nio::ByteBuffer::ByteBuffer(int32_t _capacity, int8_t* data)
	: super(*static_cast< ::default_init_tag* >(0))
{
	clinit();
	ctor(_capacity, data);
}

void ByteBuffer::ctor(int32_t capacity) {
	super::ctor(capacity);
}

void ByteBuffer::ctor(Buffer* buffer) {
	super::ctor(buffer);
}

void ByteBuffer::ctor(int32_t _capacity, int8_t* data) {
	super::ctor(_capacity, data);
}

ByteBuffer* ByteBuffer::allocateDirect(int32_t arg0)
{ /* stub */
	return new ByteBuffer(arg0);
}

FloatBuffer* ByteBuffer::asFloatBuffer() {
	return new FloatBuffer(this);
}

IntBuffer* ByteBuffer::asIntBuffer() {
	return new IntBuffer(this);
}

ShortBuffer* ByteBuffer::asShortBuffer() {
	return new ShortBuffer(this);
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

